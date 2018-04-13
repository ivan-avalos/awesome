/*
* test.c
*
* Copyright (C) 2018 - Ivan Avalos
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <curses.h>

#include "test.h"

int
main(int argc,
     char** argv)
{
  /* Check parameters */
  if(argc < 2) {
    fprintf(stderr, "Error: missing argument\n");
    exit (-1);
  }

  thing = read_string_from_file (argv[1]);

  init_fake_sh ();
  init_rng ();

  /* Something */
  something_t* something;
  something = do_something_with_something (thing);
  something_do_something (something);

  /* Something awesome */
  something_awesome_t* something_awesome;
  something_awesome = do_something_awesome_with_some_something (something);
  something_awesome_do_something_awesome (something_awesome);

  /* Responsability */
  undo_something_with_some_something (something);
  undo_something_awesome_with_some_something_awesome (something_awesome);
  free (thing);

  terminate_fake_sh ();

  return 0;
}

void init_rng ()
{
  /* Use time as seed */
  srand(time(NULL));
}

void init_fake_sh ()
{

  /* Init Ncurses */
  initscr ();
  cbreak ();
  keypad(stdscr, TRUE);

  /* Color */
  start_color ();
  init_pair (1, COLOR_BLACK, COLOR_RED);
  init_pair (2, COLOR_BLUE, COLOR_WHITE);
  refresh ();

  /* Init window */
  init_win_ ();

  refresh ();

  wattron (local_win, COLOR_PAIR (1));

  char* short_thing;
  if (strlen(thing) > 50) {
    short_thing = (char*) malloc (54*sizeof(char));
    memcpy (short_thing, thing, 50);
    short_thing[50] =
      short_thing[51] =
      short_thing[52] = '.';
    short_thing[53] = '\0';
  } else {
    short_thing = thing;
  }

  wprintw(local_win, "%% load_str \"%s\"\n", short_thing);
  wattroff (local_win, COLOR_PAIR (1));

  wrefresh (local_win);

  xgetch();
  wprintw(local_win, "[SUCCESS]\n");
  wrefresh (local_win);
}

void terminate_fake_sh ()
{
  wattron (local_win, COLOR_PAIR (1));
  wprintw(local_win, "%% exit");

  /* Terminate Ncurses */
  wrefresh (local_win);
  xgetch ();
  end_win ();
  endwin ();
}

void init_win_ ()
{

  height = LINES - 2;
  width = COLS - 2;
  startx = (COLS - width) /2;
  starty = (LINES - height) /2;

  local_win = newwin(height, width, starty, startx);
  wborder(local_win, '~', '|', '-', '-', '+', '+', '+', '+');

  wcolor_set(local_win, COLOR_PAIR(2), NULL);

  scrollok (local_win, TRUE);
  wsetscrreg(local_win, 1, height-2);

  wmove (local_win, 1, 2);

  wrefresh(local_win);
}

void end_win ()
{
  /* box(local_win, ' ', ' '); : This won't produce the desired
   * result of erasing the window. It will leave it's four corners 
   * and so an ugly remnant of window. 
   */
  wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
  /* The parameters taken are 
   * 1. win: the window on which to operate
   * 2. ls: character to be used for the left side of the window 
   * 3. rs: character to be used for the right side of the window 
   * 4. ts: character to be used for the top side of the window 
   * 5. bs: character to be used for the bottom side of the window 
   * 6. tl: character to be used for the top left corner of the window 
   * 7. tr: character to be used for the top right corner of the window 
   * 8. bl: character to be used for the bottom left corner of the window 
   * 9. br: character to be used for the bottom right corner of the window
   */
  wrefresh(local_win);
  delwin(local_win);
}

void xgetch ()
{
  switch(getchar())
    {
    case 13:
      return;
      break;
    default:
      xgetch ();
    }

  wrefresh (local_win);
}

