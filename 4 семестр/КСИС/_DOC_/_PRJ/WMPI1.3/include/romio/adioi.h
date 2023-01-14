/* 
 *   $Id: adioi.h,v 1.4 1997/10/01 20:14:44 thakur Exp $    
 *
 *   Copyright (C) 1997 University of Chicago. 
 *   See COPYRIGHT notice in top-level directory.
 */


/* contains general definitions, declarations, and macros internal to
   the ADIO implementation, though independent of the underlying file
   system. This file is included in adio.h */ 

/* Functions and datataypes that are "internal" to the ADIO implementation 
   prefixed ADIOI_. Functions and datatypes that are part of the
   "externally visible" (documented) ADIO interface are prefixed ADIO_.

   An implementation of MPI-IO, or any other high-level interface, should
   not need to use any of the ADIOI_ functions/datatypes. 
   Only someone implementing ADIO on a new file system, or modifying 
   an existing ADIO implementation, would need to use the ADIOI_
   functions/datatypes. */


#ifndef __ADIOI_INCLUDE
#define __ADIOI_INCLUDE

/* each pending nonblocking request is stored on a linked list */
typedef struct ADIOI_Async {
    ADIO_Request *request;
    struct ADIOI_Async *prev, *next;
} ADIOI_Async_node;

/* list to keep track of memory regions that have been malloced 
   for above async list */
typedef struct ADIOI_Malloc_async_ptr {
    ADIOI_Async_node *ptr;  /* ptr to malloced region */
    struct ADIOI_Malloc_async_ptr *next;
} ADIOI_Malloc_async;

/* used to malloc request objects in bulk */
typedef struct ADIOI_Req_n {
    ADIOI_RequestD reqd;
    struct ADIOI_Req_n *next;
} ADIOI_Req_node;

/* used to keep track of the malloced requests that need to be freed */
typedef struct ADIOI_Malloc_req_ptr {
    ADIOI_Req_node *ptr;  /* ptr to malloced region */
    struct ADIOI_Malloc_req_ptr *next;
} ADIOI_Malloc_req;


/* flattened datatypes. Each datatype is stored as a node of a
   globally accessible linked list. Once attribute caching on a
   datatype is available (in MPI-2), that should be used instead. */  

typedef struct ADIOI_Fl_node {  
    MPI_Datatype type;
    int count;                   /* no. of contiguous blocks */
    int *blocklens;              /* array of contiguous block lengths (bytes)*/
    MPI_Aint *indices;           /* array of byte offsets of each block */
    struct ADIOI_Fl_node *next;  /* pointer to next node */
} ADIOI_Flatlist_node;


