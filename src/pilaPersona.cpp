#include "../include/pilaPersona.h"
#include "../include/personasLDE.h"

struct rep_pilaPersona {
  TPersona persona;
  rep_pilaPersona* abj;
};

TPilaPersona crearTPilaPersona() {
  return NULL;
}

void liberarTPilaPersona(TPilaPersona &p) {
  if (p==NULL) return;
  liberarTPersona(p->persona);
  liberarTPilaPersona(p->abj);
  delete p;
  p = NULL;
}

nat cantidadEnTPilaPersona(TPilaPersona p) { 
  if (p==NULL)return 0; 
  return cantidadEnTPilaPersona(p->abj)+1;
}

void apilarEnTPilaPersona(TPilaPersona &p, TPersona persona) {
    TPilaPersona top = new rep_pilaPersona;
    top->persona=persona;
    top->abj=p;
    p=top;
}

TPersona cimaDeTPilaPersona(TPilaPersona p) { 
  return p->persona;
}

void desapilarDeTPilaPersona(TPilaPersona &p) {
  TPilaPersona nodo;
  nodo = p;
  p=p->abj;
  liberarTPersona(nodo->persona);
  delete nodo;
  nodo = NULL;
}
