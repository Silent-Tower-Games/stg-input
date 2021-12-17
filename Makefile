CC=gcc
CFLAGS=-pedantic -O3

application:
	make lib
	make objs
	${CC} ${CFLAGS} src/test.o -o main `sdl2-config --libs` -L`pwd` -lstginput -Wl,-rpath=./

application-static:
	make lib-static
	make objs
	${CC} ${CFLAGS} src/test.o libstginput.a -o main `sdl2-config --libs`

lib:
	make objs-lib
	${CC} ${CFLAGS} src/STGInput/AxisState.o src/STGInput/Convenience.o src/STGInput/ButtonState.o src/STGInput/GamepadState.o src/STGInput/KeyboardState.o src/STGInput/MouseState.o src/STGInput/STGInput.o -shared -o libstginput.so `sdl2-config --libs`

lib-static:
	make objs-lib
	ar rcs libstginput.a src/STGInput/AxisState.o src/STGInput/Convenience.o src/STGInput/ButtonState.o src/STGInput/GamepadState.o src/STGInput/KeyboardState.o src/STGInput/MouseState.o src/STGInput/STGInput.o

objs:
	${CC} ${CFLAGS} -c src/test.c -o src/test.o

objs-lib:
	${CC} ${CFLAGS} -c src/STGInput/AxisState.c -o src/STGInput/AxisState.o -fPIC
	${CC} ${CFLAGS} -c src/STGInput/Convenience.c -o src/STGInput/Convenience.o -fPIC
	${CC} ${CFLAGS} -c src/STGInput/ButtonState.c -o src/STGInput/ButtonState.o -fPIC
	${CC} ${CFLAGS} -c src/STGInput/GamepadState.c -o src/STGInput/GamepadState.o -fPIC
	${CC} ${CFLAGS} -c src/STGInput/KeyboardState.c -o src/STGInput/KeyboardState.o -fPIC
	${CC} ${CFLAGS} -c src/STGInput/MouseState.c -o src/STGInput/MouseState.o -fPIC
	${CC} ${CFLAGS} -c src/STGInput/STGInput.c -o src/STGInput/STGInput.o -fPIC

clear:
	rm -f src/STGInput/*.o ./main ./libstginput.so

valgrind:
	valgrind ./main -v --leak-check=full 2> valgrind.txt
