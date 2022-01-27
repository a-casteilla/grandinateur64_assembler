# VERSION 0.1

# target
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

# compiler used
CC = cc
CFLAGS = -Wall -pedantic -Wextra -std=c99

# debugger options
DB = gdb
DBCFLAGS = -ggdb3 # Debug level can be change
