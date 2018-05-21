#include<iostream>
#include<math.h>

//Parámetros constantes del modelo
const double c = 1.0;
const double gk = 36.0;
const double gna = 120.0;
const double gl = 0.3; 
const double vk= 12;
const double vna= 115;
const double vl= 10.6;

//Constantes temporales y de tamaño del vector
const int N = 4;                                //Tamaño del vector
const double TF = 2000;                           //Tiempo final
const double dt = 0.01;                         //Tamaño de paso

double ci(double *y, double v);
double fd(double *y2, double *y1);
double sp(double *y2, double *y1);
double an(double *y);
double am(double *y);
double ah(double *y);
double bn(double *y);
double bm(double *y);
double bh(double *y);

int main(){
  double v = 0;
  double y1[N]={0.0};
  ci(y1,v);
  double y2[N]={0.0};
  double time = 0.0;
  for(int i=0;i<=TF;i++){
  fd(y2,y1);
  sp(y2,y1);
  time = time + dt;
  std::cout<<time<<'\t'<<y1[0]<<std::endl;
  }

  
  return 0;
}

double ci(double *y, double v){
  y[0]= v;
  y[1]= an(y)/(an(y)+bn(y));
  y[2]= am(y)/(am(y)+bm(y));
  y[3]= ah(y)/(ah(y)+bh(y));

  //   std::cout<<y[0]<<'\t'<<y[1]<<'\t'<<y[2]<<'\t'<<y[3]<<std::endl;
}

double fd(double *y2, double *y1){
  y2[0]= -gk*pow(y1[1],4)*(y1[0]-vk)-gna*pow(y1[2],3)*y1[3]*(y1[0]-vna)-gl*(y1[0]-vl);
  y2[1]= an(y1)*(1.0-y1[1])-bn(y1)*y1[1];
  y2[2]= am(y1)*(1.0-y1[2])-bm(y1)*y1[2];
  y2[3]= ah(y1)*(1.0-y1[3])-bn(y1)*y1[3];
  }
double sp(double *y2, double *y1){
  for(int i=0; i<N;i++){
    y1[i] = y1[i]+dt*y2[i]; 
  } 
}


double an(double *y){
  return 0.01*(y[0]+10.0)/(exp(1.0+(y[0]/10.0))-1.0);
}
double am(double *y){
  return 0.01*(y[0]+25.0)/(exp(2.5+(y[0]/10.0))-1.0);
}
double ah(double *y){
  return 0.07*exp(y[0]/70.0);
}
double bn(double *y){
  return 0.125*exp(y[0]/80.0);
}
double bm(double *y){
  return 4.0*exp(y[0]/18.0);
}
double bh(double *y){
  return 1.0/(exp(3.0+(y[0]/10.0))+1.0);
}
