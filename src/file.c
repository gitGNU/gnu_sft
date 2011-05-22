/*
    file.c - file handling for tsft
    Copyright (C) 2004  Michael J. Flickinger

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/stat.h>

#include "options.h"
#include "lbmf.h"


/* process file */

void
process_file (char *file_name, struct poptions *soptions)
{
  struct stat sbuf;

  char *line = NULL;
  size_t len = 0;
  int i = 1;

  FILE *fp = fopen(file_name, "r");

  if (fp == NULL)
    {
      perror("Could not load");
      exit(EXIT_FAILURE);
    }
  
  if (lstat(file_name, &sbuf) == -1)
    {
      fprintf(stderr, "error: could not lstat.\n");
      exit(EXIT_FAILURE);
    }
  
   if(S_ISDIR(sbuf.st_mode))
     {
       fprintf(stderr, "error: '%s' is a directory.\n", file_name);
       exit(EXIT_FAILURE);
     }
   
   while ((getline(&line, &len, fp)) != -1)
     {           
       /* do we want to remove spaces */
      if (soptions->spaces == 1)
	rm_col(line);
      
      /* number line */
      if (soptions->number == 1)
	printf("%05i  %s", i, line);
      else
        printf("%s", line);
      
      i++;
     }
   
   if (line != NULL)
     free(line);
   
   fclose(fp);
}



/* process stream */

void
process_stream (struct poptions *soptions)
{
  char *line = NULL;
  
  size_t len = 0;
  
  int i = 1;

  while ((getline(&line, &len, stdin)) != -1)
    {
      /* do we want to remove spaces */
      if (soptions->spaces == 1)
        rm_col(line);
      
      /* number line */
      if (soptions->number == 1)
        printf("%05i  %s", i, line);
      else
        printf("%s", line);

      i++;
    }
  
  if (line != NULL)
    free(line);
}
