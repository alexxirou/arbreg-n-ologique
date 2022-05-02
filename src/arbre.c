#include "arbre.h"




void genealogieInit(Genealogie *g){ //fonction qui initilise l'arbre
    g->tab=NULL;
    g->id_cur=0;
    g->taille_max_tab=0;
    return;
}

void genealogieFree(Genealogie *g){ //liberer l'arbre
    free(g->tab); //on a besoin de liberer juste le tab (verifié avec valgrind)
    g->tab=NULL;
    return;
}




ident adj(Genealogie *g, char *s, ident p, ident m, date n, date d){
    time_t t = time (NULL); //initialise une structure time avec la fonction builtin
    struct tm* lt = localtime (&t);  //fonction pour prendre la date courante
    if(n.jour<=0 || n.mois<=0 ||n.annee<=0 || n.jour>31 || n.mois>12 || n.annee>(lt->tm_year+1900)/*annee courante*/){ //test de date  naissance donnee est entre le min et le max permissibles
        perror("Date naissance invalide."); exit(3);
        }
    
    if(d.jour>31 || d.mois>12 || d.annee>(lt->tm_year+1900)/*annee courante*/){ //test de date deces donnee 
        perror("Date deces invalide."); exit(3);
        }
    
    if(strlen(s)==0){perror("Nom invalide."); exit(4);}
    if(g->tab==NULL){   //malloc initial au tab
        g->tab=malloc(sizeof*g->tab*51);
        g->taille_max_tab=50;
        g->id_cur=0;
        if(g->tab==NULL){perror("Memoire pas alloué dans g->tab"); exit(-1);}//test malloc 
    }        
    
    else if (g->id_cur>=g->taille_max_tab-1){ //augmentation de taille du tab dynamiquement quand l'idcur depasse la taille
            g->taille_max_tab+=50;
            g->tab=realloc(g->tab,sizeof*g->tab*(g->taille_max_tab));   
    }   

    for(int i=1; i==g->id_cur; i++){ //test doublons si le nom et le mere pere et dates sont les memes on retourne le meme indice
        if (strcmp(g->tab[i].nom ,s)==0 && g->tab[i].pere==p && g->tab[i].mere==m && g->tab[i].naissance.annee==n.annee && g->tab[i].naissance.mois==n.mois && g->tab[i].naissance.jour==n.jour && g->tab[i].deces.annee==d.annee && g->tab[i].deces.mois==d.mois && g->tab[i].deces.jour==d.jour){
            return i;           
        }
    }

    g->id_cur+=1; //augmente le id_cur id 0 est utiliser pour les cas vides 
    strncpy(g->tab[g->id_cur].nom,s, strlen(s)); //copier les data des ident et lier avec les pointeurs
    memcpy(&g->tab[g->id_cur].pere,&p, sizeof p);
    memcpy(&g->tab[g->id_cur].mere,&m, sizeof m);
    memcpy(&g->tab[g->id_cur].naissance,&n, sizeof n);
    memcpy(&g->tab[g->id_cur].deces,&d, sizeof d);
    g->tab[g->id_cur].cadet=chrch_cadet(g, p, m, n, d); //mise à jour le cadet
    g->tab[g->id_cur].faine=chrch_faine(g, s, p, m, n, d); //mise à jour le faine
    return g->id_cur; //retourne l'id cour
}

//precondition: x existe
Individu *get(Genealogie *g, ident x){
   if (x<g->taille_max_tab) {return &g->tab[x];}//si x ne depasse pas la taille du g->tab on va regarder dans tab;
   return &g->tab[0];
}

