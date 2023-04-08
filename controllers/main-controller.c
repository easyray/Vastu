#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "../string-lib/stringmanip.h"
#include "../resource.h"
#include "main-controller.h"
#include "../Vastu2.h"

void handleExit(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify){
	PostQuitMessage (0) ;
}

/* void doVastu(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) */

void doVastu(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify){

	_string pszBuffer, *Items,stub;
	int     Count,i,FreeCount;
	struct TakenPosition T;

	pszBuffer = str_alloc(128);
	GetWindowText (GetDlgItem (hwnd,  IDC_INPUT), STR2(pszBuffer), 127) ;
	
	
	Count     = countOccurrence(pszBuffer ,STR(",") );
	FreeCount = Count;
	
	if(Count>6){
		Count=6;
	}
	
	if(Count>256){
		return;
	}
	
	Items = split(pszBuffer,STR(",") );
	
	stub =str_alloc(128);
	
	strcpy(stub,STR(""));
	
	T.Taken = (int*) malloc(sizeof(int)*(Count+1));
	T.Total = Count+1;
	T.Count = 0;

	for(i=0; i< T.Total; i++){
		T.Taken[i] = 0;
	}
	
	T.Taken[0];
	T.Taken[1];
	T.Taken[2];
	T.Taken[3];

	OutString =  str_alloc(65536);

	//SetWindowText (GetDlgItem (hwnd,  IDC_EDT1 ), "" );
	
	permutate( stub, Items, T );
	
	SetWindowText (GetDlgItem (hwnd,  IDC_EDT1 ), STR2(OutString)  );
	
	
	str_free(pszBuffer);
	str_free(OutString);
	free(T.Taken);
	str_free(stub);
	
	freeSList(Items, FreeCount);

	
}