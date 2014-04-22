/*********************************************************************
*                        PERTURBACION
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


#ifndef PerturbacionH
#define PerturbacionH

#define MAX_VAL 80
#define MIN_X_DEF 0.2

#include <Math.h>
#include <stdio.h>
#include <stdlib.h>
#include <System.hpp>
#include <Values.h>
#include <vcl.h>

#include "Punto.h"
#include "PuntoExtendido.h"

class Perturbacion{

     private:

             AnsiString *archivo;              //archivo de Imput
             int cteAproximacion;              //constante de aproximacion de la Optima Solucion
             unsigned int numNodos,numNodosOrig;
             float largoBoundingBox;
             unsigned int largoEnclosingBox;
             PuntoExtendido *nodosImput,**nodosOriginales;
             float minCoordX;
             float minCoordY;


             float getLargoBB();        //calcula el largo del Bounding Box
             unsigned int getLargoEB(); //calcula el largo del Bounding Box
             void getImput();           //genera un arreglo con los nodos de entrada
             void perturbar();          //realiza la perturbacion y vuelca sus resultados en la matriz
             void shiftNodos();         //ubica todos los nodos en coordenadas impares
             void cutNodos();           //fusiona nodos que esten en la misma coordenada
             void copyImput();          //realiza una copia de los nodos originales que se mantendrá sin tocar
             float getMinX();           //retorna la mínima distancia entre dos nodos en sus coordenadas X
             float getMinY();           //retorna la mínima distancia entre dos nodos en sus coordenadas Y

          
     public:
     
             Perturbacion(AnsiString *,int);
             ~Perturbacion();
             Punto *getNodosPerturbados(){ return nodosImput;};
             unsigned int getNumNodos();
             float getLargoBoundingBox();
             unsigned int getLargoEnclosingBox();
             Punto *getPerturbacion();
             bool nodos(int,int,int,int);
             PuntoExtendido *getNodo(int,int,int,int);
             PuntoExtendido **getNodosImput(){ return nodosOriginales;};
             int getNumNodosO(){return numNodosOrig;};

};
//---------------------------------------------------------------------------

#endif
