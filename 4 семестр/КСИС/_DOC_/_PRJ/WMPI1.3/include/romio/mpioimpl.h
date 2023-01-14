/* 
 *   $Id: mpioimpl.h,v 1.2 1997/09/04 19:29:18 thakur Exp $    
 *
 *   Copyright (C) 1997 University of Chicago. 
 *   See COPYRIGHT notice in top-level directory.
 */


/* header file for MPI-IO implementation. not intended to be
   user-visible */ 

#ifndef __MPIOIMPL_INCLUDE
#define __MPIOIMPL_INCLUDE

#include "mpio.h"

#ifndef __DEFINES
#define __DEFINES
#define __AIO_PRIORITY_DEFAULT
#define __UFS
#define __NEEDS_MPI_TEST
#define __MPICH
#define __INT_LT_POINTER 1
#define __NO_AIO
#endif


MPI_Delete_function ADIOI_End_call;

#include "mpioprof.h"
#endif

