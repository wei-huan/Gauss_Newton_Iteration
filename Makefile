target = GNI_Acce
src := *.c
src += ./utils/*.c
src += ./test/*.c
CC = g++
CCFLAG = -g -Wall -fsanitize=address -fno-omit-frame-pointer #-nostartfiles -etest_matrix -fno-builtin
CPPFLAG  = -g -Wall

all:
	$(CC) $(CCFLAG) $(src) -o $(target)

clean:
	rm -f $(target)