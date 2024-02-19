#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <atmi.h>
#include <userlog.h>
#include <fm132.h>
#include "biblioOper.fml.h"

tpsvrinit (int argc, char *argv []) {
    userlog ("Iniciando srvTuxedoOper");
    return (0);
}

/* Servicio para obtener datos de Operacion Suma */
void svcSumaOper (TPSVCINFO *rqst){
    float fvL_operaUno;
    float fvL_operaDos;
    float fvL_resulOpe;
    FBFR32* fbfr = (FBFR32*) rqst -> data;

    userlog ("Servicio svcSumaOper Invocado.");

    //Obtenemos los campos FML del buffer de entrada
    if (Fget32 (fbfr, OPERUN, 0, (char *)&fvL_operaUno, 0) < 0) {
        userlog ("No se leyo el primer operador");
        tpreturn (TPFAIL, 0, (char *)fbfr, 0L , 0);
    }
    if (Fget32 (fbfr, OPERDO, 0, (char *)&fvL_operaDos, 0) < 0) {
        userlog ("No se leyo el segundo operador");
        tpreturn (TPFAIL, 0, (char *)fbfr, 0L , 0) ;
    }

    userlog ("Operador uno: [%f]", fvL_operaUno);
    userlog ("Operador dos: [%f]", fvL_operaDos);

    //Realiza la operacion suma
    fvL_resulOpe = fvL_operaUno + fvL_operaDos;
    Fadd32 (fbfr, RESUL, (char *)&fvL_resulOpe, 0);
    userlog ("Resultado de la suma es: [%f]", fvL_resulOpe);
    tpreturn (TPSUCCESS, 0, rqst -> data, 0L, 0);
}

void svcRestaOper (TPSVCINFO *rqst){
    float fvL_operaUno;
    float fvL_operaDos;
    float fvL_resulOpe;
    FBFR32* fbfr = (FBFR32*) rqst -> data;

    userlog ("Servicio svcRestaOper Invocado.");

    //Obtenemos los campos FML del buffer de entrada
    if (Fget32 (fbfr, OPERUN, 0, (char *)&fvL_operaUno, 0) < 0) {
        userlog ("No se leyo el primer operador");
        tpreturn (TPFAIL, 0, (char *)fbfr, 0L , 0);
    }
    if (Fget32 (fbfr, OPERDO, 0, (char *)&fvL_operaDos, 0) < 0) {
        userlog ("No se leyo el segundo operador");
        tpreturn (TPFAIL, 0, (char *)fbfr, 0L , 0) ;
    }

    userlog ("Operador uno: [%f]", fvL_operaUno);
    userlog ("Operador dos: [%f]", fvL_operaDos);

    //Realiza la operacion resta
    fvL_resulOpe = fvL_operaUno - fvL_operaDos;
    Fadd32 (fbfr, RESUL, (char *)&fvL_resulOpe, 0);
    userlog ("Resultado de la suma es: [%f]", fvL_resulOpe);
    tpreturn (TPSUCCESS, 0, rqst -> data, 0L, 0);
}

void svcMultiOper (TPSVCINFO *rqst){
    float fvL_operaUno;
    float fvL_operaDos;
    float fvL_resulOpe;
    FBFR32* fbfr = (FBFR32*) rqst -> data;

    userlog ("Servicio svcRestaOper Invocado.");

    //Obtenemos los campos FML del buffer de entrada
    if (Fget32 (fbfr, OPERUN, 0, (char *)&fvL_operaUno, 0) < 0) {
        userlog ("No se leyo el primer operador");
        tpreturn (TPFAIL, 0, (char *)fbfr, 0L , 0);
    }
    if (Fget32 (fbfr, OPERDO, 0, (char *)&fvL_operaDos, 0) < 0) {
        userlog ("No se leyo el segundo operador");
        tpreturn (TPFAIL, 0, (char *)fbfr, 0L , 0) ;
    }

    userlog ("Operador uno: [%f]", fvL_operaUno);
    userlog ("Operador dos: [%f]", fvL_operaDos);

    //Realiza la operacion multiplicacion
    fvL_resulOpe = fvL_operaUno * fvL_operaDos;
    Fadd32 (fbfr, RESUL, (char *)&fvL_resulOpe, 0);
    userlog ("Resultado de la suma es: [%f]", fvL_resulOpe);
    tpreturn (TPSUCCESS, 0, rqst -> data, 0L, 0);
}
