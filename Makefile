target = GNI_Acce
src := *.c
src += ./utils/*.c
CC = g++
CCFLAG = -g -Wall -fsanitize=address -fno-omit-frame-pointer #-std=c99 # -lm

all:
	$(CC) $(CCFLAG) $(src) -o $(target)

clean:
	rm -f $(target)