//fonction pour trouver le cadet d'un indiv
ident chrch_cadet(Genealogie *g, ident p, ident m, date n, date d){
    date comparason;
    comparason.jour = 32;
    comparason.mois = 13;
    comparason.annee = 9999; //initialise aux valeurs max
    for (int i = 1; i < g->taille_max_tab; i++)
    {
        if (g->tab[i].naissance.annee == 0){break;} 

        if (g->tab[i].mere == m && g->tab[i].pere == p) //test pere mere
        {
            if (g->tab[i].naissance.annee < n.annee && g->tab[i].naissance.annee < comparason.annee ) //comparason de l'annee de l'indice avec l'annee donee et l'anee comparason. faut être plus petite que tous les deux
            {
                comparason.annee = g->tab[i].naissance.annee; //mettre à jour l'annee comparason
                g->tab[g->id_cur].cadet = i; //stocker le res temp
            }
            else if (g->tab[i].naissance.annee == comparason.annee) //si les annee sont égaux
            {
                if (g->tab[i].naissance.mois < n.mois && g->tab[i].naissance.mois < comparason.mois) //on compara les mois
                {
                    ;
                    comparason.mois = g->tab[i].naissance.mois; //mettre en jour le mosi comparason
                    g->tab[g->id_cur].cadet = i; //stocker le nouv res temp
                }
                else if (g->tab[i].naissance.mois == comparason.mois) //si les annees et les mois sont égaux
                {
                    if (g->tab[i].naissance.jour < n.jour && g->tab[i].naissance.jour < comparason.jour) //compare les jours
                    {
                        ;
                        comparason.jour = g->tab[i].naissance.jour; //mise à jour les jours de comparason
                        g->tab[g->id_cur].cadet = i; //stocker le res
                    }
                }
            }
        }
    }
    return g->tab[g->id_cur].cadet; //retourner le dernier res stocké
}


//fonction pour trouver le faine d'un indiv
ident chrch_faine(Genealogie *g, char *s, ident p, ident m, date n, date d){
    date comparason; //initialise une struct date
    comparason.jour = 0;
    comparason.mois = 0;
    comparason.annee = 0; //initialise aux valeurs min
    for (int i = 1; i < g->taille_max_tab; i++)
    {
        if (g->tab[i].naissance.annee == 0){break;} //si la date de naissance est 0 on s'arret la recherche car le tab est remplie de manière sequentielle

        if (g->tab[i].mere == m && g->tab[i].pere == p){ //on regarde si le nom pere et le nom mere sont les memes que données
        
            if (g->tab[i].naissance.annee > n.annee && g->tab[i].naissance.annee > comparason.annee){ //cherche pour une annee plus grande que donnée et l'annee comparason
                comparason.annee = g->tab[i].naissance.annee; //remplacer l'annee comparason
                g->tab[g->id_cur].faine = i; //stocker le resultat
            }
            else if (g->tab[i].naissance.annee == comparason.annee){ //si les annees sont egaux on regarde les mois
                if (g->tab[i].naissance.mois > n.mois && g->tab[i].naissance.mois > comparason.mois){ //il faut le mois sup de n.mois donné et inferieur de la comparaison
                    comparason.mois = g->tab[i].naissance.mois; //mise à jour le mosi comparaison
                    g->tab[g->id_cur].faine = i; //stocker le resultat
                }
                else if (g->tab[i].naissance.mois == comparason.mois){ //si les mois sont egaux on regarde les jours
                    if (g->tab[i].naissance.jour >= n.jour && g->tab[i].naissance.jour >= comparason.jour && strcmp(g->tab[i].nom, s)!=0 ){ //cherche un jour plus grande que n.jour et jour comparaison
                        comparason.jour = g->tab[i].naissance.jour; //mettre à jour le jour comparaison
                        g->tab[g->id_cur].faine = i; //stocker le res
                    }

                }
            }
        }
    }
    return g->tab[g->id_cur].faine; //retourner le resultat dernier stockée (plus grande date naissance)
}


//Partie 3

bool freres_soeurs(Genealogie *g, ident x, ident y)
{
    ident p1=get(g,get(g,x)->pere);
    ident p2=get(g,get(g,y)->pere);
    ident m1=get(g,get(g,x)->mere);
    ident m2=get(g,get(g,y)->mere);
    return (x!=y && p1!=0 && m1!=0 && p1==p2 && m1==m2);
   
}

