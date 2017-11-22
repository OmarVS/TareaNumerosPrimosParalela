#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

bool esPrimo(int valor)
{
  int maximo=sqrt(valor)+1;
  if (valor==2) return true;
  for(int i=2;i<=maximo;i++)
    if(valor%i==0) return false;
  return true;
}

int main(int argc, char* argv[]){
  if(argc < 2)
    cout<<"Ingrese un numero"<<endl;
  else{
    int valor = atoi(argv[1]);
    if (valor<=1) cout<<"No existen numeros primos hasta "<<valor<<endl;
    else{
      cout<<"Los numeros primos hasta "<<valor<<" son:"<<endl;
      for(int i=2;i<=valor;i++)
        if (esPrimo(i))
          //cout<<i<<endl; //Separados por salto de linea
          cout<<i<<", "; //Separados por coma
    }
  }
}
