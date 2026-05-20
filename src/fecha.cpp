#include "../include/fecha.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 2 //////
///////////////////////////////////


///////////////////////////////////
////// PEGAR CÓDIGO TAREA 1 //////
///////////////////////////////////

struct rep_fecha {
    nat dia,mes,anio;
};

TFecha crearTFecha(nat dia, nat mes, nat anio) {
    TFecha nuevaFecha = NULL;
    nuevaFecha = new rep_fecha;
    nuevaFecha->dia = dia;
    nuevaFecha->mes = mes;
    nuevaFecha->anio = anio;
    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha) {
    delete fecha;
    fecha = NULL;
}

void imprimirTFecha(TFecha fecha) {
    printf("%d/%d/%d\n",fecha->dia,fecha->mes,fecha->anio);
}

nat diasMes(nat mes, nat anio){
    int d;
    switch (mes){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            d = 31;
            break;
        case 4: case 6: case 9: case 11:
            d = 30;
            break;
        case 2:
            if((anio % 4) == 0){
                d = 29;
                break;
            }
            else {
                d = 28;
                break;
            }
    }
    return d;
}

void aumentarTFecha(TFecha &fecha, nat dias) {
    fecha->dia += dias;
    while (fecha->dia > diasMes(fecha->mes, fecha->anio)) {
        fecha->dia -= diasMes(fecha->mes, fecha->anio);
        fecha->mes++;
        if (fecha->mes > 12) {
            fecha->mes = 1;
            fecha->anio++;
        }
    }
}

int fechaNum(TFecha fecha){
    return fecha->anio * 10000 + fecha->mes * 100 + fecha->dia;
}

int compararTFechas(TFecha fecha1, TFecha fecha2) {
    int res = 0;
    if (fechaNum(fecha1) > fechaNum(fecha2)){
        res = 1;
    }
    else if (fechaNum(fecha1) < fechaNum(fecha2)) {
        res = -1;
    }
    return res;
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 1 //////
/////////////////////////////////

/*-----------------------------*/

///////////////////////////
////// FUNCION NUEVA //////
///////////////////////////

// Retorna una copia de la fecha
TFecha copiarTFecha(TFecha fecha) {
    return crearTFecha(fecha->dia,fecha->mes,fecha->anio);
    //return NULL;
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 2 //////
/////////////////////////////////
