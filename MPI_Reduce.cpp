#include <stdio.h>
#include "mpi.h"
double f_x(double x)
{
	return (4.0/(1.0 + x*x));
}
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int rank,size,N;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0){
    	printf("pls give N=\n");
    	scanf("%d",&N);
    }
    MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
    double h = 1.0/(double)N;
    int num_pre_proc = (N+size)/size;//向上求整
    double sum = 0, pi;
    for (int i = rank; i < N; i += size){
    	sum += f_x((i+0.5)/N);
    }
    sum *= h;
    printf("\nprocess %d ,sum %f\n",rank, sum);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
    	printf("pi is %.16f\n", pi);
    }

    MPI_Finalize();

	return 0;
}
