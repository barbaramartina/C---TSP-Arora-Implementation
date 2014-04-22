/*********************************************************************
*                       SUBSOLUCION
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


#ifndef SubSolucionH
#define SubSolucionH

#include "L.h"

#define DISTANCIAINVALIDA -1

class SubSolucion{

        private:

                float distancia;
                Lista<unsigned int> *hijos;
                Lista<unsigned int> *apareos;
                Lista<bool>     *inversiones;

        public:

                SubSolucion();
                ~SubSolucion();
                void addHijo(unsigned int x);
                void addApareo(unsigned int a);
                void setDistancia(float d){distancia = d;};
                Lista<unsigned int> *getHijos(){return hijos;};
                Lista<unsigned int> *getApareos(){return apareos;};
                Lista<bool> *getInversiones(){return inversiones;};
                float getDistancia(){return distancia;};
                void addInversion(bool);


};
//---------------------------------------------------------------------------
#endif
