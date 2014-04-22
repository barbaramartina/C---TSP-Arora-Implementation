/*********************************************************************
*                        TRIMER
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


#ifndef TrimerH
#define TrimerH

#include <System.hpp>

#include "QuadTreeTSP.h"
#include "ProgramacionDinamica.h"
#include "Portalizacion.h"

#include "Punto.h"
#include "PuntoExtendido.h"
#include "Cuadrante.h"
#include "SubSolucion.h"

class Trimer{
     private:
            QuadTreeTSP *quad;
            Cuadrante **quadtr;
            ProgramacionDinamica *pd;
            Perturbacion *pert;
            unsigned int tamanio,numNodos,divide;
            PuntoExtendido **caminoTrimed;

            void setMaxTamanio(); //setea la variable tamaño que se refiere al arreglo de Par
            void Trim(); //prepara las condiciones para optimizar el camino
            void Trim2(unsigned int,unsigned int ,unsigned int *); //optimiza el camino obtenido poligonizandolo

            void inicCaminoTrimed();

     public:
            Trimer(QuadTreeTSP *,ProgramacionDinamica *,Perturbacion *);
            ~Trimer();
            void execute();
            PuntoExtendido **getCaminoTrimed();
            AnsiString toString();
            float getLargoCamino();
            int getDivide(){return divide;};



};
//---------------------------------------------------------------------------
#endif