bool cousins(Genealogie *g, ident x, ident y)
{

    ident o1=get(g,get(g,get(g,x)->pere)->pere);
    ident o2=get(g,get(g,get(g,y)->pere)->pere);
    ident a1=get(g,get(g,get(g,x)->mere)->mere);
    ident a2=get(g,get(g,get(g,y)->mere)->mere);
    return (x!=y && o1!=0 && a1!=0 && o1==o2 && a1==a2);
}

void affiche_freres_soeurs(Genealogie *g, ident x)
{      ident i = x;
       printf("Freres/Soeurs de %s, \n",g->tab[x]->nom);
       while (g->tab[i].cadet!=0)
       {
           printf("%s ", g->tab[(g->tab[x].cadet)]->nom);
           i=g->tab[i]->cadet;
       }
       i = x;
       while (g->tab[i].faine!=0)
       {
           printf("%s ", g->tab[(g->tab[x].faine)]->nom);
           i=g->tab[i]->faine;
       }
       printf("\n"); 
    
}

void affiche_enfants(Genealogie *g, ident x)
{
    printf("Enfants de %s, \n",g->tab[x]->nom);
    for(int i = 1; i < g->taille_max_tab; i++)
    {
       if(strlen(g->tab[i].nom)==0){break;}

       else if (get(g,get(g,i)->pere)==x  || get(g,get(g,i)->mere)==x)
       {
           printf("%s\n", g->tab[i].nom);
       }
    } 
    printf("\n");
}

void affiche_cousins(Genealogie *g, ident x)
{
    printf("Cousins de %s, \n", g->tab[x].nom);
    for(int i = 1; i < g->taille_max_tab; i++)
    {   
       if(strlen(g->tab[i].nom)==0){break;} 
       else if (freres_soeurs(g, get(g,x)->pere, get(g,i)->pere) || freres_soeurs(g, get(g,x)->mere, get(g,i)->mere) || freres_soeurs(g, g->tab[x].mere , g->tab[i].pere) || freres_soeurs(g, g->tab[x].pere , g->tab[i].mere) ) 
           printf("%s", g->tab[i].nom);
       }
     
    printf("\n");
}

void affiche_oncles(Genealogie *g, ident x)
{
    printf("Cousins de %s, \n", g->tab[x].nom);
    for(int i = 1; i < g->taille_max_tab; i++)
    {
        if(strlen(g->tab[i].nom)==0){break;} 
        else if (freres_soeurs(g, get(g,x)->pere, get(g,i)->pere))
        { 
            printf("%s ", g->tab[g->tab[i].pere].nom);

        }    
        else if(freres_soeurs(g, get(g,x)->mere, get(g,i)->mere))
        {
           printf("%s ", g->tab[g->tab[i].mere].nom); 
        }
        else if( freres_soeurs(g, g->tab[x].mere , g->tab[i].pere))
        {
            printf("%s ", g->tab[g->tab[i].pere].nom); 
        } 
        else if( freres_soeurs(g, g->tab[x].pere , g->tab[i].mere))
        {
            printf("%s ", g->tab[g->tab[i].mere].nom); 
        } 
        printf("/n");
    } 
}
// partie 4 

bool ancetre(Genealogie *g, ident x, ident y){
    
    ident i ==y;
    ident j ==y;
    while (i!=0){
        ident anc1=get(g,get(g,i)->pere);
        if(anc1==x{
            return 1;
        }
        while
        i==anc1
    }

    ident i ==y;
    while (i!=0){
        ident anc2=get(g,get(g,i)->mere);
        if(anc1==x){
            return 1;
        }
        i==anc1
    }
    return 0;
}

bool ancetreCommun(Genealogie *g, ident x, ident y);

ident plus_ancien(Genealogie *g, ident x){
    ident i =x;
    while (get(g,get(g,i)->pere)!=0){

    }
}

ident affiche_parente(Genealogie *g, ident x); 

ident affiche_descendance(Genealogie *g, ident x);

