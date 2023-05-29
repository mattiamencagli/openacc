
matmul.x:

CC      = nvc++
CFLAGS  = -c -acc -std=c++17 -gpu=rdc,managed,debug -Minfo=all -Minline=1000 -O -g
LDFLAGS = -lm -acc -gpu=rdc,managed,debug
INCLUDE_DIRS = -I .

OBJ = matmul.o
#######HEADERS = matmul.h

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $< -o $@

matmul.x: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

clean:
	@rm -f	*.o  *.x
	@echo make clean: done