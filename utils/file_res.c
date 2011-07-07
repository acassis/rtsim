/*   FILE:

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


#include <stdio.h>
#include <math.h>
#include "../include/task.h"
#include "../include/processor.h"

//
//int  write_processor_list_task(processor_t* processors, char *file )
//{
//
//	task_set_t *t=NULL;                 /* Head of task set's list */
//	processor_t *p=NULL;                /* Head of processor's list */
//
//   FILE *in_file;  /* Input file */
//
//   int no_proc, i;
//   char line[80];  /* Input line */
//   float period, wcet;
//   task_set_t new_task;            /* List pointers */
//   task_set_t *task;
//   processor_t new_processor;
//   processor_t *current_processor;
//
//
//
//   no_proc = nproc;
//   if (no_proc < 0) {
//      LOG("Error: number of processor must be >= 0 (%s)\n", no_proc);
//      return NULL;
//   }
//
//   in_file = fopen(file, "r");
//   if (in_file == NULL) {
//      LOG("Error:Unable to open %s file\n", file);
//      return NULL;
//   }
//
//    /*
//     * Read in data
//     */
//
//   n = 0;
//   while (1) {
//      if (fgets(line, sizeof(line),  in_file) == NULL)
//         break;
//
//      /* convert number */
//      if (line[0] != '#') {
//         sscanf(line, "%f%f", &period, &wcet);
//         new_task.id = ++n;
//	 new_task.t = (double) period;
//         new_task.c = (double) wcet;
//         t = add_task_list_t_sorted(t, new_task);
//         // LOG("added task %d =\t%.2f\t%.2f\n", new_task.id, new_task.t, new_task.c);
//     }
//   }
//
//   if (!n) {
//      LOG("Error: empty file %s\n", file);
//      return;
//   }
////    LOG("No of tasks = %d\n", n);
////    print_task_list(t);
//
//    /*
//     * Get System's Utilization
//     */
//
//   // LOG("\nTask's utilization:\n");
//   util = 0.0;
//
//   task = t;
//   while (task) {
//      util += task -> c/task -> t;     /* Ui = Ci/Ti  */
//      // LOG("u(%d) = %f\n", task -> id, task -> c/task -> t);
//      task = (task_set_t *) task -> next;
//   }
////    LOG("\nTotal utilization of task set = %f\n", util);
////    if (no_proc)
////       LOG("\nTotal utilization of multiprocessor system = %f\n\n", util/no_proc);
////    else
////       LOG("\n");
//
//   /*
//    * Apply RM-NF algorithm
//    */
//
//   m=1;                                               /* current processor */
//   new_processor.id = m;                              /* create first processor */
//   new_processor.u = 0.0;
//   new_processor.n = 0;
//   new_processor.status = PROCESSOR_BUSY;
//   new_processor.task = NULL;
//   p = add_processor_list(p, new_processor);
//   current_processor = p;
//
//   task = t;                          /* assign tasks to processors */
//   while (task) {
//      util = current_processor -> u  + task -> c / task -> t;         /* check if task can be assigned to current processor */
//      // LOG("\nUtil current processor %d = %.4f\n", current_processor -> id, util);
//      if (current_processor -> n)
//         bound = (current_processor -> n + 1) * (pow(2, (double) 1/(current_processor -> n + 1)) - 1);
//      else
//         bound = 1;                        /* it is an empty processor */
//      // LOG("bound = %.4f\n", bound);
//      if (util <= bound) {
//         current_processor -> u = util;
//         current_processor -> n++;
//         // LOG("current processor -> %d\n", current_processor -> id);
//         new_task.id = task -> id;
//         new_task.c = task -> c;
//         new_task.t = task -> t;
//         current_processor -> task = add_task_list(current_processor -> task, new_task);
//         // LOG("task %d added to processor %d\n", task -> id, current_processor -> id);
//         task = (task_set_t *) task -> next;
//      } else {                          /* otherwise, use an empty (new) processor */
//         // LOG("\nUsing new processor\n");
//         m++;                                               /* current processor */
//         new_processor.id = m;                              /* create first processor */
//         new_processor.u = 0.0;
//         new_processor.n = 0;
//		new_processor.status = PROCESSOR_BUSY;
//		new_processor.task = NULL;
//         p = add_processor_list(p, new_processor);
//         // LOG("New processor added to list\n");
//         current_processor = get_processor_pointer(p, m);
//      }
//   }
////    LOG("Task assigned to %d processors:\n", m);
////    print_processor_list(p);
//
//   if (no_proc) {
//      if (m <= no_proc) {
//	 LOG("%d", m);
//	 return p;
//      } else {
//	 LOG("%d", 0);
//	 return NULL;
//      }
//   } else {
//      LOG("%d", m);
//      return p;
//   }
//
//
//}
