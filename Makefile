CC=gcc
CFLAGS=-pedantic -O3

application:
	make lib
	make objs
	${CC} ${CFLAGS} ./src/test.o -o main `sdl2-config --libs` -L`pwd` -lstginput -Wl,-rpath=./

application-static:
	make lib-static
	make objs
	${CC} ${CFLAGS} ./src/test.o libstginput.a -o main `sdl2-config --libs`

lib:
	make objs-lib
	${CC} ${CFLAGS} ./src/STGInput.o -shared -o libstginput.so `sdl2-config --libs`

lib-static:
	make objs-lib
	ar rcs libstginput.a src/STGInput.o

objs:
	${CC} ${CFLAGS} -c ./src/test.c -o ./src/test.o

objs-lib:
	${CC} ${CFLAGS} -c ./src/STGInput.c -o ./src/STGInput.o -fPIC

clear:
	rm -f ./src/*.o ./main ./libstginput.so

valgrind:
	valgrind ./main -v --leak-check=full 2> valgrind.txt