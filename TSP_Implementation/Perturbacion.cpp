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


#include "Perturbacion.h"

//---------------------------------------------------------------------------
Perturbacion::Perturbacion(AnsiString *arch,int cte){
      //ruta de datos y constante de aproximacion
        archivo=arch;
        cteAproximacion=cte;
        numNodosOrig=0;

        //instancia de entrada
        getImput();
        if (nodosImput==NULL)
           return;

        //guarda aparte los datos de entrada sin modificar
        copyImput();


        //calculo largo del primer bounding box sin perturbar
        largoBoundingBox=getLargoBB();


        perturbar();
};
//---------------------------------------------------------------------------
Perturbacion::~Perturbacion(){

      for (unsigned int i=0; i<numNodosOrig; i++)
         delete(nodosOriginales[i]);
      delete(nodosOriginales);
      nodosOriginales = NULL;

      delete(nodosImput);
      nodosImput = NULL;

};
//---------------------------------------------------------------------------
void Perturbacion::perturbar(){
      float resto,aux,dist_Min_X,dist_Min_Y, dist_Min_Media_X,dist_Min_Media_Y;

      //se establece la longitud mínima en cada uno de los ejes
      dist_Min_X = this->getMinX();
      dist_Min_Y = this->getMinY();

      //calculo las mitades de cada una de las distancias mínimas para reubicar los nodos
      dist_Min_Media_X = dist_Min_X / 2.0 ;
      dist_Min_Media_Y = dist_Min_Y / 2.0 ;

      //recorre cada uno de los nodos y los perturba
      for (unsigned int i=0; i<numNodos; i++){

          //perturba la coordenada X
          aux=nodosImput[i].getX()/dist_Min_X;
          resto=aux-Floor(aux);
          if (resto< dist_Min_Media_X )  //estoy mas cerca del piso del valor
                nodosImput[i].setX(Floor(aux));
          else   //estoy mas proximo al valor mayor
                nodosImput[i].setX(Ceil(aux));

          //perturba la coordenada Y
          aux=nodosImput[i].getY()/dist_Min_Y;
          resto=aux-Floor(aux);
          if (resto<dist_Min_Media_Y)
                nodosImput[i].setY(Floor(aux));
          else
                nodosImput[i].setY(Ceil(aux));

          //regrilla las coordenadas
          nodosImput[i].setX(nodosImput[i].getX()*2);
          nodosImput[i].setY(nodosImput[i].getY()*2);

      };

       //una vez perturbados los nodos calculo los largos de la instancia perturbada

       //tomo la menor de las dos distancias minimas para calcular el largo total de la nueva instancia
       float dist_Min_Menor ;
       if (dist_Min_X < dist_Min_Y )
            dist_Min_Menor = dist_Min_X ;
       else
            dist_Min_Menor = dist_Min_Y ;


       largoBoundingBox=(largoBoundingBox/dist_Min_Menor)*2+1;
       //perturba minCoordX
       aux=minCoordX / dist_Min_X;
       resto=aux - Floor(aux);
       if (resto < dist_Min_Media_X)  //estoy mas cerca del piso del valor
         minCoordX=Floor(aux);
       else   //estoy mas proximo al valor mayor
          minCoordX=(Ceil(aux));

        //perturba MinCoordY
        aux=minCoordY/dist_Min_Y;
        resto=aux-Floor(aux);
        if (resto<dist_Min_Media_Y)
          minCoordY=(Floor(aux));
        else
          minCoordY=(Ceil(aux));

        minCoordX=minCoordX*2;
        minCoordY=minCoordY*2;



       this->largoEnclosingBox=getLargoEB();

       //shift de todos los nodos de manera tal que queden en coordenadas impares
       shiftNodos();

       cutNodos();

};
//---------------------------------------------------------------------------
void Perturbacion::shiftNodos(){
      for (unsigned int i=0; i<numNodos; i++){
          nodosImput[i].setX(nodosImput[i].getX()-minCoordX+1.0);
          nodosImput[i].setY(nodosImput[i].getY()-minCoordY+1.0);
      };
};
//---------------------------------------------------------------------------
void Perturbacion::cutNodos(){
      PuntoExtendido *nuevo=new PuntoExtendido[numNodos];
      int indice=0;
      bool hayIgual=false;
      for (unsigned int i=0; i<numNodos-1; i++){
          hayIgual=false;
          for (unsigned int j=i+1; hayIgual==false && j<numNodos; j++)
                if (((int)nodosImput[i].getX()==(int)nodosImput[j].getX()) && ((int)nodosImput[i].getY()==(int)nodosImput[j].getY()))
                        hayIgual=true;
          if (!hayIgual)
               nuevo[indice++]=nodosImput[i];
      };
      nuevo[indice]=nodosImput[numNodos-1];

      nodosImput=nuevo;
      numNodos=indice+1;

};
//---------------------------------------------------------------------------
float Perturbacion::getLargoBB(){
     float minX,maxX,minY,maxY;
     maxX=0.0;
     maxY=0.0;
     minX=MAXFLOAT;
     minY=MAXFLOAT;

     //busca la mayor distancia entre coordenadas x e y en los nodos
     for (unsigned int i=0; i<numNodos; i++){
        if (nodosImput[i].getX()>maxX)
          maxX=nodosImput[i].getX();
        if (nodosImput[i].getY()>maxY)
          maxY=nodosImput[i].getY();
        if (nodosImput[i].getX()<minX)
          minX=nodosImput[i].getX();
        if (nodosImput[i].getY()<minY)
          minY=nodosImput[i].getY();
     };

     //setea variables globales
     this->minCoordX=minX;
     this->minCoordY=minY;

     //retorna la maxima diferencia entre los minimos y maximos de una de las dos coordenadas
     if (maxX-minX>maxY-minY)
        return maxX-minX;
     else
        return maxY-minY;
};
//---------------------------------------------------------------------------
unsigned int Perturbacion::getLargoEB(){
   unsigned int aux=ceil(this->largoBoundingBox)+1;
   unsigned int largo=0;
   int exponente=1;
   int base=2;

   while (largo<aux)
        largo=Power(base,exponente++);

   return largo;

};
//---------------------------------------------------------------------------
void Perturbacion::getImput(){

        TStringList *nodosList = new TStringList;
        nodosList->LoadFromFile(this->archivo->c_str());
        AnsiString coordenada ;


        //busco la dimension del archivo
        AnsiString info = nodosList->Strings[3];
        info = info.SubString(info.Pos(" "),MAX_VAL);
        this->numNodos = atoi( info.c_str() );
        nodosImput=new PuntoExtendido[numNodos];

        if (this->numNodos == 0){
                info = nodosList->Strings[3];
                info = info.SubString(info.Pos(" ")+1,MAX_VAL);
                info = info.SubString(info.Pos(" "),MAX_VAL);
                this->numNodos = atoi( info.c_str() );
                nodosImput=new PuntoExtendido[numNodos];
        }

        //cargo las coordenadas de los nodos
        this->numNodosOrig = 0;
        for (int i=6; i < nodosList->Count-1; i++){
           //obtener coordena X
           info =  nodosList->Strings[i].SubString(nodosList->Strings[i].Pos(IntToStr(numNodosOrig+1))+IntToStr(numNodosOrig+1).Length(),MAX_VAL);
           coordenada = " ";
           int j = 1;
           while (info.SubString(j,1) == " "){
                j++;
           }
           info = info.SubString(j,MAX_VAL);
           coordenada =  info.SubString(1,info.Pos(" ")-1);
           nodosImput[numNodosOrig].setX(atof(coordenada.c_str()));
           //obtener coordena Y
           coordenada =  info.SubString(info.Pos(" "),MAX_VAL);
           nodosImput[numNodosOrig].setY(atof(coordenada.c_str()));
           //coloco en el Punto la ubicacion dentro del arreglo
           nodosImput[numNodosOrig].setUbicacion(numNodosOrig);

           this->numNodosOrig++;
       }
   
}
//---------------------------------------------------------------------------
unsigned int Perturbacion::getNumNodos(){ return numNodos;}
//---------------------------------------------------------------------------
float Perturbacion::getLargoBoundingBox(){ return largoBoundingBox;}
//---------------------------------------------------------------------------
unsigned int Perturbacion::getLargoEnclosingBox(){return largoEnclosingBox;}
//---------------------------------------------------------------------------
Punto *Perturbacion::getPerturbacion(){ return nodosImput;}
//---------------------------------------------------------------------------
bool Perturbacion::nodos(int x1,int x2,int y1,int y2){
   int aux=0;
   int finx;
   int finy;

   if ((x1>this->largoBoundingBox) || (y1>this->largoBoundingBox))
        return false;

   for (unsigned int i=0; i<numNodos; i++)
        if ((((int)nodosImput[i].getX()>x1) && ((int)nodosImput[i].getX()<x2)) && (((int)nodosImput[i].getY()>y1) && ((int)nodosImput[i].getY()<y2)))
        {      aux++;
               if (aux>1)
                return true;
        };

   return false;

}
//---------------------------------------------------------------------------
PuntoExtendido *Perturbacion::getNodo(int x1,int x2,int y1,int y2){
 if ((x1>this->largoBoundingBox) || (y1>this->largoBoundingBox))
      return NULL;

  for (unsigned int i=0; i<numNodos; i++)
        if ((((int)nodosImput[i].getX()>x1) && ((int)nodosImput[i].getX()<x2)) && (((int)nodosImput[i].getY()>y1) && ((int)nodosImput[i].getY()<y2)))
              return &nodosImput[i];
  return NULL;
}
//---------------------------------------------------------------------------
void Perturbacion::copyImput(){
  nodosOriginales= new PuntoExtendido*[numNodosOrig];
  float x = MAXFLOAT;
  float y = MAXFLOAT;
  for (unsigned int i=0; i<numNodosOrig; i++) {
        nodosOriginales[i]=new PuntoExtendido(nodosImput[i].getX(),nodosImput[i].getY(),nodosImput[i].getUbicacion());
        if (nodosImput[i].getX() < x)
                x = nodosImput[i].getX();
        if (nodosImput[i].getY() < y)
                y = nodosImput[i].getY();
  }
  for (unsigned int i=0; i<numNodosOrig; i++) {
        nodosOriginales[i]->setX(nodosOriginales[i]->getX()-x);
        nodosOriginales[i]->setY(nodosOriginales[i]->getY()-y);
  }
}
//---------------------------------------------------------------------------
//retorna la mínima distancia entre dos nodos en sus coordenadas Y
float Perturbacion::getMinY(){
  float minY_1 = nodosOriginales[0]->getY();
  float minY_2 = nodosOriginales[0]->getY();


  //busco el menor Y
  for (unsigned int i=1; i<numNodosOrig; i++)
        if (nodosOriginales[i]->getY() < minY_1)
            minY_1 = nodosOriginales[i]->getY();

  //busco el menor Y mayor que el anterior
  for (unsigned int i=1; i<numNodosOrig; i++)
        if ((nodosOriginales[i]->getY() < minY_2) && (nodosOriginales[i]->getY() > minY_1))
            minY_2 = nodosOriginales[i]->getY();

  if ( minY_2 - minY_1 == 0 )
        return MIN_X_DEF;

  return minY_2 - minY_1;

}
//retorna la mínima distancia entre dos nodos en sus coordenadas X
float Perturbacion::getMinX(){
  float minX_1 = nodosOriginales[0]->getX();
  float minX_2 = nodosOriginales[0]->getX();


  //busco el menor Y
  for (unsigned int i=1; i<numNodosOrig; i++)
        if (nodosOriginales[i]->getX() < minX_1)
            minX_1 = nodosOriginales[i]->getX();

  //busco el menor Y mayor que el anterior
  for (unsigned int i=1; i<numNodosOrig; i++)
        if ((nodosOriginales[i]->getX() < minX_2) && (nodosOriginales[i]->getX() > minX_1))
            minX_2 = nodosOriginales[i]->getX();

  if ( minX_2 - minX_1 == 0 )
        return MIN_X_DEF;

  return minX_2 - minX_1;

}
//---------------------------------------------------------------------------



#pragma package(smart_init)
