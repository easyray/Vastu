#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int Seun_Reference_Count=0;

//check validity
short isValidList(List L){
    return (0==strcmp("valid", L.Valid ) );

}//------------------------

short isValidIterator(Iterator I){
 return (0==strcmp("valid",I.valid));
}//------------------------

//List
List list_Init(){
    List L;
	L.Start = NULL;
    L.End  = NULL;
    strcpy(&L.Valid[0],"valid");
	return L;
}//------------------------

void list_AddString(List *L,  char* Str){
    
	StringItem *LastItem, *Item;
    
	assert(isValidList( *L )  );
	
    Item = allocateStringItem();
    
	Item->Data = Str;
    Item->Next = NULL;
    
    if(NULL==L->Start){
		L->Start = Item;
		L->End   = Item;
    }else{
		LastItem = (StringItem *)L->End;
		LastItem->Next = Item;
		L->End   = Item;
    }

}//------------------------

StringItem * allocateStringItem(){
	void * Item = malloc(sizeof(StringItem ) );
 	printf("\n allocating %p  ref-count= %d",Item,++Seun_Reference_Count);
	return (StringItem *) Item;
}

//Iterator
Iterator  iterator_Init(List L){
	Iterator I;
	assert( isValidList(L) );
	I.current = L.Start;
	strcpy(&I.valid[0],"valid");
	
	return I;
}//------------------------

char* iterator_GetNextString(Iterator *I){

	StringItem Item;
	
	assert(isValidIterator(I[0])  );
	assert(NULL != I->current );
	
	Item = ((StringItem*)I->current)[0];
	
	I->current = Item.Next;
	
	return Item.Data;
}//------------------------

void   free_List(List *l){
#define	LL  (*l)
	StringItem *Current, *Next;

	assert(isValidList(LL));
	
	Current = (StringItem*) LL.Start;

	while(NULL != Current ){
		Next = (StringItem*)Current->Next;
		printf("\n Freeing %p  ref-count= %d",Current,--Seun_Reference_Count);
		free (Current);
		Current = Next;		
	}

	LL.Start = NULL;
	LL.End   = NULL ;	
	LL.Valid[0]= '\0';
	
#undef LL	
}

