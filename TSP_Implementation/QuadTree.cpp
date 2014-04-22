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


#include "QuadTree.h"

//---------------------------------------------------------------------------
QuadTree::QuadTree(unsigned int dim){
    dimension=dim;
    dimensionAsignada=CTEDIM;
    if (dimensionAsignada==0)
       quadtr=NULL;
    else{
       quadtr=new Cuadrante*[dimensionAsignada];
       for (unsigned int i=0; i<dimensionAsignada; i++)
         quadtr[i]=NULL;
    };
}
//---------------------------------------------------------------------------
QuadTree::~QuadTree(){}
//---------------------------------------------------------------------------
void QuadTree::agregar(Cuadrante *info,unsigned int pos){
   if (pos>dimensionAsignada)
        expandir(pos);

   *(quadtr+pos)=info;
}
//---------------------------------------------------------------------------
void QuadTree::expandir(unsigned int posRequerida){
    int indiceExpansion=posRequerida/CTEDIM;

    Cuadrante **nuevoQuadtr=new Cuadrante*[dimensionAsignada+((indiceExpansion+1)*CTEDIM)] ;

    for (unsigned int i=0; i<dimensionAsignada; i++)
        nuevoQuadtr[i]=this->quadtr[i];
    for (unsigned int j=dimensionAsignada; j<dimensionAsignada+((indiceExpansion+1)*CTEDIM); j++)
        nuevoQuadtr[j]=NULL;

    delete(this->quadtr);
    this->quadtr=nuevoQuadtr;
    dimensionAsignada=dimensionAsignada+((indiceExpansion+1)*CTEDIM);
}
//---------------------------------------------------------------------------
Cuadrante **QuadTree::root(){ return quadtr; }
//---------------------------------------------------------------------------


#pragma package(smart_init)
