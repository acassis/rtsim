/*   FILE:

         rbound-mp-nfr.c

    DESCRIPTION:

         Implements Next-Fit-Rate-Monotonic partitioned multiprocessor real-time
         scheduling algorithm*

        *Andersson, B. and Jonsson, J. The Utilization Bounds of Partitioned and Pfair
         Static-Priority Scheduling on multiprocessors are 50%. In Proceedings of the
         15th Euromicro Conference on Real-Time Systems, pages 33-40, Porto, Portugal,
         July 2003.

         To execute the program:

            $ ./rbound-mp-nfr m file

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

            $ gcc -o rbound-mp-nfr rbound-mp-nfr.c -lm

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

#include "rbound_mp_nfr.h"


processor_t*  start_rbound_mp_nfr(int nproc, char *file )
{

	DBG("Planificating by [rm rbound mp nfr]");
	

task_set_t *t=NULL, *tp=NULL;       /* Head of task set's list */
processor_t *p=NULL;                /* Head of processor's list */

int n;                             /* Number of tasks */
int m;                             /* Number of processors */
float util;                        /* system's total utilization  */
double bound;                      /* schedulability bound */
float r;                           /* period ratio */


   FILE *in_file;  /* Input file */

   int no_proc, i, use_empty_processor;
   char line[80];                       /* Input line */
   float period, wcet, phase;
   task_set_t new_task, last_task;
   task_set_t *task, *first_task;
   processor_t new_processor;
   processor_t *current_processor, *first_processor;

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
         t = add_task_list_t_sorted(t, new_task);
         // DBG("added task %d =\t%.2f\t%.2f\n", new_task.id, new_task.t, new_task.c);
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
      Apply ScaleTaskSet algorithm
  */

   task = t;
   while (task -> next)
      task = (task_set_t *) task -> next;

   if (task)
      last_task = *task;

   task = t;                                  /* transform n-1 tasks */
   while (task && task -> next) {
      new_task = *task;
      while (last_task.t/new_task.t >= 2.0) {
         new_task.t = (float) 2 * new_task.t;
         new_task.c = (float) 2 * new_task.c;
      }
      tp = add_task_list_t_sorted(tp, new_task);
      task = (task_set_t *) task -> next;
   }

   if (task && !task -> next)                                  /* add last tak wihtouth transform it */
      tp = add_task_list_t_sorted(tp, *task);

//    DBG("\nTransformed task set:\n");
//    print_task_list(tp);

   r = last_task.t / tp -> t;

   /*
    * Apply RBound-MP-NFR algorithm
    */

   m=1;                                               /* current processor */
   new_processor.id = m;                              /* create first processor */
   new_processor.u = 0.0;
   new_processor.n = 0;
   new_processor.status = PROCESSOR_BUSY;
   new_processor.task = NULL;
   p = add_processor_list(p, new_processor);
   first_processor = p;
   current_processor = p;

   task = tp;                          /* assign tasks to processors */
   while (task) {
      util = current_processor -> u  + task -> c / task -> t;         /* check if task can be assigned to current processor */
      // DBG("checking processor %d\n", current_processor -> id);
      if (current_processor -> n) {
        first_task = current_processor -> task;   /* the first task assigned to current processor */
        r = task -> t / first_task -> t;
        bound =  (current_processor -> n) * ( pow(r, (float) 1 / (float) current_processor -> n) - 1.0) + (float) 2.0 /r - 1.0;
      } else {
         bound = 1;
      }
      // DBG("bound = %.4f\n", bound);
      if (util <= bound) {
         current_processor -> u = util;
         current_processor -> n++;
         // DBG("current processor -> %d\n", current_processor -> id);
         new_task.id = task -> id;
         new_task.c = task -> c;
         new_task.t = task -> t;
         current_processor -> task = add_task_list_t_sorted(current_processor -> task, new_task);
         // DBG("task %d added to processor %d\n", task -> id, current_processor -> id);
         task = (task_set_t *) task -> next;
      } else {                             /* try to assign task to first processor */
         use_empty_processor = 1;
         if (current_processor != first_processor) {
            if (first_processor -> n) {
               first_task = first_processor -> task;   /* the first task assigned to current processor */
               r = task -> t / first_task -> t;
               bound =  (first_processor -> n) * ( pow(r, (float) 1 / (float) first_processor -> n) - 1.0) + (float) 2.0 /r - 1.0;
             } else {
                bound = 1;
             }
             if (util <= bound) {
                first_processor -> u = util;
                first_processor -> n++;
                // DBG("current processor -> %d\n", current_processor -> id);
                new_task.id = task -> id;
                new_task.c = task -> c;
                new_task.t = task -> t;
                first_processor -> task = add_task_list_t_sorted(first_processor -> task, new_task);
                // DBG("task %d added to processor %d\n", task -> id, current_processor -> id);
                task = (task_set_t *) task -> next;
                use_empty_processor = 0;
             }
         }
         if (use_empty_processor) {      /* otherwise, use an empty (new) processor */
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
   }
//    DBG("Task assigned to %d processors:\n", m);
//    print_processor_list(p);
   if (no_proc) {
      if (m <= no_proc) {
	 	LOG("\n[rm rbound mp nfr] Planifacable using %d processors", m);
	DBG("\n[rm rbound mp nfr] Planifacable using %d processors", m);
	
	
	 return p;
      } else {
	 LOG("\n[rm rbound mp nfr] Not planifacable using %d processors, processors required %d", no_proc, m);
	DBG("[rm rbound mp nfr] Not planificable required processors %d", m);
	
	 return NULL;
      }
   } else {
       	LOG("\n[rm rbound mp nfr] Planifacable using %d processors", m);
	DBG("\n[rm rbound mp nfr] Planifacable using %d processors", m);
      return p;
   }
   return NULL;
}

processor_t*  start_rbound_mp_nfr_main(int argc, char *argv[] )
{
   if (argc != 3) {
     DBG("You must supply the number of processors ( 0 = infinite ), and a file name with the task set parameters (see README file for details)\n");
     return NULL;
   }
	return start_rbound_mp_nfr(atoi(argv[1]), argv[2]);
}
