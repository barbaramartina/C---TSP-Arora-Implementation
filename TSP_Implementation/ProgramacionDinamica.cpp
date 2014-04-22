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

#include "ProgramacionDinamica.h"

//---------------------------------------------------------------------------
ProgramacionDinamica::ProgramacionDinamica(QuadTreeTSP *quadt){
  quad=quadt;
  quadtr=quad->getArreglo();
  matriz=new MatrizVariable<SubSolucion>(quad->getCantCuadrantes());
}
//---------------------------------------------------------------------------
ProgramacionDinamica::~ProgramacionDinamica(){ delete( matriz);};
//---------------------------------------------------------------------------
void ProgramacionDinamica::execute(){
  //construye las soluciones de las hojas
  makeHojas();

  unsigned int maxLevel=quad->getMaxLevelOcupado();
  //construye las soluciones en todos los demas niveles
  for (unsigned int level=maxLevel-1 ; level>0; level--)     //no se consideran ni el cero ni el maxLevel
      makeSolucionLevel(level);

  //construye la Solucion (NIVEL 0)
  makeSolucion();

}
//---------------------------------------------------------------------------
void ProgramacionDinamica::makeHojas(){
   Lista<Cuadrante> *hojas=quad->getHojas();
   unsigned int cantPortales,apareos,iReal;
   float dist1,dist2;
   Punto *apar1,*apar2,*nodo;
   SubSolucion *sb;
   apar1=NULL;
   apar2=NULL;
   nodo=NULL;

   //resuelvo el problema para cada una de las hojas

   for (Cuadrante *c=hojas->primero(); c!=NULL; c=hojas->siguiente()){
      //inicializando el tamaño de la columna correspondiente a la hoja
      iReal=c->getIndiceReal();
      cantPortales=c->getCantPortales();
      apareos=(cantPortales*(cantPortales-1));
      matriz->inicColumna(iReal,apareos);
      for (unsigned int i=0; i<apareos; i++){
         sb=new SubSolucion();
         c->getApareo(i,apar1,apar2);
         nodo=c->getNodoIn();
         if (nodo!=NULL){
            dist1=nodo->distancia_Total_a(apar1);
            dist2=nodo->distancia_Total_a(apar2);
            sb->setDistancia(dist1+dist2);
         }
         else{
            dist1=apar1->distancia_Total_a(apar2);
            sb->setDistancia(dist1);
         };

         matriz->set(sb,iReal,i);
      };
   };

}
//---------------------------------------------------------------------------
void ProgramacionDinamica::makeSolucionLevel(unsigned int level){
    unsigned int primerIndice=quad->getIndexCLevel(level); //primer cuadrante de ese nivel
    unsigned int ultimoIndice=quad->getIndexCLevel(level+1); //primer cuadrante del nivel proximo

    unsigned int cantPortales,apareos,iReal,hijo1,hijo2;
    float dist1,dist2,distMin,distActual;
    Punto *apar1,*apar2;
    SubSolucion *sb;
    apar1=NULL;
    apar2=NULL;

    //para cada Cuadrante del nivel dado             
    for (unsigned int ind=primerIndice; ind<ultimoIndice; ind++ ){
      if ((quadtr[ind]!=NULL) && (quadtr[ind]->hijos())){
        cantPortales=quadtr[ind]->getCantPortales();
        apareos=(cantPortales*(cantPortales-1));
        iReal=quadtr[ind]->getIndiceReal();
        matriz->inicColumna(iReal,apareos);
        //para cada uno de sus apareos
        for (unsigned int apareo=0; apareo<apareos; apareo++) {
            sb=new SubSolucion();
            distMin=MAXFLOAT;
            distActual=0;
            quadtr[ind]->getApareo(apareo,apar1,apar2);
            //obtengo los hijos que comparten los portales
            hijo1=quad->hijoQueCompartePortal(apar1,ind);  //hijo que comparte el portal de comienzo
            hijo2=quad->hijoQueCompartePortal(apar2,ind);  //hijo que comparte el portal de fin
            Lista<Punto> *portCompartidosI=NULL;
            Lista<Punto> *portCompartidosII=NULL;
            Lista<Punto> *portCompartidosIII=NULL;
            Lista<Punto> *portCompartidosIV=NULL;

            unsigned int aparI,aparII,aparIII,aparIV,aparV,aparMinI,aparMinII,aparMinIII,aparMinIV,aparMinV;

            
            if (hijo1!=hijo2){         //si los portales no pertenecen al mismo hijo
                //averiguo si los demas hijos poseen nodos o no, o cual de ellos posee
                int cualConNodos=quad->elRestoSinNodos(ind,hijo1,hijo2);

                //tengo en cuenta los casos posibles a presentarse
                if (quad->adyacentes(hijo1,hijo2)){
                      if (cualConNodos==NINGUNO) {     //ninguno de los otros hijos poseen nodos
                            portCompartidosI=quad->getPortalesCompartidos(hijo1,hijo2);

                            unsigned int numHijo=quad->getNumeroDeHijo(hijo1);

                            //recorro cada uno de los portales que comparten los hijos
                            for (Punto *paux=portCompartidosI->primero(); paux!=NULL; paux=portCompartidosI->siguiente()){
                                //obtengo los numeros de apareamientos
                                aparI=quadtr[hijo1]->getNumApareo(apar1,paux);
                                aparII=quadtr[hijo2]->getNumApareo(paux,apar2);
                                distActual=matriz->get(quadtr[hijo1]->getIndiceReal(),aparI)->getDistancia()+matriz->get(quadtr[hijo2
                                ]->getIndiceReal(),aparII)->getDistancia();

                                //comparo con los datos minimos anteriores
                                if (distActual<distMin) {
                                        distMin=distActual;
                                        aparMinI=aparI;
                                        aparMinII=aparII;
                                };
                            };

                            //seteo de la matriz con la min distancia obtenida
                            sb->addHijo(hijo1);
                            sb->addHijo(hijo2);
                            sb->addApareo(aparMinI);
                            sb->addApareo(aparMinII);
                            sb->setDistancia(distMin);
                            matriz->set(sb,iReal,apareo);

                      } //fin del if cualConNodos==NINGUNO
                      else{ //si los otros poseen nodos o uno de ellos posee
                            unsigned int hijo3,hijo4;
                            hijo3=quad->getAdyacenteDistintoDe(ind,hijo2);
                            hijo4=quad->getAdyacenteDistintoDe(ind,hijo1);

                            portCompartidosI=quad->getPortalesCompartidos(hijo1,hijo3);
                            portCompartidosII=quad->getPortalesCompartidos(hijo3,hijo4);
                            portCompartidosIII=quad->getPortalesCompartidos(hijo4,hijo2);

                            unsigned int numHijo=quad->getNumeroDeHijo(hijo1);
                            unsigned int numHijo2=quad->getNumeroDeHijo(hijo2);


                            for (Punto *p1=portCompartidosI->primero(); p1!=NULL; p1=portCompartidosI->siguiente()) {
                              aparI=quadtr[hijo1]->getNumApareo(apar1,p1);

                              for (Punto *p2=portCompartidosII->primero(); p2!=NULL; p2=portCompartidosII->siguiente()){
                                aparII=quadtr[hijo3]->getNumApareo(p1,p2);

                                for (Punto *p3=portCompartidosIII->primero(); p3!=NULL; p3=portCompartidosIII->siguiente()){
                                  aparIII=quadtr[hijo4]->getNumApareo(p2,p3);

                                  aparIV=quadtr[hijo2]->getNumApareo(p3,apar2);

                                   //comparo con los datos minimos anteriores
                                   distActual=matriz->get(quadtr[hijo1]->getIndiceReal(),aparI)->getDistancia()+matriz->get(quadtr[hijo2]->getIndiceReal(),aparIV)->getDistancia()+matriz->get(quadtr[hijo4]->getIndiceReal(),aparIII)->getDistancia()+matriz->get(quadtr[hijo3]->getIndiceReal(),aparII)->getDistancia();
                                   if (distActual<distMin){
                                        distMin=distActual;
                                        aparMinI=aparI;
                                        aparMinII=aparII;
                                        aparMinIII=aparIII;
                                        aparMinIV=aparIV;
                                   };
                                };
                              };
                            };
                            //seteo los datos minimos encontrados en la matriz
                            sb->addHijo(hijo1);
                            sb->addHijo(hijo3);
                            sb->addHijo(hijo4);
                            sb->addHijo(hijo2);
                            sb->addApareo(aparMinI);
                            sb->addApareo(aparMinII);
                            sb->addApareo(aparMinIII);
                            sb->addApareo(aparMinIV);
                            sb->setDistancia(distMin);
                            matriz->set(sb,iReal,apareo);


                      };//fin del else cual sin nodos

                }//fin del if adyacentes(hijo1,hijo2)
                else{ //Los Hijos Estan Cruzados
                    //si los demas hijos excepto h1 y h2, no poseen nodos ninguno de ellos
                    //habra que elegir un camino que pase por cualquiera de los otros hijos
                    if (cualConNodos==NINGUNO){
                            unsigned int hijo3;
                            hijo3=quad->getAdyacenteDe(hijo1);
                            portCompartidosI=quad->getPortalesCompartidos(hijo1,hijo3);
                            portCompartidosII=quad->getPortalesCompartidos(hijo3,hijo2);

                            unsigned int numHijo=quad->getNumeroDeHijo(hijo1);

                            for (Punto *p1=portCompartidosI->primero(); p1!=NULL; p1=portCompartidosI->siguiente()){
                               aparI=quadtr[hijo1]->getNumApareo(apar1,p1);

                               for (Punto *p2=portCompartidosII->primero(); p2!=NULL; p2=portCompartidosII->siguiente()){
                                    aparII=quadtr[hijo3]->getNumApareo(p1,p2);

                                    aparIII=quadtr[hijo2]->getNumApareo(p2,apar2);


                                    distActual=matriz->get(quadtr[hijo1]->getIndiceReal(),aparI)->getDistancia()+matriz->get(quadtr[hijo3]->getIndiceReal(),aparII)->getDistancia()+matriz->get(quadtr[hijo2]->getIndiceReal(),aparIII)->getDistancia();
                                    //comparo con los datos minimos anteriores
                                   if (distActual<distMin){
                                        distMin=distActual;
                                        aparMinI=aparI;
                                        aparMinII=aparII;
                                        aparMinIII=aparIII;
                                   };
                                 };
                            };

                            //seteo datos minimos en la matriz
                            sb->addHijo(hijo1);
                            sb->addHijo(hijo3);
                            sb->addHijo(hijo2);
                            sb->addApareo(aparMinI);
                            sb->addApareo(aparMinII);
                            sb->addApareo(aparMinIII);
                            sb->setDistancia(distMin);
                            matriz->set(sb,iReal,apareo);



                    } //fin del if cualConNodos==NINGUNO  //Los Hijos Estan Cruzados
                    else{
                        if (cualConNodos==AMBOS){ //si los otros dos hijos  poseen nodos
                                        unsigned int hijo3,hijo4,numHijo;

                                        numHijo=quad->getNumeroDeHijo(hijo1);
                                        if (numHijo==3){
                                            hijo3=hijo1-2;    //corresponde al hijo 1
                                            hijo4=hijo1+1;    //corresponde al hijo 4
                                        };
                                        //agregado

                                        if (numHijo==1) {
                                            hijo3=hijo1+2;    //corresponde al hijo 3
                                            hijo4=hijo1+1;    //corresponde al hijo 2
                                        };

                                        if (numHijo==2) {
                                              hijo3=hijo1-1;    //corresponde al hijo 1
                                              hijo4=hijo1+2;    //corresponde al hijo 4
                                        };

                                        if (numHijo==4) {
                                              hijo3=hijo1-1;    //corresponde al hijo 2
                                              hijo4=hijo1-2;    //corresponde al hijo 3
                                        };
                                        //agregado


                                        portCompartidosI=quad->getPortalesCompartidos(hijo1,hijo3);
                                        portCompartidosII=quad->getPortalesCompartidos(hijo3,hijo2);
                                        portCompartidosIII=quad->getPortalesCompartidos(hijo1,hijo4);
                                        portCompartidosIV=quad->getPortalesCompartidos(hijo4,hijo2);




                                        for (Punto *p1=portCompartidosI->primero(); p1!=NULL; p1=portCompartidosI->siguiente()){
                                          aparI=quadtr[hijo1]->getNumApareo(apar1,p1);

                                          for (Punto *p2=portCompartidosII->primero(); p2!=NULL; p2=portCompartidosII->siguiente()){
                                              aparII=quadtr[hijo3]->getNumApareo(p1,p2);

                                              aparIII=quadtr[hijo2]->getNumApareo(p2,apar2);

                                              distActual=matriz->get(quadtr[hijo1]->getIndiceReal(),aparI)->getDistancia()+matriz->get(quadtr[hijo3]->getIndiceReal(),aparII)->getDistancia()+matriz->get(quadtr[hijo2]->getIndiceReal(),aparIII)->getDistancia();
                                              //comparo con los datos minimos anteriores
                                              if (distActual<distMin){
                                                  distMin=distActual;
                                                  aparMinI=aparI;
                                                  aparMinII=aparII;
                                                  aparMinIII=aparIII;
                                              };
                                         };
                                        };


                                        float distMin2,distActual2;
                                        unsigned int aparMinV,aparMinVI,aparV,aparVI;
                                        distMin2=MAXFLOAT;
                                        distActual2=0;
                                        for (Punto *p1=portCompartidosIII->primero(); p1!=NULL; p1=portCompartidosIII->siguiente()){
                                           distActual2=apar1->distancia_Total_a(p1);
                                           aparIV=quadtr[hijo1]->getNumApareo(apar1,p1);
                                           for (Punto *p2=portCompartidosIV->primero(); p2!=NULL; p2=portCompartidosIV->siguiente()){
                                                aparV=quadtr[hijo4]->getNumApareo(p1,p2);
                                                aparVI=quadtr[hijo2]->getNumApareo(p2,apar2);

                                                distActual2+=p2->distancia_Total_a(apar2)+matriz->get(quadtr[hijo4]->getIndiceReal(),aparV)->getDistancia();

                                                if (distActual2<distMin2){
                                                   distMin2=distActual;
                                                   aparMinIV=aparIV;
                                                   aparMinV=aparV;
                                                   aparMinVI=aparVI;

                                                };
                                           };
                                        };

                                        distMin+=distMin2;

                                        //seteo los datos minimos encontrados en la matriz
                                        sb->addHijo(hijo1);
                                        sb->addHijo(hijo3);
                                        sb->addHijo(hijo2);
                                        sb->addHijo(hijo1);
                                        sb->addHijo(hijo4);
                                        sb->addHijo(hijo2);
                                        sb->addApareo(aparMinI);
                                        sb->addApareo(aparMinII);
                                        sb->addApareo(aparMinIII);
                                        sb->addApareo(aparMinIV);
                                        sb->addApareo(aparMinV);
                                        sb->addApareo(aparMinVI);
                                        sb->setDistancia(distMin);
                                        matriz->set(sb,iReal,apareo);

                        } //fin del if (cualConNodos==AMBOS)  //Los Hijos Estan Cruzados
                        else{ //si solo uno de los otros hijos posee nodos
                                        portCompartidosI=quad->getPortalesCompartidos(hijo1,cualConNodos);
                                        portCompartidosII=quad->getPortalesCompartidos(cualConNodos,hijo2);

                                        unsigned int numHijo1=quad->getNumeroDeHijo(hijo1);
                                        unsigned int numHijo2=quad->getNumeroDeHijo(cualConNodos);


                                        for (Punto *p1=portCompartidosI->primero(); p1!=NULL; p1=portCompartidosI->siguiente()){
                                           aparI=quadtr[hijo1]->getNumApareo(apar1,p1);

                                           for (Punto *p2=portCompartidosII->primero(); p2!=NULL; p2=portCompartidosII->siguiente()){
                                              aparII=quadtr[cualConNodos]->getNumApareo(p1,p2);

                                              aparIII=quadtr[hijo2]->getNumApareo(p2,apar2);

                                              distActual=matriz->get(quadtr[hijo1]->getIndiceReal(),aparI)->getDistancia()+matriz->get(quadtr[cualConNodos]->getIndiceReal(),aparII)->getDistancia()+matriz->get(quadtr[hijo2]->getIndiceReal(),aparIII)->getDistancia();
                                                //comparo con los datos minimos anteriores
                                               if (distActual<distMin){
                                                    distMin=distActual;
                                                    aparMinI=aparI;
                                                    aparMinII=aparII;
                                                    aparMinIII=aparIII;
                                               };
                                             };
                                        };

                                        //seteo datos minimos en la matriz
                                        sb->addHijo(hijo1);
                                        sb->addHijo(cualConNodos);
                                        sb->addHijo(hijo2);
                                        sb->addApareo(aparMinI);
                                        sb->addApareo(aparMinII);
                                        sb->addApareo(aparMinIII);
                                        sb->setDistancia(distMin);
                                        matriz->set(sb,iReal,apareo);
                        };//fin del else (cualConNodos==AMBOS)
                    };//fin del else cualConNodos==NINGUNO

                };//fin del else adyacentes(hijo1,hijo2)


            } //fin del if  hijo1!=hijo2
            else{    //la subsolucion se construye para portales de comienzo y fin en el mismo hijo
                unsigned int hijo3,hijo4,numHijo;

                numHijo=quad->getNumeroDeHijo(hijo1);
                if (numHijo==1){      //camino a recorrer 1-3-4-2-1
                    hijo2=hijo1+2;    //corresponde al hijo 3
                    hijo3=hijo1+3;    //corresponde al hijo 4
                    hijo4=hijo1+1;    //corresponde al hijo 2
                };

                if (numHijo==2){      //camino a recorrer 2-1-3-4-2
                    hijo2=hijo1-1;    //corresponde al hijo 1
                    hijo3=hijo1+1;    //corresponde al hijo 3
                    hijo4=hijo1+2;    //corresponde al hijo 4
                };

                if (numHijo==3) {     //camino a recorrer 3-4-2-1-3
                    hijo2=hijo1+1;    //corresponde al hijo 4
                    hijo3=hijo1-1;    //corresponde al hijo 2
                    hijo4=hijo1-2;    //corresponde al hijo 1
                };

                if (numHijo==4) {    //camino a recorrer 4-2-1-3-4
                   hijo2=hijo1-2;    //corresponde al hijo 2
                   hijo3=hijo1-3;    //corresponde al hijo 1
                   hijo4=hijo1-1;    //corresponde al hijo 3
                };


                portCompartidosI=quad->getPortalesCompartidos(hijo1,hijo2);
                portCompartidosII=quad->getPortalesCompartidos(hijo2,hijo3);
                portCompartidosIII=quad->getPortalesCompartidos(hijo3,hijo4);
                portCompartidosIV=quad->getPortalesCompartidos(hijo4,hijo1);




                for (Punto *p1=portCompartidosI->primero(); p1!=NULL; p1=portCompartidosI->siguiente()){
                  aparI=quadtr[hijo1]->getNumApareo(apar1,p1);

                  for (Punto *p2=portCompartidosII->primero(); p2!=NULL; p2=portCompartidosII->siguiente()){
                      aparII=quadtr[hijo2]->getNumApareo(p1,p2);


                      for (Punto *p3=portCompartidosIII->primero(); p3!=NULL; p3=portCompartidosIII->siguiente()){
                            aparIII=quadtr[hijo3]->getNumApareo(p2,p3);

                            for (Punto *p4=portCompartidosIV->primero(); p4!=NULL; p4=portCompartidosIV->siguiente()){
                                  aparIV=quadtr[hijo4]->getNumApareo(p3,p4);

                                  aparV=quadtr[hijo1]->getNumApareo(p4,apar2);

                                  distActual=apar2->distancia_Total_a(p4)+matriz->get(quadtr[hijo1]->getIndiceReal(),aparI)->getDistancia()+matriz->get(quadtr[hijo2]->getIndiceReal(),aparII)->getDistancia()+matriz->get(quadtr[hijo3]->getIndiceReal(),aparIII)->getDistancia()+matriz->get(quadtr[hijo4]->getIndiceReal(),aparIV)->getDistancia();

                                  //comparo con los datos minimos anteriores
                                  if (distActual<distMin){
                                      distMin=distActual;
                                      aparMinI=aparI;
                                      aparMinII=aparII;
                                      aparMinIII=aparIII;
                                      aparMinIV=aparIV;
                                      aparMinV=aparV;
                                  };
                            };
                      };
                 };
                };


                //seteo los datos minimos encontrados en la matriz
                sb->addHijo(hijo1);
                sb->addHijo(hijo2);
                sb->addHijo(hijo3);
                sb->addHijo(hijo4);
                sb->addHijo(hijo1);
                sb->addApareo(aparMinI);
                sb->addApareo(aparMinII);
                sb->addApareo(aparMinIII);
                sb->addApareo(aparMinIV);
                sb->addApareo(aparMinV);
                sb->setDistancia(distMin);
                matriz->set(sb,iReal,apareo);

            };//fin del else hijo1!=hijo2
        };//fin del for de apareo
      }; //fin del if (ind es padre)
    }; //fin del for de ind
}
//---------------------------------------------------------------------------
void ProgramacionDinamica::makeSolucion(){
    SubSolucion *sb=new SubSolucion();

    float distMin1,distMin2,distActual1,distActual2;
    distMin1=MAXFLOAT;
    distMin2=MAXFLOAT;
    distActual1=0;
    distActual2=0;

    unsigned int aparMinI,aparMinII,aparMinIII,aparMinIV;

    Lista<Punto> *portCompartidosI,*portCompartidosII,*portCompartidosIII,*portCompartidosIV;
    portCompartidosI=NULL;
    portCompartidosII=NULL;
    portCompartidosIII=NULL;
    portCompartidosIV=NULL;

    portCompartidosI=quad->getPortalesCompartidos(1,2);
    portCompartidosII=quad->getPortalesCompartidos(4,2);
    portCompartidosIII=quad->getPortalesCompartidos(1,3);
    portCompartidosIV=quad->getPortalesCompartidos(3,4);

    for (Punto *p1=portCompartidosIII->primero(); p1!=NULL; p1=portCompartidosIII->siguiente()){
       for (Punto *p3=portCompartidosII->primero(); p3!=NULL; p3=portCompartidosII->siguiente()){
          for (Punto *p2=portCompartidosI->primero(); p2!=NULL; p2=portCompartidosI->siguiente()){
               unsigned int apareo1,apareo2;
               apareo1=quadtr[1]->getNumApareo(p1,p2);
               apareo2=quadtr[2]->getNumApareo(p2,p3);

               distActual1=matriz->get(quadtr[1]->getIndiceReal(),apareo1)->getDistancia()+matriz->get(quadtr[2]->getIndiceReal(),apareo2)->getDistancia();

               if (distActual1<distMin1){
                  distMin1=distActual1;
                  aparMinI=apareo1;
                  aparMinII=apareo2;
               };
          };

          for (Punto *p4=portCompartidosIV->primero(); p4!=NULL; p4=portCompartidosIV->siguiente()){
               unsigned int apareo3,apareo4;
               apareo3=quadtr[3]->getNumApareo(p1,p4);
               apareo4=quadtr[4]->getNumApareo(p3,p4);

               distActual2=matriz->get(quadtr[3]->getIndiceReal(),apareo3)->getDistancia()+matriz->get(quadtr[4]->getIndiceReal(),apareo4)->getDistancia();

               if (distActual2<distMin2){
                  distMin2=distActual2;
                  aparMinIII=apareo3;
                  aparMinIV=apareo4;
               };
          };
       };
    };

    matriz->inicColumna(0,1);
    //seteo los datos minimos encontrados en la matriz
    sb->addHijo(1);
    sb->addHijo(2);
    sb->addHijo(3);
    sb->addHijo(4);
    sb->addApareo(aparMinI);
    sb->addApareo(aparMinII);
    sb->addApareo(aparMinIII);
    sb->addApareo(aparMinIV);
    sb->setDistancia(distMin1+distMin2);
    matriz->set(sb,0,0);


}
//---------------------------------------------------------------------------
SubSolucion *ProgramacionDinamica::getSubSolucion(unsigned int fila,unsigned int col){
  return matriz->get(fila,col);
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
