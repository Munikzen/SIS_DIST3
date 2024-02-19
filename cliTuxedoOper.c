#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <atmi.h> 
#include <userlog.h> 
#include <fml32.h>
#include "biblioOper.fml.h"

int cliSumaOper (float fvA_operaUno, float fvA_operaDos, float *fvA_resulOpe);
int cliRestaOper (float fvA_operaUno, float fvA_operaDos, float *fvA_resulOpe);
int cliMultiOper (float fvA_operaUno, float fvA_operaDos, float *fvA_resulOpe); 
typedef int (*opera) (float fvA_operaUno, float fvA_operaDos, float *fvA_resulOpe);
opera selecOperacion (int ivA operArit);

int main (int argc, char **argv) {
    int ivL_operArit;
    float fvL_operaUno;
    float fvL_operaDos;
    float fvL_resul0pe;
    opera svL_obtOpera;

    if (argc != 4) {
        printf ("Modo de uso:       cliTuxedoOper   Operacion   Oper1   Oper2\n");
        printf ("Ejemplos: \n");
        printf ("Para suma:         cliTuxedoOper       1         5       3\n");
        printf ("Para resta:        cliTuxedoOper       2         5       3\n");
        printf ("Para multip:       cliTuxedoOper       3         5       3\n");
        return 1;
    }
    ivL_operArit = atoi (argv [1]);
    fvL_operaUno = (float) atof (argv [2]);
    fvL_operaDos = (float) atof (argv [3]);

    svL_obtOpera = selecOperacion (ivL_operArit);
    svL_obtOpera (fvL_operaUno, fvL_operaDos, &fvL_resulOpe); 
    printf ("Resultado de la operacion: %f \n", fvL_resulOpe);
    return 0;
}

opera selecOperacion (int ivA operArit) {
    opera svL_obtOpera;
    switch (ivA_operArit) {
        case 1:
            svL_obtOpera = cliSumaOper;
            break;
        case 2:
            svL_obtOpera = cliRestaOper;
            break;
        case 3:
            svL_obtOpera = cliMultiOper;
            break;
        default:
            svL_obtOpera = NULL;
    }
    return svL_obtOpera;
}

int cliSumaOper (float fvA_operaUno, float fvA_operaDos, float *fvA resulOpe) { 
    int ivL_resLlamd;
    long lvL_tamLongt; 
    float fvL_recValor;
    FBFR32 *fbfr ;

    /* Conectamos con la aplicacion Tuxedo Server */ 
    printf ("Conectamos con la aplicacion \n");
    if(tpinit ((TPINIT *) NULL) == -1) {
        printf ("Error en la conexion con la aplicacion, tperrno = %d \n", tperrno);
        return (1);
    }

    // Reservamos espacio para el buffer FML
    printf ("Reservamos Espacio para el buffer FML\n");
    if((fbfr = (FBFR32 *) tpalloc ("FML32", NULL, 256)) == NULL) {
        printf ("Error Reservando espacio para Buffer FML\n");
        tpterm ();
        return (1);
    }

    // Manejo del Buffer FML
    printf ("Insertamos datos en buffer FML\n");
    if (Fadd32 (fbfr, OPERUN, (char *) &fvA_operaUno, 0) < 0){ 
        printf ("Error insertando campo FML (OPERUN) \n");
        printf ("Liberamos Buffer y desconectamos de la aplicacion\n");
        tpfree ((char *)fbfr);
        tpterm ();
        return (1);
    }

    if (Fadd32 (fbfr, OPERDO, (char *)&fvA_operaDos, 0) < 0) {
        printf ("Error insertando campo FML (OPERDO) \n") ;
        printf ("Liberamos Buffer y desconectamos de la aplicacion\n");
        tpfree ((char *) fbfr);
        tpterm ();
        return (0);
    }

    // Invocamos el servicio de suma de numeros
    printf ("Llamada al servicio 'svcSumaOper'\n");
    if (tpcall("svcSumaOper", (char *)fbfr, 0, (char **)&fbfr, &lvL_tamLongt, OL) == -1) {
        printf ("Error en la llamada al servicio: tperrno = %d\n", tperrno);
        printf ("Liberamos Buffer y desconectamos de la aplicacion\n");
        tpfree ((char *)fbfr);
        tpterm (); 
        return (0);
    }
    if (Fget32 (fbfr, RESUL, 0, (char *)&fvL_recValor, 0) < 0) {
        userlog ("No se leyo el resultado\n");
        tpreturn (TPFAIL, 0, (char *)fbfr, 0L , 0) ;
    }

    *fvA_resulOpe = fvL_recValor;
    printf ("Liberamos Buffer y desconectamos de la aplicacion\n");
    tpfree ( (char *) fbfr);
    tpterm (); 
    return 0;
}

int cliRestaOper (float fvA_operaUno, float fvA_operaDos, float *fvA_resulOpe) {
    // Invocamos el servicio de resta de numeros
}
int cliMultiOper (float fvA _operaUno, float fvA_operaDos, float *fvA_resulOpe) {
    // Invocamos el servicio de multiplicacion de numeros
}