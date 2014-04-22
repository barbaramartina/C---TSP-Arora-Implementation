/*********************************************************************
*                      MATRIZ VARIABLE
*                    Barbara M. Rodeker
*                    TSP 
*                    Arora`s implementation
*
**********************************************************************/
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


#ifndef MatrizVariableH
#define MatrizVariableH

#define TamYdefault -1
#define TamYdefaultAll -3
#define TamYEqual -2

#include <conio.h>
#include <iostream.h>
#include <System.hpp>

#include "L.h"
#include "SubSolucion.h"

template <class T> class MatrizVariable{

   private:

           T ***matriz;
           unsigned int tamX;
           int *tamY;
           bool inicializado;

           //metodos usados para manejo de dimensiones variables
           void inic_TamY();      //inicializa en default value las dimensiones de las columnas
           void reset_TamY(unsigned int);  //setea el valor pasado como parametro como dimension de las columnas
           void set_TamY(unsigned int,unsigned int);//setea el valor dado en la columna indicada

   public:

           MatrizVariable(unsigned int);
           ~MatrizVariable();
           void inicColumna(unsigned  int);
           void inicColumna(unsigned int,unsigned int);
           unsigned int getSizeY(unsigned int);
           unsigned int getSizeX();
           T *get(unsigned int,unsigned int);
           void set(T*,unsigned int,unsigned int);
           bool posValida(unsigned int,unsigned int);

};


template <class T> MatrizVariable<T>::MatrizVariable(unsigned int x){
   matriz = new T**[x];
   for (unsigned int i=0; i<x; i++)
        matriz[i]=NULL;
   tamX=x;
   inic_TamY();
}
//---------------------------------------------------------------------------
template <class T> unsigned int MatrizVariable<T>::getSizeX(){
   return tamX;
}
//---------------------------------------------------------------------------

template <class T> void MatrizVariable<T>::inicColumna(unsigned int y){
   for (unsigned int i=0; i<this->getSizeX(); i++){
       matriz[i]=new T*[y];
       for (unsigned int j=0; j<y; j++)
           matriz[i][j]=NULL;
   };
   reset_TamY(y);
}
//---------------------------------------------------------------------------
template <class T> void MatrizVariable<T>::inicColumna(unsigned int col,unsigned int y){
    matriz[col]=new T*[y];
    for (unsigned int j=0; j<y; j++)
     matriz[col][j]=NULL;

    set_TamY(col,y);
};
//---------------------------------------------------------------------------
template <class T> void MatrizVariable<T>::inic_TamY(){
   inicializado=false;
   tamY=new int[1];
   tamY[0]=TamYdefaultAll;
}
//---------------------------------------------------------------------------
template <class T> void MatrizVariable<T>::reset_TamY(unsigned int value){
  delete(tamY);
  tamY=new int[2];
  tamY[0]=TamYEqual;
  tamY[1]=value;
};
//---------------------------------------------------------------------------
template <class T> T *MatrizVariable<T>::get(unsigned int x,unsigned int y){
   if (!this->posValida(x,y))
        return NULL;
   return matriz[x][y];
}
//---------------------------------------------------------------------------
template <class T> void MatrizVariable<T>::set(T* elem,unsigned int x,unsigned int y){
   if (this->posValida(x,y))
      matriz[x][y]=elem;
}
//---------------------------------------------------------------------------
template <class T> void MatrizVariable<T>::set_TamY(unsigned int col,unsigned int value){

  if (!inicializado) {
     delete(tamY);
     tamY= new int[tamX];
     for (int i=0; i<tamX; i++)
        tamY[i]=TamYdefault;
  };

  inicializado=true;

  tamY[col]=value;

}
//---------------------------------------------------------------------------
template <class T> MatrizVariable<T>::~MatrizVariable(){
   delete(tamY);
}
//---------------------------------------------------------------------------
template <class T> unsigned int MatrizVariable<T>::getSizeY(unsigned int col){
  switch (tamY[0])
  {
    case TamYdefaultAll: return tamY[1];
    case TamYEqual:      return tamY[1];
  };

  return tamY[col];
}
//---------------------------------------------------------------------------
template <class T> bool MatrizVariable<T>::posValida(unsigned int x,unsigned int y){
   if (x>=this->getSizeX() || y>=this->getSizeY(x)) return false;
   return true;
}



template class MatrizVariable<Punto>;
template class MatrizVariable<SubSolucion>;

#endif


