#ifndef STRINGMANIP2
#define STRINGMANIP2
short   endsWith    (char * base, char* str);
short   startsWith  (char* base, char* str) ;
short   indexOf     (char* base, char* str) ;
short   lastIndexOf (char* base, char * str);
int     countOccurrence(char* base, char* str);
char ** split       ( char * base, char * str);
char    charAtIndex ( char * base, int index);
longstring   getLongString(FILE* fp);
typedef char*  string_; 

#define _string   string_
#define str_alloc (char*) malloc
#define str_free  free
#define STR(str)  str
#define STR2(str) str


#endif