OBJECTS= ./build/compiler.o ./build/compile_process.o
INCLUDES= -I ./

all: $(OBJECTS)
	gcc main.c $(INCLUDES) $(OBJECTS) -g -o ./main

./build/compiler.o: ./compiler.c
	gcc -g $(INCLUDES) -c ./compiler.c -o ./build/compiler.o

./build/compile_process.o: ./compile_process.c
	gcc -g $(INCLUDES) -c ./compile_process.c -o ./build/compile_process.o

clean:
	rm *.exe
	rm ./build/*.o