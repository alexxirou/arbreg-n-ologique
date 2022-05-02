#include "arbre.h"


/* main.c */
int main(int argc, char *argv[]) {
    Genealogie g;
    genealogieInit(&g);
    ident ia = adj(&g, "Arthur", 0, 0, (date) { 9, 11, 1879 }, (date) { 12, 11, 1934 });
    ident im = adj(&g, "Marcel", ia, 0, (date){ 1, 7, 1928 }, (date){ 21, 9, 2004 });
    ident ic = adj(&g, "Clothilde", 0, 0, (date){ 30, 8, 1929 }, (date){ 26, 4, 2005 });
    ident ije = adj(&g, "Jeanne", im, ic, (date){ 13,4, 1948 }, (date){ 0,0,0 });
    ident ihe = adj(&g, "Henri", 0,0, (date){ 2,8, 1947 }, (date){ 0,0,0 });
    ident ial = adj(&g, "Aline", 0,0, (date){ 7,9, 1943 }, (date){ 0,0,0 });
    ident ipi = adj(&g, "Pierre", 0, 0, (date){ 26,6, 1941 }, (date){ 0,0,0 });
    ident iju = adj(&g, "Julien", ipi, ial, (date){ 13,8, 1965 }, (date){ 0,0,0 });
    ident ialex = adj(&g, "Alex", ipi, ial, (date){ 18,4, 1969 }, (date){ 0,0,0 });
    ident iso = adj(&g, "Sophie", ihe, ije, (date){ 9,11, 1972 }, (date){ 0,0,0 });
    ident icl = adj(&g, "Clementine", ihe, ije, (date){ 12,10, 1973 }, (date){ 0,0,0 });
    ident ima = adj(&g, "Marion", ihe, ije, (date){ 5,5, 1976 }, (date){ 0,0,0 });
    ident ich = adj(&g, "Christian", 0, 0, (date){ 13,2, 1971 }, (date){ 0,0,0 });
    ident itho = adj(&g, "Thomas", ialex, iso, (date){ 18,10, 2012 }, (date){ 0,0,0 });
    ident icloe = adj(&g, "Cloe", ialex, iso, (date){ 21,6, 2002 }, (date){ 0,0,0 });
    ident ihu = adj(&g, "Hugo", ialex, iso, (date){ 12,5, 2005 }, (date){ 0,0,0 });
    ident isa = adj(&g, "Isabelle", ich, ima, (date){ 28,4, 2003 }, (date){ 0,0,0 });
    printf("%s\n", g.tab[g.tab[ihu].cadet].nom);//test manuel de cadet (doit être cloe)
    Individu *test=get(&g, get(&g, ihu)->cadet); //test fonction get
    printf("%s\n", test->nom); //doit être cloe le cadet de hugo
    Individu *test2=get(&g, get(&g, ihu)->faine); //test faine de hugo doit être tomas
    printf("%s\n", test2->nom);
    genealogieFree(&g);
    return 0;
}