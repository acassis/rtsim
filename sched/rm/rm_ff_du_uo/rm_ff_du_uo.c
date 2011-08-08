/*   FILE:

         rm-ff-du-uo.c

    DESCRIPTION:

         Implements First-Fit-Decreasing-Utilization Rate-Monotonic partitioned multiprocessor real-time
         scheduling algorithm, using UO condition* (we use equivalent HB condition** instead of UO conditon)

         * Oh, Y. and Son, S.H. Fixedpriority scheduling of periodic tasks on multiprocessor systems.
         Technical Report CS9516, Univ of Virginia, Deptof Computer Science, March 1995

         ** Bini, E, Butazzo, G. and Butazzo, G., "A Hyperbolic Bound for the
           Rate-Monotonic Algorithm", Proceedings of the 13th Euromicro Conference
           on Real-Time Systems, June 2001, pp. 59-65

         To execute the program:

            $ ./rm-ff-du-uo m file

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

            $ gcc -o rm-ff-du-uo rm-ff-du-uo.c -lm

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

#include "rm_ff_du_uo.h"


processor_t*  start_rm_ff_du_uo(int nproc, char *file )
{
task_set_t *t=NULL;                 /* Head of task set's list */
processor_t *p=NULL;                /* Head of processor's list */

int n;                             /* Number of tasks */
int m;                             /* Number of processors */
float util;                        /* system's total utilization  */
double bound;                      /* schedulability bound */


   FILE *in_file;  /* Input file */

   int no_proc, i, task_not_assigned;
   char line[80];            /* Input line */
   float period, wcet, phase;
   task_set_t new_task;
   task_set_t *task, *tp;
   processor_t new_processor;
   processor_t *current_processor;

   /*if (argc != 3) {
     LOG("You must supply the number of processors ( 0 = infinite ), and a file name with the task set parameters (see README file for details)\n");
     return;
   }*/

   no_proc = nproc;
   if (no_proc < 0) {
      LOG("Error: number of processor must be >= 0 (%s)\n", no_proc);
      return NULL;
   }

   in_file = fopen(file, "r");
   if (in_file == NULL) {
      LOG("Error:Unable to open %s file\n", file);
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
         t = add_task_list_u_sorted_desc(t, new_task);
         // LOG("added task %d =\t%.2f\t%.2f\n", new_task.id, new_task.t, new_task.c);
     }
   }

   if (!n) {
      LOG("Error: empty file %s\n", file);
      return;
   }
//    LOG("No of tasks = %d\n", n);
//    print_task_list(t);

    /*
     * Get System's Utilization
     */

   // LOG("\nTask's utilization:\n");
   util = 0.0;

   task = t;
   while (task) {
      util += task -> c/task -> t;     /* Ui = Ci/Ti  */
      // LOG("u(%d) = %f\n", task -> id, task -> c/task -> t);
      task = (task_set_t *) task -> next;
   }
//    LOG("\nTotal utilization of task set = %f\n", util);
//    if (no_proc)
//       LOG("\nTotal utilization of multiprocessor system = %f\n\n", util/no_proc);
//    else
//       LOG("\n");

   /*
    * Apply RM-FF-DU algorithm
    */

   m=1;                                               /* current processor */
   new_processor.id = m;                              /* create first processor */
   new_processor.u = 0.0;
   new_processor.n = 0;
   new_processor.status = PROCESSOR_BUSY;
   new_processor.task = NULL;
   p = add_processor_list(p, new_processor);

   task = t;                          /* assign tasks to processors */
   while (task) {
      util = task -> c / task -> t;
      current_processor = p;
      task_not_assigned = 1;
      while ( task_not_assigned ) {
         bound = util + (float) 1.0;
         tp = current_processor -> task;
         while (tp) {
            bound *= tp -> c/ tp -> t + (float) 1.0;
            tp = (task_set_t *) tp -> next;
         }
         // LOG("bound = %.4f\n", bound);
         if (bound <= 2) {
           current_processor -> u += util;
            current_processor -> n++;
            // LOG("current processor -> %d\n", current_processor -> id);
            new_task.id = task -> id;
            new_task.c = task -> c;
            new_task.t = task -> t;
            current_processor -> task = add_task_list(current_processor -> task, new_task);
            // LOG("task %d added to processor %d\n", task -> id, current_processor -> id);
            task = (task_set_t *) task -> next;
            task_not_assigned = 0;
         } else {                          /* otherwise, use an empty (new) processor */
            current_processor = (processor_t *) current_processor -> next;
         }
         if (!current_processor) {
            // LOG("\nUsing new processor\n");
            m++;                                               /* current processor */
            new_processor.id = m;                              /* create first processor */
            new_processor.u = 0.0;
            new_processor.n = 0;
            new_processor.status = PROCESSOR_BUSY;
            new_processor.task = NULL;
            p = add_processor_list(p, new_processor);
            // LOG("New process or added to list\n");
            current_processor = get_processor_pointer(p, m);
         }
      }
   }
//    LOG("Task assigned to %d processors:\n", m);
//    print_processor_list(p);
   if (no_proc) {
      if (m <= no_proc) {
	 LOG("%d", m);
	 return p;
      } else {
	 LOG("%d", 0);
	 return NULL;
      }
   } else {
      LOG("%d", m);
      return p;
   }
   return NULL;
}

processor_t*  start_rm_ff_du_uo_main(int argc, char *argv[] )
{
   if (argc != 3) {
     LOG("You must supply the number of processors ( 0 = infinite ), and a file name with the task set parameters (see README file for details)\n");
     return NULL;
   }

	return start_rm_ff_du_uo(atoi(argv[1]), argv[2]);
   
}