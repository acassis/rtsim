/*   FILE:

         rm_exactLehoczky.c

    DESCRIPTION:

         Verifies if a real-time task set is schedulable using the
         exact Lehoczky's Schedulability Test*

         * Lehoczky, J.P., Sha, L. and Ding, Y, "The rate-monotonic scheduling
           algorithm: exact characterization and average behavior", In Proceedings
           of IEEE Real-Time Systems Symposium, pp. 166-141 Dec 1989

         To execute the program:

            $ ./exactLehoczky file

            where "file" contains the task's parameters, ordered in this fashion
            (a line per task):

                  period   execution-time

            See README file for details.

        To compile the program:

            $ gcc -o exactLehoczky exactLehoczky.c -lm

    Copyright (C) 2008

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

   LAST REVISION:    Febraury 2008                                                         */


#include "rm_exactLehoczky.h"



int start_rm_exactLehoczky(int nproc, char *file)
{
	DBG("Planning by [rm exactLehoczky]");
	
	task_set_t *t=NULL;             /* Head of task set's list */
	int n, s_max;                   /* Number of tasks */
	s_t s_ele, *sp = NULL;          /* List of scheduling points */
	double bound;                   /* schedulability bound (Liu and Layland)  */

	FILE *in_file;  				/* Input file */

	int i, j, k, k_max;
	char line[80];  				/* Input line */
	task_set_t new_task, last_task;
	task_set_t *task;
	s_t *s_list;
	float w, period, wcet, phase;

	// if (argc != 2) {
	 // DBG("You must supply a file name (see README file for details)\n");
	 // return -1;
	// }

	in_file = fopen(file, "r");
	if (in_file == NULL) {
	  DBG("Error:Unable to open %s file\n", file);
	  return -1;
	}

	/*
	Read in data 
	*/
	n = 0;
	while (1) 
	{
	   if (fgets(line, sizeof(line),  in_file) == NULL)
		  break;

	   /* convert number */
		if (line[0] != '#') {
			sscanf(line, "%f%f%f", &period, &wcet, &phase);
			new_task.id	= ++n;
			new_task.t	= (double) period;
			new_task.c	= (double) wcet;
			new_task.f	= (double) phase;
			t = add_task_list_t_sorted(t, new_task);
			// DBG("added task %d =\t%.2f\t%.2f\n", new_task.id, new_task.t, new_task.c);
		}
	}

	if (!n) {
		DBG( "Error: empty file %s\n", file);
	  return -1;
	}

//    DBG("No of tasks = %d\n", n);
//    print_task_list(t);

	task = t;
	while (task -> next)
	  task = (task_set_t *) task -> next;

	if (task)
	  last_task = *task;
	/*
	  Get scheduling points (s) 
	*/

	s_max=0;
	task = t;
	while (task) {
	  k_max = (int) (last_task.t/task -> t);
	  for (k=1; k<=k_max; k++) {
		 s_ele.s = k * (int) task -> t;
		 sp = add_s_list_sorted_nd(sp, s_ele);
	  }
	  task = (task_set_t *) task -> next;
	}


	/*
	  Check if task set is schedulable
	*/

	//DBG("\nApplying schedulability test:\n");
	s_list = sp;
	while (s_list) {
	  w=0.0;
	  task = t;
	  while (task) {
		 w += task -> c * ( ceil( s_list -> s / task -> t) );
		 task = (task_set_t *) task -> next;
	  }
	  //DBG("w() = %.1f,\tt = %.1f\n", w, s_list -> s);
	  if ( w <=  s_list -> s) {
	  
	  
		LOG("\n[rm exactLehoczky] Schedulable");
		DBG("\n[rm exactLehoczky] Schedulable");
		 // DBG("\nFound w(): %.1f <= t: %.1f\n", w, s_list -> s);
		 //DBG("The task set (%d tasks) is schedulable  by the RM algorithm\n", n);
		 //DBG("%d", n);
		 return n;
	  }
	  s_list = (s_t *) s_list -> next;
	}

		
	LOG("\n[rm exactLehoczky] Not schedulable");
	DBG("[rm exactLehoczky] Not schedulable");
	//DBG("The complete task set is NOT schedulable by the RM algorithm\n");
	//DBG("%d", 0);
	return 0;
}

int start_rm_exactLehoczky_main(int argc, char *argv[])
{
	if (argc != 3) {
		DBG( "You must supply the number of processors ( 0 = infinite ), and a file name with the task set parameters (see README file for details)\n");
		return 0;
	}

	return start_rm_exactLehoczky(atoi(argv[1]), argv[2]);

}


