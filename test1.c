/*
Copyright 2013 Roger Gómez Castells
*/
/*
This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include "global.h"

extern void *surf3d[];

int main(){
  char **t= NULL;
	void *s1= NULL;
	if(t= decode(say(surf3d, "cmd@replicate:output@:"))){
		s1= (void *)((int)strToD(t[3]));
		free(code(&t));
	}
	if(s1){
		free(say(s1, "cmd@select:p3d@1:"));
		free(say(s1, "cmd@put:x@1.2:y@-3.4:z@8:"));
		if(t= decode(say(s1, "cmd@get:x@:y@:z@:"))){
			printf("%s\t%s\t%s\n", t[3], t[5], t[7]);
			free(code(&t));
		}
		free(say(s1, "cmd@select:p3d@2:"));
		if(t= decode(say(s1, "cmd@get:x@:y@:z@:"))){
			printf("%s\t%s\t%s\n", t[3], t[5], t[7]);
			free(code(&t));
		}
	}
	return 0;
}

/*
1.2     -3.4    8.
0.      0.      0.

*/

/*
an object of type surf3d contains three points or objects of type p3d.
that is, we can consider a surf3d type as multiple inheritance of three
p3d object type branches. because of multiple, we have first select one, 
but then we can talk to a surf3d object type as as we talk to a p3d one,
that is, a surf3d it is also a p3d type. that's inheritance, in that case,
multiple, without having to reprogram interface in each object innherited.
*/
