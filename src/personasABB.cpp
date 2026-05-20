#include "../include/personasABB.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 2 //////
///////////////////////////////////

struct rep_personasAbb {
    TPersona persona;
    TPersonasABB izq,der;
};

TPersonasABB crearTPersonasABB() {
    TPersonasABB nuevo;
    nuevo = NULL;
    return nuevo;
}

bool esVacioTPersonasABB(TPersonasABB personasABB) {
    return (personasABB == NULL);
}

void insertarTPersonasABB(TPersonasABB &personasABB, TPersona p) {
    if (personasABB == NULL){
        TPersonasABB nuevo;
        nuevo = new rep_personasAbb;
        nuevo->persona = p;
        nuevo->izq = nuevo->der = NULL;
        personasABB = nuevo;
    }else if (idTPersona(p) > idTPersona(personasABB->persona)){
        insertarTPersonasABB(personasABB->der,p);
    }else if (idTPersona(p) < idTPersona(personasABB->persona)){
        insertarTPersonasABB(personasABB->izq,p);
    }
    
}

void liberarTPersonasABB(TPersonasABB &personasABB) {
    if(personasABB != NULL){
        liberarTPersonasABB(personasABB->der);
        liberarTPersonasABB(personasABB->izq);

        liberarTPersona(personasABB->persona);
        delete personasABB;
        personasABB = NULL;
    }
}

void imprimirTPersonasABB(TPersonasABB personasABB) {
    if (personasABB != NULL){
        imprimirTPersonasABB(personasABB->izq);

        imprimirTPersona(personasABB->persona);

        imprimirTPersonasABB(personasABB->der);
    }
   
}

nat cantidadTPersonasABB(TPersonasABB personasABB) {
    nat cant = 0;
    if (personasABB != NULL){
        cant = 1 + cantidadTPersonasABB(personasABB->der) + cantidadTPersonasABB(personasABB->izq);
    }
    return cant;
}

TPersona maxIdPersona(TPersonasABB personasABB) {
    if(personasABB == NULL){
        return NULL;
    }
    if (personasABB->der == NULL){
        return personasABB->persona;
    }
    return maxIdPersona(personasABB->der);
}

void removerTPersonasABB(TPersonasABB &personasABB, nat id) {
    if(idTPersona(personasABB->persona)==id){ //encuentro persona a sacar
        
        //liberarTPersona(personasABB->persona);
        //personasABB->persona = NULL;
        
        if (personasABB->izq == NULL && personasABB->der == NULL){
            liberarTPersona(personasABB->persona);
            personasABB->persona = NULL;

            delete personasABB;
            personasABB = NULL;

        }else if (personasABB->izq == NULL && personasABB->der != NULL){
            liberarTPersona(personasABB->persona);
            personasABB->persona = NULL;

            TPersonasABB ptr = personasABB;
            personasABB = personasABB->der;
            ptr->der = NULL;
            delete ptr;
            ptr = NULL;
        }else if(personasABB->izq != NULL && personasABB->der == NULL){
            liberarTPersona(personasABB->persona);
            personasABB->persona = NULL;

            TPersonasABB ptr = personasABB;
            personasABB = personasABB->izq;
            ptr->izq = NULL;
            delete ptr;
            ptr = NULL;
        }else{
            TPersonasABB ptr = personasABB->izq;

            while (ptr->der != NULL){
                ptr = ptr->der;
            }
            liberarTPersona(personasABB->persona);
            personasABB->persona = copiarTPersona(ptr->persona);
            removerTPersonasABB(personasABB->izq,idTPersona(ptr->persona));
        }
    }else{ //busco la persona
        if(id > idTPersona(personasABB->persona))
            removerTPersonasABB(personasABB->der,id);
        else
            removerTPersonasABB(personasABB->izq,id);
    }
    
}

bool estaTPersonasABB(TPersonasABB personasABB, nat id) {
    bool res = false;
    if (personasABB != NULL){ //apunto a algo
        if(idTPersona(personasABB->persona)==id){//encontre la persona
            res = true;
        }else{ //la tengo q buscar
            res = estaTPersonasABB(personasABB->izq,id) || estaTPersonasABB(personasABB->der,id);
        }
    }
    return res;
}

TPersona obtenerDeTPersonasABB(TPersonasABB personasABB, nat id) {
    TPersona res = NULL;
    if (personasABB != NULL){
        if(idTPersona(personasABB->persona)== id){
            res = personasABB->persona;
        }else{
            if(id > idTPersona(personasABB->persona)){
                res = obtenerDeTPersonasABB(personasABB->der,id);
            } else{
                res = obtenerDeTPersonasABB(personasABB->izq,id);
            }
        }
    }
    return res;
}

nat maax(nat i, nat j){
    nat res;
    if (i > j){
        res = i;
    }else{
        res = j;
    }
    return res;
}

nat alturaTPersonasABB(TPersonasABB personasABB) {
    nat alt = 0;
    if (personasABB != NULL){
        alt = 1 + maax(alturaTPersonasABB(personasABB->izq),alturaTPersonasABB(personasABB->der));
    }else{
        alt = 0;
    }
    return alt;
}

nat perfecto(TPersonasABB arbol,bool &resultado){
    if (arbol == NULL) return 0;
    nat i = perfecto(arbol->izq,resultado);
    nat d = perfecto(arbol->der,resultado);

    if (i!=d) resultado = false;

    return 1 + maax(i,d);
}

bool esPerfectoTPersonasABB(TPersonasABB personasABB) {
    bool resultado = true;
    perfecto(personasABB,resultado);
    return resultado;
}

TPersonasABB mayoresTPersonasABB(TPersonasABB personasABB, nat edad) {
    TPersonasABB res;
    if (personasABB == NULL){
        res = NULL;
    }
    else{
        TPersonasABB aizq = mayoresTPersonasABB(personasABB->izq,edad);
        TPersonasABB ader = mayoresTPersonasABB(personasABB->der,edad);

        if (edadTPersona(personasABB->persona) > edad){
            res = new rep_personasAbb;
            res->persona = copiarTPersona(personasABB->persona);
            res->izq = aizq;
            res->der = ader;
        }else if(aizq == NULL)
            res = ader;
        else if (ader == NULL)
            res = aizq;
        else{
            res = new rep_personasAbb;
            TPersona mayor = maxIdPersona(aizq);
            res->persona = copiarTPersona(mayor);
            removerTPersonasABB(aizq,idTPersona(mayor));
            res->izq = aizq;
            res->der = ader;
        }        
    }
    return res;
}

void insert(TPersonasABB personasABB,TPersonasLDE & res){
    if(personasABB != NULL){
        insert(personasABB->der,res);
        insertarTPersonasLDE(res,copiarTPersona(personasABB->persona),1);
        insert(personasABB->izq,res);
    }
}


TPersonasLDE aTPersonasLDE(TPersonasABB personasABB) {
    TPersonasLDE result;
    result = crearTPersonasLDE();
    if(personasABB != NULL){
        insert(personasABB,result);
    }
    return result;
}
///////////////////////////////////
////// FIN CÓDIGO TAREA 2 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

nat amplitudTPersonasABB(TPersonasABB personasABB) {
    return 0;
}

TPilaPersona serializarTPersonasABB(TPersonasABB personasABB) {
    return NULL;
}

TPersonasABB deserializarTPersonasABB(TPilaPersona &pilaPersonas) {
    return NULL;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

