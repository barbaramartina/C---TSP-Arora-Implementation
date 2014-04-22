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

#include "SubSolucion.h"

//---------------------------------------------------------------------------
SubSolucion::SubSolucion(){
   distancia=DISTANCIAINVALIDA;
   apareos=new Lista<unsigned int>;
   hijos=new Lista<unsigned int>;
   inversiones = new Lista<bool>;
}
//---------------------------------------------------------------------------
SubSolucion::~SubSolucion(){
   delete(hijos);
   hijos = NULL;

   delete(apareos);
   apareos = NULL;
}
//---------------------------------------------------------------------------
void SubSolucion::addHijo(unsigned int x){
   unsigned int *x1=new unsigned int;
   *x1=x;
   hijos->agregarFinal(x1);
}
//---------------------------------------------------------------------------
void SubSolucion::addApareo(unsigned int a){
   unsigned int *a1=new unsigned int;
   *a1=a;
   apareos->agregarFinal(a1);
}
//---------------------------------------------------------------------------
void SubSolucion::addInversion(bool i){
   bool *b1= new bool;
   *b1=i;
   inversiones->agregarFinal(b1);
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
