struct TakenPosition{
	int *Taken;
	int Total;
	int Count;
};

typedef struct TakenPosition TPL;

_string  OutString;
short    isTaken(int Index, TPL T);
void     permutate(_string stub,_string *Units, TPL T );