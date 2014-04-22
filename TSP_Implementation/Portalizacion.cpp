#pragma hdrstop

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


#include "Portalizacion.h"

//---------------------------------------------------------------------------
Portalizacion::Portalizacion(unsigned int ancho,unsigned int alto){

        portales = new Matriz<Punto>(ancho , alto);

}
//---------------------------------------------------------------------------
Portalizacion::~Portalizacion(){

        delete(portales);
}
//---------------------------------------------------------------------------
Lista2<Punto> * Portalizacion::getPortales(unsigned int x,unsigned int y,unsigned int dim){

        Lista2<Punto> *aux = new Lista2<Punto>();

        for ( int x2 = x + dim  ; x2 >= (int)x ; x2--){
                Punto *p = portales->get(x2,y);
                if ( p != NULL)
                        aux->agregarFinal(p);
        }
        for ( int y2 = y ; y2 < y + dim ; y2++){
                Punto *p = portales->get(x,y2);
                if ( p != NULL)
                        aux->agregarFinal(p);
        }
        for ( int x2 = x ; x2 < x + dim ; x2++){
                Punto *p = portales->get(x2,y+dim);
                if ( p != NULL)
                        aux->agregarFinal(p);
        }
        for ( int y2 = y + dim  ; y2 > (int)y ; y2--){
                Punto *p = portales->get(x+dim,y2);
                if ( p != NULL)
                        aux->agregarFinal(p);
        }
        return aux;

};
//---------------------------------------------------------------------------
void Portalizacion::portalizar(Lista<Cuadrante> *c,Lista<Cuadrante> *h){
    unsigned int x,y,dim;
    Lista2<Punto> *portales;

    for (Cuadrante *auxH = h->primero(); auxH; auxH = h->siguiente()){

           x    = auxH->getX();
           y    = auxH->getY();
           dim  = auxH->getLargo();

         //agrego los portales
          if (!this->hayPortales(x,y,dim,ARRIBA))
            this->set( x + ( dim / 2) , y );
          if (!this->hayPortales(x,y,dim,IZQUIERDA))
            this->set( x , y + (dim / 2 ) );
          if (!this->hayPortales(x,y,dim,ABAJO))
            this->set( x + ( dim / 2 ), y + dim  );
          if (!this->hayPortales(x,y,dim,DERECHA))
            this->set( x +  dim , y + (dim / 2) );


           portales = this->getPortales(x,y,dim);

           auxH->setPortales(portales);
    }

    for (Cuadrante *auxC = c->primero(); auxC; auxC = c->siguiente()){


           x    = auxC->getX();
           y    = auxC->getY();
           dim  = auxC->getLargo();
                 
           portales = this->getPortales(x,y,dim);

           auxC->setPortales(portales);
    }
}
//---------------------------------------------------------------------------
void  Portalizacion::set(unsigned int x,unsigned int y){
        Punto *p = portales->get(x,y);
        if (p == NULL){
                p = new Punto(x,y);
                portales->set(p,x,y);
        };

}
//---------------------------------------------------------------------------
bool Portalizacion::hayPortales(int x,int y,int dim,int dir){
        bool hay = false;

  switch (dir)
        {
        case ARRIBA:
        for ( int x2 = x + dim  ; x2 >= (int)x ; x2--){
                Punto *p = portales->get(x2,y);
                if ( p != NULL)
                        hay = true;
        }
        break;
        case IZQUIERDA:
        for ( int y2 = y ; y2 < y + dim ; y2++){
                Punto *p = portales->get(x,y2);
                if ( p != NULL)
                        hay = true;
        }
        break;
        case ABAJO:
        for ( int x2 = x ; x2 < x + dim ; x2++){
                Punto *p = portales->get(x2,y+dim);
                if ( p != NULL)
                        hay = true;
        }
        break;
        case DERECHA:
        for ( int y2 = y + dim  ; y2 >= (int)y ; y2--){
                Punto *p = portales->get(x+dim,y2);
                if ( p != NULL)
                        hay = true;
        }
        break;
        }

        return hay;
}
//---------------------------------------------------------------------------


#pragma package(smart_init)
