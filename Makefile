OBJECTS= ./build/compiler.o ./build/compile_process.o ./build/helpers/buffer.o ./build/helpers/vector.o
INCLUDES= -I ./

all: $(OBJECTS)
	gcc main.c $(INCLUDES) $(OBJECTS) -g -o ./main

./build/compiler.o: ./compiler.c
	gcc -g $(INCLUDES) -c ./compiler.c -o ./build/compiler.o

./build/compile_process.o: ./compile_process.c
	gcc -g $(INCLUDES) -c ./compile_process.c -o ./build/compile_process.o

./build/helpers/buffer.o: ./helpers/buffer.c
	gcc -g $(INCLUDES) -c ./helpers/buffer.c -o ./build/helpers/buffer.o

./build/helpers/vector.o: ./helpers/vector.c
	gcc -g $(INCLUDES) -c ./helpers/vector.c -o ./build/helpers/vector.o


clean:
	rm *.exe
	rm ./build/*.o