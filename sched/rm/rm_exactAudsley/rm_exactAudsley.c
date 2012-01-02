/*   FILE:

         rm_exactAudsley.c

    DESCRIPTION:

         Verifies if a real-time task set is schedulable using the
         exact Audsley et al. Schedulability Test*

         * Audsley, N.; Burns, A.;  Richardson, M.;  Tindell, K.  and Wellings, A.J.,
           "Applying new scheduling theory to static priority pre-emptive
            scheduling", Software Engineering Journal, Vol. 8, pp. 284-292, Dec 1993

         To execute the program:

            $ ./exactAudsley file

            where "file" contains the task's parameters, ordered in this fashion
            (a line per task):

                  period   execution-time

            See README file for details.

        To compile the program:

            $ gcc -o exactAudsley exactAudsley.c -lm

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


#include "rm_exactAudsley.h"



int start_rm_exactAudsley(int nproc, char *file)
{

	DBG("Planning by [rm exactAudsley]");
	

	task_set_t *t=NULL;              /* Head of task set's list */
	int n;                           /* Number of tasks */
	FILE *in_file;  /* Input file */

	int i;
	char line[80];  /* Input line */
	task_set_t new_task, last_task;
	task_set_t *task;
	float r, s, x, period, wcet, phase;

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
		  new_task.id = ++n;
			new_task.t	= (double) period;
			new_task.c	= (double) wcet;
			new_task.f	= (double) phase;
		  t = add_task_list_t_sorted(t, new_task);
		  // printf("added task %d =\t%.2f\t%.2f\n", new_task.id, new_task.t, new_task.c);
	  }
	}

	if (!n) {
		DBG( "Error: empty file %s\n", file);
	  return -1;
	}

	// printf("\nNo of tasks = %d\n", n);
	//print_task_list(t);

	task = t;
	while (task -> next)
	  task = (task_set_t *) task -> next;

	if (task)
	  last_task = *task;

	/*
	  Check if task set is schedulable
	*/

	// printf("\nApplying schedulability test:\n");
	r = last_task.c;
	while (r <= last_task.t) {
	  s = last_task.c;
	  task = t;
	  while (task->next) {
		 s += ceil(r / task -> t) * task -> c;
	//         printf("s += x = %.2f\n", s);
		 task = (task_set_t *) task -> next;
	  }
	  //printf("r(n) = %.2f\n", r);
	  //printf("r(n+1) = %.2f\n\n", s);
	  if ( r == s ) {
		LOG("\n[rm exactAudsley] Schedulable ");
		DBG("\n[rm exactAudsley] Schedulable ");
		 //printf("The task set (%d tasks) is schedulable  by the RM algorithm\n", n);
		 //printf("%d", n);
		 return n;
	  } else {
		 r = s; // + last_task.c ;
	  }
	}

	
	LOG("\n[rm exactAudsley] Not schedulable");
	DBG("\n[rm exactAudsley] Not schedulable ");
	//printf("The complete task set is NOT schedulable by the RM algorithm\n");
	//printf("%d", 0);
	return 0;
}

int start_rm_exactAudsley_main(int argc, char *argv[])
{
	if (argc != 3) {
		DBG( "You must supply the number of processors ( 0 = infinite ), and a file name with the task set parameters (see README file for details)\n");
		return 0;
	}

	return start_rm_exactAudsley(atoi(argv[1]), argv[2]);

}
