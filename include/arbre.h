#ifndef ARBRE_H
#define ARBRE_H

#include <stdio.h>
#include <stdlib.h>
#include "individu.h"
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct s_genealogie {
    Individu *tab; // tableau alloué dynamiquement
    Nat id_cur; // identifiant actuel
    Nat taille_max_tab; // taille max du tableau
} Genealogie; 


void genealogieInit(Genealogie *g);

void genealogieFree(Genealogie *g);


Individu *get(Genealogie *g, ident x); 

ident adj(Genealogie *g, char *s, ident p, ident m, date n, date d); 

ident chrch_cadet(Genealogie *g, ident p, ident m, date n, date d);

ident chrch_faine(Genealogie *g, ident p, ident m, date n, date d);

bool freres_soeurs(Genealogie *g, ident x, ident y);

bool cousins(Genealogie *g, ident x, ident y);

void affiche_freres_soeurs(Genealogie *g, ident x);

void affiche_enfants(Genealogie *g, ident x);

void affiche_cousins(Genealogie *g, ident x);

void affiche_oncles(Genealogie *g, ident x);

bool ancetre(Genealogie *g, ident x, ident y);

bool ancetreCommun(Genealogie *g, ident x, ident y);

ident plus_ancien(Genealogie *g, ident x); 

ident affiche_parente(Genealogie *g, ident x); 

ident affiche_descendance(Genealogie *g, ident x);

#endif