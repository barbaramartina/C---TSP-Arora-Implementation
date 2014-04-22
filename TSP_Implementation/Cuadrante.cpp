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

#include "Cuadrante.h"

//---------------------------------------------------------------------------
Cuadrante::Cuadrante(){
  tieneHijos=false;
  level=0;
  indice=0;
  indiceReal=0;
  portales=NULL;
  cantPortales=0;
  Dato.nodoIn=NULL;
  

}
//---------------------------------------------------------------------------
Cuadrante::~Cuadrante(){
   //se borran cada uno de los portales que posee el cuadrante
   for (unsigned int i=0; i<cantPortales; i++)
      if (portales[i] != NULL) {
         delete(portales[i]);
         portales[i] = NULL;
      };

   //borro el puntero a todos los portales
   delete(portales);
   portales = NULL;

}
//---------------------------------------------------------------------------
void Cuadrante::inicPortales(unsigned int tam){
   cantPortales=tam;
   portales=new Punto*[tam];
   for  (unsigned int i=0; i<tam; i++)
        portales[i]=NULL;
}
//---------------------------------------------------------------------------
PuntoExtendido * Cuadrante::getNodoIn(){
    if (this->tieneHijos)
        return NULL;

    return this->Dato.nodoIn;
}
//---------------------------------------------------------------------------
bool Cuadrante::contienePortal(Punto *portal){
 unsigned int pos=0;

 while ((pos<cantPortales) && (portales[pos]!=portal))
        pos++;

 return pos<cantPortales;

}
//---------------------------------------------------------------------------
void Cuadrante::getApareo(unsigned int apareo,Punto *&portal1,Punto *&portal2){
  if ((cantPortales!=0) &&(apareo<((cantPortales*(cantPortales-1))/2)) ){
    int aux=apareo;
    int num=1;
    int resta=0;


    while ((aux-((int)this->cantPortales-num))>=0){
       aux-=this->cantPortales-num;
       if  (aux>=0)
               resta=aux;
       num++;
    }

    portal1= this->portales[num-1];

    if ((num-1)==0)
        portal2=this->portales[apareo+1];
    else
        portal2=this->portales[resta+num];
  }
  else {
    apareo = apareo - ((cantPortales*(cantPortales-1))/2);
    return getApareo(apareo,portal2,portal1);
  };

}
//---------------------------------------------------------------------------
unsigned int Cuadrante::getNumApareo(Punto *portal1,Punto *portal2){
   int ubicacion1,ubicacion2,pos;
   ubicacion1=ubicacion2=-1;


   pos=0;
   while ((pos<cantPortales) && ((ubicacion1==-1) || (ubicacion2==-1))){
      if (portales[pos]==portal1)
        ubicacion1=pos;
      if (portales[pos]==portal2)
        ubicacion2=pos;
      pos++;
   };

   if (ubicacion1>=ubicacion2) {  //el primer portal es mayor que el primero
          return getNumApareo(portal2,portal1)  + ((cantPortales*(cantPortales-1))/2);
   };

   if (ubicacion1==0)          //si el primer indice de portal es el cero
        return ubicacion2-1;

   unsigned int indice=0;

   for (unsigned int s=0; s<ubicacion1; s++)
        indice+=this->cantPortales-(1+s);

   for (unsigned int s=ubicacion1+1; s<ubicacion2; s++)
        indice++;

   return indice;

}
//---------------------------------------------------------------------------
void Cuadrante::setPortales(Lista2<Punto> *port){
    inicPortales(port->tamanio());

    this->cantPortales = 0;

    for (Punto *p = port->primero(); p; p = port->siguiente()){
         portales[cantPortales++] = p;
    }
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
