############
#Makefile
#Lucas Manker
#COSC 3750 Spring 2020
#Homework #7
#4/1/20
#
#Makefile for hw7
###########

CC=gcc
CFLAGS=-ggdb -Wall

.PHONY: clean

wytalkC: wytalkD wytalkC.c socketfun.c
	$(CC) $(CFLAGS) wytalkC.c socketfun.c -o wytalkC

wytalkD: wytalkD.c socketfun.c
	$(CC) $(CFLAGS) wytalkD.c socketfun.c -o wytalkD

clean:
	/bin/rm -f wytalkD wytalkC
