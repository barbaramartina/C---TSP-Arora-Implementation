/*********************************************************************
*                          LISTA 2
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


#ifndef L2H
#define L2H

#include "Punto.h"

template <class T>

class Lista2{

              class Nodo{
              public:
                      Nodo * sig;
                      T *elem;
              };


              Nodo* raiz, *actual, *final;
              int longitud;

        public:
              Lista2();
              ~Lista2();
              void vaciar();
              void agregar(T *elem);
              void agregarOrdenado(T *elem);
              void agregarFinal(T *elem);
              void eliminar(T *elem);
              void eliminarSinBorrar(T *elem);
              T *primero();
              T *siguiente();
              T *Lista2<T>::pertenece (T *elem);
              int tamanio();
              T *get(int);
              void clonar(Lista2<T> *origen);
              void agregarLista(Lista2<T> *list);

};

#endif
