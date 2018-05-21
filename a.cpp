#include<iostream>
#include<math.h>


double an(double v);
double am(double v);
double ah(double v);
double bn(double v);
double bm(double v);
double bh(double v);


int main (){

  double v = -120.0;
  double n, m, h;
  for (int i=1; i<=3000; i++){
  
    n = an(v)/(an(v)*bn(v)); 
    m = am(v)/(am(v)*bm(v));
    h = ah(v)/(ah(v)*bh(v));

      std::cout<<v<<'\t'<<n<<'\t'<<m<<'\t'<<h<<std::endl;
  v = v + 0.05;
    
  }
  return 0;
}


double an(double v){
  return 0.01*(v+10.0)/(exp(1+(v/10.0))-1);
}
double am(double v){
  return 0.01*(v+25.0)/(exp(2.5+(v/10.0))-1);
}
double ah(double v){
  return 0.07*exp(v/70.0);
}
double bn(double v){
  return 0.125*exp(v/80);
}
double bm(double v){
  return 4*exp(v/18);
}
double bh(double v){
  return 1/(exp(3+(v/10.0))+1);
}
