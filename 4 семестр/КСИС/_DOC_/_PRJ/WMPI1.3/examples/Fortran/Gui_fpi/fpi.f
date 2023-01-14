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
****************************************************************************
	subroutine 	MAIN
      include "mpif.h"	
	           
      double precision  PI25DT
      parameter        (PI25DT = 3.141592653589793238462643d0)

      double precision  mypi, pi, h, sum, x, f, a
      integer n, myid, numprocs, i, rc	

c                                 function to integrate
      f(a) = 4.d0 / (1.d0 + a*a)
      call MPI_INIT( ierr )

	call MPI_COMM_RANK( MPI_COMM_WORLD, myid, ierr )
      call MPI_COMM_SIZE( MPI_COMM_WORLD, numprocs, ierr )

      sizetype   = 1
      sumtype    = 2
      
 10   if ( myid .eq. 0 ) then
	call p_str('\nEnter the number of intervals: (0 quits)\n'C)
	call r_int(n)
      endif
      
      call MPI_BCAST(n,1,MPI_INTEGER,0,MPI_COMM_WORLD,ierr)

c                                 check for quit signal
      if ( n .le. 0 ) then
		goto 30
	endif

	if (myid .ne. 0) then
		call P_STR('\nSlave #'C)
		call P_INT(myid) 
		call P_STR('\n received interval\nComputation begins...'C)
	else
		call P_STR('\nMaster broadcasted interval\nComputation begins...
     &'C)
	endif
c                                 calculate the interval size
      h = 1.0d0/n

      sum  = 0.0d0
      do 20 i = myid+1, n, numprocs
         x = h * (dble(i) - 0.5d0)
         sum = sum + f(x)
 20   continue
      mypi = h * sum

	call P_STR('ends\nReduction begins...'C)
c                                 collect all the partial sums
      call MPI_REDUCE(mypi,pi,1,MPI_DOUBLE_PRECISION,MPI_SUM,0,
     $	 MPI_COMM_WORLD,ierr)

	call P_STR('ends\n'C)
c                                 node 0 prints the answer.
      if (myid .eq. 0) then
      call P_STR('pi is approximately: 'C)
	call P_DOUBLE(pi,10,0) 
	call P_STR('\nError is: 'C)
	call P_DOUBLE(abs(pi - PI25DT),10,1)
      endif

      goto 10

 30   call MPI_FINALIZE(rc)
      
      end




