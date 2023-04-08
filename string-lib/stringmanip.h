#include <windows.h>
#include <stdarg.h>

#ifndef STRINGMANIP
#define STRINGMANIP

struct _s_str {
	char  Id[10];
	char* Txt;
	int   Size;
};

struct long_string{
	int length;
	char* String;
};

typedef struct   long_string longstring;
typedef struct   _s_str      s_str;
typedef char*                string_ ;

extern int      _Seun_Max_Alloc  ;
extern int      _Seun_Alloc_Count;

//Error reporting 
extern int      _Seun_IDC_MSG    ;
extern int      _Seun_IDC_ERR    ;
extern HWND     _Seun_HWND       ;

//Creating String
char   *str_alloc(int x);

// creating/converting s-str
short   isvalid_s_str(s_str str1);
s_str   New_s_str        (int W);
s_str   s_str_fromCharPtr(char* str);
char   *charPtr_from_s_str  (s_str str);
s_str   copy_s_str       (s_str dst, s_str x);
s_str   copy_free_s_str  (s_str old, s_str x);
void    destroy_str      ( s_str str);


// New functions to manipulate strings
short      startsWith    (char* base, char* str);
short      endsWith      (char * base, char* str);
int        indexOf       (char* base, char* str);
int        lastIndexOf   (char* base, char * str) ;
char     **split         (char * base, char * str);
void       freeSList     (char** List, int Count);
int        countOccurrence(char* base, char* str);
char       charAtIndex   (char * base, int index);
char      *strFromChar   (char a);
char      *substr        (char * base, unsigned start, unsigned len);
//debug mode
void       initializeErrorMessage();

//New String-scheme equivalents of new functions
short   starts_With (s_str base, s_str str);
short   ends_With   (s_str base, s_str str);
int     index_Of    (s_str base, s_str str);
int     last_Index_Of (s_str base, s_str str);
s_str  *_split        (s_str base, s_str str);
void    free_SList    (s_str * List, int Count);
int     count_Occurrence(s_str base, s_str str);
char    char_At_Index   ( s_str base, int index);
s_str   str_From_Char   (char a);
s_str   s_str_substring (s_str base, unsigned start, unsigned len);


//debug-mode alternative to some native-functions
int     s_str_printf     (s_str format, ...);
int     s_str_sprintf    (s_str Dst, s_str format, ...);
s_str   getString        (int size);
s_str   dup_s_str        (s_str x);
s_str   catenate_s_str   (s_str dst, s_str x);


//New macros to use in our code debug or no debug 
#ifndef _Seun_Debug_
	#define _string   string_
	#define str_free  free
	#define STR(str)  str
	#define STR2(str) str
#endif

#ifdef _Seun_Debug_
	#define _string      s_str
	#define str_alloc    New_s_str	
	#define str_free     destroy_str
	#define STR(str)     s_str_fromCharPtr(str)
	#define STR2(str)    charPtr_from_s_str(str)
#endif


//Macro Mapping
#ifdef _Seun_Debug_
	#define strcpy       copy_s_str
	#define strdup       dup_s_str
	#define endsWith     ends_With
	#define strlen       length
	#define indexOf      index_Of
	#define lastIndexOf  last_Index_Of
	#define substr       s_str_substring
	#define split        _split
	#define printf       s_str_printf
	#define sprintf      s_str_sprintf
	#define strcat       catenate_s_str
	#define strFromChar  str_From_Char
	#define char_At_Index   charAtIndex
	#define countOccurrence count_Occurrence
#endif


//required for s_str_printf and s_str_sprintf
int     parseFormat(s_str source, va_list ap);
int     parseSpecifier(const char* ,int index);
int     readFlag(const char * source,int index);
int     readWidth(const char * source,int index);
int     readPrecision(const char * source,int index);
int     readLength(const char * source,int index);
int     isDigit(char c);

//more
short   isGreater  (s_str str1, s_str str2);
short   isLess     (s_str str1, s_str str2);
short   isEqual    (s_str str1, s_str str2);
void    showX      ( int x);
void show_Error_Msg(char *e, char *file, int line);
#endif