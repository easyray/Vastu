#ifdef _Seun_Debug_
#define prev_SD 1
#undef   _Seun_Debug_
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stringmanip.h"


int      seun_toye_str_lmodify;
int      seun_toye_str_len;
int      seun_toye_str_prec;
#define  Max_Format_Buffer    4096
#define  Max_Format_Str_Size  256
#define  Max_Format_Literal   1024
char     seun_toye_str_out[Max_Format_Buffer];
char     Fmt [Max_Format_Str_Size];
char     Fmt_Literal[Max_Format_Literal];
int      Fmt_Index;
int      Fmt_Literal_Index;



int readFlag(const char * source,int index){
	switch(source[index]){
		case '#':
		case ' ':
		case '+':
		case '-':
		case '0': 
			assert(Fmt_Index < Max_Format_Str_Size);
			Fmt[Fmt_Index++] = source[index++];
		break;
		default: index += 0; break;
	}
	
	return index;
}

int readWidth(const char * source,int index){
	int len = 0;
	seun_toye_str_len = 0;
	if( source[index] =='*'){
		assert(Fmt_Index < Max_Format_Str_Size);
		Fmt[Fmt_Index++] = source[index++];	
		return index;
	}else{
		
		while(isDigit(source[index])){
			len = 10*len +(source[index]-'0');
			assert(Fmt_Index < Max_Format_Str_Size);
			Fmt[Fmt_Index++] = source[index++];
		}
	}
	seun_toye_str_len = len;
	return index;
}

int readPrecision(const char * source,int index){
	int len = 0;
	seun_toye_str_prec = 0;
	if(source[index] == '.'){
		assert(Fmt_Index < Max_Format_Str_Size);
		Fmt[Fmt_Index++] = source[index++];
	}else{
		return index;
	}
	
	while(isDigit(source[index])){
		len = 10*len +(source[index]-'0');
		assert(Fmt_Index < Max_Format_Str_Size);
		Fmt[Fmt_Index++] = source[index++];
	}
	seun_toye_str_prec = len;
	return index;
}

int isDigit(char c){
	return (c>='0' && c<='9');
	
}

int readLength(const char * source,int index){
	seun_toye_str_lmodify =1;
	switch(source[index]){	
		case 'L':  seun_toye_str_lmodify =2;
		case 'j':
		case 'z':
		case 't':	
		assert(Fmt_Index < Max_Format_Str_Size);
		Fmt[Fmt_Index++] = source[index++];
		break;
		case 'h': 
			assert(Fmt_Index < Max_Format_Str_Size);
			Fmt[Fmt_Index++] = source[index++];
		    if(source[index]=='h'){
				assert(Fmt_Index < Max_Format_Str_Size);
				Fmt[Fmt_Index++] = source[index++];
			}
			break;
		case 'l':
			seun_toye_str_lmodify = 2;

			assert(Fmt_Index < Max_Format_Str_Size);
			Fmt[Fmt_Index++] = source[index++];

		    if(source[index]== 'l'){
				assert(Fmt_Index < Max_Format_Str_Size);
				Fmt[Fmt_Index++] = source[index++];
				seun_toye_str_lmodify = 4;
			}
			break;
		default: index += 0;	
	}
	
	return index;
}



int parseSpecifier(const char* source ,int index){
	Fmt_Index = 1;
	Fmt[0]    = '%';
	
	index = readFlag(source, index);
	index = readWidth(source, index);
	index = readPrecision(source, index);
	index = readLength(source, index);
	
	Fmt[Fmt_Index] = '\0';
	
	return index;
}

void seun_format_addToLiteral(char c){
	Fmt_Literal[Fmt_Literal_Index++] = c;
	Fmt_Literal[Fmt_Literal_Index]   = '\0';
}

