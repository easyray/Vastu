#ifdef _Seun_Debug_
#define prev_SD 1
#undef   _Seun_Debug_
#endif

#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int      _Seun_Max_Alloc   = 25;
int      _Seun_Alloc_Count = 0;

// Error reporting flags
int      _Seun_IDC_MSG     = 0;
int      _Seun_IDC_ERR     = 0;
HWND     _Seun_HWND        = NULL;

#include "stringmanip.h"



char   *str_alloc(int x){
	char *ret;
	assert(x>0);
	ret = (char*) malloc(sizeof(char)*x);
	assert(ret !=NULL);
	ret[0] = '\0';
	return ret;
}

s_str   New_s_str   (int W){
	
	assert(	_Seun_Alloc_Count <= _Seun_Max_Alloc );
	assert(W>0);
	
	char* Id ="string";
	s_str retval;
	
	strcpy(retval.Id, Id);
	retval.Txt = (char*) malloc(W);
	
	if(retval.Txt==NULL){
		printf("Could not allocate string");
		exit(0);
	}

	retval.Txt[0] = '\0';
	retval.Size   = W;
	
	_Seun_Alloc_Count ++;

	if(_Seun_IDC_MSG && _Seun_HWND){
		showX(_Seun_Alloc_Count);
	}

	return retval;
}

s_str s_str_fromCharPtr(char* str){

	char*   Id     = "string";
	int     len    = strlen(str)+1;
	s_str   retval   ;

	retval.Txt = str;
	strcpy(retval.Id, Id);
	retval.Size = len;


	if(retval.Txt==NULL){
		printf("bad string");
		exit(0);
	}

	return retval;
}

char *  charPtr_from_s_str(s_str str){
	assert(isvalid_s_str(str));
	return str.Txt;
}

short   isvalid_s_str(s_str str1){
	return (strcmp(str1.Id ,"string")==0);
}

s_str   copy_s_str     (s_str dst, s_str x){
	int   len ;
	s_str retval;

	assert(isvalid_s_str(dst));
	assert(isvalid_s_str(x));
	
	len = strlen(x.Txt);
	assert(dst.Size >= len);



	strcpy(dst.Txt, x.Txt);


	return dst;
}

s_str   catenate_s_str     (s_str dst, s_str x){
	int   len ;
	s_str retval;

	assert(isvalid_s_str(dst));
	assert(isvalid_s_str(x));
	
	len = strlen(x.Txt)+ strlen(dst.Txt);
	assert(dst.Size >= len);

	strcat(dst.Txt, x.Txt);


	return dst;
}


s_str   dup_s_str     (s_str x){
	int   len ;
	s_str retval;
	assert(isvalid_s_str(x));
	
	len    = strlen(x.Txt);
	retval = New_s_str(len+1);
	if(retval.Txt==NULL){
		printf("Could not allocate string");
		exit(0);
	}
	
	strcpy(retval.Txt, x.Txt);
	return retval;
}

void destroy_str(s_str str){
	
	assert( isvalid_s_str( str) );
	str.Id[0] = '\0';
	free(str.Txt);
	str.Txt = NULL;
	_Seun_Alloc_Count --;
	
	if(_Seun_IDC_MSG && _Seun_HWND){
		showX(_Seun_Alloc_Count);
	}
}

short endsWith (char * base, char* str) {
		
    int blen = strlen(base);
    int slen = strlen(str);
    return (blen >= slen) && (0 == strcmp(base + blen - slen, str));
}

short ends_With (s_str base, s_str str) {
	assert(isvalid_s_str(base));
	assert(isvalid_s_str(str));
	
    int blen = strlen(base.Txt);
    int slen = strlen(str.Txt);
    return (blen >= slen) && (0 == strcmp(base.Txt + blen - slen, str.Txt));
}

int length(s_str base){
	assert(isvalid_s_str(base));
	return strlen(base.Txt);
	
}


int indexOf_shift (char* base, char* str, int startIndex) {
    int    result;
    int    baselen = strlen(base);
	char* pos;
	// str should not longer than base
    if (strlen(str) > baselen || startIndex > baselen) {
		result = -1;
    } else {
        if (startIndex < 0 ) {
            startIndex = 0;
        }
        pos = strstr(base+startIndex, str);
        if (pos == NULL) {
            result = -1;
        } else {			
            result = pos - base;
        }
    }
    return result;
}


	
int indexOf (char* base, char* str) {
    return indexOf_shift(base, str, 0);
}	
	
	
int  index_Of (s_str base, s_str str) {
	assert(isvalid_s_str(base));
	assert(isvalid_s_str(str));
	
    return indexOf_shift(base.Txt, str.Txt, 0);
}
/** use two index to search in two part to prevent the worst case
 * (assume search 'aaa' in 'aaaaaaaa', you cannot skip three char each time)
 */
