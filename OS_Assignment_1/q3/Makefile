CC = gcc
PROGS = date cal uptime main

all: $(PROGS)

date: date.c
	$(CC) -o $@ $^

calc: cal.c
	$(CC) -o $@ $^

uptime: uptime.c
	$(CC) -o $@ $^

main: date cal uptime main.c
	$(CC) -o $@ main.c
