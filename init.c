#include "init.h"

void initialisationChantier(IndexChantier *list)
{
    short i=0;
    IndexChantier *tmp = list;
    Chantier chantier;
    FILE *fp;
    fp = fopen(LISTE_CHANTIER,"r+b");

    if(fp==NULL)
    {
        printf("Chantier>  Fichier non existant => creation d'un nouveau fichier\n\n");
        fp = fopen(LISTE_CHANTIER,"w+b");

        while(i<MAXCHANTIER)
        {
            tmp->adresse = i;
            tmp->Numchantier = -1;
            i++;
            tmp++;
        }
    }
    else
    {
        printf("Chantier> Lecture du fichier\n");
        fread(&chantier,sizeof(Chantier),1,fp);

        while(!feof(fp) && i<MAXCHANTIER)
        {
            tmp->adresse = i;
            tmp->Numchantier = chantier.Numchantier;
            strcpy(tmp->NomChantier,chantier.NomChantier);
            fread(&chantier,sizeof(Chantier),1,fp);
            i++;
            tmp++;
        }

        while(feof(fp) && i<MAXCHANTIER)
        {
            tmp->adresse = i;
            tmp->Numchantier = -1;
            i++;
            tmp++;
        }
    }
    fclose(fp);
}

void initialisationOuvrier(IndexOuvrier *list)
{
    short i=0;
    IndexOuvrier *tmp = list;
    Ouvrier ouvrier;
    FILE *fp;
    fp = fopen(LISTE_OUVRIER,"r+b");

    if(fp==NULL)
    {
        printf("Ouvrier> Fichier non existant => creation d'un nouveau fichier\n\n");
        fp = fopen(LISTE_OUVRIER,"w+b");

        while(i<MAXOUVRIER)
        {
            tmp->adresse = i;
            tmp->NumRegistre = -1;
            i++;
            tmp++;
        }
    }
    else
    {
        printf("Ouvrier> Lecture du fichier\n");
        fread(&ouvrier,sizeof(Ouvrier),1,fp);

        while(!feof(fp) && i<MAXOUVRIER)
        {
            //printf("%d\t%ld\t%s\t%s\n",i,ouvrier.NumRegistre,ouvrier.nom,ouvrier.prenom);
            tmp->adresse = i;
            tmp->NumRegistre = ouvrier.NumRegistre;
            strcpy(tmp->nom,ouvrier.nom);
            strcpy(tmp->prenom,ouvrier.prenom);
            fread(&ouvrier,sizeof(Ouvrier),1,fp);
            i++;
            tmp++;
        }

        while(feof(fp) && i<MAXOUVRIER)
        {
            tmp->adresse = i;
            tmp->NumRegistre = -1;
            i++;
            tmp++;
        }
    }
    fclose(fp);
}