int last_Index_Of (s_str base, s_str str) {
    
	int result;
	int start;
	int endinit;
	int end;
	int endtmp;
    
	assert(isvalid_s_str(base));
	assert(isvalid_s_str(str));
	// str should not longer than base
    if (strlen(str.Txt) > strlen(base.Txt)) {
        result = -1;
    } else {
        
		start   = 0;
        endinit = strlen(base.Txt) - strlen(str.Txt);
        end     = endinit;
		endtmp  = endinit;
		
        while(start != end) {
            start = indexOf_shift(base.Txt, str.Txt, start);
            end   = indexOf_shift(base.Txt, str.Txt, end);

            // not found from start
            if (start == -1) {
                end = -1; // then break;
            } else if (end == -1) {
                // found from start
                // but not found from end
                // move end to middle
                if (endtmp == (start+1)) {
                    end = start; // then break;
                } else {
                    end = endtmp - (endtmp - start) / 2;
                    if (end <= start) {
                        end = start+1;
                    }
                    endtmp = end;
                }
            } else {
                // found from both start and end
                // move start to end and
                // move end to base - strlen(str)
                start = end;
                end = endinit;
            }
        }//end while
        result = start;
    }//end if(strlen(str.Txt) > strlen(base.Txt))
    return result;
}


int  lastIndexOf (char* base, char * str) {
    
	int result;
	int start;
	int endinit;
	int end;
	int endtmp;
    
	// str should not longer than base
    if (strlen(str) > strlen(base)) {
        return  -1;
    }
        
	start   = 0;
    end     = strlen(base) - strlen(str);
	endtmp  = end;
	endinit = end;
	
    while(start != end) {
        start = indexOf_shift(base, str, start);
        end   = indexOf_shift(base, str, end);

        // not found from start
        if (start == -1) {
            return -1; // then break;
        }

        if (end == -1) {
            // found from start
            // but not found from end
            // move end to middle(cover 1/2 remaining space @ 1ce)
            // start remains where we found the first
            // n log n
            if (endtmp == (start+1)) {
            	//this happens if in the previous iteration
            	// you found from start(start remains) but not from end
            	//and there was no more free space 
            	//(endtmp was = start+1)
                end = start; // then break;
            } else {
                end = (endtmp + start) / 2;
                if (end <= start) {
                	// happens iff endtmp = start+1
                	// mid point becomes start with integer div
                    end = start+1;
                }
                endtmp = end;
            }
        } else {
            // found from both start and end
            // move start to end and
            // move end to base - strlen(str)
            start = end;
            end   = endinit;
            //while galivanting over huge spaces we could have left
            // matches between newly found end and initial end
        }
    }//end while
    result = start;
    return result;
}


int countOccurrence(char* base, char* str){
	
	int index1=0, index2, count=0;
	
	while(  (index2 = indexOf_shift(base, str,index1)) != -1  ) {
		index1 = index2+ strlen(str);
		count++;
	}
	
	return count;
}

int count_Occurrence(s_str base, s_str str){
	int index1=0, index2, count=0;
	
	assert(isvalid_s_str(base));
	assert(isvalid_s_str(str));
	
	while(  (index2 = indexOf_shift(base.Txt,str.Txt,index1)) != -1  ) {
		index1 = index2+ length(str);
		count++;
	}
	
	return count;
}

s_str s_str_substring(s_str base, unsigned start, unsigned len){
	
	s_str     ret;
	int       base_len;
	int       i;

	base_len = strlen(base.Txt);


	assert (isvalid_s_str(base) );
	assert (base.Txt != NULL);
	assert (base_len >= (start+len) );

	ret = New_s_str(len+1);

	for(i=0; i<len; i++){
		ret.Txt[i] = base.Txt[start+i];
	}
	ret.Txt[i] = '\0';
	return ret;
}


char * substr (char * base, unsigned start, unsigned len){
	
	char     *ret;
	int       base_len;
	int       i;

	base_len = strlen(base);


	assert (base != NULL);
	assert (base_len >= (start+len) );

	ret = str_alloc(len+1);

	for(i=0; i<len; i++){
		ret[i] = base[start+i];
	}
	ret[i] = '\0';
	return ret;
}


