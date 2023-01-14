/* 
 *   $Id: mpio.h.in,v 1.2 1997/10/01 07:21:22 thakur Exp $    
 *
 *   Copyright (C) 1997 University of Chicago. 
 *   See COPYRIGHT notice in top-level directory.
 */

/* user include file for MPI-IO programs */

#ifndef __MPIO_INCLUDE
#define __MPIO_INCLUDE

#if defined(__cplusplus)
extern "C" {
#endif

#include "adio.h"

#ifndef __DEFINES
#define __DEFINES
#define __AIO_PRIORITY_DEFAULT
#define __UFS
#define __NEEDS_MPI_TEST
#define __MPICH
#define __INT_LT_POINTER 1
#define __NO_AIO
#endif

#define ROMIO_VERSION 100      /* Version 1.0.0 */

/* define MPI-IO datatypes and constants */

typedef ADIOI_FileD *MPI_File;
typedef ADIO_Offset MPI_Offset;      
typedef int MPI_Info;               /* info ignored completely at present */
typedef ADIO_Request MPIO_Request;  /* no generalized requests as yet */

#define __NEEDS_MPI_FINT

#ifdef __NEEDS_MPI_FINT
typedef int MPI_Fint; 
#endif

#define MPI_MODE_RDONLY              ADIO_RDONLY 
#define MPI_MODE_RDWR                ADIO_RDWR 
#define MPI_MODE_WRONLY              ADIO_WRONLY 
#define MPI_MODE_CREATE              ADIO_CREATE 
#define MPI_MODE_EXCL                ADIO_EXCL
#define MPI_MODE_DELETE_ON_CLOSE     ADIO_DELETE_ON_CLOSE
#define MPI_MODE_UNIQUE_OPEN         ADIO_UNIQUE_OPEN
#define MPI_MODE_APPEND              ADIO_APPEND

#define MPI_FILE_NULL           0
#define MPI_INFO_NULL           0
#define MPIO_REQUEST_NULL       0

#define MPI_SEEK_SET            600
#define MPI_SEEK_CUR            602
#define MPI_SEEK_END            604

#define MPI_ORDER_C             56
#define MPI_ORDER_FORTRAN       57

#define MPI_DISTRIBUTE_BLOCK    121
#define MPI_DISTRIBUTE_CYCLIC   122
#define MPI_DISTRIBUTE_NONE     123
#define MPI_DISTRIBUTE_DFLT_ARG -49767

#define MPI_MAX_DATAREP_STRING  128

#include "mpio_binding.h"

#if defined(__cplusplus)
}
#endif

#endif
