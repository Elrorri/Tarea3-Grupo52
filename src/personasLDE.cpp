#include "../include/personasLDE.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 2 //////
///////////////////////////////////
struct listaDoblePersonas{
    TPersona persona;
    listaDoblePersonas* ant;
    listaDoblePersonas* sig;
};

struct rep_personasLDE {
    listaDoblePersonas* inicio;
    listaDoblePersonas* fin;
    nat cant;
};

typedef listaDoblePersonas* listaDpersonas;

TPersonasLDE crearTPersonasLDE(){
    TPersonasLDE nuevo;
    nuevo = new rep_personasLDE;
    nuevo->inicio = NULL;
    nuevo->fin = NULL;
    nuevo->cant = 0;
    return nuevo;
}

void insertarTPersonasLDE(TPersonasLDE &personas, TPersona persona, nat pos){
    listaDpersonas nuevo,aux;
    nuevo = new listaDoblePersonas;
    nuevo->persona = persona;
    personas->cant ++;

    if(pos == 1){
        nuevo->sig = personas->inicio;
        if(personas->inicio != NULL){
            personas->inicio->ant = nuevo;
        }
        nuevo->ant = NULL;
        personas->inicio = nuevo;
        if (personas->fin == NULL){
            personas->fin = nuevo;
        }
    }else{
        nat cont = 1;
        aux = personas->inicio;
        while( (aux != NULL) && (cont<pos)){
            cont++;
            aux = aux->sig;
        }
        if (aux == NULL){
            nuevo->sig = NULL;
            nuevo->ant = personas->fin;

            if (personas->fin == NULL){
                personas->inicio = nuevo;
            }else{
                personas->fin->sig = nuevo;
            }
            personas->fin = nuevo;

        }else{
            nuevo->sig = aux;
            nuevo->ant = aux->ant;
            if (aux->ant != NULL){
                aux->ant->sig = nuevo;
            }else{
                personas->inicio = nuevo;
            }
            aux->ant = nuevo;
            aux = NULL;
        }
    }
    nuevo = NULL;
}

void liberarTPersonasLDE(TPersonasLDE &personasLDE){
    listaDpersonas aux;
    aux = personasLDE->inicio;

    while(aux != NULL){
        personasLDE->inicio = aux->sig;

        liberarTPersona(aux->persona);
        delete aux;
        
        aux = personasLDE->inicio;
    }
    personasLDE->fin = NULL;
    personasLDE->cant = 0;
    delete personasLDE;
    personasLDE = NULL;
}

void imprimirTPersonasLDE(TPersonasLDE personas){
    listaDpersonas aux = personas->inicio;
    while(aux != NULL){
        imprimirTPersona(aux->persona);
        aux = aux->sig;
    }
}

nat cantidadTPersonasLDE(TPersonasLDE personas){
    return (personas->cant);
}

void eliminarInicioTPersonasLDE(TPersonasLDE &personas){
    listaDpersonas aux;
    aux = personas->inicio;
    if (aux != NULL){
        personas->cant --;
        personas->inicio = aux->sig;
        if(aux->sig != NULL){
            aux->sig->ant = NULL;
        }else{
            personas->fin = NULL;
        }
        liberarTPersona(aux->persona);
        delete aux;
    }
    aux = NULL;
}

void eliminarFinalTPersonasLDE(TPersonasLDE &personas){
    listaDpersonas aux;
    aux = personas->fin;
    if (aux != NULL){
        personas->cant --;
        personas->fin = aux->ant;
        if (aux->ant != NULL){
            aux->ant->sig = NULL;
        }else{
            personas->inicio = NULL;
        }
        aux->ant = NULL;
        liberarTPersona(aux->persona);
        delete aux;
    }
}

bool estaEnTPersonasLDE(TPersonasLDE personas, nat id){
    listaDpersonas aux = personas->inicio;

    while (aux != NULL && (idTPersona(aux->persona)!=id)){
    aux = aux->sig;
    }
    return (aux!=NULL);
}

TPersona obtenerDeTPersonasLDE(TPersonasLDE personas, nat id){
    listaDpersonas aux = personas->inicio;
    while(aux != NULL && (idTPersona(aux->persona)!=id)){
        aux = aux->sig;
    }
    return aux->persona;
}

TPersonasLDE concatenarTPersonasLDE(TPersonasLDE personas1, TPersonasLDE personas2){
    TPersonasLDE nuevo = crearTPersonasLDE();
    
    if((personas1->fin != NULL)&&(personas2->inicio != NULL)){
        personas1->fin->sig = personas2->inicio;
        personas2->inicio->ant = personas1->fin;

        nuevo->inicio = personas1->inicio;
        nuevo->fin = personas2->fin;

    }else if(personas1->inicio == NULL){
        nuevo->inicio = personas2->inicio;
        nuevo->fin = personas2->fin;
    }else{
        nuevo->inicio = personas1->inicio;
        nuevo->fin = personas1->fin;
    }
    nuevo->cant = personas1->cant + personas2->cant;
    personas1->inicio = personas2->inicio = NULL;
    personas1->fin = personas2->fin = NULL;
    delete personas1;
    delete personas2;

    return nuevo;
}


///////////////////////////////////
////// FIN CÓDIGO TAREA 2 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void insertarInicioDeTPersonasLDE(TPersonasLDE &personas, TPersona persona){
    insertarTPersonasLDE(personas,persona,1);
}

void insertarFinalDeTPersonasLDE(TPersonasLDE &personas, TPersona persona){    
    insertarTPersonasLDE(personas,persona,personas->cant+1);
}

TPersona obtenerInicioDeTPersonasLDE(TPersonasLDE personas){
    return personas->inicio->persona;
}

TPersona obtenerFinalDeTPersonasLDE(TPersonasLDE personas){
    return personas->fin->persona;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

