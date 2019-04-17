INCLDIR	:= headers
OBJDIR	:= objects
SRCDIR	:= sources
BINDIR	:= builds
TSTDIR	:= tests

CC 		:= gcc
CFLAGS 	:= -Wall
LDFLAGS	:=

# Fichiers sources et objets
SRCS = $(wildcard $(SRCDIR)/*.c)

OBJS = $(subst $(SRCDIR)/,$(OBJDIR)/, $(subst .c,.o, $(SRCS)))

# Définir les executables principaux ici
EXEC = raid5 raid5_test

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
$(EXEC): %: $(TSTDIR)/%.c $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $^ $(LDFLAGS)

.PHONY: makedir
makedir:
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	rm -rf $(OBJDIR)/*
	rm -rf $(BINDIR)/*