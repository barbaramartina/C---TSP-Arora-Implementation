/*********************************************************************
*                    PROGRAMACION DINAMICA
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


#ifndef ProgramacionDinamicaH
#define ProgramacionDinamicaH

#define NINGUNO -1
#define AMBOS -2

#include <ExtCtrls.hpp>
#include <System.hpp>
#include <Values.h>

#include "L.h"
#include "MatrizVariable.h"
#include "QuadTreeTSP.h"
#include "SubSolucion.h"

class ProgramacionDinamica{

   private:
           QuadTreeTSP *quad;
           Cuadrante **quadtr;
           MatrizVariable<SubSolucion> *matriz;

           void makeHojas(); //resuelve la Programacion para las hojas
           void makeSolucionLevel(unsigned int); //construye la solucion del nivel dado
           void makeSolucion();


   public:
           ProgramacionDinamica(QuadTreeTSP *);
           ~ProgramacionDinamica();
           void execute();
           SubSolucion *getSubSolucion(unsigned int,unsigned int);
 
};
//---------------------------------------------------------------------------
#endif
