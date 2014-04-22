/*********************************************************************
*                          MATRIZ
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


#ifndef MatrizH
#define MatrizH

#define VALUE_DEF 0

#include <conio.h>
#include <iostream.h>
#include <System.hpp>

#include "Punto.h"

template <class T> class Matriz{

   private:

           T ***matriz;
           unsigned int tamX,tamY;
           
   public:

           Matriz(unsigned int,unsigned int);
          ~Matriz();
           unsigned int getSizeX();
           unsigned int getSizeY(unsigned int);
           T *get(unsigned int,unsigned int);
           void set(T*,unsigned int,unsigned int);
           bool posValida(unsigned int,unsigned int);

};



template class Matriz<Punto>;
//---------------------------------------------------------------------------
template <class T> Matriz<T>::Matriz(unsigned int x,unsigned int y){
   matriz = new T**[x];
   for (unsigned int i=0; i<x; i++){
      matriz[i] = new T*[y];
      for (unsigned int j=0; j<y; j++)
        matriz[i][j]=NULL;
   };


   tamX=x;
   tamY=y;
}
//---------------------------------------------------------------------------
template <class T> Matriz<T>::~Matriz(){
   for(unsigned int j=0;j<this->getSizeY(VALUE_DEF);delete matriz[j++]);
   delete matriz;
}
//---------------------------------------------------------------------------
template <class T> unsigned int Matriz<T>::getSizeX(){
   return tamX;
}
//---------------------------------------------------------------------------
template <class T> unsigned int Matriz<T>::getSizeY(unsigned int col){
   return tamY;
}
//---------------------------------------------------------------------------
template <class T> T *Matriz<T>::get(unsigned int x,unsigned int y){
   if (!this->posValida(x,y)) return NULL;
   return matriz[x][y];
}
//---------------------------------------------------------------------------
template <class T> void Matriz<T>::set(T* elem,unsigned int x,unsigned int y){
   if (this->posValida(x,y))
      matriz[x][y]=elem;
}
//---------------------------------------------------------------------------
template <class T> bool Matriz<T>::posValida(unsigned int x,unsigned int y){
   if (x>=this->getSizeX() || y>=this->getSizeY(VALUE_DEF)) return false;
   return true;
}

#endif
