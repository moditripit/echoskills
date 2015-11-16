PROGRAM = ../bin/echo_server
COMPILER = g++
CFLAGS = -g -gstabs
objects := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
LIBS = -lcurl -lfcgi++ -lfcgi
SWITCHES = -O2 -Wall

all : $(objects)
	$(COMPILER) $(CFLAGS) $(objects) $(SWITCHES) $(LIBS) -o $(PROGRAM)
	rm -f *.o *~ 

clean:
	rm -f *.o *~ 
	rm ../bin/echo_server

