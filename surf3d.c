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
#define INSTRnUM 2

struct surf3d{
  char *(*foo)(void *, char *);
	void *p1, *p2, *p3;
	int p3dSel;
};

extern struct surf3d surf3d[];
extern void *p3d[];

void *Surf3dReplicate(struct surf3d *ob){
	struct surf3d *ob2= malloc(sizeof(struct surf3d));
	*ob2= *ob;
	char **t= NULL;
	if(t= decode(say(p3d, "cmd@replicate:output@:"))){
		ob2->p1= (void *)((int)strToD(t[3]));
		free(code(&t));
	}
	if(t= decode(say(p3d, "cmd@replicate:output@:"))){
		ob2->p2= (void *)((int)strToD(t[3]));
		free(code(&t));
	}
	if(t= decode(say(p3d, "cmd@replicate:output@:"))){
		ob2->p3= (void *)((int)strToD(t[3]));
		free(code(&t));
	}
	if(ob2->p1&& ob2->p2&& ob2->p3){
		return ob2;
	}	
	if(ob2->p1){
		free(ob2->p1);
	}	
	if(ob2->p2){
		free(ob2->p2);
	}	
	if(ob2->p3){
		free(ob2->p3);
	}
	free(ob2);
	return NULL;
}

void Surf3dSelectP3d(struct surf3d *ob, int a){
	if(a== 1|| a== 2|| a== 3){
		ob->p3dSel= a;
	}
	else{
		ob->p3dSel= 0;
	}
}

char *Surf3dResend(struct surf3d *ob, char *mess){
	switch(ob->p3dSel){
		case 1:
			return say(ob->p1, mess);
		break;
		case 2:
			return say(ob->p2, mess);
		break;
		case 3:
			return say(ob->p3, mess);
		break;
	}
	return NULL;
}

double Surf3dArea(struct surf3d *ob){
	char **t1, **t2, **t3;
	t1= decode(say(ob->p1, "cmd@get:x@:y@:z@:"));
	t2= decode(say(ob->p2, "cmd@get:x@:y@:z@:"));
	t3= decode(say(ob->p3, "cmd@get:x@:y@:z@:"));
	double x1= strToD(t1[3]), y1= strToD(t1[5]), z1= strToD(t1[7]);
	double x2= strToD(t2[3]), y2= strToD(t2[5]), z2= strToD(t2[7]);
	double x3= strToD(t3[3]), y3= strToD(t3[5]), z3= strToD(t3[7]);
	free(code(&t1));
	free(code(&t2));
	free(code(&t3));
	double v1x= x2- x1, v1y= y2- y1, v1z= z2- z1;
	double v2x= x3- x1, v2y= y3- y1, v2z= z3- z1;
	
}

char *Surf3d(void *ob, char *mess){
	char **t= decode(mess), **t1;	
	char *mess1[INSTRnUM]=	{
	/*0*/	"cmd@replicate:output@:",
	/*1*/	"cmd@select:p3d@:"
	};
	int i;
	for(i= 0; i< INSTRnUM; i++){
		t1= decode(mess1[i]);	
		arrange(&t1, t);	
		if(t1){
			switch(i){
				case 0: 
					free(t1[3]);
					t1[3]= dToStr((int)Surf3dReplicate(ob));
				break;
				case 1:
					Surf3dSelectP3d(ob, strToD(t1[3]));
				break;
			}
			arrange(&t, t1);
			free(code(&t1));
			return code(&t);	
		}
	}
	free(code(&t));
	return Surf3dResend(ob, mess);
}

struct surf3d surf3d[1]= {
	Surf3d,
	NULL, NULL, NULL,
	0
};
