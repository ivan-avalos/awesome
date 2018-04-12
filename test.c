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

typedef struct something
{
  char* some_a;
  char some_b;
} something_t;

typedef struct something_awesome
{
  char* some_awesome_a;
  char* some_awesome_b;
} something_awesome_t;

void                 init_rng                    ();
void                 init_fake_sh                ();
void                 terminate_fake_sh           ();

something_t*         do_something_with_something (char* thing);
char*                something_extract_some_a    (something_t* something);
char                 something_extract_some_b    (something_t* something);
void                 something_do_something      (something_t* something);
void                 undo_something_with_some_something
                                                 (something_t* something);

something_awesome_t* do_something_awesome_with_some_something
                                                (something_t* something);
char*                something_awesome_extract_some_awesome_a
                                                (something_awesome_t* something_awesome);
char*                something_awesome_extract_some_awesome_b
                                                (something_awesome_t* something_awesome);
void                 something_awesome_do_something_awesome
                                                (something_awesome_t* something_awesome);
void                 undo_something_awesome_with_some_something_awesome
                                                (something_awesome_t* something_awesome);

const char* thing =
  "Cuando despertó, el dinosaurio todavía estaba allí";

int
main(int argc,
     char** argv)
{

  init_fake_sh ();
  init_rng ();

  /* Something */
  something_t* something;
  something = do_something_with_something ((char*) thing);
  something_do_something (something);

  /* Something awesome */
  something_awesome_t* something_awesome;
  something_awesome = do_something_awesome_with_some_something (something);
  something_awesome_do_something_awesome (something_awesome);

  /* Responsability */
  undo_something_with_some_something (something);
  undo_something_awesome_with_some_something_awesome (something_awesome);

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
  start_color ();
  /*init_pair (1, COLOR_BLACK, COLOR_RED);*/
  init_pair (1, COLOR_GREEN, COLOR_BLACK);

  attron (COLOR_PAIR (1));
  printw("%% load_str \"%s\"", thing);
  attroff (COLOR_PAIR (1));

  getch();
  refresh ();

  printw("[SUCCESS]\n");
}

void terminate_fake_sh ()
{
  attron (COLOR_PAIR (1));
  printw("%% exit");

  /* Terminate Ncurses */
  refresh ();
  getch ();
  endwin ();
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
  attron (COLOR_PAIR (1));
  printw("%% do something with something");
  attroff (COLOR_PAIR (1));

  refresh ();
  getch();

  printw("a) %s\n", something_extract_some_a (something));
  printw("b) %i\n", something_extract_some_b (something));
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
  attron (COLOR_PAIR (1));
  printw("%% do something awesome with some something");
  attroff (COLOR_PAIR (1));

  refresh ();
  getch();

  printw("a) [awesome] %s\n", something_awesome_extract_some_awesome_a (something_awesome));
  printw("b) [awesome] %s\n", something_awesome_extract_some_awesome_b (something_awesome));
}

void undo_something_awesome_with_some_something_awesome (something_awesome_t* something_awesome)
{
  if (something_awesome->some_awesome_a != NULL)
    free (something_awesome->some_awesome_a);
  if (something_awesome->some_awesome_b != NULL)
    free (something_awesome->some_awesome_b);

  free (something_awesome);
}
