#include <stdio.h>
#include "mpi.h"
//int MPI_Gather(void* sendbuf, int sendcount, MPI_Datatype sendtype,
//    void* recvbuf, int recvcount, MPI_Datatype recvtype,
//    int root, MPI_Comm comm)
/*
root进程从其他进程收集数据函数
IN sendbuf 发送消息缓冲区的起始地址(可选数据类型)
IN sendcount 发送消息缓冲区中的数据个数(整型)
IN sendtype 发送消息缓冲区中的数据类型(句柄)
OUT recvbuf 接收消息缓冲区的起始地址(可选数据类型)
IN recvcount 待接收的元素个数(整型,仅对于根进程有意义)
IN recvtype 接收元素的数据类型(句柄,仅对于根进程有意义)
IN root 接收进程的序列号(整型)
IN comm 通信域(句柄)
*/

//int MPI_Gatherv(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf,
//     int *recvcounts, int *displs, MPI_Datatype recvtype, int root, MPI_Comm comm)
/*
本函数与MPI_Gather基本相同，只不过MPI_Gatherv函数支持从不同进程读取不同的数据个数，第5个参数是个数组，最终的结果放入recvbuf中，偏移的位置由displs数据来指定偏移，recvbuf的内容可以是不连续的
*/
int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);
	int gsize,sendarray[100];
	int root,*rbuf,stride=200;
	int *displs, i, *rcounts;
	MPI_Comm_size(MPI_COMM_WORLD, &gsize);
    rbuf = (int*)malloc(gsize*stride*sizeof(int));
	displs = (int*)malloc(gsize*sizeof(int));
	rcounts = (int*)malloc(gsize*sizeof(int));
	for (int i = 0; i < gsize; ++i)	{
		displs[i]  = i*stride;
		rcounts[i] = 100;
	}

	MPI_Gatherv(sendarray, 100, MPI_INT, rbuf, rcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Finalize();

	return 0;
}
