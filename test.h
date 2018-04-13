/*
* test.h
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

void                 init_win_                   ();
void                 end_win                     ();
void                 xgetch                      ();

char*                read_string_from_file       (char* filename);

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
/* Window params */
WINDOW *local_win;
int height;
int width;
int startx;
int starty;

/*const char* thing =
  "Cuando despertó, el dinosaurio todavía estaba allí"; */
char* thing = NULL;
