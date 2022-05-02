#include "arbre.h"



void genealogieInit(Genealogie *g){
    g=malloc(sizeof *g);
    g->tab=NULL;
    g->id_cur=0;
    return;
}

void genealogieFree(Genealogie *g){
    free(g->tab);
    g->tab=NULL;
    free(g);
    return;
}


Nat preHash(char *s, ident p, ident m, date n, date d){
    Nat hash=0;
    Nat mul=1;
    for(int i=0; i<LG_MAX; i++){
        if (s[i]=='\0'){break;}
        hash+=(int)(mul*s[i]);
        mul=mul*10;
    }
    hash+=p;
    hash+=m;
    hash+=n.jour*100000000;
    hash+=n.mois*1000000;
    hash+=n.annee;
    hash+=d.jour*100000000;
    hash+=d.mois*1000000;
    hash+=d.annee;
    hash=hash%1999957;
    return hash;
}







ident adj(Genealogie *g, char *s, ident p, ident m, date n, date d){
    if(g->tab==NULL){
        g->tab=malloc(sizeof*g->tab*51);
        g->tab=malloc(sizeof*g->tab*50);
        g->taille_max_tab=50;
        if(g->tab==NULL){exit(1); printf("Tab pas alloué.");}
    }        
    else if (g->id_cur==g->taille_max_tab-1){
     

    g->id_cur=preHash(s,p,m,n,d);
    while (g->id_cur>=g->taille_max_tab-1){
            g->tab=realloc(g->tab,sizeof*g->tab*(g->taille_max_tab+50));
            g->taille_max_tab+=50;
        }    

    
    }   
    
    strncpy(g->tab[g->id_cur].nom,s, strlen(s));
    memcpy(&g->tab[g->id_cur].pere,&p, sizeof p);
    memcpy(&g->tab[g->id_cur].mere,&m, sizeof m);
    memcpy(&g->tab[g->id_cur].naissance,&n, sizeof n);
    memcpy(&g->tab[g->id_cur].deces,&d, sizeof d);
    g->tab[g->id_cur].cadet=0;
    g->tab[g->id_cur].faine=0;
    return g->id_cur;
}


//precondition: x existe
Individu *get(Genealogie *g, ident x){
    return &g->tab[x];
    
} 

//Partie 4

bool freres_soeurs(Genealogie *g, ident x, ident y);

bool cousins(Genealogie *g, ident x, ident y);

void affiche_freres_soeurs(Genealogie *g, ident x);

void affiche_enfants(Genealogie *g, ident x);

void affiche_cousins(Genealogie *g, ident x);

void affiche_oncles(Genealogie *g, ident x);