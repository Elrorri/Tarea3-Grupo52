#include "../include/pilaPersona.h"
#include "../include/personasLDE.h"

struct rep_pilaPersona {
  TPersonasLDE pPersonas;
};

TPilaPersona crearTPilaPersona() {
  TPilaPersona nuevo = new rep_pilaPersona;
  nuevo->pPersonas = crearTPersonasLDE();
  return nuevo;
}

void liberarTPilaPersona(TPilaPersona &p) {
  liberarTPersonasLDE(p->pPersonas);
  delete p;
  p=NULL;
  }

nat cantidadEnTPilaPersona(TPilaPersona p) { 
  return cantidadTPersonasLDE(p->pPersonas);
}

void apilarEnTPilaPersona(TPilaPersona &p, TPersona persona) {
   insertarInicioDeTPersonasLDE(p->pPersonas,copiarTPersona(persona)); 
}

TPersona cimaDeTPilaPersona(TPilaPersona p) { 
  return obtenerInicioDeTPersonasLDE(p->pPersonas);
}

void desapilarDeTPilaPersona(TPilaPersona &p) {
  eliminarInicioTPersonasLDE(p->pPersonas);
}
