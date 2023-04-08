Vastu_exe_C_SRC   =  Vastu.c controllers/main-controller.c string-lib/format-string.c string-lib/stringmanip.c Vastu2.c 
Vastu_exe_CPP_SRC =  
Vastu_exe_RC_SRC  =  resource.rc 
Vastu_exe_O_SRC   =  $(patsubst %.c,%.o, $(Vastu_exe_C_SRC)) $(patsubst %.cpp,%.o,$(Vastu_exe_CPP_SRC)) $(patsubst %.rc,%.o, $(Vastu_exe_RC_SRC)) 
Vastu_exe_LIB_SRC =  



#Tools
RM       = rm.exe -f
#CC       = gcc.exe -D__DEBUG__ -D_Seun_Debug_  -g
CC       = gcc.exe -D__DEBUG__  -g
WINDRES  = windres.exe

#Environment
LIBS     = -L C:/MinGW/lib  -static-libgcc -lcomdlg32 -mwindows -m32 -g3
INCS     = -I C:/MinGW/include


Vastu_exe = Vastu.exe

all:  $(Vastu_exe) 

clean: 
	$(Vastu_exe) $(Vastu_exe_O_SRC)

touch:
	touch $(Vastu_exe_C_SRC)
	
$(Vastu_exe): $(Vastu_exe_O_SRC)
	$(CC) $(Vastu_exe_O_SRC)  -o $(Vastu_exe) $(Vastu_exe_LIB_SRC) $(LIBS) 

%.o: %.c
	$(CC) -c $(INC) -o $@ $^ 

%.o: %.cpp
	$(CC) -c $(INC) -o $@ $^ 

%.o: %.rc
	$(CC) -c $(INC) -o $@ $^ 

%.o: %.rc
	$(WINDRES)  -o $@ -i $^ 


