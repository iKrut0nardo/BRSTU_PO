/* Uses collective I/O. Writes a 3D block-distributed array to a file
   corresponding to the global array in row-major (C) order, reads it
   back, and checks that the data read is correct. 

*/

/* The file name is taken as a command-line argument. */

/* Note that the file access pattern is noncontiguous. */

#include "mpio.h"

#define FILE_SIZE (32*32*32*4)   
/* A 32^3 array. For other array sizes, change FILE_SIZE above and
   array_of_gsizes below. */

void main(int argc, char **argv)
{
    MPI_Datatype newtype;
    int i, ndims, array_of_gsizes[3], array_of_distribs[3];
    int order, nprocs, j, len, flag;
    int array_of_dargs[3], array_of_psizes[3];
    int *readbuf, *writebuf, bufcount, mynod, *tmpbuf, array_size;
    char *filename;
    MPI_File fh;
    MPI_Status status;
    MPI_Request request;

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
	    printf("\n*#  Usage: coll_test -fname filename\n");
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


/* create the distributed array filetype */
    ndims = 3;
    order = MPI_ORDER_C;

    array_of_gsizes[0] = 32;
    array_of_gsizes[1] = 32;
    array_of_gsizes[2] = 32;

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

/* initialize writebuf */

    MPI_Type_size(newtype, &bufcount);
    bufcount = bufcount/sizeof(int);
    writebuf = (int *) malloc(bufcount * sizeof(int));
    for (i=0; i<bufcount; i++) writebuf[i] = 1;

    array_size = array_of_gsizes[0]*array_of_gsizes[1]*array_of_gsizes[2];
    tmpbuf = (int *) calloc(array_size, sizeof(int));
    MPI_Irecv(tmpbuf, 1, newtype, mynod, 10, MPI_COMM_WORLD, &request);
    MPI_Send(writebuf, bufcount, MPI_INT, mynod, 10, MPI_COMM_WORLD);
    MPI_Wait(&request, &status);

    j = 0;
    for (i=0; i<array_size; i++)
	if (tmpbuf[i]) {
	    writebuf[j] = i;
	    j++;
	}
    free(tmpbuf);

    if (j != bufcount) {
	printf("Error in initializing writebuf on node %d\n", mynod);
	MPI_Abort(MPI_COMM_WORLD, 1);
    }
/* end of initialization */

    /* write the array to the file */
    MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_RDWR 
                  | MPI_MODE_UNIQUE_OPEN, MPI_INFO_NULL, &fh);
    MPI_File_set_view(fh, 0, MPI_INT, newtype, "native", MPI_INFO_NULL);
    MPI_File_write_all(fh, writebuf, bufcount, MPI_INT, &status);
    MPI_File_close(&fh);


    /* now read it back */
    readbuf = (int *) malloc(bufcount * sizeof(int));
    MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | MPI_MODE_RDWR 
                  | MPI_MODE_UNIQUE_OPEN, MPI_INFO_NULL, &fh);
    MPI_File_set_view(fh, 0, MPI_INT, newtype, "native", MPI_INFO_NULL);
    MPI_File_read_all(fh, readbuf, bufcount, MPI_INT, &status);
    MPI_File_close(&fh);

    /* check the data read */
    flag = 0;
    for (i=0; i<bufcount; i++) 
	if (readbuf[i] != writebuf[i]) {
	    printf("Node %d, readbuf %d, writebuf %d, i %d\n", mynod, readbuf[i], writebuf[i], i);
            flag = 1;
	}
    if (!flag) printf("Node %d: data read back is correct\n", mynod);

    MPI_Type_free(&newtype);
    free(readbuf);
    free(writebuf);
    free(filename);

    MPI_Finalize();
}
