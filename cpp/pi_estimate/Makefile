
pi.x:

CC      = nvc++
CFLAGS  = -c -acc -std=c++17 -gpu=rdc,managed,debug -Minfo=all -Minline=1000 -O3 #-g
LDFLAGS = -lm -acc -gpu=rdc,managed,debug
INCLUDE_DIRS = -I .

#CC      = g++
#CFLAGS  = -c -Wall -O3
#LDFLAGS = -lm
#INCLUDE_DIRS = -I .

OBJ = pi.o
#######HEADERS = pi.h

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $< -o $@

pi.x: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

clean:
	@rm -f	*.o  *.x
	@echo make clean: done
