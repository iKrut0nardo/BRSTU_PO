/* 
 *   $Id: mpio_binding.h,v 1.3 1997/09/09 19:48:28 thakur Exp $    
 *
 *   Copyright (C) 1997 University of Chicago. 
 *   See COPYRIGHT notice in top-level directory.
 */


#ifndef __MPIO_BINDINGS
#define __MPIO_BINDINGS

/* Section 9.2, excluding 9.2.8 (file info) */
__declspec( dllimport ) int MPI_File_open(MPI_Comm comm, char *filename, int amode, MPI_Info info,
             MPI_File *fh);
__declspec( dllimport ) int MPI_File_close(MPI_File *fh);
__declspec( dllimport ) int MPI_File_delete(char *filename, MPI_Info info);
__declspec( dllimport ) int MPI_File_set_size(MPI_File fh, MPI_Offset size);
__declspec( dllimport ) int MPI_File_preallocate(MPI_File fh, MPI_Offset size);
__declspec( dllimport ) int MPI_File_get_size(MPI_File fh, MPI_Offset *size);
__declspec( dllimport ) int MPI_File_get_group(MPI_File fh, MPI_Group *group);
__declspec( dllimport ) int MPI_File_get_amode(MPI_File fh, int *amode);

/* Section 9.3 */
__declspec( dllimport ) int MPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype,
		 MPI_Datatype filetype, char *datarep, MPI_Info info);
__declspec( dllimport ) int MPI_File_get_view(MPI_File fh, MPI_Offset *disp, MPI_Datatype *etype,
		 MPI_Datatype *filetype, char *datarep);

/* Section 9.4.2 */
__declspec( dllimport ) int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPI_Status *status);
__declspec( dllimport ) int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPI_Status *status);
__declspec( dllimport ) int MPI_File_write_at(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPI_Status *status);
__declspec( dllimport ) int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPI_Status *status);

/* nonblocking calls currently use MPIO_Request, because generalized
   requests not yet implemented. For the same reason, MPIO_Test and 
   MPIO_Wait are used to test and wait on nonblocking I/O requests */ 

__declspec( dllimport ) int MPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPIO_Request *request);
__declspec( dllimport ) int MPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPIO_Request *request);

/* Section 9.4.3 */
__declspec( dllimport ) int MPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype
	     datatype, MPI_Status *status); 
__declspec( dllimport ) int MPI_File_read_all(MPI_File fh, void *buf, int count, MPI_Datatype
	     datatype, MPI_Status *status); 
__declspec( dllimport ) int MPI_File_write(MPI_File fh, void *buf, int count, MPI_Datatype
	      datatype, MPI_Status *status);
__declspec( dllimport ) int MPI_File_write_all(MPI_File fh, void *buf, int count, MPI_Datatype
	      datatype, MPI_Status *status);

/* nonblocking calls currently use MPIO_Request, because generalized
   requests not yet implemented. For the same reason, MPIO_Test and 
   MPIO_Wait are used to test and wait on nonblocking I/O requests */ 

__declspec( dllimport ) int MPI_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype
	     datatype, MPIO_Request *request); 
__declspec( dllimport ) int MPI_File_iwrite(MPI_File fh, void *buf, int count, MPI_Datatype
	      datatype, MPIO_Request *request);

__declspec( dllimport ) int MPI_File_seek(MPI_File fh, MPI_Offset offset, int whence);
__declspec( dllimport ) int MPI_File_get_position(MPI_File fh, MPI_Offset *offset);
__declspec( dllimport ) int MPI_File_get_byte_offset(MPI_File fh, MPI_Offset offset, MPI_Offset *disp);


/* Section 9.5.1 */
__declspec( dllimport ) int MPI_File_get_type_extent(MPI_File fh, MPI_Datatype datatype, 
                             MPI_Aint *extent);

/* Section 9.6.1 */
__declspec( dllimport ) int MPI_File_set_atomicity(MPI_File fh, int flag);
__declspec( dllimport ) int MPI_File_get_atomicity(MPI_File fh, int *flag);
__declspec( dllimport ) int MPI_File_sync(MPI_File fh);

/* Section 4.14.4 */
__declspec( dllimport ) int MPI_Type_create_subarray(int ndims, int *array_of_sizes, int
            *array_of_subsizes, int *array_of_starts, int order, 
            MPI_Datatype oldtype, MPI_Datatype *newtype);

/* Section 4.14.5 */
__declspec( dllimport ) int MPI_Type_create_darray(int size, int rank, int ndims, int *array_of_gsizes,
		    int *array_of_distribs, int *array_of_dargs, int 
		    *array_of_psizes, int order, MPI_Datatype oldtype,
		    MPI_Datatype *newtype);

/* Section 4.12.4 */
#ifdef MPI_File_f2c
#undef MPI_File_f2c
#endif
#ifdef MPI_File_c2f
#undef MPI_File_c2f
#endif
/* above needed for some versions of mpi.h in MPICH!! */
__declspec( dllimport ) MPI_File MPI_File_f2c(MPI_Fint fh);
__declspec( dllimport ) MPI_Fint MPI_File_c2f(MPI_File fh);


/* The foll. functions are required, because an MPIO_Request object
   is currently used for nonblocking I/O. These functions will go away
   after generalized requests are implemented. */
__declspec( dllimport ) int MPIO_Test(MPIO_Request *request, int *flag, MPI_Status *status);
__declspec( dllimport ) int MPIO_Wait(MPIO_Request *request, MPI_Status *status);
__declspec( dllimport ) MPI_Fint MPIO_Request_c2f(MPIO_Request request);
__declspec( dllimport ) MPIO_Request MPIO_Request_f2c(MPI_Fint request);


