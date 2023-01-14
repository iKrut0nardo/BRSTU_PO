c**********************************************************************
c     matmul.f - matrix - vector multiply, simple self-scheduling version
c************************************************************************
      program Main

      include 'mpif.h'

      integer MAX_ROWS, MAX_COLS, rows, cols
      parameter (MAX_ROWS = 1000, MAX_COLS = 1000)
      double precision a(MAX_ROWS,MAX_COLS), b(MAX_COLS), c(MAX_COLS)
      double precision buffer(MAX_COLS), ans

      integer myid, master, numprocs, ierr, status(MPI_STATUS_SIZE)
      integer i, j, numsent, numrcvd, sender, job(MAX_ROWS)
      integer rowtype, anstype, donetype

      call MPI_INIT( ierr )
      call MPI_COMM_RANK( MPI_COMM_WORLD, myid, ierr )
	call MPI_COMM_SIZE( MPI_COMM_WORLD, numprocs, ierr )
      if (numprocs .lt. 2) then
         call p_str('Must have at least 2 processes!'C)
         call MPI_ABORT( MPI_COMM_WORLD, 1, ierr)
         stop
      endif

	call p_str('Process 'C)
	call p_int(myid)
	call p_str(' of 'C)
	call p_int(numprocs)
	call p_str('is alive\n'C)

c      print *, "Process ", myid, " of ", numprocs, " is alive"

      rowtype  = 1
      anstype  = 2
      donetype = 3

      master   = 0
      rows     = 100
      cols     = 100

      if ( myid .eq. master ) then
c        master initializes and then dispatches
c        initialize a and b
         do 20 i = 1,cols
            b(i) = 1
            do 10 j = 1,rows
               a(i,j) = i
 10         continue
 20      continue

         numsent = 0
         numrcvd = 0
         
c        send b to each other process
         call MPI_BCAST(b, cols, MPI_DOUBLE_PRECISION, master,
     $        MPI_COMM_WORLD, ierr)

c        send a row to each other process
         do 40 i = 1,numprocs-1
            do 30 j = 1,cols
               buffer(j) = a(i,j)
 30         continue
            call MPI_SEND(buffer, cols, MPI_DOUBLE_PRECISION, i,
     $           rowtype, MPI_COMM_WORLD, ierr)
            job(i)  = i
            numsent = numsent+1
 40      continue
         
         do 70 i = 1,rows
            call MPI_RECV(ans, 1, MPI_DOUBLE_PRECISION, MPI_ANY_SOURCE,
     $           anstype, MPI_COMM_WORLD, status, ierr)
            sender = status(MPI_SOURCE)
            c(job(sender)) = ans

            if (numsent .lt. rows) then
               do 50 j = 1,cols
                  buffer(j) = a(numsent+1,j)
 50            continue
               call MPI_SEND(buffer, cols, MPI_DOUBLE_PRECISION, sender,
     $              rowtype, MPI_COMM_WORLD, ierr)
               job(sender) = numsent+1
               numsent     = numsent+1
            else
            call MPI_SEND(1, 1, MPI_INTEGER, sender, donetype,
     $           MPI_COMM_WORLD, ierr)
            endif
 70      continue
         
c        print out the answer
         do 80 i = 1,cols
            call p_str('c('C)
		  call p_int(i)
		  call p_str(') = 'C)
		  call p_int(c(i))
		  call p_str('\n'C)
 80         continue
	
      call p_str('Press a key...')

	call r_int(i)

      else
c        slaves receive b, then compute dot products until done message
         call MPI_BCAST(b, cols, MPI_DOUBLE_PRECISION, master,
     $        MPI_COMM_WORLD, ierr)
 90      call MPI_RECV(buffer, cols, MPI_DOUBLE_PRECISION, master,
     $        MPI_ANY_TAG, MPI_COMM_WORLD, status, ierr)
         if (status(MPI_TAG) .eq. donetype) then
            go to 200
         else
            ans = 0.0
            do 100 i = 1,cols
               ans = ans+buffer(i)*b(i)
 100        continue
            call MPI_SEND(ans, 1, MPI_DOUBLE_PRECISION, master, anstype,
     $           MPI_COMM_WORLD, ierr)
            go to 90
         endif
      endif

 200  call MPI_FINALIZE(ierr)

	stop
      end




