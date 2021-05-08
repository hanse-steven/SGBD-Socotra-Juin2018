#ifndef SOCOTRA_STRUCT_H
#define SOCOTRA_STRUCT_H

#include <windows.h>
#include "saisie.h"

#define LISTE_OUVRIER "ouvrier.dat"
#define LISTE_CHANTIER "chantier.dat"
#define LIST_HORAIRE "horaire.dat"

#define MAXOUVRIER 100
#define MAXCHANTIER 20
#define MAXOCCUPE 2000

#define MAXNOM 25
#define MAXPRENOM 30
#define MAXRUE 50
#define MAXVILLE 20
#define MAXSPE 20

#define MAXNOMCHAN 25
#define MAXMAITRE 30
#define MAXGERANT 5

struct _date{
    short jour;
    short mois;
    short annee;
};
typedef struct _date Date;

struct _ouvriers{
    long NumRegistre ;
    char nom[MAXNOM] ;
    char prenom[MAXPRENOM] ;
    char rue[MAXRUE] ;
    int CodePostal ;
    char ville[MAXVILLE] ;
    char specialite[MAXSPE] ;
    Date d_engag ;
    Date d_naiss ;
};
typedef struct _ouvriers Ouvrier;

struct _EstOccupe{
    long NumRegistre ;
    long NumChantier ;
    Date date ;
    short heures;
    short minutes;
};
typedef struct _EstOccupe EstOccupe;

struct _chantier{
    long Numchantier;
    char NomChantier[MAXNOMCHAN] ;
    char rue[MAXRUE] ;
    int CodePostal ;
    char ville[MAXVILLE];
    char MaitreOuvrage[MAXMAITRE] ;
    float Montant;
    int Duree;
    char CodeGerant[MAXGERANT] ;
};
typedef struct _chantier Chantier;

struct _indexOuvrier {
    int adresse;
    long NumRegistre ;
    char nom[MAXNOM] ;
    char prenom[MAXPRENOM];
};
typedef struct _indexOuvrier IndexOuvrier;

struct _indexChantier {
    int adresse;
    long Numchantier;
    char NomChantier[MAXNOMCHAN];
};
typedef struct _indexChantier IndexChantier;

#endif