struct ADIOI_Fns_struct {
    void (*ADIOI_xxx_Open) (ADIO_File fd, int *error_code);
    void (*ADIOI_xxx_Close) (ADIO_File fd, int *error_code);
    void (*ADIOI_xxx_ReadContig) (ADIO_File fd, void *buf, int len, int
               file_ptr_type, ADIO_Offset offset, ADIO_Status *status,
	       int *error_code);
    void (*ADIOI_xxx_WriteContig) (ADIO_File fd, void *buf, int len, int
	       file_ptr_type, ADIO_Offset offset, ADIO_Status *status,
               int *error_code);   
    void (*ADIOI_xxx_IreadContig) (ADIO_File fd, void *buf, int len, 
               int file_ptr_type, ADIO_Offset offset, ADIO_Request *request, 
               int *error_code);   
    void (*ADIOI_xxx_IwriteContig) (ADIO_File fd, void *buf, int len, int
	       file_ptr_type, ADIO_Offset offset, ADIO_Request *request, 
               int *error_code);   
    int (*ADIOI_xxx_ReadDone) (ADIO_Request *request, ADIO_Status *status, 
               int *error_code); 
    int (*ADIOI_xxx_WriteDone) (ADIO_Request *request, ADIO_Status *status, 
               int *error_code);
/*    int (*ADIOI_xxx_ReadIcomplete) (ADIO_Request *request, ADIO_Status *status, 
               int *error_code); 
    int (*ADIOI_xxx_WriteIcomplete) (ADIO_Request *request, ADIO_Status *status,
	       int *error_code); 
	       */
    void (*ADIOI_xxx_ReadComplete) (ADIO_Request *request, ADIO_Status *status, 
               int *error_code); 
    void (*ADIOI_xxx_WriteComplete) (ADIO_Request *request, ADIO_Status *status,
	       int *error_code); 
    void (*ADIOI_xxx_ReadStrided) (ADIO_File fd, void *buf, int count,
	       MPI_Datatype datatype, int file_ptr_type,
	       ADIO_Offset offset, ADIO_Status *status, int *error_code);
    void (*ADIOI_xxx_WriteStrided) (ADIO_File fd, void *buf, int count,
	       MPI_Datatype datatype, int file_ptr_type,
	       ADIO_Offset offset, ADIO_Status *status, int *error_code);
    void (*ADIOI_xxx_ReadStridedColl) (ADIO_File fd, void *buf, int count,
	       MPI_Datatype datatype, int file_ptr_type,
	       ADIO_Offset offset, ADIO_Status *status, int *error_code);
    void (*ADIOI_xxx_WriteStridedColl) (ADIO_File fd, void *buf, int count,
	       MPI_Datatype datatype, int file_ptr_type,
	       ADIO_Offset offset, ADIO_Status *status, int *error_code);
    void (*ADIOI_xxx_IreadStrided) (ADIO_File fd, void *buf, int count,
	       MPI_Datatype datatype, int file_ptr_type,
	       ADIO_Offset offset, ADIO_Request *request, int *error_code);
    void (*ADIOI_xxx_IwriteStrided) (ADIO_File fd, void *buf, int count,
	       MPI_Datatype datatype, int file_ptr_type,
	       ADIO_Offset offset, ADIO_Request *request, int *error_code);
    void (*ADIOI_xxx_Fcntl) (ADIO_File fd, int flag, ADIO_Fcntl_t *fcntl_struct, 
	       int *error_code); 
    void (*ADIOI_xxx_Flush) (ADIO_File fd, int *error_code); 
};


/* optypes for ADIO_RequestD */
#define ADIOI_READ                26
#define ADIOI_WRITE               27

#define ADIOI_MIN(a, b) ((a) < (b) ? (a) : (b))
#define ADIOI_MAX(a, b) ((a) > (b) ? (a) : (b))


/* some of the ADIO functions are macro-replaced */

#define ADIO_ReadContig(fd,buf,len,file_ptr_type,offset,status,error_code) \
        (*(fd->fns->ADIOI_xxx_ReadContig))(fd,buf,len,file_ptr_type,offset,status,error_code)

#define ADIO_WriteContig(fd,buf,len,file_ptr_type,offset,status,error_code) \
        (*(fd->fns->ADIOI_xxx_WriteContig))(fd,buf,len,file_ptr_type,offset,status,error_code)

#define ADIO_IreadContig(fd,buf,len,file_ptr_type,offset,request,error_code) \
        (*(fd->fns->ADIOI_xxx_IreadContig))(fd,buf,len,file_ptr_type,offset,request,error_code)

#define ADIO_IwriteContig(fd,buf,len,file_ptr_type,offset,request,error_code) \
        (*(fd->fns->ADIOI_xxx_IwriteContig))(fd,buf,len,file_ptr_type,offset,request,error_code)

/* in these routines a pointer to request is passed */
#define ADIO_ReadDone(request,status,error_code) \
        (*((*(request))->fd->fns->ADIOI_xxx_ReadDone))(request,status,error_code)

#define ADIO_WriteDone(request,status,error_code) \
        (*((*(request))->fd->fns->ADIOI_xxx_WriteDone))(request,status,error_code)

#define ADIO_ReadIcomplete(request,status,error_code) \
        (*((*(request))->fd->fns->ADIOI_xxx_ReadIcomplete))(request,status,error_code)

#define ADIO_WriteIcomplete(request,status,error_code) \
        (*((*(request))->fd->fns->ADIOI_xxx_WriteIcomplete))(request,status,error_code)

#define ADIO_ReadComplete(request,status,error_code) \
        (*((*(request))->fd->fns->ADIOI_xxx_ReadComplete))(request,status,error_code)

