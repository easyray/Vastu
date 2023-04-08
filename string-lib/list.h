//**********
// Data structure definition
//***********************/

struct LinkedList{
    void *Start,*End;
    char Valid [10];
};
typedef struct LinkedList List;
//----------------------------

struct StringItem_{
	char *Data;
	void *Next;
};
typedef struct StringItem_ StringItem;
//----------------------------

struct Iterator_{
	void* current;
	char valid[10];
};
typedef struct Iterator_ Iterator;
//----------------------------
//******************
//   Function Declarations
//***************************/
short isValidList(List L);
short isValidIterator(Iterator I);

List  list_Init();
void  list_AddString(List *L,  char* Str);
void  free_List(List *l);
#define freeList(L) free_List(&L)
#define listAddString(L,Str) list_AddString(&L,Str)

StringItem * allocateStringItem();
Iterator iterator_Init( List L);

char* iterator_GetNextString(Iterator *I);
#define iteratorGetNextString(I) iterator_GetNextString(&I)