int parseFormat(s_str src, va_list ap){
	
	int index = 0;
	int index2= 0;
	int total = 0;
	int len ;
	int sz;
	int len2;
	char* source;
	int       intVal;
	int       I_Size;
	double    dobleVal;
	long      longVal;
	long long llVal;
	
	source = src.Txt;
	
	len   = strlen(source);
	
	seun_toye_str_out[0] = '\0';
	
	Fmt_Literal_Index = 0;
	
	while(index < len){
		if(source[index] !='%'){
			seun_format_addToLiteral(source[index]);
			index ++;
		}else{
			if(Fmt_Literal_Index){
				sprintf(seun_toye_str_out+index2,"%s",Fmt_Literal);
				index2 += Fmt_Literal_Index;
				Fmt_Literal_Index = 0;
			}
			index = parseSpecifier(source, ++index);
			//sz = getSz(source[index]);
			
			Fmt[Fmt_Index++] = source[index];
			Fmt[Fmt_Index++] = '\0';
			
			if(source[index] !='s'){
				
				switch(source[index]){
					case 'f': 
					case 'F':
					case 'e':
					case 'E':
					case 'g':
					case 'G': 
						dobleVal = va_arg(ap, double); 	
						if(source[index]=='f' || source[index]== 'F'){
							I_Size =(abs(dobleVal)>1)? ceil(log(abs(dobleVal))/ log(10) )+1:2;
							total += I_Size;
						}else{
							total += 9;
							I_Size = 9;
						}
						sz     = (seun_toye_str_prec < 8)? 8: seun_toye_str_prec;
						total += sz;
						
						I_Size +=sz;
						
					assert((index2+I_Size) < Max_Format_Buffer);	
					sprintf(seun_toye_str_out+index2,Fmt,dobleVal);
						
						index2 += strlen(seun_toye_str_out+index2);
						
						break;
					case 'd':
					case 'i':
					case 'o':
					case 'u':
					case 'x':
					case 'X':
					case 'a':
					case 'A': 
					case 'p': 
						if(seun_toye_str_lmodify ==1){
							intVal = va_arg(ap, int);
							sz = (abs(intVal)>1)?ceil(log(abs(intVal))/log(8)):1;
							
						I_Size = (sz> seun_toye_str_prec)? sz : seun_toye_str_prec;
						assert((index2+I_Size+2) < Max_Format_Buffer);
						sprintf(seun_toye_str_out+index2,Fmt,intVal);
						
						}else if(seun_toye_str_lmodify==2){
							longVal = va_arg(ap, long);
							sz = (abs(longVal)>1)?ceil(log(abs(longVal))/log(8)):1;
						
						I_Size = (sz> seun_toye_str_prec)? sz : seun_toye_str_prec;
						assert((index2+I_Size+2) < Max_Format_Buffer);
						sprintf(seun_toye_str_out+index2,Fmt,longVal);
						
						}else if(seun_toye_str_lmodify==4){
							llVal =va_arg(ap, long long);
							sz = (abs(llVal)>1)?ceil(log(abs(llVal))/log(8)):1;

						I_Size = (sz> seun_toye_str_prec)? sz : seun_toye_str_prec;
						assert((index2+I_Size+2) < Max_Format_Buffer);
						sprintf(seun_toye_str_out+index2,Fmt,llVal);
							
						}
						
						total  += I_Size;
						index2 += strlen(seun_toye_str_out+index2);
						break;
					case 'c': 
						intVal = va_arg(ap, int);
						total += 1;
						
						assert((index2+1) < Max_Format_Buffer);
						sprintf(seun_toye_str_out+index2,Fmt,intVal);
						index2 += strlen(seun_toye_str_out+index2);
					default: break;
				}
				
			}else{
				char *s = va_arg(ap, s_str).Txt;
				
				len2   = strlen(s);
				I_Size = (seun_toye_str_len>len2)? seun_toye_str_len: len2;
				total += I_Size;
				assert((index2+I_Size) < Max_Format_Buffer);
				sprintf(seun_toye_str_out + index2, Fmt, s );
				index2 += I_Size;
			}
			
			index++;
		}
	}

	va_end(ap);
	total += strlen(source);
	return total;
}

int  s_str_printf(s_str format, ...){
	int       len;
	va_list   ap;
	

	assert(isvalid_s_str(format));
	
	va_start(ap,format);
	len = parseFormat(format,ap)+2;
	va_end(ap);


	return printf("%s",seun_toye_str_out );

}


int  s_str_sprintf(s_str Dst, s_str format, ...){
	int       len;
	va_list   ap;
	

	assert(isvalid_s_str(Dst));
	assert(isvalid_s_str(format));
	
	va_start(ap,format);
	len = parseFormat(format,ap)+2;
	va_end(ap);
	
	assert(len <= Dst.Size );

	strcpy(Dst.Txt, seun_toye_str_out);
	
	return len;
}

#ifdef prev_SD
#define   _Seun_Debug_ 1
#endif