s_str * _split( s_str base, s_str str) {
	
	int     index1 = 0;
	int     index2 = 0, count = 0;
	s_str* string_array;
	
	assert(isvalid_s_str(base));
	assert(isvalid_s_str(str));
	
	count = count_Occurrence(base, str) +1 ;
	string_array = (s_str*) malloc(count*sizeof(s_str));
	assert(string_array != NULL);
	
	_Seun_Alloc_Count += (count+1);

	index1=0; index2=0; count = 0;

	while(  (index2 = indexOf_shift(base.Txt,str.Txt,index1)) != -1  ) {
		string_array[count] = s_str_substring(base,index1,index2-index1);
		index1 = index2+ length(str);
		count++;
	}
	
	index2 = length(base);
	string_array[count] = s_str_substring(base,index1,index2-index1);

	
	
	return string_array;
}

void free_SList(s_str * List, int Count){
	int i;
	
	for(i=0; i<Count; i++){
		destroy_str(List[i]);
	}
	
	_Seun_Alloc_Count -= (Count+1);
	
	free(List);
}

char ** split( char * base, char * str) {
	
	int     index1 = 0;
	int     index2 = 0, count = 0;
	char**  string_array;
	
	
	count = countOccurrence(base, str) +1 ;
	
	string_array = (char**)  malloc(count*sizeof(char*));

	index1=0; index2=0; count = 0;

	while(  (index2 = indexOf_shift(base,str,index1)) != -1  ) {
		string_array[count] = substr(base,index1,index2-index1);
		index1 = index2 + strlen(str);
		count++;
	}
	
	index2 = strlen(base);
	string_array[count] = substr(base,index1,index2-index1);

	return string_array;
}

void freeSList(char** List, int Count){
	int i;
	
	for(i=0; i<Count; i++){
		free(List[i]);
	}
	
	free(List);
}

char charAtIndex ( char * base, int index){
	
	assert(index< strlen(base));
	return base[index];
}

char    char_At_Index( s_str base, int index){
	
	assert(isvalid_s_str(base) );
	assert(index< strlen(base.Txt));

	return base.Txt[index];
}

short   startsWith  (char* base, char* str) {
	return (indexOf(base,str)== 0 );
}

short starts_With (s_str base, s_str str){
	
	assert(isvalid_s_str(base) );
	assert(isvalid_s_str(str)  );
	
	return startsWith(base.Txt, str.Txt);
}

/*
longstring   getLongString(FILE* fp){
#define CHUNK_SIZE 1024
#define MAX_LEN	   65536

	printf("%p\n",fp);
	char * listr ;
	List     List1;
	Iterator L1_Itr;
	int  i,    n=0, count = 0, total=0;
	longstring H;
	List1  = list_Init();	

	do{
		listr = (char*) malloc(CHUNK_SIZE);
		
		
		fgets(listr,CHUNK_SIZE,fp);
		
		//printf("\n%s",listr);
			
		listAddString(List1,listr);
		n = strlen(listr);
		printf("\n%d",n);
		total += n;
		count +=1;
	}while (n>=CHUNK_SIZE-1 && total< MAX_LEN);
	
	listr = (char*) malloc(total+1);
	strcpy(listr,"");
	
	L1_Itr = iterator_Init(List1);
	
	for(i=0 ;  i< count; i++){
		strcat(listr,iteratorGetNextString( L1_Itr)  );
	}

	H.String = listr;
	H.length = total;
	freeList(List1);
	
	return H;
}
*/
char  _Seun_Error_Message[1024];

void show_Error_Msg(char *e, char *file, int line){

	sprintf(_Seun_Error_Message, "\r\n%s \r\n%s \r\nLine: %d ",e, file, line );
	MessageBox(
		NULL, 
		_Seun_Error_Message, 
		TEXT("Error"), 
		MB_ICONERROR | MB_OK
	);
	
	if(_Seun_HWND && _Seun_IDC_ERR){
		
		SetWindowText (
			GetDlgItem (_Seun_HWND, _Seun_IDC_ERR), 
			_Seun_Error_Message  
		) ;
	}
}

void showX(int x){
	//windowHandle
	
/*	char Str[128];

	sprintf(Str,"\r\n%d",x);
	
	strcat(_Seun_Error_Message,Str);
*/	
	sprintf(_Seun_Error_Message,"%d",x);
	
	SetWindowText (
		GetDlgItem (_Seun_HWND, _Seun_IDC_MSG), 
		_Seun_Error_Message  
	) ;
	
	
}

#ifdef prev_SD
#define   _Seun_Debug_ 1
#endif



