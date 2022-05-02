
#ifndef INDIVIDU_H
#define INDIVIDU_H

#define LG_MAX 64

typedef struct s_date { unsigned short jour, mois, annee; } date;
typedef unsigned int Nat;
typedef unsigned int ident;

typedef struct s_individu {
    char nom[LG_MAX];
    date naissance, deces;
    ident pere, mere, cadet, faine;
} Individu; 






#endif