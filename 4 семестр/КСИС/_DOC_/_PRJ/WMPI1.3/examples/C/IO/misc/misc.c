/* Tests various miscellaneous functions.

*/

#include "mpio.h"

void Main(int argc, char **argv)
{
    int buf[1024], amode, flag, mynod, len, i;
    MPI_File fh;
    MPI_Status status;
    MPI_Datatype newtype;
    MPI_Offset disp, offset;
    MPI_Aint extent, extent1;
    MPI_Group group;
    MPI_Datatype etype, filetype;
    char datarep[25], *filename;

    MPI_Init(&argc,&argv);
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
	    printf("\n*#  Usage: misc -fname filename\n");
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


    MPI_File_open(MPI_COMM_SELF, filename, MPI_MODE_CREATE | MPI_MODE_RDWR
                  | MPI_MODE_UNIQUE_OPEN, MPI_INFO_NULL, &fh);

    MPI_File_write(fh, buf, 1024, MPI_INT, &status);

    MPI_File_sync(fh);

    MPI_File_get_amode(fh, &amode);
    printf("testing MPI_File_get_amode\n");
    printf("amode is %d, should be %d\n\n", amode, MPI_MODE_CREATE |
                      MPI_MODE_RDWR | MPI_MODE_UNIQUE_OPEN);

    MPI_File_get_atomicity(fh, &flag);
    printf("atomicity is %d, should be 0\n", flag);
    printf("setting atomic mode\n");
    MPI_File_set_atomicity(fh, 1);
    MPI_File_get_atomicity(fh, &flag);
    printf("atomicity is %d, should be 1\n", flag);
    MPI_File_set_atomicity(fh, 0);
    printf("reverting back to nonatomic mode\n\n");

    MPI_Type_vector(10, 10, 20, MPI_INT, &newtype);
    MPI_File_set_view(fh, 1000, MPI_INT, newtype, "native", MPI_INFO_NULL);
    printf("testing MPI_File_get_view\n");
    MPI_File_get_view(fh, &disp, &etype, &filetype, datarep);
    printf("disp = %d, datarep = %s, should be 1000, native\n\n", disp, datarep);

    printf("testing MPI_File_get_byte_offset\n");
    MPI_File_get_byte_offset(fh, 10, &disp);
    printf("byte offset = %d, should be 1080\n\n", disp);

    printf("testing MPI_File_get_type_extent\n");
    MPI_File_get_type_extent(fh, newtype, &extent);
    MPI_Type_extent(newtype, &extent1);
    printf("extent in file = %d, should be %d\n\n", extent, extent1);

    MPI_File_get_group(fh, &group);


    printf("setting file size to 1060 bytes\n");
    MPI_File_set_size(fh, 1060);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_File_sync(fh);
    MPI_File_get_size(fh, &disp);
    printf("file size = %d, should be 1060\n\n", disp);
 
    printf("seeking to eof and testing MPI_File_get_position\n");
    MPI_File_seek(fh, 0, MPI_SEEK_END);
    MPI_File_get_position(fh, &disp);
    printf("file pointer posn = %d, should be 10\n\n", disp);

    printf("testing MPI_File_get_byte_offset\n");
    MPI_File_get_byte_offset(fh, disp, &offset);
    printf("byte offset = %d, should be 1080\n\n", offset);
    MPI_Barrier(MPI_COMM_WORLD);

    printf("testing MPI_File_seek with MPI_SEEK_CUR\n");
    MPI_File_seek(fh, -10, MPI_SEEK_CUR);
    MPI_File_get_position(fh, &disp);
    MPI_File_get_byte_offset(fh, disp, &offset);
    printf("file pointer posn in bytes = %d, should be 1000\n\n", offset);

    printf("preallocating disk space up to 8192 bytes\n\n");
    MPI_File_preallocate(fh, 8192);

    printf("closing the file and deleting it\n\n");
    MPI_File_close(&fh);
    
    MPI_Barrier(MPI_COMM_WORLD);

    if (!mynod)
	MPI_File_delete(filename, MPI_INFO_NULL);

    free(filename);
    MPI_Finalize(); 
}
