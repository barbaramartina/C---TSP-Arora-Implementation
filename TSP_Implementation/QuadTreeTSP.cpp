//---------------------------------------------------------------------------

//
//  Licensed to the Apache Software Foundation (ASF) under one
//  or more contributor license agreements.  See the NOTICE file
//  distributed with this work for additional information
//  regarding copyright ownership.  The ASF licenses this file
//  to you under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance
//  with the License.  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing,
//  software distributed under the License is distributed on an
//  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
//  KIND, either express or implied.  See the License for the
//  specific language governing permissions and limitations
//  under the License.
//


#pragma hdrstop

#include  <iostream.h>
#include "QuadTreeTSP.h"


//---------------------------------------------------------------------------
QuadTreeTSP::QuadTreeTSP(unsigned int dim,unsigned int ancho,unsigned int alto,int cte):QuadTree(dim){
 cantCuadrantes=0;
 cantHojas=0;
 this->alto=alto;
 this->ancho=ancho;
 maxCuadrante=0;
 dimComprimida=0;

 unsigned int profundidad = this->getProfundidad();
 indicesLevel = new unsigned int[profundidad+1];
 indicesLevel[0] = 0;
 for (unsigned int l = 1; l <= profundidad; l++){
        indicesLevel[l] = Power(4,l-1)  + indicesLevel[l-1] ;
 }
}
//---------------------------------------------------------------------------
QuadTreeTSP :: ~QuadTreeTSP(){
    for (unsigned int i=0; i<dimComprimida; i++)
        if (quadtr[i]!=NULL){
          delete(quadtr[i]);
          quadtr[i] = NULL;

        };

    if (quadtr!=NULL){
      delete(quadtr);
      quadtr = NULL;
    };

}
//---------------------------------------------------------------------------
Cuadrante *QuadTreeTSP::getHijo(unsigned int padre,unsigned int nHijo){ return quadtr[4*padre+nHijo]; }
//---------------------------------------------------------------------------
unsigned int QuadTreeTSP:: getPadre(unsigned int x){  return Floor((x-1)/4); }
//---------------------------------------------------------------------------
unsigned int QuadTreeTSP:: getNumeroDeHijo(unsigned int h){ return ( (h-1)%4) + 1; }
//---------------------------------------------------------------------------
unsigned int QuadTreeTSP:: getCantCuadrantes(){ return cantCuadrantes; }
//---------------------------------------------------------------------------
unsigned int QuadTreeTSP::getAnchoLevel(unsigned int level){ return this->ancho/Power(2,level);}
//---------------------------------------------------------------------------
Cuadrante **QuadTreeTSP:: getArreglo(){ return this->quadtr; }
//---------------------------------------------------------------------------
unsigned int QuadTreeTSP:: getAncho(){ return this->ancho; }
//---------------------------------------------------------------------------
unsigned int QuadTreeTSP:: getProfundidad(){ return Log2(ancho);}
//---------------------------------------------------------------------------
unsigned int QuadTreeTSP:: getDimComprimida(){return dimComprimida;};
//---------------------------------------------------------------------------
//Devuelve si una posicion del Quadtree es "nodo" u "hoja"
bool QuadTreeTSP::esPadre(unsigned int pos){
    if (this->quadtr[pos]!=NULL)
     return quadtr[pos]->hijos();

    return false;
}
//---------------------------------------------------------------------------
//en base a una instancia de Perturbacion genera un QuadTreeTSP
void QuadTreeTSP::make(Perturbacion *pert,Portalizacion *portalizacion){
     unsigned int *indice=new unsigned int;
     *indice=0;
     make(pert,ancho,indice,0,0,0,portalizacion);
     comprimirRepresentacion();

     delete(indice);
}
//---------------------------------------------------------------------------
void QuadTreeTSP::make(Perturbacion *pert,unsigned int dim,unsigned int *indiceReal,unsigned int numCuadrante,unsigned int x,unsigned int y, Portalizacion *portalizacion){
    this->cantCuadrantes++;

    Cuadrante *aux=new Cuadrante;
    aux->setLevel(Log2(this->ancho/dim));     //calculo del Numero de Nivel
    aux->setIndice(numCuadrante);
    aux->setIndiceReal(*indiceReal);
    aux->setX(x);
    aux->setY(y);
    aux->setLargo(dim);

    //actualizando el indice real para el proximo cuadrante
    (*indiceReal)=(*indiceReal)+1;

    if (maxCuadrante<numCuadrante)
        maxCuadrante=numCuadrante;

    //Corte Recursion: Dimension minima o Cuadrante con menos de dos nodos
    if ((dim>1) && (pert->nodos(x,x+dim,y,y+dim))){
        aux->setTieneHijos();
        aux->setposHijos(4*numCuadrante+1);
        this->agregar(aux,numCuadrante);

        //llamado a la recursion
        make(pert,dim/2,indiceReal,4*numCuadrante+1,x,y,portalizacion);
        make(pert,dim/2,indiceReal,4*numCuadrante+2,x+(dim/2),y,portalizacion);
        make(pert,dim/2,indiceReal,4*numCuadrante+3,x,y+(dim/2),portalizacion);
        make(pert,dim/2,indiceReal,4*numCuadrante+4,x+(dim/2),y+(dim/2),portalizacion);

   }
    else{ //llegue a una hoja
      cantHojas++;
      aux->setNodoIn(pert->getNodo(x,x+dim,y,y+dim));
      this->agregar(aux,numCuadrante);


 
    }
}
//---------------------------------------------------------------------------
void QuadTreeTSP::comprimirRepresentacion(){
   Cuadrante **newQuad;

   newQuad=new Cuadrante*[maxCuadrante+1];

   for (unsigned int i=maxCuadrante+1; i<this->dimensionAsignada; i++)
        delete(this->quadtr[i]);

   for (unsigned int i=0; i<maxCuadrante+1; i++)
        newQuad[i]=this->quadtr[i];

   this->quadtr=newQuad;
   this->dimComprimida=maxCuadrante+1;

}
//---------------------------------------------------------------------------
Lista<Cuadrante> *QuadTreeTSP::getCuadrantes(){
  //si ya fue construido el quadtree
  if (cantCuadrantes!=0){
    Lista<Cuadrante> *auxL=new Lista<Cuadrante>;
    for (unsigned int i=0; i<this->dimComprimida; i++)
        //si el lugar esta ocupado
        if (this->quadtr[i]!=NULL)
             auxL->agregar(this->quadtr[i]);
    return auxL;
  }
  else
        return NULL;
};
//---------------------------------------------------------------------------
Lista<Cuadrante> *QuadTreeTSP::getCuadrantesPadres(){
  //si ya fue construido el quadtree
  if (cantCuadrantes!=0){
    Lista<Cuadrante> *auxL=new Lista<Cuadrante>;
    for (unsigned int i=0; i<this->dimComprimida; i++)
        //si el lugar esta ocupado
        if ((this->quadtr[i]!=NULL) && (this->quadtr[i]->hijos()))
             auxL->agregar(this->quadtr[i]);
    return auxL;
  }
  else
        return NULL;
};
//---------------------------------------------------------------------------
unsigned int QuadTreeTSP::getIndexCLevel(unsigned int level){
    return indicesLevel[level];
}
//---------------------------------------------------------------------------
bool QuadTreeTSP::adyacentes(unsigned int hijo1,unsigned int hijo2){
     unsigned int padre1=this->getPadre(hijo1);
     unsigned int padre2=this->getPadre(hijo2);

     //si poseen el mismo padre
     if (padre1==padre2){
          //hijos 1 y 2
          if (padre1*4+1==hijo1)
                if ((padre1*4+3==hijo2) || (padre1*4+2==hijo2))
                         return true;
          if (padre1*4+1==hijo2)
                if ((padre1*4+3==hijo1) || (padre1*4+2==hijo1))
                         return true;
          //hijos 2 y 4
          if (padre1*4+2==hijo1)
                if (padre1*4+4==hijo2)
                         return true;
          if (padre1*4+2==hijo2)
                if (padre1*4+4==hijo1)
                         return true;
          //hijos 3 y 4
          if (padre1*4+3==hijo1)
                if (padre1*4+4==hijo2)
                         return true;
          if (padre1*4+3==hijo2)
                if (padre1*4+4==hijo1)
                         return true;

          return false;

     }
     else
        return false;
};
//---------------------------------------------------------------------------
bool QuadTreeTSP::hermanos(unsigned int hijo1,unsigned int hijo2){
    return (this->getPadre(hijo1)==this->getPadre(hijo2));
}
//---------------------------------------------------------------------------
Lista<Cuadrante> *QuadTreeTSP::getHojas(){
  //si ya fue construido el quadtree
  if (cantCuadrantes!=0){
    Lista<Cuadrante> *auxL=new Lista<Cuadrante>;
    for (int i=this->dimComprimida-1; i>=0; i--)
        //si no posee hijos es una hoja
        if ((this->quadtr[i]!=NULL) && (!this->quadtr[i]->hijos()))
                auxL->agregarFinal(this->quadtr[i]);
    return auxL;
  }
  else
        return NULL;
}
//---------------------------------------------------------------------------
Cuadrante *QuadTreeTSP::getCuadrante(unsigned int cuadr){
   if (cuadr<this->dimComprimida)
        return this->quadtr[cuadr];
   else
        return NULL;
}
//---------------------------------------------------------------------------
Lista<Cuadrante> *QuadTreeTSP::getHijosde(unsigned int padre){
     if (this->esPadre(padre)){
        Lista<Cuadrante> *auxL=new Lista<Cuadrante>;

        auxL->agregar(this->getHijo(padre,4));
        auxL->agregar(this->getHijo(padre,3));
        auxL->agregar(this->getHijo(padre,2));
        auxL->agregar(this->getHijo(padre,1));

        return auxL;
     }
     else
        return NULL;

}
//---------------------------------------------------------------------------
unsigned int QuadTreeTSP::getMaxLevelOcupado(){
     return this->quadtr[maxCuadrante]->getLevel();
}
//---------------------------------------------------------------------------
Lista<Punto> *QuadTreeTSP::getPortalesCompartidos(unsigned int hijo1,unsigned int hijo2){
     //si son hijos adyacentes
     if (this->adyacentes(hijo1,hijo2)){
         Punto **auxH1;
         Punto **auxH2;
         Lista<Punto> *auxRtdo=new Lista<Punto>;

         auxH1=this->quadtr[hijo1]->getPortales();
         auxH2=this->quadtr[hijo2]->getPortales();
         unsigned int longitud=this->quadtr[hijo2]->getCantPortales();

         for (unsigned int i=0; i<this->quadtr[hijo1]->getCantPortales(); i++)
              if (pertenece(auxH1[i],auxH2,longitud))
                auxRtdo->agregar(auxH1[i]);

         if (auxRtdo->tamanio()!=0)
            return auxRtdo;
         else
            return NULL;

     }
     else
        return NULL;
}
//---------------------------------------------------------------------------
bool QuadTreeTSP::pertenece(Punto *punto,Punto **lista,unsigned int longitud){
     for (unsigned int i=0; i<longitud; i++)
          if (lista[i]==punto)
                return true;
     return false;
}
//---------------------------------------------------------------------------
int QuadTreeTSP::elRestoSinNodos(unsigned int padre,unsigned int hijoI,unsigned int hijoII){
   unsigned int h1,h2;

   h1=4*padre+1;    //ubica la posicion del primer hijo del padre
   while ((h1==hijoI) || (h1==hijoII) )
        h1++;
   h2=4*padre+1;
   while ((h2==h1) || (h2==hijoI) || (h2==hijoII) )
        h2++;

   //si los dos hijos son padres se supone que siempre tiene algun hijo con nodos
   if ((quadtr[h1]->hijos()) && (quadtr[h2]->hijos()))
        return AMBOS;

   //si el h1 es padre y h2 no lo es
   if (quadtr[h1]->hijos()){
        if (quadtr[h2]->getNodoIn()==NULL)
                return   h1;
        else
                return AMBOS;
   };

   //si el h2 es padre y h1 no lo es
   if (quadtr[h2]->hijos()){
        if (quadtr[h1]->getNodoIn()==NULL)
                return   h2;
        else
                return AMBOS;
   };

   //si ambos hijos son hojas se analiza si poseen o no nodos
   if ((quadtr[h1]->getNodoIn()==NULL) && (quadtr[h2]->getNodoIn()==NULL))
        return NINGUNO;   //ninguno de los  hijos posee nodos

   if ((quadtr[h1]->getNodoIn()!=NULL) && (quadtr[h2]->getNodoIn()!=NULL))
        return AMBOS;    //los dos poseen

   if ((quadtr[h1]->getNodoIn()!=NULL) && (quadtr[h2]->getNodoIn()==NULL))
        return h1;       //el hijo h1 posee nodos

   if ((quadtr[h1]->getNodoIn()==NULL) && (quadtr[h2]->getNodoIn()!=NULL))
        return h2;      //el hijo h2 posee nodos

   return NINGUNO;

}
//---------------------------------------------------------------------------
unsigned int QuadTreeTSP::getAdyacenteDe(unsigned int indice){
   unsigned int numHijo=this->getNumeroDeHijo(indice);
  if ((numHijo==1))
    return indice+2;

  if ((numHijo==3))
    return indice+1;

   if (numHijo==2)
    return indice+2;

   if (numHijo==4)
    return indice-2;

}
//---------------------------------------------------------------------------
unsigned int QuadTreeTSP::hijoQueCompartePortal(Punto *portal,unsigned int padre){
  unsigned int hijo=4*padre+1; // tomamos el primer hijo
  unsigned int fin=4*padre+4;


  while ((hijo<=fin) && (!quadtr[hijo]->contienePortal(portal)))
        hijo++;

  if (hijo<=fin) //si pare en alguno de los hijos validos
        return hijo;
  else
        return fin+1;      //sino retorno hijo imposible
}
//---------------------------------------------------------------------------
unsigned int QuadTreeTSP::getAdyacenteDistintoDe(unsigned int padre,unsigned int adyConocido){
   unsigned int suma=((padre*4)+1);
   suma=suma+(suma+3);

   return suma-adyConocido;
}
//---------------------------------------------------------------------------


#pragma package(smart_init)
