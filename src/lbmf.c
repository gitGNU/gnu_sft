/*
    lbmf.c - line based manipulation functions
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

#include <stdlib.h>
#include <string.h>
#include "s_malloc.h"

/* remove excess spaces */

void
rm_col (char *line)
{
  int i = 0;
  int j = 0;
  int smax_len = strlen(line);
  
  char *eval_string = (char *) s_malloc ( smax_len + 1 );
  char *ret_string = (char *) s_malloc ( smax_len + 1 );


  memset(ret_string, 0x0, (smax_len +1));
  strcpy(eval_string, line);

  /* remove first tab; if exists */
  if (eval_string[0] == '\t')
    eval_string[0] = ' ';

  /* remove excess spaces */
  for (i = 0; i != smax_len; i++)
    {
      if (i != smax_len)
	{
	  /* remove all tabs */
	  if (eval_string[i+1] == '\t')
	    eval_string[i+1] = ' ';
	  
	  
	  if (!((eval_string[i] == ' ') && (eval_string[i+1] == ' ')))
	    {
	      ret_string[j] = eval_string[i];
	      j++;
	    }
	}
    }
  
  strcpy(line, ret_string);
  free(eval_string);
  free(ret_string);
}

