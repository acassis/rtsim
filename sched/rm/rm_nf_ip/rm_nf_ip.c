/*   FILE:

         rm-nf-ip.c

    DESCRIPTION:

         Implements Next-Fit-Rate-Monotonic partitioned multiprocessor real-time
         scheduling algorithm, using the IP condition*

         * Dhall, S.K. and Liu, C.L., On a Real-Time Scheduling Problem,
           Operations Research, 26(1):127-140, January 1978.


         To execute the program:

            $ ./rm-nf-ip m file

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

            $ gcc -o rm-nf-ip rm-nf-ip.c -lm

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

#include "rm_nf_ip.h"


processor_t*  start_rm_nf_ip(int nproc, char *file )
{
task_set_t *t=NULL;                 /* Head of task set's list */
processor_t *p=NULL;                /* Head of processor's list */

int n;                             /* Number of tasks */
int m;                             /* Number of processors */
float util;                        /* system's total utilization  */
double bound;                      /* schedulability bound  */


   FILE *in_file;  /* Input file */

   int no_proc, i, task_not_assigned;
   char line[80];  /* Input line */
   float period, wcet,phase;
   task_set_t new_task;            /* List pointers */
   task_set_t *task;
   processor_t new_processor;
   processor_t *current_processor;
   float power;



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
	 new_task.t  = (double) period;
	 new_task.c  = (double) wcet;
		 new_task.f = (double) phase;
         t = add_task_list_t_sorted(t, new_task);
         // LOG("added task %d =\t%.2f\t%.2f\n", new_task.id, new_task.t, new_task.c);
     }
   }


   if (!n) {
      LOG("Error: empty file %s\n", file);
      return;
   }

//    LOG("No of tasks = %d\n", n);
//    print_task_list(t);
//    getchar();

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
    * Apply RM-NF algorithm
    */

   m=1;                                               /* current processor */
   new_processor.id = m;                              /* create first processor */
   new_processor.u = 0.0;
   new_processor.n = 0;
   new_processor.status = PROCESSOR_BUSY;
   new_processor.task = NULL;
   p = add_processor_list(p, new_processor);
   current_processor = p;

   task = t;
   while (task) {
      util = task -> c / task -> t;         /* check if task can be assigned to current processor */
      // LOG("\nUtil current processor %d = %.4f\n", current_processor -> id, util);
      if (current_processor -> n)
         bound = 2 * pow( (1 + ( current_processor -> u / (current_processor -> n)) ), -1 * (current_processor -> n)) - 1;
      else
         bound = 1;                        /* it is an empty processor */
      // LOG("bound = %.4f\n", bound);
      if (util <= bound) {
         current_processor -> u += util;
         current_processor -> n++;
         // LOG("current processor -> %d\n", current_processor -> id);
         new_task.id = task -> id;
         new_task.c = task -> c;
         new_task.t = task -> t;
         current_processor -> task = add_task_list(current_processor -> task, new_task);
         // LOG("task %d added to processor %d\n", task -> id, current_processor -> id);
         task = (task_set_t *) task -> next;
      } else {                          /* otherwise, use an empty (new) processor */
         // LOG("\nUsing new processor\n");
         m++;                                               /* current processor */
         new_processor.id = m;                              /* create first processor */
         new_processor.u = 0.0;
         new_processor.n = 0;
	 new_processor.status = PROCESSOR_BUSY;
	 new_processor.task = NULL;
         p = add_processor_list(p, new_processor);
         // LOG("New processor added to list\n");
         current_processor = get_processor_pointer(p, m);
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

processor_t*  start_rm_nf_ip_main(int argc, char *argv[] )
{
   if (argc != 3) {
     LOG("You must supply the number of processors ( 0 = infinite ), and a file name with the task set parameters (see README file for details)\n");
     return NULL;
   }

	return start_rm_nf_ip(atoi(argv[1]), argv[2]);
   
}
