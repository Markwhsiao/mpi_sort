
//***************************广播************************************
int MPI_Bcast(void* buffer,int count,MPI_Datatype datatype,int root, MPI_Comm comm);
//***************************分发************************************
/*
IN sendbuf 发送消息缓冲区的起始地址(可选数据类型)
IN sendcount 发送到各个进程的数据个数(整型)
IN sendtype 发送消息缓冲区中的数据类型(句柄)
OUT recvbuf 接收消息缓冲区的起始地址(可选数据类型)
IN recvcount 待接收的元素个数(整型)
IN recvtype 接收元素的数据类型(句柄)
IN root 发送进程的序列号(整型)
IN comm 通信域(句柄)
*/
int MPI_Scatter(void* sendbuf, int sendcount, MPI_Datatype sendtype,
                void* recvbuf, int recvcount, MPI_Datatype recvtype,
                int root, MPI_Comm comm);
/*
比MPI_Scatter更灵活，不要求发送到对方的数据个数一致
IN sendbuf 发送消息缓冲区的起始地址(可选数据类型)
IN sendcounts 发送数据的个数整数数组 (整型)
IN displs 发送数据偏移整数数组(整型)
IN sendtype 发送消息缓冲区中元素类型(句柄)
OUT recvbuf 接收消息缓冲区的起始地址(可变)
IN recvcount 接收消息缓冲区中数据的个数(整型)
IN recvtype 接收消息缓冲区中元素的类型(句柄)
IN root 发送进程的标识号(句柄)
IN comm 通信域(句柄)
*/
int MPI_Scatterv(void* sendbuf, int *sendcounts, int *displs, MPI_Datatype sendtype,
                 void* recvbuf, int recvcount, MPI_Datatype recvtype, int root,
                 MPI_Comm comm);




//*************************收集*********************************************
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
int MPI_Gather(void* sendbuf, int sendcount, MPI_Datatype sendtype,
    void* recvbuf, int recvcount, MPI_Datatype recvtype,
    int root, MPI_Comm comm);
/*
本函数与MPI_Gather基本相同，只不过MPI_Gatherv函数支持从不同进程读取不同的数据个数，第5个参数是个数组，最终的结果放入recvbuf中，偏移的位置由displs数据来指定偏移，recvbuf的内容可以是不连续的
*/
int MPI_Gatherv(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf,
                int *recvcounts, int *displs, MPI_Datatype recvtype, int root, MPI_Comm comm);

/*
与MPI_Gather类似，这里是所有进程都当root进程来收集数据,发送方发到其它进程的数据都是相同的
IN sendbuf 发送消息缓冲区的起始地址(可选数据类型)
IN sendcount 发送消息缓冲区中的数据个数(整型)
IN sendtype 发送消息缓冲区中的数据类型(句柄)
OUT recvbuf 接收消息缓冲区的起始地址(可选数据类型)
IN recvcount 从其它进程中接收的数据个数(整型)
IN recvtype 接收消息缓冲区的数据类型(句柄)
IN comm 通信域(句柄)
*/
int MPI_Allgather(void* sendbuf, int sendcount, MPI_Datatype sendtype,
                  void* recvbuf, int recvcount, MPI_Datatype recvtype,
                  MPI_Comm comm);
/*
与MPI_Gatherv类似，所有进程都当root进程来收集数据,发送方发到其它进程的数据都是相同的
IN sendbuf 发送消息缓冲区的起始地址(可选数据类型)
IN sendcount 发送消息缓冲区中的数据个数(整型)
IN sendtype 发送消息缓冲区中的数据类型(句柄)
OUT recvbuf 接收消息缓冲区的起始地址(可选数据类型)
IN recvcounts 接收数据的个数整型数组(整型)
IN displs 接收数据的偏移整数数组(整型)
IN recvtype 接收消息缓冲区的数据类型(句柄)
IN comm 通信域(句柄)
*/
int MPI_Allgatherv(void* sendbuf, int sendcount,MPI_Datatype sendtype,
                   void* recvbuf, int *recvcounts, int *displs, MPI_Datatype recvtype,
                   MPI_Comm comm);


/*
这个函数是全交换函数，发送方发送的数据是sendbuf开始的sendcount*size个数据，
发送到每个进程的数据不一样的;这个要求所有发送方发到每个进程的数据个数都是相同的

IN sendbuf 发送消息缓冲区的起始地址(可选数据类型)
IN sendcount 发送到每个进程的数据个数(整型)
IN sendtype 发送消息缓冲区中的数据类型(句柄)
OUT recvbuf 接收消息缓冲区的起始地址(可选数据类型)
IN recvcount 从每个进程中接收的元素个数(整型)
IN recvtype 接收消息缓冲区的数据类型(句柄)
IN comm 通信域(句柄)
*/
int MPI_Alltoall(void* sendbuf, int sendcount, MPI_Datatype sendtype,
                 void* recvbuf, int recvcount, MPI_Datatype recvtype,
                 MPI_Comm comm);
