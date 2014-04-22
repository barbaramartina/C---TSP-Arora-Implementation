/*********************************************************************
*                        QUADTREE
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


#ifndef QuadTreeH
#define QuadTreeH

#define CTEDIM 10000

#include "Cuadrante.h"

class QuadTree{

      protected:

              Cuadrante **quadtr;
              unsigned __int64 dimension;
              unsigned __int64 dimensionAsignada;

              void expandir(unsigned int);   //le da mas espacio de memoria al quadtree

      public:
      
             QuadTree(unsigned int);
             ~QuadTree();
             void agregar(Cuadrante *,unsigned int);
             Cuadrante **root();
             
};

#endif