/**************** BINDINGS FOR THE PROFILING INTERFACE ***************/


/* Section 9.2, excluding 9.2.8 (file info) */
__declspec( dllimport ) int PMPI_File_open(MPI_Comm comm, char *filename, int amode, MPI_Info info,
             MPI_File *fh);
__declspec( dllimport ) int PMPI_File_close(MPI_File *fh);
__declspec( dllimport ) int PMPI_File_delete(char *filename, MPI_Info info);
__declspec( dllimport ) int PMPI_File_set_size(MPI_File fh, MPI_Offset size);
__declspec( dllimport ) int PMPI_File_preallocate(MPI_File fh, MPI_Offset size);
__declspec( dllimport ) int PMPI_File_get_size(MPI_File fh, MPI_Offset *size);
__declspec( dllimport ) int PMPI_File_get_group(MPI_File fh, MPI_Group *group);
__declspec( dllimport ) int PMPI_File_get_amode(MPI_File fh, int *amode);

/* Section 9.3 */
__declspec( dllimport ) int PMPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype,
		 MPI_Datatype filetype, char *datarep, MPI_Info info);
__declspec( dllimport ) int PMPI_File_get_view(MPI_File fh, MPI_Offset *disp, MPI_Datatype *etype,
		 MPI_Datatype *filetype, char *datarep);

/* Section 9.4.2 */
__declspec( dllimport ) int PMPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPI_Status *status);
__declspec( dllimport ) int PMPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPI_Status *status);
__declspec( dllimport ) int PMPI_File_write_at(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPI_Status *status);
__declspec( dllimport ) int PMPI_File_write_at_all(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPI_Status *status);

/* nonblocking calls currently use MPIO_Request, because generalized
   requests not yet implemented. For the same reason, MPIO_Test and 
   MPIO_Wait are used to test and wait on nonblocking I/O requests */ 

__declspec( dllimport ) int PMPI_File_iread_at(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPIO_Request *request);
__declspec( dllimport ) int PMPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, void *buf,
	      int count, MPI_Datatype datatype, MPIO_Request *request);

/* Section 9.4.3 */
__declspec( dllimport ) int PMPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype
	     datatype, MPI_Status *status); 
__declspec( dllimport ) int PMPI_File_read_all(MPI_File fh, void *buf, int count, MPI_Datatype
	     datatype, MPI_Status *status); 
__declspec( dllimport ) int PMPI_File_write(MPI_File fh, void *buf, int count, MPI_Datatype
	      datatype, MPI_Status *status);
__declspec( dllimport ) int PMPI_File_write_all(MPI_File fh, void *buf, int count, MPI_Datatype
	      datatype, MPI_Status *status);

/* nonblocking calls currently use MPIO_Request, because generalized
   requests not yet implemented. For the same reason, MPIO_Test and 
   MPIO_Wait are used to test and wait on nonblocking I/O requests */ 

__declspec( dllimport ) int PMPI_File_iread(MPI_File fh, void *buf, int count, MPI_Datatype
	     datatype, MPIO_Request *request); 
__declspec( dllimport ) int PMPI_File_iwrite(MPI_File fh, void *buf, int count, MPI_Datatype
	      datatype, MPIO_Request *request);

__declspec( dllimport ) int PMPI_File_seek(MPI_File fh, MPI_Offset offset, int whence);
__declspec( dllimport ) int PMPI_File_get_position(MPI_File fh, MPI_Offset *offset);
__declspec( dllimport ) int PMPI_File_get_byte_offset(MPI_File fh, MPI_Offset offset, MPI_Offset *disp);


/* Section 9.5.1 */
__declspec( dllimport ) int PMPI_File_get_type_extent(MPI_File fh, MPI_Datatype datatype, 
                             MPI_Aint *extent);

/* Section 9.6.1 */
__declspec( dllimport ) int PMPI_File_set_atomicity(MPI_File fh, int flag);
__declspec( dllimport ) int PMPI_File_get_atomicity(MPI_File fh, int *flag);
__declspec( dllimport ) int PMPI_File_sync(MPI_File fh);

/* Section 4.14.4 */
__declspec( dllimport ) int PMPI_Type_create_subarray(int ndims, int *array_of_sizes, int
            *array_of_subsizes, int *array_of_starts, int order, 
            MPI_Datatype oldtype, MPI_Datatype *newtype);

/* Section 4.14.5 */
__declspec( dllimport ) int PMPI_Type_create_darray(int size, int rank, int ndims, int *array_of_gsizes,
		    int *array_of_distribs, int *array_of_dargs, int 
		    *array_of_psizes, int order, MPI_Datatype oldtype,
		    MPI_Datatype *newtype);

/* Section 4.12.4 */
__declspec( dllimport ) MPI_File PMPI_File_f2c(MPI_Fint fh);
__declspec( dllimport ) MPI_Fint PMPI_File_c2f(MPI_File fh);


/* The foll. functions are required, because an MPIO_Request object
   is currently used for nonblocking I/O. These functions will go away
   after generalized requests are implemented. */
__declspec( dllimport ) int PMPIO_Test(MPIO_Request *request, int *flag, MPI_Status *status);
__declspec( dllimport ) int PMPIO_Wait(MPIO_Request *request, MPI_Status *status);
__declspec( dllimport ) MPI_Fint PMPIO_Request_c2f(MPIO_Request request);
__declspec( dllimport ) MPIO_Request PMPIO_Request_f2c(MPI_Fint request);

#endif
