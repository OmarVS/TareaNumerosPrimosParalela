 #include <iostream>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

using namespace std;

bool esPrimo(int valor)
{
  int maximo=sqrt(valor)+1;
  if (valor==2) return true;
  for(int i=2;i<=maximo;i++)
    if(valor%i==0) return false;
  return true;
}

int main(int argc, char* argv[])
{
  int         status, my_rank, cant;  /* Valor de retorno, id, cant */
  int limites[2];
  MPI_Status rec_stat; /* Status object*/

  if(argc < 2)
  {
    cout<<"Ingrese un numero"<<endl;
  }
  else
  {
    int valor = atoi(argv[1]);

    
    
      MPI_Init(&argc, &argv); /* Inicio de MPI */
      MPI_Comm_size(MPI_COMM_WORLD, &cant);      /* numero de procesos */
      MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); /* rango de procesos  */

      if(my_rank == 0)
      {
          if (valor<=1)
          {
            cout<<"No existen numeros primos hasta "<<valor<<endl;
          }
          else
          {
          cout<<"Los numeros primos hasta "<<valor<<" son:"<<endl;
          for(int i=0; i<cant; i++)
          {
            limites[0] = ((valor/cant)*i)+2;
            limites[1] = ((valor/cant)*(i+1));
            status = MPI_Send(limites, 2, MPI_INT, i, 0, MPI_COMM_WORLD);
          }
          status = MPI_Recv(limites, 2, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &rec_stat);
          for(int i=limites[0];i<=limites[1];i++)
          {
            if (esPrimo(i))
            {
              cout<<i<<endl;
            }
          }
        }
      }

      else
      {
        status = MPI_Recv(limites, 2, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &rec_stat);
        for(int i=limites[0];i<=limites[1];i++)
        {
          if (esPrimo(i))
          {
            cout<<i<<endl;
          }
        }
      }
      MPI_Finalize();
    
  }
  return 0;
}
