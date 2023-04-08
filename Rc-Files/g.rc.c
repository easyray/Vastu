
CreateWindowEx(0,
	"edit", 
	TEXT (""),
	WS_CHILDWINDOW|WS_VISIBLE|WS_TABSTOP|ES_AUTOHSCROLL|WS_EX_STATICEDGE,
	22,
	72,
	180,
	45,
	hWnd,
	(HMENU)IDC_INPUT, // window menu handle
	hInst, 
	0
);

CreateWindowEx(0,
	"button", 
	TEXT ("Compute"),
	WS_CHILDWINDOW|WS_VISIBLE|WS_TABSTOP,
	210,
	72,
	112,
	45,
	hWnd,
	(HMENU)IDC_BTN, // window menu handle
	hInst, 
	0
);

CreateWindowEx(0,
	"static", 
	TEXT ("VASTU"),
	WS_CHILDWINDOW|WS_VISIBLE|WS_GROUP|SS_CENTER|WS_EX_CLIENTEDGE,
	22,
	27,
	256,
	32,
	hWnd,
	(HMENU)IDC_LBL, // window menu handle
	hInst, 
	0
);

CreateWindowEx(0,
	"edit", 
	TEXT (""),
	WS_CHILDWINDOW|WS_VISIBLE|WS_VSCROLL|WS_TABSTOP|ES_AUTOHSCROLL|ES_AUTOVSCROLL|ES_MULTILINE|WS_EX_CLIENTEDGE,
	22,
	450,
	144,
	176,
	hWnd,
	(HMENU)IDC_X, // window menu handle
	hInst, 
	0
);

CreateWindowEx(0,
	"edit", 
	TEXT (""),
	WS_CHILDWINDOW|WS_VISIBLE|WS_TABSTOP|WS_EX_CLIENTEDGE,
	210,
	448,
	114,
	172,
	hWnd,
	(HMENU)IDC_Y, // window menu handle
	hInst, 
	0
);

CreateWindowEx(0,
	"edit", 
	TEXT (""),
	WS_CHILDWINDOW|WS_VISIBLE|WS_VSCROLL|WS_HSCROLL|WS_TABSTOP|ES_MULTILINE|WS_EX_CLIENTEDGE,
	22,
	126,
	300,
	315,
	hWnd,
	(HMENU)IDC_EDT1, // window menu handle
	hInst, 
	0
);