/*
这个函数比MPI_Alltoall更灵活些，每个进程发送给其他进程的个数都可以不一样。
IN sendbuf 发送消息缓冲区的起始地址(可选数据类型)
IN sendcounts 向每个进程发送的数据个数(整型数组)
IN sdispls 向每个进程发送数据的位移整型数组
IN sendtype 发送数据的数据类型(句柄)
OUT recvbuf 接收消息缓冲区的起始地址(可选数据类型)
IN recvcounts 从每个进程中接收的数据个数(整型数组)
IN rdispls 从每个进程接收的数据在接收缓冲区的位移整型数组
IN recvtype 接收数据的数据类型(句柄)
IN comm 通信域(句柄)
*/
int MPI_Alltoallv(void* sendbuf, int *sendcounts, int *sdispls, MPI_Datatype sendtype,
	              void* recvbuf, int *recvcounts, int *rdispls, MPI_Datatype recvtype,
	              MPI_Comm comm);

//*****************************同步*****************************************
/*
阻塞所有的调用者，直到所有的组成员都调用了它
*/
int MPI_Barrier(MPI_Comm comm);
//****************************归约******************************************
/*

IN sendbuf 发送消息缓冲区的起始地址(可选数据类型)
OUT recvbuf 接收消息缓冲区中的地址(可选数据类型)
IN count 发送消息缓冲区中的数据个数(整型)
IN datatype 发送消息缓冲区的元素类型(句柄)
IN op 归约操作符(句柄),内置的有MPI_SUM,MPI_MAX,MPI_MIN，MPI_LAND, MPI_BAND，MPI_LOR, MPI_BOR
IN root 根进程序列号(整型)
IN comm 通信域(句柄)
*/
int MPI_Reduce(void* sendbuf, void* recvbuf, int count, PI_Datatype datatype,
               MPI_Op op, int root, MPI_Comm comm);
/*
与MPI_Reduce不一样的是，这个是所有进程的recvbuf都会得到归约的结果
IN sendbuf 发送消息缓冲区的起始地址(可选数据类型)
OUT recvbuf 接收消息缓冲区的起始地址(可选数据类型)
IN count 发送消息缓冲区中的数据个数(整型)
IN datatype 发送消息缓冲区中的数据类型(句柄)
IN op 操作(句柄)
IN comm 通信域(句柄)
*/
int MPI_Allreduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype,
                  MPI_Op op, MPI_Comm comm);

/*
这个函数实际上是分组进行归约，将recvbuf 的前recvcounts[0]个元素推送给0号rank，recvcounts[1]个元素推送给1号rank....,每个rank归约的部分结果
IN sendbuf 发送消息缓冲区的起始地址(可选数据类型)
OUT recvbuf 接收消息缓冲区的起始地址(可选数据类型)
IN recvcounts 接收数据个数整型数组
IN datatype 发送缓冲区中的数据类型(句柄)
IN op 操作(句柄)
IN comm 通信域(句柄)
*/
int MPI_Reduce_scatter(void* sendbuf, void* recvbuf, int *recvcounts
                       MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
/*
每个进程的recvbuf都是有效的，第i个进程存放的是0到i进程的sendbuf归约之后的结果，0号进程是它sendbuf结果
IN sendbuf 发送消息缓冲区的起始地址(可选数据类型)
OUT recvbuf 接收消息缓冲区的起始地址(可选数据类型)
IN count 输入缓冲区中元素的个数(整型)
IN datatype 输入缓冲区中元素的类型(句柄)
IN op 操作(句柄)
IN comm 通信域(句柄)
*/
int MPI_Scan(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype,
	         MPI_Op   op, MPI_Comm comm);

/*
MPI_Op_create建立用户函数与op的联系。
*/
int MPI_Op_create(MPI_User_function *function,int commute,MPI_Op *op);
/*
用户自己实现归约函数
foreach i in [0,len)
inoutvec[i] = inoutvec[i] @ invec[i];
@用户实现的功能，以inoutvec[i] 及invec[i]为输入，结果存放在inoutvec[i]
*/
typedef void MPI_User_function(void *invec, void *inoutvec, int *len,
                               MPI_Datatype *datatype);

////////////////////////////////点对点通信/////////////////////////////////
/*
IN buf 发送缓冲区的起始地址(可选数据类型)
IN count 发送数据的个数(整型)
IN datatype 发送数据的数据类型(句柄)
IN dest 目的进程号(整型)
IN tag 消息标志(整型)
IN comm 通信域(句柄)
OUT request 返回的非阻塞通信对象(句柄)
*/
int MPI_Isend(void* buf, int count, MPI_Datatype datatype, int dest, int tag,
MPI_Comm comm, MPI_Request *request);
/*
OUT buf 接收缓冲区的起始地址(可选数据类型)
IN count 接收数据的最大个数(整型)
IN datatype 每个数据的数据类型(句柄)
IN source 源进程标识(整型)
IN tag 消息标志(整型),为了区分同一进程往另一进程发送多次
IN comm 通信域(句柄)
OUT request 非阻塞通信对象(句柄)，代表了一批发送或接收的标签，可以调用MPI_Wait来阻塞这一批发送和接收都完成。
*/
int MPI_Irecv(void* buf, int count, MPI_Datatype datatype, int source, int tag,
MPI_Comm comm, MPI_Request *request);
