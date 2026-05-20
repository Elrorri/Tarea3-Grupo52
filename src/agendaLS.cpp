#include "../include/agendaLS.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 2 //////
///////////////////////////////////

struct rep_agendaLS {
    TEvento evento;
    rep_agendaLS * sig;
};

TAgendaLS crearAgendaLS() {
    TAgendaLS agenda = NULL;
    return agenda;
}

void agregarEnAgendaLS(TAgendaLS &agenda, TEvento evento) {
    if (agenda == NULL || compararTFechas(fechaTEvento(agenda->evento),fechaTEvento(evento))!=-1){
        TAgendaLS nuevo = new rep_agendaLS;
        nuevo->evento = evento;
        nuevo->sig = agenda;
        agenda = nuevo;
    }
    else{
        agregarEnAgendaLS(agenda->sig,evento);
    }
}


void imprimirAgendaLS(TAgendaLS agenda) {
    while (agenda != NULL){
        imprimirTEvento(agenda->evento);
        agenda = agenda->sig;
    }
    
}

void liberarAgendaLS(TAgendaLS &agenda) {
    TAgendaLS aux;
    while (agenda != NULL){
        liberarTEvento(agenda->evento);
        aux = agenda;
        agenda = agenda->sig;
        delete aux;
    }
    agenda = NULL;
}

bool esVaciaAgendaLS(TAgendaLS agenda){
    return (agenda == NULL);
}

TAgendaLS copiarAgendaLS(TAgendaLS agenda){
    TAgendaLS copia,copia2;
    copia2 = new rep_agendaLS;
    copia2->sig = NULL;
    copia = copia2;
    while(agenda != NULL){
        copia->sig = new rep_agendaLS;
        copia = copia->sig;
        copia->evento = copiarTEvento(agenda->evento);
        copia->sig = NULL;
        agenda = agenda->sig;
    }
    copia = copia2->sig;
    delete copia2;
    return copia;
}

bool estaEnAgendaLS(TAgendaLS agenda, int id) {
    bool esta = false;
    while ((!esta)&&(agenda != NULL)&&(idTEvento(agenda->evento)!=id)){
        agenda = agenda->sig;
    }
    if (agenda !=NULL){
        esta = true;
    }
    return esta;
}

TEvento obtenerDeAgendaLS(TAgendaLS agenda, int id) {
    while ((agenda != NULL)&&(idTEvento(agenda->evento)!= id)){
        agenda = agenda->sig;        
    }
    TEvento res;
    res = agenda->evento;
    return res;
}



void posponerEnAgendaLS(TAgendaLS &agenda, int id, nat n) {
    TAgendaLS aux, aux2, previo;
    
    aux = agenda;
    previo = NULL;

    while ((aux != NULL)&&(idTEvento(aux->evento) != id)){
        previo = aux;
        aux = aux->sig;
    }
    posponerTEvento(aux->evento,n);

    if(previo == NULL){
        agenda = agenda->sig;
    }else{
        previo->sig = aux->sig;
        aux->sig = NULL;
    }

    aux2 = aux;
    aux = agenda;
    previo = NULL;

    while (aux != NULL && compararTFechas(fechaTEvento(aux2->evento),fechaTEvento(aux->evento))==1){
        previo = aux;
        aux = aux->sig;
    }
    if (previo == NULL){
        aux2->sig=agenda;
        agenda = aux2;    
    }else{
        aux2->sig = aux;
        previo->sig = aux2;
    }
    
}

void imprimirEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    while (agenda != NULL && compararTFechas(fecha,fechaTEvento(agenda->evento))!=-1){
        if (compararTFechas(fecha,fechaTEvento(agenda->evento)) == 0){
            imprimirTEvento(agenda->evento);
        }
        agenda = agenda->sig;
    }
    
}

bool hayEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    bool res = false;
    while (agenda != NULL && compararTFechas(fecha,fechaTEvento(agenda->evento))!=-1){
        if (compararTFechas(fecha,fechaTEvento(agenda->evento)) == 0){
            res = true;
        }
        agenda = agenda->sig;
    }
    return res;
}

void removerDeAgendaLS(TAgendaLS &agenda, int id) {
    TAgendaLS aux;
    if(idTEvento(agenda->evento) == id){
        liberarTEvento(agenda->evento);
        aux = agenda;
        agenda = agenda->sig;
        delete aux;
    }else{
        removerDeAgendaLS(agenda->sig,id);   
    }
}

///////////////////////////////////
////// FIN CÓDIGO TAREA 2 //////
///////////////////////////////////