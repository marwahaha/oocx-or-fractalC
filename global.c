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

char *say(void **ob, char *mess){  
	if(ob){				
		return (*(char *(**)(void *, char *))ob)((void *)ob, mess);
	}
	return NULL;
}

int stringLength(char *st){
	int len= -1;
	if(st){
		int i;
		for(i= 0; st[i]; i++);
		len= i;
	}
	return len;
}

char *stringMake(int len){
	char *st= NULL;
	if(len>= 0){
		st= malloc(sizeof(char)* (len+ 1));
	}
	int i;
	for(i= 0; i< len; i++){
		st[i]= '\1';
	}
	if(len>= 0){
		st[len]= '\0';
	}
	return st;
}

void stringFill(char *to, char *from){
	int len1= stringLength(to);
	int len2= stringLength(from);
	int j;
	if(len1< len2){
		j= len1;
	}
	else{
		j= len2;
	}
	int i;
	for(i= 0; i< j; i++){
		to[i]= from[i];
	}
}

int stringEquals(char *st1, char *st2){
	if(st1&& st2){
		while(*st1== *st2++){
			if(!*st1++){
				return 1;
			}
		}
	}
	return 0;
}

char *stringCopy(char *st){
	char *st2= stringMake(stringLength(st));
	stringFill(st2, st);
	return st2;
}

void stringConcat(char **rst, char *st2){
	char *st= *rst;
	int len1, len2;
	if((len1= stringLength(st2))< 0){
		len2= 0;
	}
	else{
	    if((len2= stringLength(st))< 0){
	    	len2= 0;
	    	len1= -1;
	    }
	}
	char *st3= stringMake(len2+ len1);
	stringFill(st3, st);
	stringFill(st3+ len2, st2);
	free(st);
	*rst= st3;
}

char *stringParse(char **rst, char dl){
	char *st= *rst;
	int i, len= stringLength(st);
	for(i= 0; i< len; i++){
		if(st[i]== dl){
			break;
		}
	}
	int dim1, dim2;
	if(i< len){
		dim1= i;
		dim2= len- 1 -i;
	}
	else{
		dim1= dim2= -1;
	}
	char *st2= stringMake(dim1);
	stringFill(st2, st);	
	char *st3= stringMake(dim2);
	if(st){	
		stringFill(st3, st+ i+ 1);
	}	
	free(st);
	*rst= st3;	
	return st2;
}

char *stringParseRight(char **rst, char dl){
	char *st= *rst;
	int i, len= stringLength(st);
	for(i= len- 1; i>= 0; i--){
		if(st[i]== dl){
			break;
		}
	}
	int dim1, dim2;
	if(i>= 0){
		dim2= i;
		dim1= len- 1 -i;
	}
	else{
		dim1= dim2= -1;
	}
	char *st2= stringMake(dim2);
	stringFill(st2, st);	
	char *st3= stringMake(dim1);
	if(st){	
		stringFill(st3, st+ i+ 1);
	}	
	free(st);
	*rst= st2;	
	return st3;
}

void stringTrailRight(char **rst, char tr){
	char *st= *rst;
	int i, len;
	for(len= stringLength(st), i= len- 1; i>= 0&& st[i]== tr; i--){
	}
	if(st&& i>= 0&& i!= len- 1){
		if(++tr){
			st[++i]= tr;
		}
		else{
			st[++i]= ++tr;
		}
		free(stringParseRight(rst, tr));
	}
}

char *dToStr(double d){
	char b[50], *c= stringMake(sprintf(b, "%f", d));
	sprintf(c, "%f", d);
	stringTrailRight(&c, '0');
	return c;
}

double strToD(char *a){
	double d= strtod(a, NULL);
	return d;
}

char *code(char ***rt){
	char **t= *rt;
	char *code= NULL;
	if(t){
		code= "";
		int i;
		for(i= 0; t[i*2]; i++){
			stringConcat(&code, t[i*2]);
			stringConcat(&code, "@");
			stringConcat(&code, t[i*2+ 1]);
			stringConcat(&code, ":");
		}
		for(i= 0; t[i*2]; i++){	
			free(t[i*2]);
			free(t[i*2+ 1]);
		}
		free(t);
		*rt= NULL;
	}
	return code;
}

char **decode(char *code){	
	char **t= NULL;
	int i= 0;
	char *aux= NULL;
	if(code){
		t= malloc(sizeof(int)*64);
		do{
			aux= stringParse(&code, ':');
			t[i++]= stringParse(&aux, '@');
			t[i++]= aux;
		} while(code&& *code&& i< 64);
		free(code);
		for(; i< 64; i++){
			t[i]= NULL;
		}
	}		
	return t;
}

void arrange(char ***rt2, char **t1){
	char **t2= *rt2;
	int pos[64];/*compare*/
	int i, j, k;
	for(i= 0, k= 1; t2[i]&& k; i+= 2){
		for(j= k= 0; t1[j]; j+= 2){
			if(stringEquals(t2[i], t1[j])){
				if(stringEquals(t2[i], "cmd")){
					if(!stringEquals(t2[i+ 1], t1[j+ 1])){
						k--;
					}
				}
				pos[i]= j;
				k++;
				break;
			}
 		}
	}/*if ok, order*/
	if(!t2[i]&& k&& !t1[i]){
		for(i= 0; t2[i]; i+= 2){
			free(t2[i+ 1]);
			t2[i+ 1]= stringCopy(t1[pos[i]+ 1]);
		}
	}
	else{
		free(code(rt2));
	}
}
