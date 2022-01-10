.PHONY=application
application:
	make lib
	make objs
	${CC} ${CFLAGS} src/test.o -o main ${LIBS} -L`pwd` -lstginput -Wl,-rpath=./

.PHONY=application-static
application-static:
	make lib-static
	make objs
	${CC} ${CFLAGS} src/test.o libstginput.a -o main ${LIBS}

.PHONY=lib
lib:
	make objs-lib
	${CC} ${CFLAGS} src/STGInput/AxisState.o src/STGInput/Convenience.o src/STGInput/ButtonState.o src/STGInput/GamepadState.o src/STGInput/KeyboardState.o src/STGInput/MouseState.o src/STGInput/STGInput.o -shared -o libstginput.${EXT} ${LIBS}

.PHONY=lib-static
lib-static:
	make objs-lib
	ar rcs libstginput.a src/STGInput/AxisState.o src/STGInput/Convenience.o src/STGInput/ButtonState.o src/STGInput/GamepadState.o src/STGInput/KeyboardState.o src/STGInput/MouseState.o src/STGInput/STGInput.o ${LIBS}

.PHONY=objs
objs:
	${CC} ${CFLAGS} -c src/test.c -o src/test.o ${INCS}

.PHONY=objs-lib
objs-lib:
	${CC} ${CFLAGS} -c src/STGInput/AxisState.c -o src/STGInput/AxisState.o -fPIC ${INCS}
	${CC} ${CFLAGS} -c src/STGInput/Convenience.c -o src/STGInput/Convenience.o -fPIC ${INCS}
	${CC} ${CFLAGS} -c src/STGInput/ButtonState.c -o src/STGInput/ButtonState.o -fPIC ${INCS}
	${CC} ${CFLAGS} -c src/STGInput/GamepadState.c -o src/STGInput/GamepadState.o -fPIC ${INCS}
	${CC} ${CFLAGS} -c src/STGInput/KeyboardState.c -o src/STGInput/KeyboardState.o -fPIC ${INCS}
	${CC} ${CFLAGS} -c src/STGInput/MouseState.c -o src/STGInput/MouseState.o -fPIC ${INCS}
	${CC} ${CFLAGS} -c src/STGInput/STGInput.c -o src/STGInput/STGInput.o -fPIC ${INCS}

.PHONY=clean
clean:
	rm -f src/STGInput/*.o ./main ./libstginput.${EXT}

.PHONY=valgrind
valgrind:
	valgrind ./main -v --leak-check=full 2> valgrind.txt
