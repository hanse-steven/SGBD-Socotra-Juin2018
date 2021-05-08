#include "horaire.h"

void ajoutHoraire(IndexChantier *listChantier,IndexOuvrier *listOuvrier)
{
    short choix,i,indice = -1,nbreJ,trouve,vali = 0;
    char pch[MAXDATE];
    Date date;
    long tmpL;
    EstOccupe tmp;
    IndexChantier *tabChantier = listChantier;
    IndexOuvrier *tabOuvrier = listOuvrier;

    long idInterdit[MAXOUVRIER];

    system("cls");
    printf("+-------------------------------------------+\n");
    printf("|                                           |\n");
    printf("|          Affichage des chantiers          |\n");
    printf("|                                           |\n");
    printf("+-------------------------------------------+\n\n");

    printf(" +-------+---------------------------+\n");
    printf(" |  id   |            nom            |\n");
    printf(" +-------+---------------------------+\n");

    i = 0;
    while(i < MAXCHANTIER)
    {
        if(tabChantier->Numchantier != -1)
            printf(" | %05ld | %25s | \n",tabChantier->Numchantier,tabChantier->NomChantier);
        i++;
        tabChantier++;
    }

    printf(" +-------+---------------------------+\n");

    printf("Chantier (introduire id): ");
    choix = LireLong(1,10000);

    indice = RechercheIndexChantier(listChantier,(long)choix) ;

    if(indice != -1)
    {
        tmp.NumChantier = choix;

        do
        {
            printf("Date du chantier:");
            LireChaine(pch,MAXDATE);
            if(!LireDate(&date, pch) || !ValideDate(&date))
            {
                vali = 0;
                printf("Veuillez encoder une date valide\n");
            }
            else
            {
                vali = 1;
            }
        }while(!vali);

        tmp.date.jour = date.jour;
        tmp.date.mois = date.mois;
        tmp.date.annee = date.annee;

        printf("Entrez les heure: ");
        tmp.heures = LireShort(0,24);

        printf("Entrez les mintues: ");
        tmp.minutes = LireShort(0,59);

        system("cls");
        printf("+------------------------------------------+\n");
        printf("|                                          |\n");
        printf("|          Affichage des ouvriers          |\n");
        printf("|                                          |\n");
        printf("+------------------------------------------+\n\n");

        printf(" +-------+---------------------------+--------------------------------+\n");
        printf(" |  id   |            nom            |             prenom             |\n");
        printf(" +-------+---------------------------+--------------------------------+\n");

        i = 0;
        while(i < MAXOUVRIER)
        {
            if(tabOuvrier->NumRegistre != -1)
                printf(" | %5ld | %25s | %30s |\n",tabOuvrier->NumRegistre,tabOuvrier->nom,tabOuvrier->prenom);
            i++;
            tabOuvrier++;
        }

        printf(" +-------+---------------------------+--------------------------------+\n");
        idExistantOuvrier(listOuvrier,idInterdit);
        do
        {
            printf("ID de l\'ouvrier (-1 pour annuler): ");
            tmpL = LireLong(-1,99999);
        }while(tmpL != -1 && verifNumOuvrierDispo(idInterdit,tmpL) != 1);

        if(tmpL >= 0)
        {
            tmp.NumRegistre = tmpL;

            if(verificationUnicite(&tmp) == 0)
            {
                ecrirePartieFichiers(&tmp);
                i++;
            }
            else
            {
                printf("Problème unicite des donnees => Annulation de l\'action en cours\nRetour au menu principal...\n");
            }
        }
        else
        {
            printf("Ajout annule !\nRetour au menu principale...\n");
        }

    }
    else
    {
        printf("Pas de chantier trouve !\n");
    }
    system("pause");
}

short verificationUnicite(EstOccupe *tab)
{
    short res = 0;
    FILE *fp = fopen(LIST_HORAIRE, "r+b");
    EstOccupe tmp;

    if(fp != NULL)
    {
        fread(&tmp,sizeof(EstOccupe), 1, fp);
        while(!feof(fp) && res != 1)
        {
            if(tmp.NumRegistre == tab->NumRegistre &&
               tmp.NumChantier == tab->NumChantier &&
               tmp.date.jour == tab->date.jour &&
               tmp.date.mois == tab->date.mois &&
               tmp.date.annee == tab->date.annee)
            {
                printf("Donnees deja enregistree !");
                res = 1;
            }

            fread(&tmp,sizeof(EstOccupe), 1, fp);
        }

        fclose(fp);
    }
    else
    {
        res = 0;
    }

    return res;
}

void ecrirePartieFichiers(EstOccupe *tab)
{
    FILE *fp = fopen(LIST_HORAIRE, "a+b");

    if(fp != NULL)
    {
        fseek(fp,0,SEEK_END);
        fwrite(tab, sizeof(EstOccupe), 1, fp);
        fclose(fp);
    }
    else
    {
        perror("Erreur rencontree lors de l'ouverture du fichier !\n");
    }
}

void affichageHoraires()
{
    EstOccupe tmp;
    FILE *fp;

    system("cls");
    printf("+---------------------------------------+\n");
    printf("|                                       |\n");
    printf("|         Affichage des horaires        |\n");
    printf("|                                       |\n");
    printf("+---------------------------------------+\n\n");

    fp = fopen(LIST_HORAIRE, "rb");

    if(fp != NULL)
    {
        printf("+--------------+-------------+------------+-------+\n");
        printf("| NumRegistre  | NumChantier |    Date    | Temps |\n");
        printf("+--------------+-------------+------------+-------+\n");
        fread(&tmp,sizeof(EstOccupe), 1, fp);
        while(!feof(fp))
        {
            printf("| %12ld |",tmp.NumRegistre);
            printf(" %11ld |",tmp.NumChantier);
            printf(" %02hd/%02hd/%04hd ",tmp.date.jour,tmp.date.mois,tmp.date.annee);
            printf("| %02hdH%02hd |\n",tmp.heures,tmp.minutes);
            fread(&tmp,sizeof(EstOccupe), 1, fp);
        }
        printf("+--------------+-------------+------------+-------+\n");
        fclose(fp);
    }
    else
    {
        printf("Echec de l'ouverture du fichier :( \n");
    }

    system("pause");
}