//#define _Seun_Debug_
#include <stdio.h>
#include <stdlib.h>
#include "stringmanip.h"
#include "list.h"

double getDouble();
long   getLong();

long   factorial(int N);
int main(){
	
	float        Tc, Tf;
	int           N,R;
	long          NCR;
	longstring    MyLongString;
	FILE         *fp;
	char          stro[100];
	void          *Null;
	
	printf(STR("%s"), STR("Temperature : ") );
	
	Tc = getDouble();
	Tf = 32.0 +(9.0/5)*Tc;
	
	printf(STR("\n%f Celcius = %f Fahr\n"),Tc, Tf );
	
	printf(STR("\n%s\n"), STR("***Combination*** ") );
	
	printf(STR("%s")  , STR("N : ") ); N  = getLong();
	printf(STR("\n%s"), STR("R : ") ); R  = getLong();
	
	NCR = 0.0 + factorial(N)/(factorial(N-R) * factorial(R) );
	
	printf(STR("\n%d Combo %d = %ld \n"),N, R, NCR );
	/****/

	fp = fopen("string-file.txt","r");
	if(NULL==fp){
		perror("File open error");
		exit(1);
	}
	MyLongString = getLongString(fp);
	
	
	printf(STR("%s") , STR(MyLongString.String) );
	return 0;
}//TestString.exe

long   factorial(int N){
	int    i;
	long   F;
	
	if(N<0){ 
		return 0;
	}
	
	F=1;
	for (i=1; i<=N; i++){
		F *= i;
	}
	
	return F;
}


double getDouble(){
	
	double     ret;
	char       buffer[20];
	short      flag;
	
	fgets( buffer,19,stdin);
	flag = sscanf(buffer,"%lf", &ret);
	
	if(!flag){
		printf(STR("%s\n"), STR("Number Format Exception")  );
		exit(0);
	}
	
	return ret;
	
}

long getLong(){
	long       ret;
	char       buffer[25];
	short      flag;
	
	fgets( buffer,24,stdin);
	flag = sscanf(buffer,"%ld", &ret);
	
	if(!flag){
		printf(STR("%s\n"), STR("Number Format Exception")  );
		exit(0);
	}
	
	return ret;
}