#define ADIO_WriteComplete(request,status,error_code) \
        (*((*(request))->fd->fns->ADIOI_xxx_WriteComplete))(request,status,error_code)

#define ADIO_ReadStrided(fd,buf,count,datatype,file_ptr_type,offset,status,error_code) \
        (*(fd->fns->ADIOI_xxx_ReadStrided))(fd,buf,count,datatype,file_ptr_type,offset,status,error_code)

#define ADIO_WriteStrided(fd,buf,count,datatype,file_ptr_type,offset,status,error_code) \
        (*(fd->fns->ADIOI_xxx_WriteStrided))(fd,buf,count,datatype,file_ptr_type,offset,status,error_code)

#define ADIO_ReadStridedColl(fd,buf,count,datatype,file_ptr_type,offset,status,error_code) \
        (*(fd->fns->ADIOI_xxx_ReadStridedColl))(fd,buf,count,datatype,file_ptr_type,offset,status,error_code)

#define ADIO_WriteStridedColl(fd,buf,count,datatype,file_ptr_type,offset,status,error_code) \
        (*(fd->fns->ADIOI_xxx_WriteStridedColl))(fd,buf,count,datatype,file_ptr_type,offset,status,error_code)

#define ADIO_IreadStrided(fd,buf,count,datatype,file_ptr_type,offset,request,error_code) \
        (*(fd->fns->ADIOI_xxx_IreadStrided))(fd,buf,count,datatype,file_ptr_type,offset,request,error_code)

#define ADIO_IwriteStrided(fd,buf,count,datatype,file_ptr_type,offset,request,error_code) \
        (*(fd->fns->ADIOI_xxx_IwriteStrided))(fd,buf,count,datatype,file_ptr_type,offset,request,error_code)

#define ADIO_Flush(fd,error_code) (*(fd->fns->ADIOI_xxx_Flush))(fd,error_code)


/* prototypes for ADIO internal functions */

void ADIOI_SetFunctions(ADIO_File fd);
void ADIOI_Flatten_datatype(MPI_Datatype type);
void ADIOI_Flatten(MPI_Datatype type, ADIOI_Flatlist_node *flat, int
		  st_offset, int *curr_index);  
void ADIOI_Delete_flattened(MPI_Datatype datatype);
int ADIOI_Count_contiguous_blocks(MPI_Datatype type, int *curr_index);
ADIOI_Async_node *ADIOI_Malloc_async_node(void);
void ADIOI_Free_async_node(ADIOI_Async_node *node);
void ADIOI_Add_req_to_list(ADIO_Request *request);
void ADIOI_Complete_async(int *error_code);
void ADIOI_Del_req_from_list(ADIO_Request *request);
ADIOI_RequestD *ADIOI_Malloc_request(void);
void ADIOI_Free_request(ADIOI_Req_node *node);
void *ADIOI_Malloc(unsigned int size, int lineno, char *fname);
void *ADIOI_Calloc(unsigned int nelem, unsigned int elsize, int
		   lineno, char *fname);
void *ADIOI_Realloc(void *ptr, unsigned int size, int lineno, char *fname);
void ADIOI_Free(void *ptr, int lineno, char *fname);
void ADIOI_Datatype_iscontig(MPI_Datatype datatype, int *flag);
void ADIOI_Get_position(ADIO_File fd, ADIO_Offset *offset);
void ADIOI_Get_eof_offset(ADIO_File fd, ADIO_Offset *eof_offset);

void ADIOI_GEN_Flush(ADIO_File fd, int *error_code);

#define ADIOI_Malloc(a) ADIOI_Malloc(a,__LINE__,__FILE__)
#define ADIOI_Calloc(a,b) ADIOI_Calloc(a,b,__LINE__,__FILE__)
#define ADIOI_Realloc(a,b) ADIOI_Realloc(a,b,__LINE__,__FILE__)
#define ADIOI_Free(a) ADIOI_Free(a,__LINE__,__FILE__)


/* structure for storing access info of this process's request 
   from the file domain of other processes, and vice-versa. used 
   as array of structures indexed by process number. */
