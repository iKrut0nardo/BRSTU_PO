/***********************************************************************
*                                                                      *
*   WMPI - Windows Message Passing Interface                           *
*   http://dsg.dei.uc.pt/wmpi                                          *
*                                                                      *
*   (C) 1999 by Dependable Systems Group                               *
*   CISUC - Centre of Informatics and Systems Research                 *
*   Department of Informatics Engineering                              *
*   University of Coimbra - Portugal                                   *
*                                                                      *
*   This is an MPI implementation for MS Windows                       *
*   It is based on the MPICH implementation from Argonne               *
*   National Laboratory and Mississippi State University,              *
*   version 1.1.2.                                                     *
*                                                                      *
***********************************************************************/

#ifndef __MPI_BINDINGS
#define __MPI_BINDINGS

#include "mpi.h"

//#if defined(__STDC__) || defined(__cplusplus) || defined(HAVE_PROTOTYPES)
__declspec( dllexport ) int MPI_Send(void*, int, MPI_Datatype, int, int, MPI_Comm);
__declspec( dllexport ) int MPI_Recv(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Status *);
#ifdef TRAPPER_ANIMATION
__declspec( dllexport ) int _MPI_Send(void*, int, MPI_Datatype, int, int, MPI_Comm, short, short);
__declspec( dllexport ) int _MPI_Recv(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Status *, short, short);
#endif
__declspec( dllexport ) int MPI_Get_count(MPI_Status *, MPI_Datatype, int *);
__declspec( dllexport ) int MPI_Bsend(void*, int, MPI_Datatype, int, int, MPI_Comm);
__declspec( dllexport ) int MPI_Ssend(void*, int, MPI_Datatype, int, int, MPI_Comm);
__declspec( dllexport ) int MPI_Rsend(void*, int, MPI_Datatype, int, int, MPI_Comm);
#ifdef TRAPPER_ANIMATION
__declspec( dllexport ) int _MPI_Bsend(void*, int, MPI_Datatype, int, int, MPI_Comm, short, short);
__declspec( dllexport ) int _MPI_Ssend(void*, int, MPI_Datatype, int, int, MPI_Comm, short, short);
__declspec( dllexport ) int _MPI_Rsend(void*, int, MPI_Datatype, int, int, MPI_Comm, short, short);
#endif
__declspec( dllexport ) int MPI_Buffer_attach( void*, int);
__declspec( dllexport ) int MPI_Buffer_detach( void*, int*);
__declspec( dllexport ) int MPI_Isend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int MPI_Ibsend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int MPI_Issend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int MPI_Irsend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int MPI_Irecv(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int MPI_Wait(MPI_Request *, MPI_Status *);
#ifdef TRAPPER_ANIMATION
__declspec( dllexport ) int _MPI_Isend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *, short, short);
__declspec( dllexport ) int _MPI_Ibsend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *, short, short);
__declspec( dllexport ) int _MPI_Issend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *, short, short);
__declspec( dllexport ) int _MPI_Irsend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *, short, short);
__declspec( dllexport ) int _MPI_Irecv(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *, short, short);
__declspec( dllexport ) int _MPI_Wait(MPI_Request *, MPI_Status *, short, short);
#endif
__declspec( dllexport ) int MPI_Test(MPI_Request *, int *, MPI_Status *);
__declspec( dllexport ) int MPI_Request_free(MPI_Request *);
__declspec( dllexport ) int MPI_Waitany(int, MPI_Request *, int *, MPI_Status *);
#ifdef TRAPPER_ANIMATION
__declspec( dllexport ) int _MPI_Waitany(int, MPI_Request *, int *, MPI_Status *, short, short);
#endif
__declspec( dllexport ) int MPI_Testany(int, MPI_Request *, int *, int *, MPI_Status *);
__declspec( dllexport ) int MPI_Waitall(int, MPI_Request *, MPI_Status *);
#ifdef TRAPPER_ANIMATION
__declspec( dllexport ) int _MPI_Waitall(int, MPI_Request *, MPI_Status *, short, short);
#endif
__declspec( dllexport ) int MPI_Testall(int, MPI_Request *, int *, MPI_Status *);
__declspec( dllexport ) int MPI_Waitsome(int, MPI_Request *, int *, int *, MPI_Status *);
#ifdef TRAPPER_ANIMATION
__declspec( dllexport ) int _MPI_Waitsome(int, MPI_Request *, int *, int *, MPI_Status *, short, short);
#endif
__declspec( dllexport ) int MPI_Testsome(int, MPI_Request *, int *, int *, MPI_Status *);
__declspec( dllexport ) int MPI_Iprobe(int, int, MPI_Comm, int *flag, MPI_Status *);
__declspec( dllexport ) int MPI_Probe(int, int, MPI_Comm, MPI_Status *);
#ifdef TRAPPER_ANIMATION
__declspec( dllexport ) int _MPI_Probe(int, int, MPI_Comm, MPI_Status *, short, short);
#endif
__declspec( dllexport ) int MPI_Cancel(MPI_Request *);
__declspec( dllexport ) int MPI_Test_cancelled(MPI_Status *, int *flag);
__declspec( dllexport ) int MPI_Send_init(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int MPI_Bsend_init(void*, int, MPI_Datatype, int,int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int MPI_Ssend_init(void*, int, MPI_Datatype, int,int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int MPI_Rsend_init(void*, int, MPI_Datatype, int,int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int MPI_Recv_init(void*, int, MPI_Datatype, int,int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int MPI_Start(MPI_Request *);
__declspec( dllexport ) int MPI_Startall(int, MPI_Request *);
__declspec( dllexport ) int MPI_Sendrecv(void *, int, MPI_Datatype,int, int, void *, int, 
		 MPI_Datatype, int, int, MPI_Comm, MPI_Status *);
__declspec( dllexport ) int MPI_Sendrecv_replace(void*, int, MPI_Datatype, 
			 int, int, int, int, MPI_Comm, MPI_Status *);
__declspec( dllexport ) int MPI_Type_contiguous(int, MPI_Datatype, MPI_Datatype *);
__declspec( dllexport ) int MPI_Type_vector(int, int, int, MPI_Datatype, MPI_Datatype *);
__declspec( dllexport ) int MPI_Type_hvector(int, int, MPI_Aint, MPI_Datatype, MPI_Datatype *);
__declspec( dllexport ) int MPI_Type_indexed(int, int *, int *, MPI_Datatype, MPI_Datatype *);
__declspec( dllexport ) int MPI_Type_hindexed(int, int *, MPI_Aint *, MPI_Datatype, MPI_Datatype *);
__declspec( dllexport ) int MPI_Type_struct(int, int *, MPI_Aint *, MPI_Datatype *, MPI_Datatype *);
__declspec( dllexport ) int MPI_Address(void*, MPI_Aint *);
__declspec( dllexport ) int MPI_Type_extent(MPI_Datatype, MPI_Aint *);

/* See the 1.1 version of the Standard; I think that the standard is in 
   error; however, it is the standard */
/* int MPI_Type_size(MPI_Datatype, MPI_Aint *size); */
__declspec( dllexport ) int MPI_Type_size(MPI_Datatype, int *);
__declspec( dllexport ) int MPI_Type_count(MPI_Datatype, int *);
__declspec( dllexport ) int MPI_Type_lb(MPI_Datatype, MPI_Aint*);
__declspec( dllexport ) int MPI_Type_ub(MPI_Datatype, MPI_Aint*);
__declspec( dllexport ) int MPI_Type_commit(MPI_Datatype *);
__declspec( dllexport ) int MPI_Type_free(MPI_Datatype *);
__declspec( dllexport ) int MPI_Get_elements(MPI_Status *, MPI_Datatype, int *);
__declspec( dllexport ) int MPI_Pack(void* inbuf, int, MPI_Datatype, void *outbuf, 
	     int outsize, int *position,  MPI_Comm);
__declspec( dllexport ) int MPI_Unpack(void* inbuf, int insize, int *position, void *outbuf, 
	       int , MPI_Datatype, MPI_Comm);
__declspec( dllexport ) int MPI_Pack_size(int, MPI_Datatype, MPI_Comm, 
		  int *);
__declspec( dllexport ) int MPI_Barrier(MPI_Comm );

__declspec( dllexport ) int MPI_Bcast(void*fer, int, MPI_Datatype, int root, 
	      MPI_Comm );
__declspec( dllexport ) int MPI_Gather(void* , int, MPI_Datatype, 
	       void*, int, MPI_Datatype, 
	       int root, MPI_Comm); 
__declspec( dllexport ) int MPI_Gatherv(void* , int, MPI_Datatype, 
		void*, int *recvcounts, int *displs, 
		MPI_Datatype, int root, MPI_Comm); 
__declspec( dllexport ) int MPI_Scatter(void* , int, MPI_Datatype, 
		void*, int, MPI_Datatype, 
		int root, MPI_Comm);
__declspec( dllexport ) int MPI_Scatterv(void* , int *sendcounts, int *displs, 
		 MPI_Datatype, void*, int, 
		 MPI_Datatype, int root, MPI_Comm);
__declspec( dllexport ) int MPI_Allgather(void* , int, MPI_Datatype, 
		  void*, int, MPI_Datatype, 
		  MPI_Comm);
__declspec( dllexport ) int MPI_Allgatherv(void* , int, MPI_Datatype, 
		   void*, int *recvcounts, int *displs, 
		   MPI_Datatype, MPI_Comm);
__declspec( dllexport ) int MPI_Alltoall(void* , int, MPI_Datatype, 
		 void*, int, MPI_Datatype, 
		 MPI_Comm);
__declspec( dllexport ) int MPI_Alltoallv(void* , int *sendcounts, int *sdispls, 
		  MPI_Datatype, void*, int *recvcounts, 
		  int *rdispls, MPI_Datatype, MPI_Comm);
__declspec( dllexport ) int MPI_Reduce(void* , void*, int, 
	       MPI_Datatype, MPI_Op op, int root, MPI_Comm);
#ifdef TRAPPER_ANIMATION
__declspec( dllexport ) int _MPI_Barrier(MPI_Comm, short, short);

__declspec( dllexport ) int _MPI_Bcast(void*fer, int, MPI_Datatype, int root, 
	      MPI_Comm, short, short );
__declspec( dllexport ) int _MPI_Gather(void* , int, MPI_Datatype, 
	       void*, int, MPI_Datatype, 
	       int root, MPI_Comm, short, short); 
__declspec( dllexport ) int _MPI_Gatherv(void* , int, MPI_Datatype, 
		void*, int *recvcounts, int *displs, 
		MPI_Datatype, int root, MPI_Comm, short, short); 
__declspec( dllexport ) int _MPI_Scatter(void* , int, MPI_Datatype, 
		void*, int, MPI_Datatype, 
		int root, MPI_Comm, short, short);
__declspec( dllexport ) int _MPI_Scatterv(void* , int *sendcounts, int *displs, 
		 MPI_Datatype, void*, int, 
		 MPI_Datatype, int root, MPI_Comm, short, short);
__declspec( dllexport ) int _MPI_Allgather(void* , int, MPI_Datatype, 
		  void*, int, MPI_Datatype, 
		  MPI_Comm, short, short);
__declspec( dllexport ) int _MPI_Allgatherv(void* , int, MPI_Datatype, 
		   void*, int *recvcounts, int *displs, 
		   MPI_Datatype, MPI_Comm, short, short);
__declspec( dllexport ) int _MPI_Alltoall(void* , int, MPI_Datatype, 
		 void*, int, MPI_Datatype, 
		 MPI_Comm, short, short);
__declspec( dllexport ) int _MPI_Alltoallv(void* , int *sendcounts, int *sdispls, 
		  MPI_Datatype, void*, int *recvcounts, 
		  int *rdispls, MPI_Datatype, MPI_Comm, short, short);
__declspec( dllexport ) int _MPI_Reduce(void* , void*, int, 
	       MPI_Datatype, MPI_Op op, int root, MPI_Comm, short, short);
#endif
__declspec( dllexport ) int MPI_Op_create(MPI_User_function *, int, MPI_Op *);
__declspec( dllexport ) int MPI_Op_free( MPI_Op *);
__declspec( dllexport ) int MPI_Allreduce(void* , void*, int, 
		  MPI_Datatype, MPI_Op op, MPI_Comm);
__declspec( dllexport ) int MPI_Reduce_scatter(void* , void*, int *recvcounts, 
		       MPI_Datatype, MPI_Op op, MPI_Comm);
__declspec( dllexport ) int MPI_Scan(void* , void*, int, MPI_Datatype, 
	     MPI_Op op, MPI_Comm );
#ifdef TRAPPER_ANIMATION
__declspec( dllexport ) int _MPI_Allreduce(void* , void*, int, 
		  MPI_Datatype, MPI_Op op, MPI_Comm, short, short);
__declspec( dllexport ) int _MPI_Reduce_scatter(void* , void*, int *recvcounts, 
		       MPI_Datatype, MPI_Op op, MPI_Comm, short, short);
__declspec( dllexport ) int _MPI_Scan(void* , void*, int, MPI_Datatype, 
	     MPI_Op op, MPI_Comm, short, short );
#endif
__declspec( dllexport ) int MPI_Group_size(MPI_Group group, int *);
__declspec( dllexport ) int MPI_Group_rank(MPI_Group group, int *rank);
__declspec( dllexport ) int MPI_Group_translate_ranks (MPI_Group group1, int n, int *ranks1, 
			       MPI_Group group2, int *ranks2);
__declspec( dllexport ) int MPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result);
__declspec( dllexport ) int MPI_Comm_group(MPI_Comm, MPI_Group *);
__declspec( dllexport ) int MPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
__declspec( dllexport ) int MPI_Group_intersection(MPI_Group group1, MPI_Group group2, 
			   MPI_Group *newgroup);
__declspec( dllexport ) int MPI_Group_difference(MPI_Group group1, MPI_Group group2, 
			 MPI_Group *newgroup);
__declspec( dllexport ) int MPI_Group_incl(MPI_Group group, int n, int *ranks, MPI_Group *newgroup);
__declspec( dllexport ) int MPI_Group_excl(MPI_Group group, int n, int *ranks, MPI_Group *newgroup);
__declspec( dllexport ) int MPI_Group_range_incl(MPI_Group group, int n, int ranges[][3], 
			 MPI_Group *newgroup);
__declspec( dllexport ) int MPI_Group_range_excl(MPI_Group group, int n, int ranges[][3], 
			 MPI_Group *newgroup);
__declspec( dllexport ) int MPI_Group_free(MPI_Group *);
__declspec( dllexport ) int MPI_Comm_size(MPI_Comm, int *);
__declspec( dllexport ) int MPI_Comm_rank(MPI_Comm, int *rank);
__declspec( dllexport ) int MPI_Comm_compare(MPI_Comm, MPI_Comm, int *result);
__declspec( dllexport ) int MPI_Comm_dup(MPI_Comm, MPI_Comm *newcomm);
__declspec( dllexport ) int MPI_Comm_create(MPI_Comm, MPI_Group group, MPI_Comm *newcomm);
__declspec( dllexport ) int MPI_Comm_split(MPI_Comm, int color, int key, MPI_Comm *newcomm);
__declspec( dllexport ) int MPI_Comm_free(MPI_Comm *comm);
__declspec( dllexport ) int MPI_Comm_test_inter(MPI_Comm, int *flag);
__declspec( dllexport ) int MPI_Comm_remote_size(MPI_Comm, int *);
__declspec( dllexport ) int MPI_Comm_remote_group(MPI_Comm, MPI_Group *);
__declspec( dllexport ) int MPI_Intercomm_create(MPI_Comm local_comm, int local_leader, 
			 MPI_Comm peer_comm, int remote_leader, 
			 int, MPI_Comm *newintercomm);
__declspec( dllexport ) int MPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm *newintracomm);
__declspec( dllexport ) int MPI_Keyval_create(MPI_Copy_function *copy_fn, 
		      MPI_Delete_function *delete_fn, 
		      int *keyval, void* extra_state);
__declspec( dllexport ) int MPI_Keyval_free(int *keyval);
__declspec( dllexport ) int MPI_Attr_put(MPI_Comm, int keyval, void* attribute_val);
__declspec( dllexport ) int MPI_Attr_get(MPI_Comm, int keyval, void *attribute_val, int *flag);
__declspec( dllexport ) int MPI_Attr_delete(MPI_Comm, int keyval);
__declspec( dllexport ) int MPI_Topo_test(MPI_Comm, int *);
__declspec( dllexport ) int MPI_Cart_create(MPI_Comm comm_old, int ndims, int *dims, int *periods,
		    int reorder, MPI_Comm *comm_cart);
__declspec( dllexport ) int MPI_Dims_create(int nnodes, int ndims, int *dims);
__declspec( dllexport ) int MPI_Graph_create(MPI_Comm, int, int *, int *, int, MPI_Comm *);
__declspec( dllexport ) int MPI_Graphdims_get(MPI_Comm, int *nnodes, int *nedges);
__declspec( dllexport ) int MPI_Graph_get(MPI_Comm, int, int, int *, int *);
__declspec( dllexport ) int MPI_Cartdim_get(MPI_Comm, int *ndims);
__declspec( dllexport ) int MPI_Cart_get(MPI_Comm, int maxdims, int *dims, int *periods,
		 int *coords);
__declspec( dllexport ) int MPI_Cart_rank(MPI_Comm, int *coords, int *rank);
__declspec( dllexport ) int MPI_Cart_coords(MPI_Comm, int rank, int maxdims, int *coords);
__declspec( dllexport ) int MPI_Graph_neighbors_count(MPI_Comm, int rank, int *nneighbors);
__declspec( dllexport ) int MPI_Graph_neighbors(MPI_Comm, int rank, int maxneighbors,
			int *neighbors);
__declspec( dllexport ) int MPI_Cart_shift(MPI_Comm, int direction, int disp, 
		   int *rank_source, int *rank_dest);
__declspec( dllexport ) int MPI_Cart_sub(MPI_Comm, int *remain_dims, MPI_Comm *newcomm);
__declspec( dllexport ) int MPI_Cart_map(MPI_Comm, int ndims, int *dims, int *periods, 
		 int *newrank);
__declspec( dllexport ) int MPI_Graph_map(MPI_Comm, int, int *, int *, int *);
__declspec( dllexport ) int MPI_Get_processor_name(char *, int *);
__declspec( dllexport ) int MPI_Errhandler_create(MPI_Handler_function *function, 
			  MPI_Errhandler *errhandler);
__declspec( dllexport ) int MPI_Errhandler_set(MPI_Comm, MPI_Errhandler errhandler);
__declspec( dllexport ) int MPI_Errhandler_get(MPI_Comm, MPI_Errhandler *errhandler);
__declspec( dllexport ) int MPI_Errhandler_free(MPI_Errhandler *errhandler);
__declspec( dllexport ) int MPI_Error_string(int errorcode, char *string, int *result_len);
__declspec( dllexport ) int MPI_Error_class(int errorcode, int *errorclass);
__declspec( dllexport ) double MPI_Wtime(void);
__declspec( dllexport ) double MPI_Wtick(void);
#ifndef MPI_Wtime
__declspec( dllexport ) double PMPI_Wtime(void);
__declspec( dllexport ) double PMPI_Wtick(void);
#endif
__declspec( dllexport ) int MPI_Init(int *argc, char ***argv);
__declspec( dllexport ) int MPI_Finalize(void);
__declspec( dllexport ) int MPI_Initialized(int *flag);
__declspec( dllexport ) int MPI_Abort(MPI_Comm, int errorcode);

#ifdef TRAPPER_ANIMATION
__declspec( dllexport ) int _MPI_Init(int *argc, char ***argv, short file, short line);
__declspec( dllexport ) int _MPI_Finalize(short file, short line);
__declspec( dllexport ) int _MPI_Abort(MPI_Comm, int errorcode, short file, short line);
#endif
/* MPI-2 communicator naming functions */
__declspec( dllexport ) int MPI_Comm_set_name(MPI_Comm, char *);
__declspec( dllexport ) int MPI_Comm_get_name(MPI_Comm, char **);
#ifdef HAVE_NO_C_CONST
/* Default Solaris compiler does not accept const but does accept prototypes */
__declspec( dllexport ) int MPI_Pcontrol(int level, ...);
#else
__declspec( dllexport ) int MPI_Pcontrol(const int level, ...);
#endif

__declspec( dllexport ) int MPI_NULL_COPY_FN ( MPI_Comm oldcomm, int keyval, void *extra_state, 
		       void *attr_in, void *attr_out, int *flag );
__declspec( dllexport ) int MPI_NULL_DELETE_FN ( MPI_Comm, int keyval, void *attr, 
			 void *extra_state );
__declspec( dllexport ) int MPI_DUP_FN ( MPI_Comm, int keyval, void *extra_state, void *attr_in,
		 void *attr_out, int *flag );

/* MPI-1.2 Function */
__declspec( dllexport ) int MPI_Get_version(int *, int *);

/* Here are the bindings of the profiling routines */
#if !defined(MPI_BUILD_PROFILING)
__declspec( dllexport ) int PMPI_Send(void*, int, MPI_Datatype, int, int, 
	     MPI_Comm);
__declspec( dllexport ) int PMPI_Recv(void*, int, MPI_Datatype, int, 
	     int, MPI_Comm, MPI_Status *);
__declspec( dllexport ) int PMPI_Get_count(MPI_Status *, MPI_Datatype, int *);
__declspec( dllexport ) int PMPI_Bsend(void*, int, MPI_Datatype, int, int, 
	      MPI_Comm);
__declspec( dllexport ) int PMPI_Ssend(void*, int, MPI_Datatype, int, int, 
	      MPI_Comm);
__declspec( dllexport ) int PMPI_Rsend(void*, int, MPI_Datatype, int, int, 
	      MPI_Comm);
__declspec( dllexport ) int PMPI_Buffer_attach( void* buffer, int size);
__declspec( dllexport ) int PMPI_Buffer_detach( void* buffer, int* size);
__declspec( dllexport ) int PMPI_Isend(void*, int, MPI_Datatype, int, int, 
	      MPI_Comm, MPI_Request *);
__declspec( dllexport ) int PMPI_Ibsend(void*, int, MPI_Datatype, int, 
	       int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int PMPI_Issend(void*, int, MPI_Datatype, int, 
	       int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int PMPI_Irsend(void*, int, MPI_Datatype, int, 
	       int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int PMPI_Irecv(void*, int, MPI_Datatype, int, 
	      int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int PMPI_Wait(MPI_Request *, MPI_Status *);
__declspec( dllexport ) int PMPI_Test(MPI_Request *, int *flag, MPI_Status *);
__declspec( dllexport ) int PMPI_Request_free(MPI_Request *);
__declspec( dllexport ) int PMPI_Waitany(int, MPI_Request *, int *, MPI_Status *);
__declspec( dllexport ) int PMPI_Testany(int, MPI_Request *, int *, int *, MPI_Status *);
__declspec( dllexport ) int PMPI_Waitall(int, MPI_Request *, 
		MPI_Status *);
__declspec( dllexport ) int PMPI_Testall(int, MPI_Request *, int *flag, 
		MPI_Status *);
__declspec( dllexport ) int PMPI_Waitsome(int, MPI_Request *, int *, 
		 int *, MPI_Status *);
__declspec( dllexport ) int PMPI_Testsome(int, MPI_Request *, int *, 
		 int *, MPI_Status *);
__declspec( dllexport ) int PMPI_Iprobe(int, int, MPI_Comm, int *flag, 
	       MPI_Status *);
__declspec( dllexport ) int PMPI_Probe(int, int, MPI_Comm, MPI_Status *);
__declspec( dllexport ) int PMPI_Cancel(MPI_Request *);
__declspec( dllexport ) int PMPI_Test_cancelled(MPI_Status *, int *flag);
__declspec( dllexport ) int PMPI_Send_init(void*, int, MPI_Datatype, int, 
		  int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int PMPI_Bsend_init(void*, int, MPI_Datatype, int, 
		   int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int PMPI_Ssend_init(void*, int, MPI_Datatype, int, 
		   int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int PMPI_Rsend_init(void*, int, MPI_Datatype, int, 
		   int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int PMPI_Recv_init(void*, int, MPI_Datatype, int, 
		  int, MPI_Comm, MPI_Request *);
__declspec( dllexport ) int PMPI_Start(MPI_Request *);
__declspec( dllexport ) int PMPI_Startall(int, MPI_Request *);
__declspec( dllexport ) int PMPI_Sendrecv(void *, int, MPI_Datatype, 
		 int, int, void *, int, 
		 MPI_Datatype, int, int, 
		 MPI_Comm, MPI_Status *);
__declspec( dllexport ) int PMPI_Sendrecv_replace(void*, int, MPI_Datatype, 
			 int, int, int, int, 
			 MPI_Comm, MPI_Status *);
__declspec( dllexport ) int PMPI_Type_contiguous(int, MPI_Datatype, 
			MPI_Datatype *);
__declspec( dllexport ) int PMPI_Type_vector(int, int, int, 
		    MPI_Datatype, MPI_Datatype *);
__declspec( dllexport ) int PMPI_Type_hvector(int, int, MPI_Aint, 
		     MPI_Datatype, MPI_Datatype *);
__declspec( dllexport ) int PMPI_Type_indexed(int, int *, 
		     int *, MPI_Datatype, 
		     MPI_Datatype *);
__declspec( dllexport ) int PMPI_Type_hindexed(int, int *, 
		      MPI_Aint *, MPI_Datatype, 
		      MPI_Datatype *);
__declspec( dllexport ) int PMPI_Type_struct(int, int *, 
		    MPI_Aint *, 
		    MPI_Datatype *, MPI_Datatype *);
__declspec( dllexport ) int PMPI_Address(void*, MPI_Aint *);
__declspec( dllexport ) int PMPI_Type_extent(MPI_Datatype, MPI_Aint *);

/* See the 1.1 version of the Standard; I think that the standard is in 
   error; however, it is the standard */
/* __declspec( dllexport ) int PMPI_Type_size(MPI_Datatype, MPI_Aint *); */
__declspec( dllexport ) int PMPI_Type_size(MPI_Datatype, int *);
__declspec( dllexport ) int PMPI_Type_count(MPI_Datatype, int *);
__declspec( dllexport ) int PMPI_Type_lb(MPI_Datatype, MPI_Aint*);
__declspec( dllexport ) int PMPI_Type_ub(MPI_Datatype, MPI_Aint*);
__declspec( dllexport ) int PMPI_Type_commit(MPI_Datatype *);
__declspec( dllexport ) int PMPI_Type_free(MPI_Datatype *);
__declspec( dllexport ) int PMPI_Get_elements(MPI_Status *, MPI_Datatype, int *);
__declspec( dllexport ) int PMPI_Pack(void* inbuf, int, MPI_Datatype, void *outbuf, 
	     int outsize, int *position,  MPI_Comm);
__declspec( dllexport ) int PMPI_Unpack(void*, int, int *, void *, 
	       int, MPI_Datatype, MPI_Comm);
__declspec( dllexport ) int PMPI_Pack_size(int, MPI_Datatype, MPI_Comm, 
		  int *);
__declspec( dllexport ) int PMPI_Barrier(MPI_Comm );
__declspec( dllexport ) int PMPI_Bcast(void* buffer, int, MPI_Datatype, int root, 
	      MPI_Comm );
__declspec( dllexport ) int PMPI_Gather(void* , int, MPI_Datatype, 
	       void*, int, MPI_Datatype, 
	       int root, MPI_Comm); 
__declspec( dllexport ) int PMPI_Gatherv(void* , int, MPI_Datatype, 
		void*, int *recvcounts, int *displs, 
		MPI_Datatype, int root, MPI_Comm); 
__declspec( dllexport ) int PMPI_Scatter(void* , int, MPI_Datatype, 
		void*, int, MPI_Datatype, 
		int root, MPI_Comm);
__declspec( dllexport ) int PMPI_Scatterv(void* , int *sendcounts, int *displs, 
		 MPI_Datatype, void*, int, 
		 MPI_Datatype, int root, MPI_Comm);
__declspec( dllexport ) int PMPI_Allgather(void* , int, MPI_Datatype, 
		  void*, int, MPI_Datatype, 
		  MPI_Comm);
__declspec( dllexport ) int PMPI_Allgatherv(void* , int, MPI_Datatype, 
		   void*, int *recvcounts, int *displs, 
		   MPI_Datatype, MPI_Comm);
__declspec( dllexport ) int PMPI_Alltoall(void* , int, MPI_Datatype, 
		 void*, int, MPI_Datatype, 
		 MPI_Comm);
__declspec( dllexport ) int PMPI_Alltoallv(void* , int *sendcounts, int *sdispls, 
		  MPI_Datatype, void*, int *recvcounts, 
		  int *rdispls, MPI_Datatype, MPI_Comm);
__declspec( dllexport ) int PMPI_Reduce(void* , void*, int, 
	       MPI_Datatype, MPI_Op op, int root, MPI_Comm);
__declspec( dllexport ) int PMPI_Op_create(MPI_User_function *, int, MPI_Op *);
__declspec( dllexport ) int PMPI_Op_free( MPI_Op *);
__declspec( dllexport ) int PMPI_Allreduce(void* , void*, int, 
		  MPI_Datatype, MPI_Op op, MPI_Comm);
__declspec( dllexport ) int PMPI_Reduce_scatter(void* , void*, int *recvcounts, 
		       MPI_Datatype, MPI_Op op, MPI_Comm);
__declspec( dllexport ) int PMPI_Scan(void* , void*, int, MPI_Datatype, 
	     MPI_Op op, MPI_Comm );
__declspec( dllexport ) int PMPI_Group_size(MPI_Group group, int *);
__declspec( dllexport ) int PMPI_Group_rank(MPI_Group group, int *rank);
__declspec( dllexport ) int PMPI_Group_translate_ranks (MPI_Group group1, int n, int *ranks1, 
			       MPI_Group group2, int *ranks2);
__declspec( dllexport ) int PMPI_Group_compare(MPI_Group group1, MPI_Group group2, int *result);
__declspec( dllexport ) int PMPI_Comm_group(MPI_Comm, MPI_Group *);
__declspec( dllexport ) int PMPI_Group_union(MPI_Group group1, MPI_Group group2, MPI_Group *newgroup);
__declspec( dllexport ) int PMPI_Group_intersection(MPI_Group group1, MPI_Group group2, 
			   MPI_Group *newgroup);
__declspec( dllexport ) int PMPI_Group_difference(MPI_Group group1, MPI_Group group2, 
			 MPI_Group *newgroup);
__declspec( dllexport ) int PMPI_Group_incl(MPI_Group group, int n, int *ranks, MPI_Group *newgroup);
__declspec( dllexport ) int PMPI_Group_excl(MPI_Group group, int n, int *ranks, MPI_Group *newgroup);
__declspec( dllexport ) int PMPI_Group_range_incl(MPI_Group group, int n, int ranges[][3], 
			 MPI_Group *newgroup);
__declspec( dllexport ) int PMPI_Group_range_excl(MPI_Group group, int n, int ranges[][3], 
			 MPI_Group *newgroup);
__declspec( dllexport ) int PMPI_Group_free(MPI_Group *);
__declspec( dllexport ) int PMPI_Comm_size(MPI_Comm, int *);
__declspec( dllexport ) int PMPI_Comm_rank(MPI_Comm, int *rank);
__declspec( dllexport ) int PMPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int *result);
__declspec( dllexport ) int PMPI_Comm_dup(MPI_Comm, MPI_Comm *newcomm);
__declspec( dllexport ) int PMPI_Comm_create(MPI_Comm, MPI_Group group, MPI_Comm *newcomm);
__declspec( dllexport ) int PMPI_Comm_split(MPI_Comm, int color, int key, MPI_Comm *newcomm);
__declspec( dllexport ) int PMPI_Comm_free(MPI_Comm *comm);
__declspec( dllexport ) int PMPI_Comm_test_inter(MPI_Comm, int *flag);
__declspec( dllexport ) int PMPI_Comm_remote_size(MPI_Comm, int *);
__declspec( dllexport ) int PMPI_Comm_remote_group(MPI_Comm, MPI_Group *);
__declspec( dllexport ) int PMPI_Intercomm_create(MPI_Comm local_comm, int local_leader, 
			 MPI_Comm peer_comm, int remote_leader, 
			 int, MPI_Comm *newintercomm);
__declspec( dllexport ) int PMPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm *newintracomm);
__declspec( dllexport ) int PMPI_Keyval_create(MPI_Copy_function *copy_fn, 
		      MPI_Delete_function *delete_fn, 
		      int *keyval, void* extra_state);
__declspec( dllexport ) int PMPI_Keyval_free(int *keyval);
__declspec( dllexport ) int PMPI_Attr_put(MPI_Comm, int keyval, void* attribute_val);
__declspec( dllexport ) int PMPI_Attr_get(MPI_Comm, int keyval, void *attribute_val, int *flag);
__declspec( dllexport ) int PMPI_Attr_delete(MPI_Comm, int keyval);
__declspec( dllexport ) int PMPI_Topo_test(MPI_Comm, int *);
__declspec( dllexport ) int PMPI_Cart_create(MPI_Comm comm_old, int ndims, int *dims, int *periods,
		    int reorder, MPI_Comm *comm_cart);
__declspec( dllexport ) int PMPI_Dims_create(int nnodes, int ndims, int *dims);
__declspec( dllexport ) int PMPI_Graph_create(MPI_Comm, int, int *, int *, int, MPI_Comm *);
__declspec( dllexport ) int PMPI_Graphdims_get(MPI_Comm, int *nnodes, int *nedges);
__declspec( dllexport ) int PMPI_Graph_get(MPI_Comm, int, int, int *, int *);
__declspec( dllexport ) int PMPI_Cartdim_get(MPI_Comm, int *ndims);
__declspec( dllexport ) int PMPI_Cart_get(MPI_Comm, int maxdims, int *dims, int *periods,
		 int *coords);
__declspec( dllexport ) int PMPI_Cart_rank(MPI_Comm, int *coords, int *rank);
__declspec( dllexport ) int PMPI_Cart_coords(MPI_Comm, int rank, int maxdims, int *coords);
__declspec( dllexport ) int PMPI_Graph_neighbors_count(MPI_Comm, int rank, int *nneighbors);
__declspec( dllexport ) int PMPI_Graph_neighbors(MPI_Comm, int rank, int maxneighbors,
			int *neighbors);
__declspec( dllexport ) int PMPI_Cart_shift(MPI_Comm, int direction, int disp, 
		   int *rank_source, int *rank_dest);
__declspec( dllexport ) int PMPI_Cart_sub(MPI_Comm, int *remain_dims, MPI_Comm *newcomm);
__declspec( dllexport ) int PMPI_Cart_map(MPI_Comm, int ndims, int *dims, int *periods, 
		 int *newrank);
__declspec( dllexport ) int PMPI_Graph_map(MPI_Comm, int, int *, int *, int *);
__declspec( dllexport ) int PMPI_Get_processor_name(char *, int *);
__declspec( dllexport ) int PMPI_Errhandler_create(MPI_Handler_function *function, 
			  MPI_Errhandler *errhandler);
__declspec( dllexport ) int PMPI_Errhandler_set(MPI_Comm, MPI_Errhandler errhandler);
__declspec( dllexport ) int PMPI_Errhandler_get(MPI_Comm, MPI_Errhandler *errhandler);
__declspec( dllexport ) int PMPI_Errhandler_free(MPI_Errhandler *errhandler);
__declspec( dllexport ) int PMPI_Error_string(int errorcode, char *string, int *result_len);
__declspec( dllexport ) int PMPI_Error_class(int errorcode, int *errorclass);
/* Wtime done above */
__declspec( dllexport ) int PMPI_Init(int *argc, char ***argv);
__declspec( dllexport ) int PMPI_Finalize(void);
__declspec( dllexport ) int PMPI_Initialized(int *flag);
__declspec( dllexport ) int PMPI_Abort(MPI_Comm, int);
/* MPI-2 communicator naming functions */
__declspec( dllexport ) int PMPI_Comm_set_name(MPI_Comm, char *);
__declspec( dllexport ) int PMPI_Comm_get_name(MPI_Comm, char **);
#ifdef HAVE_NO_C_CONST
/* Default Solaris compiler does not accept const but does accept prototypes */
__declspec( dllexport ) int PMPI_Pcontrol(int level, ...);
#else
__declspec( dllexport ) int PMPI_Pcontrol(const int level, ...);
#endif

/* MPI-1.2 Function - Profiling */
__declspec( dllexport ) int PMPI_Get_version(int *, int *);

#endif  /* MPI_BUILD_PROFILING */

#else 
extern __declspec( dllexport ) double MPI_Wtime();
extern __declspec( dllexport ) double MPI_Wtick();
#ifndef MPI_Wtime
extern __declspec( dllexport ) double PMPI_Wtime();
extern __declspec( dllexport ) double PMPI_Wtick();
#endif

extern __declspec( dllexport ) int MPI_NULL_COPY_FN(), MPI_NULL_DELETE_FN();
//#endif

#endif
