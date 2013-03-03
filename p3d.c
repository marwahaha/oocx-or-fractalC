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
#define INSTRnUM 15

struct p3d{
  char *(*foo)(void *, char *);
	double x, y, z;
};

extern struct p3d p3d[];

void *P3dReplicate(struct p3d *ob){
	struct p3d *ob2= malloc(sizeof(struct p3d));
	*ob2= *ob;
	return ob2;
}

void P3dPutX(struct p3d *ob, double x){
	ob->x= x;
}

void P3dPutY(struct p3d *ob, double y){
	ob->y= y;
}

void P3dPutZ(struct p3d *ob, double z){
	ob->z= z;
}

double P3dGetX(struct p3d *ob){
	return ob->x;
}

double P3dGetY(struct p3d *ob){
	return ob->y;
}

double P3dGetZ(struct p3d *ob){
	return ob->z;
}

char *P3d(void *ob, char *mess){
	char **t= decode(mess), **t1;	
	char *mess1[INSTRnUM]=	{
	/*0*/	"cmd@replicate:output@:",
	/*1*/	"cmd@put:x@:",
	/*2*/	"cmd@put:y@:",
	/*3*/	"cmd@put:z@:",
	/*4*/	"cmd@put:x@:y@:",
	/*5*/	"cmd@put:x@:z@:",
	/*6*/	"cmd@put:y@:z@:",
	/*7*/	"cmd@put:x@:y@:z@:",
	/*8*/	"cmd@get:x@:",
	/*9*/	"cmd@get:y@:",
	/*10*/	"cmd@get:z@:",
	/*11*/	"cmd@get:x@:y@:",
	/*12*/	"cmd@get:x@:z@:",
	/*13*/	"cmd@get:y@:z@:",
	/*14*/	"cmd@get:x@:y@:z@:"
	};
	int i;
	for(i= 0; i< INSTRnUM; i++){
		t1= decode(mess1[i]);	
		arrange(&t1, t);	
		if(t1){
			switch(i){
				case 0: 
					free(t1[3]);
					t1[3]= dToStr((int)P3dReplicate(ob));
				break;
				case 1:
					P3dPutX(ob, strToD(t1[3]));
				break;
				case 2:
					P3dPutY(ob, strToD(t1[3]));
				break;
				case 3:
					P3dPutZ(ob, strToD(t1[3]));
				break;
				case 4:
					P3dPutX(ob, strToD(t1[3]));
					P3dPutY(ob, strToD(t1[5]));
				break;
				case 5:
					P3dPutX(ob, strToD(t1[3]));
					P3dPutZ(ob, strToD(t1[5]));
				break;
				case 6:
					P3dPutY(ob, strToD(t1[3]));
					P3dPutZ(ob, strToD(t1[5]));
				break;
				case 7:
					P3dPutX(ob, strToD(t1[3]));
					P3dPutY(ob, strToD(t1[5]));
					P3dPutZ(ob, strToD(t1[7]));
				break;
				case 8:
					free(t1[3]);
					t1[3]= dToStr(P3dGetX(ob));
				break;
				case 9:
					free(t1[3]);
					t1[3]= dToStr(P3dGetY(ob));
				break;
				case 10:
					free(t1[3]);
					t1[3]= dToStr(P3dGetZ(ob));
				break;
				case 11:
					free(t1[3]);
					t1[3]= dToStr(P3dGetX(ob));
					free(t1[5]);
					t1[5]= dToStr(P3dGetY(ob));
				break;
				case 12:
					free(t1[3]);
					t1[3]= dToStr(P3dGetX(ob));
					free(t1[5]);
					t1[5]= dToStr(P3dGetZ(ob));
				break;
				case 13:
					free(t1[3]);
					t1[3]= dToStr(P3dGetY(ob));
					free(t1[5]);
					t1[5]= dToStr(P3dGetZ(ob));
				break;
				case 14:
					free(t1[3]);
					t1[3]= dToStr(P3dGetX(ob));
					free(t1[5]);
					t1[5]= dToStr(P3dGetY(ob));
					free(t1[7]);
					t1[7]= dToStr(P3dGetZ(ob));
				break;
			}
			arrange(&t, t1);
			free(code(&t1));
			return code(&t);	
		}
	}
	free(code(&t));
	return NULL;
}

struct p3d p3d[1]= {
	P3d,
	0, 0, 0
};
