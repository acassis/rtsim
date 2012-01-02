/*   FILE:

         rm-st.c

    DESCRIPTION:


         Implements Rate-Monotonic Small-Tasks partitioned multiprocessor real-time
         scheduling algorithm*

         *Burchard, A., Liebeherr, J., Oh, Y., and Son, S.H. New Strategies for Assigning
          Real-Time Tasks to Multiprocessor Systems. IEEE Transactions on Computers,
          44(12):1429-1442, Dec 1995

         To execute the program:

            $ ./rm-st m file

            where

            "m" indicates the number of identical processors; if m=0, the number of
             processors is infinite,

            "file" contains the task's parameters, ordered in this fashion
            (a line per task):

                  period   execution-time

          Output:

             0  indicates that the task set can not be scheduled on m processors

             n  indicates the number of processor on which the task set can be feasible scheduled

            See README file for details.

        To compile the program:

            $ gcc -o rm-st rm-st.c -lm

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

#include "rm_st.h"


processor_t*  start_rm_st(int nproc, char *file )
{

	DBG("Planning by [rm st]");
	
	

task_set_t *t=NULL;                 /* Head of task set's list */
processor_t *p=NULL;                /* Head of processor's list */

int n;                             /* Number of tasks */
int m;                             /* Number of processors */
float util;                        /* system's total utilization  */
double bound;                      /* schedulability bound (Liu and Layland)  */


   FILE *in_file;  /* Input file */

   int no_proc, i, task_not_assigned;
   char line[80];  /* Input line */
   float period, wcet,phase;
   task_set_t new_task;            /* List pointers */
   task_set_t *task;
   processor_t new_processor;
   processor_t *current_processor;
   float s, beta;

   /*if (argc != 3) {
     DBG("You must supply the number of processors ( 0 = infinite ), and a file name with the task set parameters (see README file for details)\n");
     return;
   }*/

   no_proc = nproc;
   if (no_proc < 0) {
      DBG("Error: number of processor must be >= 0 (%s)\n", no_proc);
      return NULL;
   }

   in_file = fopen(file, "r");
   if (in_file == NULL) {
      DBG("Error:Unable to open %s file\n", file);
      return NULL;
   }

    /*
     * Read in data
     */

   n = 0;
   while (1) {
      if (fgets(line, sizeof(line),  in_file) == NULL)
         break;

      /* convert number */
      if (line[0] != '#') {
         sscanf(line, "%f%f%f", &period, &wcet,&phase);
	 new_task.id = ++n;
	 new_task.t= (double) period;
	 new_task.c= (double) wcet;
	 new_task.f = (double) phase;
         new_task.s = log10(new_task.t)/log10(2)  - floor( log10(new_task.t)/log10(2) );  /* get Si */
         t = add_task_list_s_sorted(t, new_task);                                      /* sort tasks by Si  */
         //DBG("added task %d =\t%.2f\t%.2f\t%.4f\n", new_task.id, new_task.t, new_task.c, new_task.s);
     }
   }

   if (!n) {
      DBG("Error: empty file %s\n", file);
      return;
   }
//    DBG("No of tasks = %d\n", n);
//    print_task_list(t);

    /*
     * Get System's Utilization
     */
   // DBG("\nTask's utilization:\n");
   util = 0.0;

   task = t;
   while (task) {
      util += task -> c/task -> t;     /* Ui = Ci/Ti  */
      // DBG("u(%d) = %f\n", task -> id, task -> c/task -> t);
      task = (task_set_t *) task -> next;
   }
//    DBG("\nTotal utilization of task set = %f\n", util);
//    if (no_proc)
//       DBG("\nTotal utilization of multiprocessor system = %f\n\n", util/no_proc);
//    else
//       DBG("\n");

   /*
    * Apply RM-ST algorithm
    */

   m=1;                                               /* current processor */
   new_processor.id = m;                              /* create first processor */
   new_processor.u = 0.0;
   new_processor.n = 0;
   new_processor.status = PROCESSOR_BUSY;
   new_processor.task = NULL;
   p = add_processor_list(p, new_processor);
   current_processor = p;

   s = 0.0;
   task = t;                          /* assign tasks to processors */
   while (task) {
      util = current_processor -> u  + task -> c / task -> t;         /* check if task can be assigned to current processor */
      // DBG("\nUtil current processor %d = %.4f\n", current_processor -> id, util);

      if (current_processor -> n) {
         beta = task -> s - s;
         bound = 1 - (beta * log(2));
         if ( log(2) > bound ) {
            bound =   log(2);
         }
      } else {
         bound = 1;              /* it is an empty processor */
      }

      // DBG("bound = %.4f\n", bound);
      if (util <= bound) {
         current_processor -> u = util;
         current_processor -> n++;
         // DBG("current processor -> %d\n", current_processor -> id);
         new_task.id = task -> id;
         new_task.c = task -> c;
         new_task.t = task -> t;
         current_processor -> task = add_task_list(current_processor -> task, new_task);
         // DBG("task %d assigned to processor %d\n", task -> id, current_processor -> id);
         s = task -> s;
         task = (task_set_t *) task -> next;
      } else {                          /* otherwise, use an empty (new) processor */
         // DBG("\nUsing new processor\n");
         m++;                                               /* current processor */
         new_processor.id = m;                              /* create first processor */
         new_processor.u = 0.0;
         new_processor.n = 0;
         new_processor.status = PROCESSOR_BUSY;
         new_processor.task = NULL;
         p = add_processor_list(p, new_processor);
         current_processor = get_processor_pointer(p, m);
      }
   }
//    DBG("Task assigned to %d processors:\n", m);
//    print_processor_list(p);
   if (no_proc) {
      if (m <= no_proc) {
	 LOG("\n[rm st] Schedulable using %d processors", m);
	DBG("\n[rm st] Schedulable using %d processors", m);
	
	
	 return p;
      } else {
	 LOG("\n[rm st] Not schedulable using %d processors, processors required %d", no_proc, m);
	DBG("[rm st] Not schedulable required processors %d", m);
	 return NULL;
      }
   } else {
      LOG("\n[rm st] Schedulable using %d processors", m);
	DBG("\n[rm st] Schedulable using %d processors", m);
      return p;
   }
   return NULL;
}

processor_t*  start_rm_st_main(int argc, char *argv[] )
{
   if (argc != 3) {
     DBG("You must supply the number of processors ( 0 = infinite ), and a file name with the task set parameters (see README file for details)\n");
     return NULL;
   }

	return start_rm_st(atoi(argv[1]), argv[2]);
   
}
