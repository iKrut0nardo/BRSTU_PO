c**********************************************************************
c   pi.f - compute pi by integrating f(x) = 4/(1 + x**2)     
c     
c   Each node: 
c    1) receives the number of rectangles used in the approximation.
c    2) calculates the areas of it's rectangles.
c    3) Synchronizes for a global summation.
c   Node 0 prints the result.
c
c  Variables:
c
c    pi  the calculated result
c    n   number of points of integration.  
c    x           midpoint of each rectangle's interval
c    f           function to integrate
c    sum,pi      area of rectangles
c    tmp         temporary scratch space for global summation
c    i           do loop index
c****************************************************************************
      include "mpif.h"
      include "console_fpi.h"

      double precision  PI25DT
      parameter        (PI25DT = 3.141592653589793238462643d0)

      double precision  mypi, pi, h, sum, x, f, a
      integer n, myid, numprocs, i, rc	
	character*(20) string

c                                 function to integrate
      f(a) = 4.d0 / (1.d0 + a*a)
      call MPI_INIT( ierr )

	call MPI_COMM_RANK( MPI_COMM_WORLD, myid, ierr )
      call MPI_COMM_SIZE( MPI_COMM_WORLD, numprocs, ierr )

      sizetype   = 1
      sumtype    = 2
      
 10   if ( myid .eq. 0 ) then
	   string = 'Hello World!'
	   write(6,98)
 98      format(' Enter the number of intervals: (0 quits)')
         read(5,99) n
 99      format(i10)
      endif
      
      call MPI_BCAST(n,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)
	call MPI_BARRIER(MPI_COMM_WORLD, ierr)
	write(*,*) 'Hello',myid
      call MPI_BCAST(string,12,MPI_CHARACTER,0,MPI_COMM_WORLD,ierr)

c                                 check for quit signal
      if ( n .le. 0 ) goto 30

c                                 calculate the interval size
      h = 1.0d0/n

      sum  = 0.0d0
      do 20 i = myid+1, n, numprocs
         x = h * (dble(i) - 0.5d0)
         sum = sum + f(x)
 20   continue
      mypi = h * sum

c                                 collect all the partial sums
      call MPI_REDUCE(mypi,pi,1,MPI_DOUBLE_PRECISION,MPI_SUM,0,
     $	 MPI_COMM_WORLD,ierr)

c                                 node 0 prints the answer.
      if (myid .eq. 0) then
         write(6, 97) pi, abs(pi - PI25DT)
 97      format('  pi is approximately: ', F18.16,
     +          '  Error is: ', F18.16)
	else
		write (*,*) string
      endif

      goto 10

 30   call MPI_FINALIZE(rc)

      end

	SUBROUTINE MPI_BCAST_C(BUFFER, COUNT, DATATYPE, ROOT, COMM,
     &    IERROR) 
        CHARACTER*(*), INTENT(INOUT) :: BUFFER
          INTEGER, INTENT(IN)  :: COUNT
          INTEGER, INTENT(IN)  :: DATATYPE
          INTEGER, INTENT(IN)  :: ROOT
          INTEGER, INTENT(IN)  :: COMM
          INTEGER, INTENT(OUT) :: IERROR 

          EXTERNAL MPI_BCAST_STR
          CALL MPI_BCAST_STR(BUFFER,COUNT,DATATYPE,ROOT,COMM,IERROR)
      END SUBROUTINE  MPI_BCAST_C

	SUBROUTINE MPI_BCAST_I4(BUFFER, COUNT, DATATYPE, ROOT, COMM,
     &	IERROR) 
          INTEGER(4), INTENT(INOUT) :: BUFFER
          INTEGER, INTENT(IN)  :: COUNT
          INTEGER, INTENT(IN)  :: DATATYPE
          INTEGER, INTENT(IN)  :: ROOT
          INTEGER, INTENT(IN)  :: COMM
          INTEGER, INTENT(OUT) :: IERROR 

          EXTERNAL MPI_BCAST
          CALL MPI_BCAST(BUFFER,COUNT,DATATYPE,ROOT,COMM,IERROR)
      END SUBROUTINE  MPI_BCAST_I4



