/*********************************************************************
*                      QUADTREE TSP
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


#include  <iostream.h>
#ifndef QuadTreeTSPH
#define QuadTreeTSPH

#define LADOS 4

#define EERROR 5

#define NINGUNO -1
#define AMBOS -2


#include <System.hpp>

#include <math.h>
#include <stdio.h>


#include "QuadTree.h"
#include "L.h"
#include "L2.h"
#include "Perturbacion.h"
#include "Portalizacion.h"



class QuadTreeTSP:public QuadTree{

      private:

               unsigned int ancho;
               unsigned int alto;
               unsigned int cantCuadrantes;
               unsigned int cantHojas;
               unsigned int maxCuadrante;
               unsigned int dimComprimida;
               unsigned int *indicesLevel;

               void make(Perturbacion *,unsigned int,unsigned int *,unsigned int,unsigned int,unsigned int,Portalizacion *);
               bool pertenece(Punto *,Punto **,unsigned int);
               void comprimirRepresentacion();

      public:

              QuadTreeTSP(unsigned int,unsigned int,unsigned int,int);
              ~QuadTreeTSP();
              bool esPadre(unsigned int);
              unsigned int getPadre(unsigned int x);
              unsigned int getNumeroDeHijo(unsigned int h);
              Cuadrante *QuadTreeTSP::getHijo(unsigned int,unsigned int);
              void make(Perturbacion *,Portalizacion *);
              unsigned int getCantCuadrantes();
              unsigned int getProfundidad();
              unsigned int getDimComprimida();
              unsigned int getAncho();
              Lista<Cuadrante> *getCuadrantes();
              Lista<Cuadrante> *getCuadrantesPadres();
              unsigned int getIndexCLevel(unsigned int);
              Cuadrante *getCuadrante(unsigned int );
              Cuadrante **getArreglo();
              unsigned int getAnchoLevel(unsigned int level);
              unsigned int getMaxLevelOcupado();
              Punto *getComienzo(unsigned int);
              bool adyacentes(unsigned int,unsigned int);
              unsigned int getAdyacenteDe(unsigned int);
              unsigned int getAdyacenteDistintoDe(unsigned int,unsigned int);
              bool hermanos(unsigned int,unsigned int);
              Lista<Cuadrante> *getHojas();
              Lista<Cuadrante> *getHijosde(unsigned int);
              Lista<Punto> *getPortalesCompartidos(unsigned int,unsigned int);
              int elRestoSinNodos(unsigned int,unsigned int,unsigned int);
                  /* Informa si el resto de los hijos de un padre
                   que no son los hijos pasados como parametro
                   no poseen nodos, o bien si ambos o alguno de ellos posee
                  */
              unsigned int hijoQueCompartePortal(Punto *,unsigned int);
                  /* Retorna el hijo que comparte el portal indicado
                     con el padre.
                     Retorna padre*4+5 (hijo invalido) caso contrario
                  */


};

#endif
