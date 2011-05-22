/* 
    main.c - main driver for sft
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "options.h"
#include "version.h"
#include "file.h"

/* parse help option */
void 
hprint (char *commands, char *explain)
{
  printf("   %s\t\t%s\n", commands, explain);
}


/* display help */
void 
show_help()
{
  printf("Options:\n");
  hprint("-f, --file", "input file, if undeclared stdin is processed");
  hprint("-s, --spaces", "rids of access spaces and tabs");
  hprint("-n, --number", "number lines");
}


/* display usage */
void
usage (char *progname)
{
  printf("Usage: %s [options]\n", progname);
  printf("Try `%s --help' for more information.\n", progname);
}



int
main (int argc, char **argv)
{

  char *in_file = NULL;  
  int c; 

  struct poptions soptions;
  soptions.spaces = 0;
  soptions.whitespace = 0;
  soptions.number = 0;
  

  while (1)
  {
    
    static struct option long_options[] =
    {
      {"spaces",  no_argument,       0, 's'},
      {"whitespace",  no_argument,   0, 'w'},
      {"number",  no_argument,       0, 'n'},
      {"help",  no_argument,         0, 'h'},
      {"version",  no_argument,      0, 'v'},
      {"file",    required_argument, 0, 'f'},
      {0, 0, 0, 0}
    };

    int option_index = 0;
    
    c = getopt_long (argc, argv, "swnvhf:", long_options, &option_index);
    
    if (c == -1)
      break;

    switch (c)
      {
      case 's':
	soptions.spaces = 1;
	break;
	
      case 'n':
        soptions.number = 1;
        break;

      case 'w':
        soptions.whitespace = 1;
        break;

      case 'v':
	printf("sft - stream formatting tool\n");
	printf("Version: %s\n", VERSION);
	exit(EXIT_SUCCESS);

	break;
	
      case 'f':
	in_file = optarg;
	break;
	
      case 'h':
	usage(argv[0]);
	show_help();
	exit(EXIT_SUCCESS);

      default:
	usage(argv[0]);
	exit(EXIT_FAILURE);
	break;
	
      }
  }


  /* check for proper amount of args in argv */
  if (!soptions.spaces && !soptions.whitespace && !soptions.number)
    {
      usage(argv[0]);
      exit(EXIT_FAILURE);
    }
  
  
  if ((argc < 2) && !in_file)
    {
      usage(argv[0]);
      exit(EXIT_FAILURE);
    }
  
  if ((argc < 4) && in_file)
    {
      usage(argv[0]);
      exit(EXIT_FAILURE);
    }
  
  
  /* handle file input */
  if (in_file)
    process_file(in_file, &soptions);
  else
    process_stream(&soptions);
  
  return 0;
}
