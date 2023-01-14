/* Measures the I/O bandwidth for writing/reading a 3D
   block-distributed array to a file corresponding to the global array
   in row-major (C) order. 

*/ 


/* Note that the file access pattern is noncontiguous. */
/* The file name is taken as a command-line argument. */


#include "mpio.h"

//#define SIZE	128
//#define FILE_SIZE (128*128*128*4)

#define SIZE	32
#define FILE_SIZE (SIZE*SIZE*SIZE*sizeof(int))

/* A 128^3 array. For other array sizes, change FILE_SIZE above and
   array_of_gsizes below. */

void Main(int argc, char **argv)
{
    MPI_Datatype newtype;
    int i, ndims, array_of_gsizes[3], array_of_distribs[3];
    int order, nprocs, len;
    int array_of_dargs[3], array_of_psizes[3];
    int *buf, bufcount, mynod;
    MPI_File fh;
    MPI_Status status;
    double stim, write_tim, new_write_tim, write_bw;
    double read_tim, new_read_tim, read_bw;
    char *filename;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &mynod);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

/* process 0 takes the file name as a command-line argument and 
   broadcasts it to other processes */
    if (!mynod) {
	i = 1;
	while ((i < argc) && strcmp("-fname", *argv)) {
	    i++;
	    argv++;
	}
	if (i >= argc) {
	    printf("\n*#  Usage: coll_perf -fname filename\n");
	    printf("*#  The filename must be prefixed with a string to indicate\n"); 
	    printf("*#  the type of file system (nfs:, ufs:, pfs:, piofs:).\n");
	    printf("*#  An example filename is nfs:test\n\n");
	    MPI_Abort(MPI_COMM_WORLD, 1);
	}
	argv++;
	len = strlen(*argv);
	filename = (char *) malloc(len+1);
	strcpy(filename, *argv);
	if (strncmp(filename, "pfs:",4) && strncmp(filename,"piofs:",6)
	   && strncmp(filename, "ufs:", 4) && strncmp(filename, "nfs:", 4)) {
	    printf("\n*#  The filename must be prefixed with a string to indicate\n"); 
	    printf("*#  the type of file system (nfs:, ufs:, pfs:, piofs:).\n");
	    printf("*#  An example filename is nfs:test\n\n");
	    MPI_Abort(MPI_COMM_WORLD, 1);
	}
	MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(filename, len+1, MPI_CHAR, 0, MPI_COMM_WORLD);
    }
    else {
	MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
	filename = (char *) malloc(len+1);
	MPI_Bcast(filename, len+1, MPI_CHAR, 0, MPI_COMM_WORLD);
    }


    ndims = 3;
    order = MPI_ORDER_FORTRAN;

    array_of_gsizes[0] = SIZE;
    array_of_gsizes[1] = SIZE;
    array_of_gsizes[2] = SIZE;

    array_of_distribs[0] = MPI_DISTRIBUTE_BLOCK;
    array_of_distribs[1] = MPI_DISTRIBUTE_BLOCK;
    array_of_distribs[2] = MPI_DISTRIBUTE_BLOCK;

    array_of_dargs[0] = MPI_DISTRIBUTE_DFLT_ARG;
    array_of_dargs[1] = MPI_DISTRIBUTE_DFLT_ARG;
    array_of_dargs[2] = MPI_DISTRIBUTE_DFLT_ARG;

    for (i=0; i<ndims; i++) array_of_psizes[i] = 0;
    MPI_Dims_create(nprocs, ndims, array_of_psizes);

    MPI_Type_create_darray(nprocs, mynod, ndims, array_of_gsizes,
			   array_of_distribs, array_of_dargs,
			   array_of_psizes, order, MPI_INT, &newtype);
    MPI_Type_commit(&newtype);

    MPI_Type_size(newtype, &bufcount);
    bufcount = bufcount/sizeof(int);
    buf = (int *) malloc(bufcount * sizeof(int));

/* to eliminate paging effects, do the operations once but don't time
   them */

    MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_RDWR 
                  | MPI_MODE_UNIQUE_OPEN, MPI_INFO_NULL, &fh);
    MPI_File_set_view(fh, 0, MPI_INT, newtype, "native", MPI_INFO_NULL);
    MPI_File_write_all(fh, buf, bufcount, MPI_INT, &status);
    MPI_File_seek(fh, 0, MPI_SEEK_SET);
    MPI_File_read_all(fh, buf, bufcount, MPI_INT, &status);
    MPI_File_close(&fh);

    MPI_Barrier(MPI_COMM_WORLD);
/* now time write_all */

    MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_RDWR 
                  | MPI_MODE_UNIQUE_OPEN, MPI_INFO_NULL, &fh);
    MPI_File_set_view(fh, 0, MPI_INT, newtype, "native", MPI_INFO_NULL);

    MPI_Barrier(MPI_COMM_WORLD);
    stim = MPI_Wtime();
    MPI_File_write_all(fh, buf, bufcount, MPI_INT, &status);
    write_tim = MPI_Wtime() - stim;
    MPI_File_close(&fh);

    MPI_Allreduce(&write_tim, &new_write_tim, 1, MPI_DOUBLE, MPI_MAX,
                    MPI_COMM_WORLD);

    if (mynod == 0) {
      write_bw = (FILE_SIZE)/(new_write_tim*1000000.0);
      printf("Global array size %d x %d x %d integers\n", array_of_gsizes[0], array_of_gsizes[1], array_of_gsizes[2]);
      printf("Collective write time = %f sec, Collective write bandwidth = %f Mbytes/sec\n", new_write_tim, write_bw);
    }

    MPI_Barrier(MPI_COMM_WORLD);
/* now time read_all */

    MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_RDWR 
                  | MPI_MODE_UNIQUE_OPEN, MPI_INFO_NULL, &fh); 
    MPI_File_set_view(fh, 0, MPI_INT, newtype, "native", MPI_INFO_NULL);

    MPI_Barrier(MPI_COMM_WORLD);
    stim = MPI_Wtime();
    MPI_File_read_all(fh, buf, bufcount, MPI_INT, &status);
    read_tim = MPI_Wtime() - stim;
    MPI_File_close(&fh);

    MPI_Allreduce(&read_tim, &new_read_tim, 1, MPI_DOUBLE, MPI_MAX,
                    MPI_COMM_WORLD);

    if (mynod == 0) {
      read_bw = (FILE_SIZE)/(new_read_tim*1000000.0);
      printf("Collective read time = %f sec, Collective read bandwidth = %f Mbytes/sec\n", new_read_tim, read_bw);
    }

    MPI_Type_free(&newtype);
    free(buf);
    free(filename);

    MPI_Finalize();
}
