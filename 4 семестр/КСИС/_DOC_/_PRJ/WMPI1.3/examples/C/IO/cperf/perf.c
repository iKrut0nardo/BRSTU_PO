/* A simple performance test. The file name is taken as a 
   command-line argument. 

*/

#include "mpio.h"

#define SIZE (1048576*4)       /* read/write size per node in bytes */

void main(int argc, char **argv)
{
    int *buf, i, j, mynod, nprocs, nints, ntimes=5, len;
    double stim, read_tim, write_tim, new_read_tim, new_write_tim;
    double min_read_tim=10000000.0, min_write_tim=10000000.0, read_bw, write_bw;
    MPI_File fh;
    MPI_Status status;
    char *filename;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &mynod);

/* process 0 takes the file name as a command-line argument and 
   broadcasts it to other processes */
    if (!mynod) {
	i = 1;
	while ((i < argc) && strcmp("-fname", *argv)) {
	    i++;
	    argv++;
	}
	if (i >= argc) {
	    printf("\n*#  Usage: perf -fname filename\n");
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
	printf("Access size per process = %d bytes, ntimes = %d\n", SIZE, ntimes);
    }
    else {
	MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
	filename = (char *) malloc(len+1);
	MPI_Bcast(filename, len+1, MPI_CHAR, 0, MPI_COMM_WORLD);
    }


    buf = (int *) malloc(SIZE);
    nints = SIZE/4;

    for (j=0; j<ntimes; j++) {
	MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | 
             MPI_MODE_RDWR | MPI_MODE_UNIQUE_OPEN, MPI_INFO_NULL, &fh);
	MPI_File_seek(fh, mynod*SIZE, MPI_SEEK_SET);

	MPI_Barrier(MPI_COMM_WORLD);
	stim = MPI_Wtime();
	MPI_File_write(fh, buf, SIZE, MPI_BYTE, &status);
	write_tim = MPI_Wtime() - stim;
  
	MPI_File_close(&fh);

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | 
                   MPI_MODE_RDWR | MPI_MODE_UNIQUE_OPEN, MPI_INFO_NULL, &fh);
	MPI_File_seek(fh, mynod*SIZE, MPI_SEEK_SET);
      
	MPI_Barrier(MPI_COMM_WORLD);
	stim = MPI_Wtime();
	MPI_File_read(fh, buf, SIZE, MPI_BYTE, &status);
	read_tim = MPI_Wtime() - stim;
  
	MPI_File_close(&fh);
  
	MPI_Allreduce(&write_tim, &new_write_tim, 1, MPI_DOUBLE, MPI_MAX,
		      MPI_COMM_WORLD);
	MPI_Allreduce(&read_tim, &new_read_tim, 1, MPI_DOUBLE, MPI_MAX,
		    MPI_COMM_WORLD);

	min_read_tim = (new_read_tim < min_read_tim) ? 
	    new_read_tim : min_read_tim;
	min_write_tim = (new_write_tim < min_write_tim) ? 
	    new_write_tim : min_write_tim;
    }
    
    if (mynod == 0) {
	read_bw = (SIZE*nprocs)/(min_read_tim*1000000.0);
	write_bw = (SIZE*nprocs)/(min_write_tim*1000000.0);
	printf("Write bandwidth without file sync = %f Mbytes/sec\n", write_bw);
	printf("Read bandwidth without prior file sync = %f Mbytes/sec\n", read_bw);
    }

    min_write_tim=10000000.0;
    min_read_tim=10000000.0;

    for (j=0; j<ntimes; j++) {
	MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | 
                 MPI_MODE_RDWR | MPI_MODE_UNIQUE_OPEN, MPI_INFO_NULL, &fh);
	MPI_File_seek(fh, mynod*SIZE, MPI_SEEK_SET);

	MPI_Barrier(MPI_COMM_WORLD);
	stim = MPI_Wtime();
	MPI_File_write(fh, buf, SIZE, MPI_BYTE, &status);
	MPI_File_sync(fh);
	write_tim = MPI_Wtime() - stim;
  
	MPI_File_close(&fh);
  
	MPI_Barrier(MPI_COMM_WORLD);

	MPI_File_open(MPI_COMM_WORLD, filename, MPI_MODE_CREATE | 
                   MPI_MODE_RDWR | MPI_MODE_UNIQUE_OPEN, MPI_INFO_NULL, &fh);
	MPI_File_seek(fh, mynod*SIZE, MPI_SEEK_SET);
      
	MPI_Barrier(MPI_COMM_WORLD);
	stim = MPI_Wtime();
	MPI_File_read(fh, buf, SIZE, MPI_BYTE, &status);
	read_tim = MPI_Wtime() - stim;
  
	MPI_File_close(&fh);
  
	MPI_Allreduce(&write_tim, &new_write_tim, 1, MPI_DOUBLE, MPI_MAX,
		      MPI_COMM_WORLD);
	MPI_Allreduce(&read_tim, &new_read_tim, 1, MPI_DOUBLE, MPI_MAX,
		    MPI_COMM_WORLD);

	min_read_tim = (new_read_tim < min_read_tim) ? 
	    new_read_tim : min_read_tim;
	min_write_tim = (new_write_tim < min_write_tim) ? 
	    new_write_tim : min_write_tim;
    }

    if (mynod == 0) {
	read_bw = (SIZE*nprocs)/(min_read_tim*1000000.0);
	write_bw = (SIZE*nprocs)/(min_write_tim*1000000.0);
	printf("Write bandwidth including file sync = %f Mbytes/sec\n", write_bw);
	printf("Read bandwidth after file sync = %f Mbytes/sec\n", read_bw);
    }


    free(buf);
    free(filename);
    MPI_Finalize();
}
