# ******************************************************************** #
# @file 	Makefile du projet RAID									   #
# @author 	Dylan CARON (dcaron81.dc@gmail.com)                        #
#         															   #
# @copyright Licence MIT											   #
# ******************************************************************** #

INCLDIR	:= headers
OBJDIR	:= objects
SRCDIR	:= sources
BINDIR	:= builds
MNSDIR	:= mains
DSKDIR	:= ../RAID

CC 		:= gcc
CFLAGS 	:= -Wall
LDFLAGS	:=

# Fichiers sources et objets
SRCS = $(wildcard $(SRCDIR)/*.c)

OBJS = $(subst $(SRCDIR)/,$(OBJDIR)/, $(subst .c,.o, $(SRCS)))

# Définir les executables principaux ici
EXEC = raid5 cmd_repair cmd_test1 cmd_test2 cmd_dump_inode dump_raid5

ifeq ($(DEBUG), yes)
	CFLAGS += -g
	LDFLAGS =
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS =
endif

all: makedir $(EXEC)

# Création automatique des fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Création automatique des exécutables
$(EXEC): %: $(MNSDIR)/%.c $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^ $(LDFLAGS)

.PHONY: makedir
makedir:
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	rm -rf $(OBJDIR)/*
	rm -rf $(BINDIR)/*

.PHONY: reset_raid
reset_raid:
	rm -rf $(DSKDIR)/*
	touch $(DSKDIR)/vDisk0
	touch $(DSKDIR)/vDisk1
	touch $(DSKDIR)/vDisk2
	touch $(DSKDIR)/vDisk3