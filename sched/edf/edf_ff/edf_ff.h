/*   FILE:

         rm-nf-ll.h

    DESCRIPTION:

         Implements Next-Fit-Rate-Monotonic partitioned multiprocessor real-time
         scheduling algorithm*

        * Lopez, J.M., Diaz, J.L., and Garcia, D.F. Minimum and Maximum Utilization
          Bounds for Multiprocessor Rate Monotonic Scheduling, IEEE Transactions on
          Parallel and Distributed Systems15(7):642-653 Jul 2004

    Copyright (C) 2009

         Arnoldo Diaz Ramirez, Pedro Mejia Alvarez

   This is free software;  you can  redistribute it  and/or modify it under
   terms of the  GNU General Public License as published  by the Free Soft-
   ware  Foundation;  either version 2,  or (at your option) any later ver-
   sion.  It is distributed in the hope that it will be useful, but WITH-
   OUT ANY WARRANTY;  without even the  implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
   for  more details.  You should have  received  a copy of the GNU General
   Public License;  see file COPYING.  If not, write to  the Free Software
   Foundation,  59 Temple Place - Suite 330,  Boston, MA 02111-1307, USA.

   LAST REVISION:    June 2009                                                         */
#ifndef __EDF_FF__
#define __EDF_FF__


#include <stdio.h>
#include <math.h>
#include "simulator.h"
#include "task.h"
#include "processor.h"

extern processor_t*  start_edf_ff(int nproc, char *file );
extern processor_t*  start_edf_ff_main(int argc, char *argv[] );

#endif