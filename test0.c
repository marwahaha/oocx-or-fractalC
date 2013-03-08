/*
file test0.c from oocx project. example application and using of p3d type object.
Copyright (C) 2013 Roger Gómez Castells

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include "global.h"

extern void *p3d[];

int main(){
  char **t= NULL;
 	void *p1= NULL;
			
	if(t= decode(say(p3d, stringCopy("cmd@replicate:output@:")))){		
		p1= (void *)((int)strToD(t[3]));		
		free(code(&t));
	}				
	
	if(p1){		
		if(t= decode(say(p1, stringCopy("cmd@get:x@:z@:y@:")))){
			printf("\n%s\t%s\t%s", t[3], t[7], t[5]);
			free(code(&t));
		}
	
		free(say(p1, stringCopy("cmd@put:x@.1:"))); 
		free(say(p1, stringCopy("cmd@put:y@2.1:z@3.2:x@-1.2:")));	

		if(t= decode(say(p1, stringCopy("x@:cmd@get:")))){	
			printf("\n%s", t[1]);
			free(code(&t));
		}

		if(t= decode(say(p1, stringCopy("cmd@get:y@:z@:")))){
			printf("\t%s\t%s", t[3], t[5]);
			free(code(&t));
		}
	}
}

/*

0.      0.      0.
-1.2    2.1     3.2
*/
