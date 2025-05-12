# Copyright (C) 1989 Free Software Foundation, Inc.
# written by Douglas C. Schmidt (schmidt@ics.uci.edu)
# 
# This file is part of GNU GPERF.
# 
# GNU GPERF is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 1, or (at your option)
# any later version.
# 
# GNU GPERF is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU GPERF; see the file COPYING.  If not, write to
# the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. 

CC = gcc
DFLAGS= -DLO_CAL -DGATHER_STATISTICS #-DRLIMIT_STACK 
# OFLAGS= -O -p -g -fstrength-reduce -fomit-frame-pointer -fdelayed-branch -finline-functions # gcc options 
OFLAGS= -O -p -g  -Wall -d
CFLAGS= $(DFLAGS) $(OFLAGS)
OBJS = options.o iterator.o main.o perfect.o keylist.o listnode.o xmalloc.o \
       hashtable.o boolarray.o readline.o stderr.o version.o getopt.o
SOURCES = options.c iterator.c main.c perfect.c keylist.c listnode.c xmalloc.c \
       hashtable.c boolarray.c readline.c stderr.c version.c getopt.c

all: gperf

gperf: $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

clean: 
	-rm -f *.o core *~ #*#

realclean: clean
	-rm -f gperf

# dependencies
# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

boolarray.o: boolarray.c boolarray.h prototype.h options.h
boolarray.o: prototype.h
getopt.o: getopt.c 
hashtable.o: hashtable.c hashtable.h keylist.h
hashtable.o: listnode.h prototype.h prototype.h options.h
hashtable.o: prototype.h
iterator.o: iterator.c iterator.h
iterator.o: prototype.h
keylist.o: keylist.c options.h
keylist.o: prototype.h readline.h prototype.h keylist.h
keylist.o: listnode.h prototype.h hashtable.h keylist.h
keylist.o: prototype.h stderr.h prototype.h 
listnode.o: listnode.c options.h 
listnode.o: prototype.h listnode.h prototype.h stderr.h prototype.h
main.o: main.c stderr.h prototype.h 
main.o: options.h prototype.h perfect.h prototype.h
main.o: keylist.h listnode.h prototype.h boolarray.h
main.o: prototype.h
options.o: options.c options.h
options.o: prototype.h iterator.h prototype.h stderr.h
options.o: prototype.h
perfect.o: perfect.c 
perfect.o: options.h prototype.h
perfect.o: perfect.h prototype.h keylist.h listnode.h
perfect.o: prototype.h boolarray.h prototype.h stderr.h prototype.h
readline.o: readline.c readline.h prototype.h
stderr.o: stderr.c stderr.h prototype.h
version.o: version.c
xmalloc.o: xmalloc.c 

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
