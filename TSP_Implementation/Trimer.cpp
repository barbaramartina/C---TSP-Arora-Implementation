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

#include "Trimer.h"

//---------------------------------------------------------------------------
Trimer::Trimer(QuadTreeTSP *q,ProgramacionDinamica *pdin,Perturbacion *per){
   quad=q;
   quadtr=quad->getArreglo();
   pd=pdin;
   pert=per;
   tamanio=0;
   caminoTrimed=NULL;

   //setea los datos del Maximo tamaño del arreglo
   setMaxTamanio();

   //inicializo camino
   inicCaminoTrimed();


};
//---------------------------------------------------------------------------
Trimer::~Trimer(){
  
};
//---------------------------------------------------------------------------
void Trimer::inicCaminoTrimed(){
  numNodos=pert->getNumNodos();
  caminoTrimed=new PuntoExtendido*[numNodos];

  for (unsigned int i=0; i<numNodos; i++)
   caminoTrimed[i]=NULL;

};
//---------------------------------------------------------------------------
void Trimer::execute(){
   //Realiza el trim del camino
   this->Trim();
};
//---------------------------------------------------------------------------
PuntoExtendido ** Trimer::getCaminoTrimed(){
   return caminoTrimed;
};
//---------------------------------------------------------------------------
void Trimer::setMaxTamanio(){
   unsigned int maxL;
   maxL=quad->getMaxLevelOcupado();

   for (unsigned int i=0; i<maxL; i++)
      tamanio+=6*Power(6,i);

   tamanio++; //nunca se usa la posicion cero por ello se necesita un espacio mas
};
//---------------------------------------------------------------------------
void Trimer::Trim(){
   SubSolucion *sb=pd->getSubSolucion(0,0);
   Lista<unsigned int> *hijos=sb->getHijos();
   Lista<unsigned int> *apareos=sb->getApareos();
   unsigned int *pos = new unsigned int;

   *pos=0;
   unsigned int *apar=apareos->primero();
   for (unsigned int *h=hijos->primero(); h!=NULL; h=hijos->siguiente()){
      if (*h==3)
         this->divide=(*pos);
      Trim2(*h,*apar,pos);

      //actualizo apareo
      apar=apareos->siguiente();
   };
};
//---------------------------------------------------------------------------
void Trimer::Trim2(unsigned int indice, unsigned int apareo,unsigned int *posArr){
    if (!(quadtr[indice]->hijos())){  //si es una hoja
      PuntoExtendido *nodo=quadtr[indice]->getNodoIn();
      if (nodo!=NULL){
         caminoTrimed[*posArr]=nodo;
         (*posArr)++;
      };
   }     //tiene hijos que se deben analizar
    else{
       //sucesivos llamados a la recursion
       SubSolucion *sb=pd->getSubSolucion(quadtr[indice]->getIndiceReal(),apareo);
       Lista<unsigned int> *apareos=sb->getApareos();
       Lista<unsigned int> *hijos=sb->getHijos();

       //incorporo otros casos donde se debe invertir
       SubSolucion *sb_hijoActual;    //será la subsolucion del hijo actual
       sb_hijoActual = NULL;
       unsigned int *h=new unsigned int;
       unsigned int *apar=new unsigned int;
       (*h)=0;
       (*apar)=0;


       int tam=hijos->tamanio();
       //un tamaño mayor a 5 indicara que pasara por el mismo cuadrantre mas de una vez
       //pero solo se tiene en cuenta una por eso se lo acota
       if (tam >= 5)
         tam = 4;

       for (int i=0; i<tam; i++){
              apar=apareos->get(i);
              h=hijos->get(i);

              Trim2(*h,*apar,posArr);
       }
    }
};
//---------------------------------------------------------------------------
AnsiString Trimer::toString(){
   AnsiString resultado="Camino Trimed \n";

   for (unsigned int pos=0; pos<numNodos ; pos++)
      resultado+=caminoTrimed[pos]->toString()+"\n";

//   resultado+="Unir El Punto 1 al Punto "+IntToStr(divide)+"\n";
   resultado+="Largo del Camino = "+FloatToStr(this->getLargoCamino());

   return resultado;
};
//---------------------------------------------------------------------------
float Trimer::getLargoCamino(){
  PuntoExtendido **puntosOriginales = pert->getNodosImput();
  float res=0;

  for (unsigned int i=0; i<divide-1; i++)
   res+=puntosOriginales[caminoTrimed[i]->getUbicacion()]->distancia_Total_a(puntosOriginales[caminoTrimed[i+1]->getUbicacion()]);
  for (unsigned int i=divide; i<numNodos-1; i++)
   res+=puntosOriginales[caminoTrimed[i]->getUbicacion()]->distancia_Total_a(puntosOriginales[caminoTrimed[i+1]->getUbicacion()]);

  res+=puntosOriginales[caminoTrimed[divide-1]->getUbicacion()]->distancia_Total_a(puntosOriginales[caminoTrimed[numNodos-1]->getUbicacion()]);


  return res;

};
//---------------------------------------------------------------------------



#pragma package(smart_init)