typedef struct {
    ADIO_Offset *offsets;   /* array of offsets */
    int *lens;              /* array of lengths */
    MPI_Aint *mem_ptrs;     /* array of pointers. used in the read/write
			       phase to indicate where the data
			       is stored in memory */
    int count;             /* size of above arrays */
} ADIOI_Access_info;


void ADIOI_GEN_ReadStrided(ADIO_File fd, void *buf, int count,
                       MPI_Datatype datatype, int file_ptr_type,
                       ADIO_Offset offset, ADIO_Status *status, int
                       *error_code);
void ADIOI_GEN_WriteStrided(ADIO_File fd, void *buf, int count,
                       MPI_Datatype datatype, int file_ptr_type,
                       ADIO_Offset offset, ADIO_Status *status, int
                       *error_code);

/*size of buffer used for data sieving in independent strided write requests*/
#define ADIOI_IND_WR_BUFSZ (1048576*4) 
/*size of buffer used for data sieving in independent strided read requests*/
#define ADIOI_IND_RD_BUFSZ (1048576*4) 


/* foll. are for collective I/O only */

#define ADIOI_MAX_NPROCS_FOR_COLL 4096
#define ADIOI_COLL_BUFSIZE (1048576*4)  /* size of buffer used for coll. I/O*/

void ADIOI_GEN_ReadStridedColl(ADIO_File fd, void *buf, int count,
                       MPI_Datatype datatype, int file_ptr_type,
                       ADIO_Offset offset, ADIO_Status *status, int
                       *error_code);
void ADIOI_GEN_WriteStridedColl(ADIO_File fd, void *buf, int count,
                       MPI_Datatype datatype, int file_ptr_type,
                       ADIO_Offset offset, ADIO_Status *status, int
                       *error_code);
void ADIOI_Calc_my_off_len(ADIO_File fd, int bufcount, MPI_Datatype
			    datatype, int file_ptr_type, ADIO_Offset 
			    offset, ADIO_Offset **offset_list_ptr, int
			    **len_list_ptr, ADIO_Offset *start_offset_ptr,
			    ADIO_Offset *end_offset_ptr, int
			   *contig_access_count_ptr);
void ADIOI_Calc_file_domains(ADIO_Offset *st_offsets, ADIO_Offset
			     *end_offsets, int nprocs, int nprocs_for_coll,
			     ADIO_Offset *min_st_offset_ptr,
			     ADIO_Offset **fd_start_ptr, ADIO_Offset 
			     **fd_end_ptr, ADIO_Offset *fd_size_ptr);
void ADIOI_Calc_my_req_info(ADIO_Offset *offset_list, int *len_list, int
			    contig_access_count, ADIO_Offset 
			    min_st_offset, ADIO_Offset *fd_start,
			    ADIO_Offset *fd_end, ADIO_Offset fd_size,
                            int nprocs, int nprocs_for_coll, 
                            int *count_my_req_procs_ptr,
			    int **count_my_req_per_proc_ptr,
			    ADIOI_Access_info **my_req_info_ptr,
			    int **buf_idx_ptr);
void ADIOI_Calc_others_req_info(ADIO_File fd, int count_my_req_procs, 
				int *count_my_req_per_proc,
				ADIOI_Access_info *my_req_info, 
				int nprocs, int myrank, int nprocs_for_coll, 
				int *count_others_req_procs_ptr,
				ADIOI_Access_info **others_req_info_ptr);  


/* Unix-style file locking */
#define ADIOI_WRITE_LOCK(fd, offset, whence, len) \
        ADIOI_Set_lock(fd, F_SETLKW, F_WRLCK, offset, whence, len)
#define ADIOI_READ_LOCK(fd, offset, whence, len) \
        ADIOI_Set_lock(fd, F_SETLKW, F_RDLCK, offset, whence, len)
#define ADIOI_UNLOCK(fd, offset, whence, len) \
        ADIOI_Set_lock(fd, F_SETLK, F_UNLCK, offset, whence, len)

int ADIOI_Set_lock(int fd, int cmd, int type, off_t offset, int whence, off_t len);

#endif
