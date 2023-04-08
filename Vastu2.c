#include <stdio.h>
#include <string.h>
#include "string-lib/stringmanip.h"
#include "Vastu2.h"


void permutate(_string stub,_string *Units, TPL T ){
	int i;
	_string NewStub;
	

	
	for(i=0; i<T.Total; i++){ //scan units 0,1,2...
		if(! isTaken(i, T) ){ // is this string already taken?
			//then don't bother
			
			//Else append string to the given stub
			NewStub = str_alloc(strlen(stub)+strlen(Units[i])+ 2);
			strcpy(NewStub,stub);  
			strcat(NewStub,Units[i] );


			if((T.Total-T.Count)>1){ //Not yet in the last position ?

				T.Taken[T.Count] = i; //specify the string recently taken
				T.Count += 1;  //Allow the next level to check specified 
				//string
				

				// Let the next position(s) be done for us
				permutate(NewStub,Units,T); 
				T.Count -= 1; //back to our own position
				//reduce number of strings to check back to previous
				str_free(NewStub);
			}else{
				strcat(OutString,NewStub);
				strcat(OutString,STR("\r\n") );	
				str_free(NewStub);
				return;
			}//~if last position

		}//~if taken
	}//Next

}
 
short isTaken(int Index, TPL T){
	int i;
	
	for (i=0; i<T.Count; i++){
		if(Index == T.Taken[i]){
			return (1==1);
		}
	}
	
	return (1==0);
}


