/* 
 *   $Id: adio.h,v 1.4 1997/09/04 20:05:06 thakur Exp $    
 *
 *   Copyright (C) 1997 University of Chicago. 
 *   See COPYRIGHT notice in top-level directory.
 */


/* main include file for ADIO.
   contains general definitions, declarations, and macros independent 
   of the underlying file system */

/* Functions and datataypes that are "internal" to the ADIO implementation 
   prefixed ADIOI_. Functions and datatypes that are part of the
   "externally visible" (documented) ADIO interface are prefixed ADIO_.

   An implementation of MPI-IO, or any other high-level interface, should
   not need to use any of the ADIOI_ functions/datatypes. 
   Only someone implementing ADIO on a new file system, or modifying 
   an existing ADIO implementation, would need to use the ADIOI_
   functions/datatypes. */


#ifndef __ADIO_INCLUDE
#define __ADIO_INCLUDE

#ifndef __DEFINES
#define __DEFINES
#define __AIO_PRIORITY_DEFAULT
#define __UFS
#define __NEEDS_MPI_TEST
#define __MPICH
#define __INT_LT_POINTER 1
#define __NO_AIO
#endif


#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/timeb.h>
#include <io.h>
#include <sys\locking.h>
#include "mpi.h"

typedef int ADIO_Hints;             /* hints ignored completely at present */

typedef int ADIO_Offset;     /* this is OK for the moment since we are only
                                supporting file sizes less than 2Gbytes */
#define ADIO_Status MPI_Status      /* for the time being */

typedef struct ADIOI_Fns_struct ADIOI_Fns;

typedef struct {
    int cookie;              /* for error checking */
    int fd_sys;              /* system file descriptor */
    ADIO_Offset fp_ind;      /* individual file pointer in MPI-IO (in bytes)*/
    ADIO_Offset fp_sys_posn; /* current location of the system file-pointer
                                in bytes */
    ADIOI_Fns *fns;          /* struct of I/O functions to use */
    MPI_Comm comm;           /* communicator indicating who called open */
    char *filename;          
    int file_system;         /* type of file system */
    int access_mode;         
    ADIO_Offset disp;        /* reqd. for MPI-IO */
    MPI_Datatype etype;      /* reqd. for MPI-IO */
    MPI_Datatype filetype;   /* reqd. for MPI-IO */
    int etype_size;          /* in bytes */
    int async_count;         /* count of outstanding nonblocking operations */
    int perm;
    int atomicity;          /* true=atomic, false=nonatomic */
    ADIO_Hints hints;
    int iomode;              /* reqd. to implement Intel PFS modes */
} ADIOI_FileD;

typedef ADIOI_FileD *ADIO_File;

typedef struct ADIOI_Req {
    int cookie;              /* for error checking */
    void *handle;        /* return handle */
    int optype;          /* ADIOI_READ or ADIOI_WRITE */
    ADIO_File fd;        /* associated file descriptor */
    int queued;          /* 1 = request still queued in the system, 
                            0 = request already dequeued */
    struct ADIOI_Async *ptr_in_async_list;  /* pointer to location in list of 
					   asynchronous requests */
    struct ADIOI_Req *next;    /* for strided accesses, pointer to next 
                                 request structure.*/ 
#ifdef __PFS
    void *handle_extra;  /* handle for storing iov* for ireadv/iwritev in PFS*/
#endif
} ADIOI_RequestD;

typedef ADIOI_RequestD *ADIO_Request;

/* fcntl structure */
typedef struct {
    ADIO_Offset disp;       
    MPI_Datatype etype;
    MPI_Datatype filetype;
    int info;                /* info ignored at present */
    int iomode;              /* to change PFS I/O mode. for MPI-IO
				implementation, just set it to M_ASYNC. */  
    int atomicity;
    ADIO_Offset fsize;       /* for get_fsize only */
    ADIO_Offset diskspace;   /* for file preallocation */
} ADIO_Fcntl_t;              /* should contain more stuff */

/* access modes */
#define ADIO_CREATE              1
#define ADIO_RDONLY              2
#define ADIO_WRONLY              4
#define ADIO_RDWR                8
#define ADIO_DELETE_ON_CLOSE     16
#define ADIO_UNIQUE_OPEN         32
#define ADIO_EXCL                64
#define ADIO_APPEND             128
#define ADIO_SEQUENTIAL         256

/* file-pointer types */
#define ADIO_EXPLICIT_OFFSET     100
#define ADIO_INDIVIDUAL          101
#define ADIO_SHARED              102

#define ADIO_REQUEST_NULL        ((ADIO_Request) 0)

/* file systems */
#define ADIO_PFS                 150
#define ADIO_PIOFS               151
#define ADIO_UFS                 152
#define ADIO_NFS                 153

