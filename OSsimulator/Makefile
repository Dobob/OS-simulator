########################################
##
## Makefile
## LINUX compilation 
##
##############################################





#FLAGS
C++FLAG = -g -std=c++0x -Wall

#Math Library
MATH_LIBS = -lm

#Executable directory
EXEC_DIR0=./bin
EXEC_DIR_FINAL=~/temp

#Object directory
BUILD_DIR0=./build

#Rule for .cpp files
# .SUFFIXES : .cpp.o 

.cpp.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@




#Including
INCLUDES=  -I. 


LIBS_ALL =  -L/usr/lib -L/usr/local/lib $(MATH_LIBS) 


#ZEROTH PROGRAM
ALL_OBJ0=src/run.me.o
#Need to make run.me.exe otherwise you get run.me with an "me" extension file!

PROGRAM_0=run.me
$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR0)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

#Compiling all

all: 	
		make $(PROGRAM_0)


#Clean obj files

clean:
	(cd src; rm -f *.o;)



(:
