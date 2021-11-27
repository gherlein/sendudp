SRC := sendudp.c
OUT := sendudp

all:
	gcc ${SRC} -o ${OUT}

arm:
	arm-linux-gnueabihf-gcc ${SRC} -o ${OUT}

clean:
	-@rm -Rf *~ ${OUT}