char* read_string_from_file (char* filename)
{
  FILE* in_file;
  char* string;

  if ((in_file = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Error: Cannot open input file.\n");
    exit (-1);
  }

  size_t size;
  fseek (in_file, 0L, SEEK_END);
  size = ftell (in_file);
  rewind (in_file);

  string = (char*) malloc(size*sizeof(char));

  fread (string, sizeof(char), size, in_file);

  if (string == NULL || size <= 1) {
    fprintf (stderr, "Error: Input file is empty.\n");
    exit (-1);
  }

  fclose (in_file);

  return string;
}

something_t* do_something_with_something (char* thing)
{
  something_t* something;
  something = malloc (sizeof(something_t));

  /* a) Magic #1 - Replace vowels */
  something->some_a = (char*) malloc (strlen(thing)*sizeof(char));

  int i;
  for (i=0;i<strlen(thing);i++)
    {
      switch (thing[i])
	{
	case 'a':
	case 'A':
	  something->some_a[i] = 'e';
	  break;
	case 'e':
	case 'E':
	  something->some_a[i] = 'i';
	  break;
	case 'i':
	case 'I':
	  something->some_a[i] = 'o';
	  break;
	case 'o':
	case 'O':
	  something->some_a[i] = 'u';
	  break;
	case 'u':
	case 'U':
	  something->some_a[i] = 'a';
	  break;
	default:
	  something->some_a[i] = thing[i];
	}
    }

  /* b) Magic #2 - Generate hash xD */

  char hash = 0;
  for (i=0;i<strlen(thing);i++)
    {
      hash ^= thing[i];
    }
  something->some_b = hash;

  return something;
}

char* something_extract_some_a (something_t* something)
{
  return something->some_a;
}

char something_extract_some_b (something_t* something)
{
  return something->some_b;
}

void something_do_something (something_t* something)
{
  wattron (local_win, COLOR_PAIR (1));
  wprintw(local_win, "%% do something with something\n");
  wattroff (local_win, COLOR_PAIR (1));

  wrefresh (local_win);
  xgetch();

  wprintw(local_win, "> %s\n", something_extract_some_a (something));
  wprintw(local_win, "> %i\n", something_extract_some_b (something));

  wrefresh (local_win);
}

void undo_something_with_some_something (something_t* something)
{
  if (something->some_a != NULL)
    free (something->some_a);
  free (something);
}

something_awesome_t* do_something_awesome_with_some_something (something_t* something)
{
  something_awesome_t* something_awesome;
  something_awesome = malloc (sizeof(something_awesome_t));

  /* a) Awesome MAGIC #1 - Swap consonants */
  char* some_a;
  some_a = something_extract_some_a (something);
  something_awesome->some_awesome_a = (char*) malloc(strlen(some_a));
  int i;
  for (i=0;i<strlen(some_a);i++)
    {
      switch(some_a[i])
	{
	case 'b':
	case 'B':
	  something_awesome->some_awesome_a[i] = 'v';
	  break;
	case 'h':
	case 'H':
	  something_awesome->some_awesome_a[i] = '\'';
	  break;
	case 'm':
	case 'M':
	  something_awesome->some_awesome_a[i] = 'n';
	  break;
	case 'n':
	case 'N':
	  something_awesome->some_awesome_a[i] = 'm';
	  break;
	case 'p':
	case 'P':
	  something_awesome->some_awesome_a[i] = 'q';
	  break;
	case 'q':
	case 'Q':
	  something_awesome->some_awesome_a[i] = 'p';
	  break;
	case 'v':
	case 'V':
	  something_awesome->some_awesome_a[i] = 'b';
	  break;
	case 'y':
	case 'Y':
	  something_awesome->some_awesome_a[i] = 'i';
	  break;
	default:
	  something_awesome->some_awesome_a[i] = some_a[i];
	}
    }

  /* b) Awesome MAGIC #2 - Upper case, randomly */
  char* some_b;
  some_b = some_a;
  something_awesome->some_awesome_b = (char*) malloc (strlen(some_b));

  for(i=0;i<strlen(some_b);i++)
    {
      if (rand () % 2 == 0)
	{
	  switch(some_b[i])
	    {
	    case 'a':
	      something_awesome->some_awesome_b[i] = ' ';
	      break;
	    case 'e':
	      something_awesome->some_awesome_b[i] = '\'';
	      break;
	    case 'i':
	      something_awesome->some_awesome_b[i] = 'I';
	      break;
	    case 'o':
	      something_awesome->some_awesome_b[i] = 'O';
	      break;
	    case 'u':
	      something_awesome->some_awesome_b[i] = ' ';
	      break;
	    default:
	      something_awesome->some_awesome_b[i] = some_b[i];
	    }
	}
      else
	{
	  something_awesome->some_awesome_b[i] = some_b[i];
	}
    }

  return something_awesome;

}
char* something_awesome_extract_some_awesome_a (something_awesome_t* something_awesome)
{
  return something_awesome->some_awesome_a;
}
char* something_awesome_extract_some_awesome_b (something_awesome_t* something_awesome)
{
  return something_awesome->some_awesome_b;
}

void something_awesome_do_something_awesome (something_awesome_t* something_awesome)
{
  wattron (local_win, COLOR_PAIR (1));
  wprintw(local_win, "%% do something awesome with some something\n");
  wattroff (local_win, COLOR_PAIR (1));

  wrefresh (local_win);
  xgetch();

  wprintw(local_win, "> [awesome] %s\n", something_awesome_extract_some_awesome_a (something_awesome));
  wprintw(local_win, "> [awesome] %s\n", something_awesome_extract_some_awesome_b (something_awesome));

  wrefresh (local_win);
}

void undo_something_awesome_with_some_something_awesome (something_awesome_t* something_awesome)
{
  if (something_awesome->some_awesome_a != NULL)
    free (something_awesome->some_awesome_a);
  if (something_awesome->some_awesome_b != NULL)
    free (something_awesome->some_awesome_b);

  free (something_awesome);
}
