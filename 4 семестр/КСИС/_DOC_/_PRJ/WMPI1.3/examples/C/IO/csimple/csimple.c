/* Each process writes to separate files and reads them back. 
   The file name is taken as a command-line argument, and the process rank 
   is appended to it. 

*/ 

#include <windows.h>
#include "mpio.h"


#define SIZE (65536)


void main(int argc, char **argv)
{
    int *buf, i, rank, nints, len, flag;
    char *filename, *tmp;
    MPI_File fh;
    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

/* process 0 takes the file name as a command-line argument and 
   broadcasts it to other processes */
    if (!rank) {
		i = 1;
		while ((i < argc) && strcmp("-fname", *argv)) {
			i++;
			argv++;
		}


		if (i >= argc) {
			printf("\n*#  Usage: simple -fname filename\n");
		    printf("*#  The filename must be prefixed with a string to indicate\n"); 
		    printf("*#  the type of file system (nfs:, ufs:, pfs:, piofs:).\n");
			printf("*#  An example filename is nfs:test\n\n");
			MPI_Abort(MPI_COMM_WORLD, 1);
		}

		argv++;
		len = strlen(*argv);
		filename = (char *) malloc(len+1);
		strcpy(filename, *argv);
		printf("%s\n", filename);
		if (strncmp(filename, "pfs:",4) && strncmp(filename,"piofs:",6)
		&& strncmp(filename, "ufs:", 4) && strncmp(filename, "nfs:", 4)) {
			printf("\n*#  (2)The filename must be prefixed with a string to indicate\n"); 
			printf("*#  the type of file system (nfs:, ufs:, pfs:, piofs:).\n");
			printf("*#  An example filename is nfs:test\n\n");
			MPI_Abort(MPI_COMM_WORLD, 1);
		}
		MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(filename, len+1, MPI_CHAR, 0, MPI_COMM_WORLD);
    }else {
		MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
		filename = (char *) malloc(len+1);
		filename[0]=0;
		MPI_Bcast(filename, len+1, MPI_CHAR, 0, MPI_COMM_WORLD);
	  }
    

    buf = (int *) malloc(SIZE);
    nints = SIZE/sizeof(int);
    for (i=0; i<nints; i++) buf[i] = rank*100000 + i;

    /* each process opens a separate file called filename.'myrank' */
    tmp = (char *) malloc(len+1);
    strcpy(tmp, filename);
    sprintf(filename, "%s.%d", tmp, rank);


    MPI_File_open(MPI_COMM_SELF, filename, MPI_MODE_CREATE | MPI_MODE_RDWR
		   | MPI_MODE_UNIQUE_OPEN, MPI_INFO_NULL, &fh);
    MPI_File_set_view(fh, 0, MPI_INT, MPI_INT, "native", MPI_INFO_NULL);
    if(MPI_File_write(fh, buf, nints, MPI_INT, &status)!=MPI_SUCCESS){
		printf("ERROR\n");
		printf("%s\n", strerror(errno));
	}
   
    MPI_File_close(&fh);

    /* reopen the file and read the data back */

    for (i=0; i<nints; i++) buf[i] = 0;
    MPI_File_open(MPI_COMM_SELF, filename, MPI_MODE_CREATE | MPI_MODE_RDWR 
                  | MPI_MODE_UNIQUE_OPEN, MPI_INFO_NULL, &fh);
    MPI_File_set_view(fh, 0, MPI_INT, MPI_INT, "native", MPI_INFO_NULL);
    if(MPI_File_read(fh, buf, nints, MPI_INT, &status)!=MPI_SUCCESS){
		printf("ERROR READ\n");
		printf("%s\n", strerror(errno));
	}
    MPI_File_close(&fh);

    /* check if the data read is correct */
    flag = 0;
   for (i=0; i<nints; i++) 
	if (buf[i] != (rank*100000 + i)) {
	    printf("node %d: error, read %d, should be %d\n", rank, buf[i], rank*100000+i);
	    flag = 1;
	}

    if (!flag) printf("Node %d: data read back is correct\n", rank);
	 
    free(buf);
    free(filename);
    free(tmp);

	Sleep(5000);
	MPI_Finalize(); 

}
