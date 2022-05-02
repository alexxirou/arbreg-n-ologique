# Variables dossiers
SDIR=src
ODIR=obj
BDIR=bin
VER=

# -> Iinclude pour les fichiers .h
CPPFLAGS += -Iinclude -g

# Compile flags 
CFLAGS= $(CPPFLAGS) 

vpath %.c $(SDIR)
vpath %.h $(IDIR)
vpath %.o $(ODIR)	

# Instructions

all: $(BDIR)/main 

	

$(BDIR)/main: $(ODIR)/main.o $(ODIR)/arbre.o
	@mkdir -p $(BDIR)
	gcc  $(ODIR)/main.o $(ODIR)/arbre.o -o $@ $(CFLAGS) 




$(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(ODIR)
	gcc $(CFLAGS) -o $@ -c $<



dist:
	@mkdir -p dist
	tar -c --lzma -f dist/arbreGeneologique-$(VER).tar.xz include src Makefile Doxyfile README.md

clean:
	rm -rf $(ODIR)/
	rm -rf $(BDIR)/
	rm -rf dist/
	rm -rf doc/

doc:
	@doxygen

help:
	@echo "======== Help Arbre Généologique $(VER) ========"
	@echo "./bin/main <grille>: éxécuter le programme"
	@echo "make: compiler le programme"
	@echo "make clean: effacer les fichiers générés"
	@echo "make dist: créer une archive du projet"
	@echo "make doc: générér la documentation doxygen"
	@echo "make help: afficher l'aide"

