/* 
 *   $Id: mpioprof.h,v 1.2 1997/09/04 19:29:18 thakur Exp $    
 *
 *   Copyright (C) 1997 University of Chicago. 
 *   See COPYRIGHT notice in top-level directory.
 */

/* 
   This header file converts all MPI_ names into PMPI_ names, for 
   building the profiling interface
 */

#ifdef __MPIO_BUILD_PROFILING

#define MPI_File_open PMPI_File_open
#define MPI_File_close PMPI_File_close
#define MPI_File_delete PMPI_File_delete
#define MPI_File_set_size PMPI_File_set_size
#define MPI_File_preallocate PMPI_File_preallocate
#define MPI_File_get_size PMPI_File_get_size
#define MPI_File_get_group PMPI_File_get_group
#define MPI_File_get_amode PMPI_File_get_amode

#define MPI_File_set_view PMPI_File_set_view
#define MPI_File_get_view PMPI_File_get_view

#define MPI_File_read_at PMPI_File_read_at
#define MPI_File_read_at_all PMPI_File_read_at_all
#define MPI_File_write_at PMPI_File_write_at
#define MPI_File_write_at_all PMPI_File_write_at_all
#define MPI_File_iread_at PMPI_File_iread_at
#define MPI_File_iwrite_at PMPI_File_iwrite_at

#define MPI_File_read PMPI_File_read
#define MPI_File_read_all  PMPI_File_read_all 
#define MPI_File_write PMPI_File_write
#define MPI_File_write_all PMPI_File_write_all
#define MPI_File_iread PMPI_File_iread
#define MPI_File_iwrite PMPI_File_iwrite
#define MPI_File_seek PMPI_File_seek
#define MPI_File_get_position PMPI_File_get_position
#define MPI_File_get_byte_offset PMPI_File_get_byte_offset

#define MPI_File_get_type_extent PMPI_File_get_type_extent
#define MPI_File_set_atomicity PMPI_File_set_atomicity
#define MPI_File_get_atomicity PMPI_File_get_atomicity
#define MPI_File_sync PMPI_File_sync

#define MPI_Type_create_subarray PMPI_Type_create_subarray
#define MPI_Type_create_darray PMPI_Type_create_darray

#define MPI_File_f2c PMPI_File_f2c
#define MPI_File_c2f PMPI_File_c2f

#define MPIO_Test PMPIO_Test
#define MPIO_Wait PMPIO_Wait
#define MPIO_Request_f2c PMPIO_Request_f2c
#define MPIO_Request_c2f PMPIO_Request_c2f

#endif
