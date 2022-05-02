#ifndef ARBRE_H
#define ARBRE_H
#include "individu.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define LG_MAX 64

typedef struct s_date { unsigned short jour, mois, annee; } date;
typedef unsigned int Nat;
typedef unsigned int ident;

typedef struct s_individu {
    char nom[LG_MAX];
    date naissance, deces;
    ident pere, mere, cadet, faine;
} Individu; 



typedef struct s_genealogie {
    Individu *tab; // tableau alloué dynamiquement
    Nat id_cur; // identifiant actuel
    Nat taille_max_tab; // taille max du tableau
} Genealogie; 

void genealogieFree(Genealogie *g);

ident adj(Genealogie *g, char *s, ident p, ident m, date n, date d); 

Nat preHash(char *s, ident p, ident m, date n, date d);

Individu *get(Genealogie *g, ident x); 



#endif