#define ADIO_SEEK_SET            SEEK_SET
#define ADIO_SEEK_CUR            SEEK_CUR
#define ADIO_SEEK_END            SEEK_END

#define ADIO_FCNTL_SET_VIEW      176
#define ADIO_FCNTL_SET_ATOMICITY 180
#define ADIO_FCNTL_SET_IOMODE    184
#define ADIO_FCNTL_SET_DISKSPACE 188
#define ADIO_FCNTL_GET_FSIZE     200

/* for default file permissions */
#define ADIO_PERM_NULL           -1

/* PFS file-pointer modes */
#ifndef M_ASYNC 
#define M_UNIX                    0
/*#define M_LOG                     1  redefined in malloc.h on SGI! */
#define M_SYNC                    2
#define M_RECORD                  3
#define M_GLOBAL                  4
#define M_ASYNC                   5
#endif

#define ADIOI_FILE_COOKIE 2487376
#define ADIOI_REQ_COOKIE 3493740

/* ADIO function prototypes */
/* all these may not be necessary, as many of them are macro replaced to 
   function pointers that point to the appropriate functions for each
   different file system (in adioi.h), but anyway... */

void ADIO_Init(int *argc, char ***argv, int *error_code);
void ADIO_End(int *error_code);
ADIO_File ADIO_Open(MPI_Comm comm, char *filename, int file_system,
                    int access_mode, ADIO_Offset disp, MPI_Datatype etype, 
                    MPI_Datatype filetype, int iomode, 
                    ADIO_Hints hints, int perm, int *error_code);
void ADIO_Close(ADIO_File fd, int *error_code);
void ADIO_ReadContig(ADIO_File fd, void *buf, int len, int file_ptr_type,
                     ADIO_Offset offset, ADIO_Status *status, int
		     *error_code);
void ADIO_WriteContig(ADIO_File fd, void *buf, int len, int file_ptr_type,
                      ADIO_Offset offset, ADIO_Status *status, int
		      *error_code);   
void ADIO_IwriteContig(ADIO_File fd, void *buf, int len, int file_ptr_type,
                      ADIO_Offset offset, ADIO_Request *request, int
		      *error_code);   
void ADIO_IreadContig(ADIO_File fd, void *buf, int len, int file_ptr_type,
                      ADIO_Offset offset, ADIO_Request *request, int
		      *error_code);   
int ADIO_ReadDone(ADIO_Request *request, ADIO_Status *status, 
               int *error_code);
int ADIO_WriteDone(ADIO_Request *request, ADIO_Status *status, 
               int *error_code);
int ADIO_ReadIcomplete(ADIO_Request *request, ADIO_Status *status, int
		       *error_code); 
int ADIO_WriteIcomplete(ADIO_Request *request, ADIO_Status *status,
			int *error_code); 
void ADIO_ReadComplete(ADIO_Request *request, ADIO_Status *status, int
		       *error_code); 
void ADIO_WriteComplete(ADIO_Request *request, ADIO_Status *status,
			int *error_code); 
void ADIO_Fcntl(ADIO_File fd, int flag, ADIO_Fcntl_t *fcntl_struct, int
		*error_code); 
void ADIO_ReadStrided(ADIO_File fd, void *buf, int count,
		       MPI_Datatype datatype, int file_ptr_type,
		       ADIO_Offset offset, ADIO_Status *status, int
		       *error_code);
void ADIO_WriteStrided(ADIO_File fd, void *buf, int count,
		       MPI_Datatype datatype, int file_ptr_type,
		       ADIO_Offset offset, ADIO_Status *status, int
		       *error_code);
void ADIO_ReadStridedColl(ADIO_File fd, void *buf, int count,
		       MPI_Datatype datatype, int file_ptr_type,
		       ADIO_Offset offset, ADIO_Status *status, int
		       *error_code);
void ADIO_WriteStridedColl(ADIO_File fd, void *buf, int count,
		       MPI_Datatype datatype, int file_ptr_type,
		       ADIO_Offset offset, ADIO_Status *status, int
		       *error_code);
void ADIO_IreadStrided(ADIO_File fd, void *buf, int count,
		       MPI_Datatype datatype, int file_ptr_type,
		       ADIO_Offset offset, ADIO_Request *request, int
		       *error_code);
void ADIO_IwriteStrided(ADIO_File fd, void *buf, int count,
		       MPI_Datatype datatype, int file_ptr_type,
		       ADIO_Offset offset, ADIO_Request *request, int
		       *error_code);
ADIO_Offset ADIO_SeekIndividual(ADIO_File fd, ADIO_Offset offset, 
                       int whence, int *error_code);
void ADIO_Delete(char *filename, int *error_code);
void ADIO_Flush(ADIO_File fd, int *error_code);
void ADIO_Resize(ADIO_File fd, ADIO_Offset size, int *error_code);

#include "adioi.h"
#include "adioi_fs_proto.h"

#endif
