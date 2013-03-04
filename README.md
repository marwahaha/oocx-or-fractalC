/*
file README.md from oocx project. definition and explanation of oocx project.
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

oocx
====
This is C as C++ but C, or fractal C, or OOCX. In essence is a way to program C, to structure code, to allow OO design characteristics on C as C++.
It has a unique interface to dialog with objects, function say(,). That function accepts as a first argument a pointer to an object and as a second argument the message we want to give to that object. If the object understands the message will do whatever it is programmed to do and will answer us with another message. Message passing it is through a chain of pairs field@value: or attribute@value:. The order or sequence of the pairs in the chain it is indifferent. Message answer will be gived to us in the same order of pairs we gived or passed to the object, no matter how the object really keep the order of pairs in its own sequence. What must coincide in order for the object to accept the message it is the number of pairs and the first part of each pair, that is, the field name. There is an exception, for the 'cmd' (standing for command abreviation) field name also value name (or chars) will be checked. That is, if we pass 'cmd@length:' and the object has as a message 'cmd@put:' but not the first one, will not operate.

To put examples:
  "cmd@put:x@3:" passed (to the object)
  "cmd@put:x@:" contemplated (by the object)
  ok, result successfull, will interpret, decode, and act and give an answer.
  
  "x@4.3:y@4.2:cmd@put:" passed (to the object)
  "cmd@put:x@:" contemplated (by the object)
  "cmd@put:x@:y@:" not explicitly contemplated (by the object)
  wrong, not successfull, the object will not interpret and decode and act and will give answer NULL if it not pass or resend the message through the inheritance (multiple) chain and other objects in that chain understands it and give proper answer (not NULL).
  
  "cmd@get:x@:" passed (to the object)
  "cmd@put:x@:" contemplated (by the object)
  "cmd@get:x@:" not explicitly contemplated (by the object)
  wrong, the object answer will be NULL (except in case of multiple inheritance and ressend of the message).
  
There is a unique interface to dialog with objects, all kind of them, as I said, it's say(nameObj, "message") giving answer char * or NULL.
Answers are dinamically allocated space in memory, so if we want to reject them (in case we gave an order put so we don't expect output at all) we must free space answer. we do that directly with free, as in
  free(say(p1, "cmd@put:x@1.2:"));

In case we give a message to expect an answer with relevant output, as an order get, then we must decode the message in tokens, we do that with function decode:
  char **t;
  if(t= decode(say(p1, "cmd@get:x@:"))){
    printf("%s", t[3]);
    free(code(&t));
  }
  
function decode automatically free spaces of answer given by say(,) and allocates new sapce for tokens containing answer in a token way, not message way. That is, we free from one hand and allocate new space for another, in that way we pass the allocated space from one place to another, keeping knowledge of where it is the allocated space.
after that code() function deallocates or free space generated or ocuppied by tokens and allocate new space for a message string. It is the reverse step from decode(). It is for this reason that if we want finally to free all space not necessary, we must do free(code(&t)). we pass 't' as a reference so we want to stay it NULL for future use, and after that, in that way, we know it will be NULL (because code() func will set it NULL because of the reference given to it).
we printf token 3, because counting begins from 0, and if we look at the sequence of pairs passed, the answer interesting to us (the value of x from p1) will be located in token number 3. '@' and ':' are deprecated in the token conversion.
in that case, because of tokens are itself strings, it is not necessarily to make any conversion on the value to print it. If we wanted to use the value for its own mathematical value, we must use strToD() function:
  double z= strToD(t[3])+ 3.2;
  
That function use the standard library function strtod(,) function, but simplifying it. Returns double and accepts a char *. There is also the function dToStr() which takes a double and returns a string. That function makes use of the standard library sprintf twice, first to calculate the number of chars in the conversion, and after to really convert it and store it in a chain of chars, or string.

Finally say and add that objects are of tipe void *. If we want to instantiate an object we do like this:

  void *p1;
  char **t;
  if(t= decode(say(p3d, "cmd@replicate:output@:"))){
    p1= (void *)((int)(strToD(t[3])));
    free(code(&t));
  }

We give order or command 'replicate' to existing object 'p3d'. p3d will be the equivalent to a class, but it is an instance that define that class or type. It is declared as extern void *p3d[]; The array is necessary because it was defined as an array, of 1 element, to a struct p3d type. In that case 'struct p3d' and 'p3d' not enter in conflict because the first is a pair sequence and the second it is a token by its own. In the use of p3d we do not need, and don't do, to know the type of p3d, so we make it void *. It is for this reason that func say(,) it is definned as accepting void * * as first parameter (because of the couple void * and [] in the extern declaration).

The term fractal C it is because objects with multiple inheritance can have a structure similar to fractals, in the sense the multiple branches in whatever order can appear in the evolution upstream. And also in the fact that everything, from a program to an OS, can be contemplated as an object in that way.

The original term for that way of programming it is  OOCX (OOC and successive versions ended in OOCX).

Ok, hope you like and enjoy it, find it usefull and apply it to your own code and projects. Good Luck!!!
