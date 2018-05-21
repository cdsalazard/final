#include<iostream>
#include<math.h>
#include<vector>

//Parámetros constantes del modelo
const double c = 1.0;
const double gk = 36.0;
const double gna = 120.0;
const double gl = 0.3; 
const double vk= 12;
const double vna= 115;
const double vl= 10.6;

//Constantes temporales y de tamaño del vector
const int N = 4; //Tamaño del vector
const double TF = 20;
const double dt = 0.01;
//Funciones principales: Funcion voltaje y funciones compuerta
void time_step(const double &dt,std::vector<double>& y,const double &t);
void print(const double &time, const std::vector<double> &y);
double f(const double & time,const std::vector<double> &y,int idx);
void condiciones_iniciales(std::vector<double> & y, double v);

//Funciones no lineales dependedientes del voltaje, en está parte ayudan a determinar las condiciones iniciales.
double an(std::vector<double> & y);
double am(std::vector<double> & y);
double ah(std::vector<double> & y);
double bn(std::vector<double> & y);
double bm(std::vector<double> & y);
double bh(std::vector<double> & y);


int main (){
  
  double v = 0;  
  std::vector<double> y(N);
  
  double time=0.0;
  condiciones_iniciales(y,v);

  int nsteps=(TF-0.0)/dt;
  
  for (int ii=0;ii<nsteps;++ii){
    time=0.0+ii*dt;
    time_step(dt,y,time);
    print(time,y);
  }
  
  return 0;
}


double an(std::vector<double> & y){
  return 0.01*(y[0]+10.0)/(exp(1+(y[0]/10.0))-1);
}
double am(std::vector<double> & y){
  return 0.01*(y[0]+25.0)/(exp(2.5+(y[0]/10.0))-1);
}
double ah(std::vector<double> & y){
  return 0.07*exp(y[0]/70.0);
}
double bn(std::vector<double> & y){
  return 0.125*exp(y[0]/80);
}
double bm(std::vector<double> & y){
  return 4*exp(y[0]/18);
}
double bh(std::vector<double> & y){
  return 1/(exp(3+(y[0]/10.0))+1);
}

void condiciones_iniciales(std::vector<double> &y, double v)
{
  y[0]= v;
  y[1]= an(y)/(an(y)*bn(y));
  y[2]= am(y)/(am(y)*bm(y));
  y[3]= ah(y)/(ah(y)*bh(y));


  std::cout<<y[0]<<'\t'<<y[1]<<'\t'<<y[2]<<'\t'<<y[3]<<std::endl;
}

double f(const double &time, std::vector<double> &y,int idx)
{
  if(0==idx){
    return -gk*pow(y[1],4)*(y[0]-vk)-gna*pow(y[2],3)*y[3]*(y[0]-vna)-gl*(y[0]-vl) ;
  }
  else if (1==idx)
    {
      return an(y)*(1-y[1])-bn(y)*y[1];
    }
  else if (2==idx)
    {
      return am(y)*(1-y[2])-bm(y)*y[2];
    }
  else if (3==idx)
    {
      return ah(y)*(1-y[3])-bn(y)*y[3];
    }
  
  else{
    std::cerr<<"Error: index not allowed:\n";
   
  }
}


void time_step(const double &dt,std::vector<double>& y,const double &time)
{ std::vector<double> ytmp=y;
  for(int ii=0;ii<y.size();ii++)
    {
      y[ii]+=dt*f(time,ytmp,ii);
    }
}

void print(const double &time, const std::vector<double> &y){
  std::cout<<time<<'\t'<<y[0]<<'\t'<<y[1]<<'\t'<<y[2]<<'\t'<<y[3]<<std::endl;
}
