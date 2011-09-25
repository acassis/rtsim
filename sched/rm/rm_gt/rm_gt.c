/*   FILE:

         rm-gt.c

    DESCRIPTION:


         Implements Rate-Monotonic General-Tasks partitioned multiprocessor real-time
         scheduling algorithm*

         *Burchard, A., Liebeherr, J., Oh, Y., and Son, S.H. New Strategies for Assigning
          Real-Time Tasks to Multiprocessor Systems. IEEE Transactions on Computers,
          44(12):1429-1442, Dec 1995

         To execute the program:

            $ ./rm-gt m file

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

            $ gcc -o rm-gt rm-gt.c -lm

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

#include "rm_gt.h"


processor_t*  start_rm_gt(int nproc, char *file )
{
	DBG("Planificating by [rm gt]");
	
	
task_set_t *t=NULL;                 /* Head of task set's list 1 (alpha <= 1/3) */
task_set_t *t2=NULL;                /* Head of task set's list 2 (alpha > 1/3) */
processor_t *p=NULL;                /* Head of processor's list */

int n;                             /* Number of tasks */
int m;                             /* Number of processors */
float util;                        /* system's total utilization  */
double bound;                      /* schedulability bound (Liu and Layland)  */


   FILE *in_file;  /* Input file */

   int task_not_assigned, no_proc, i, k, is_schedulable;
   char line[80];                 /* Input line */
   float period, wcet,phase;
   task_set_t new_task;
   task_set_t *task, *task_in_proc;
   processor_t new_processor;
   processor_t *current_processor;
   float s, beta, condition1, condition2;

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
         if ( (new_task.c/new_task.t) <= (float) 1/3 ) {
            new_task.s = log10(new_task.t)/log10(2)  - floor( log10(new_task.t)/log10(2) );  /* get Si */
            t = add_task_list_s_sorted(t, new_task);                                      /* sort tasks by Si  */
            // DBG("added task %d to list 1 =\t%.2f\t%.2f\t%.4f\n", new_task.id, new_task.t, new_task.c, new_task.s);
         } else {
            t2 = add_task_list(t2, new_task);
         }
     }
   }

   if (!n) {
      DBG("Error: empty file %s\n", file);
      return;
   }
//    DBG("No of tasks list 1:\n");
//    print_task_list(t);
//    DBG("No of tasks list 2:\n");
//    print_task_list(t2);

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

   task = t2;
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
    * Apply RM-ST algorithm to task set of list 1 (alpha <= 1/3)
    */

   if (t) {                                    /* if there are tasks in t list */
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
            // DBG("task %d added to processor %d\n", task -> id, current_processor -> id);
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
   }

   /*
    * Apply RM-GT algorithm to task set of list 2 (alpha > 1/3)
    */

   if (t2) {                                      /* if there are tasks in t2 list */
      m++;                                        /* k = current processor index */
      k = m;
      new_processor.id = m;                       /* create first processor for t2 tasks */
      new_processor.u = 0.0;
      new_processor.n = 0;
      p = add_processor_list(p, new_processor);

      task = t2;                          /* assign ts tasks to processors */
      while (task) {
         util = task -> c / task -> t;
         current_processor = get_processor_pointer(p, k);        /* start from k'th processor */
         task_not_assigned = 1;
         while ( task_not_assigned ) {
            if ( (current_processor) && (current_processor -> n < 2)) {  /* processor is not full, we're going to check it */
               // DBG("checking processor %d\n", current_processor -> id);
               is_schedulable = 1;
               if (current_processor -> n) {           /* it has one task assigned to it */
                  // DBG("current processor has one task\n");
                  task_in_proc = current_processor -> task;
                  if (task -> t < task_in_proc -> t) { /* check if first schedulabilty condition is satisfied */
                     condition1 = floor( task_in_proc -> t / task -> t) * (task -> t - task -> c);
                     condition2 = ceil( task_in_proc -> t / task -> t) * task -> c + task_in_proc -> c;
                     if ( (condition1 <  task_in_proc -> c) &&  ( task_in_proc -> t < condition2 ) ) {
                        is_schedulable = 0;
                     }
                  }  else {  /* or if second schedulabilty condition is satisfied */
                     condition1 = floor( task -> t / task_in_proc -> t) * (task_in_proc -> t - task_in_proc -> c);
                     condition2 = ceil( task -> t / task_in_proc -> t) * task_in_proc -> c + task -> c;
                     if ( (condition1 <  task -> c) && (task_in_proc -> t < condition2) ) {
                        is_schedulable = 0;
                     }
                  }
               }
               if (is_schedulable) {  /* if schedulability condition is satisfied, or if it's an empty processor, assign task */
                  current_processor -> u += util;
                  current_processor -> n++;
                  // DBG("current processor -> %d\n", current_processor -> id);
                  new_task.id = task -> id;
                  new_task.c = task -> c;
                  new_task.t = task -> t;
                  current_processor -> task = add_task_list(current_processor -> task, new_task);
                  // DBG("task %d added to processor %d\n", task -> id, current_processor -> id);
                  task = (task_set_t *) task -> next;
                  task_not_assigned = 0;
               } else {                          /* otherwise, check next processor, if any */
                  current_processor = (processor_t *) current_processor -> next;
               }
            } else {                      /* last processor is full, we need an empty one */
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
   }
//    DBG("Task assigned to %d processors:\n", m);
//    print_processor_list(p);
   if (no_proc) {
      if (m <= no_proc) {
	 
	LOG("\n[rm gt] Planifacable using %d processors", m);
	DBG("\n[rm gt] Planifacable using %d processors", m);
	
	
	 return p;
      } else {
	 LOG("\n[rm gt] Not planifacable using %d processors, processors required %d", no_proc, m);
	DBG("[rm gt] Not planificable required processors %d", m);
	 return NULL;
      }
   } else {
      LOG("\n[rm gt] Planifacable using %d processors", m);
	DBG("\n[rm gt] Planifacable using %d processors", m);
      return p;
   }
   return NULL;
}

processor_t*  start_rm_gt_main(int argc, char *argv[] )
{
   if (argc != 3) {
     DBG("You must supply the number of processors ( 0 = infinite ), and a file name with the task set parameters (see README file for details)\n");
     return NULL;
   }

	return start_rm_gt(atoi(argv[1]), argv[2]);
   
}
