#include <stdbool.h>
#include "chantier.h"

//Ajout case 6
void AjoutChantier(IndexChantier list[MAXCHANTIER])
{
    short erreur = 0;
    long idInterdit[MAXCHANTIER];
    int i;
    Chantier tab;
    FILE *fp;


    system("cls");
    printf("+----------------------------+\n");
    printf("|     Ajouter un chantier    |\n");
    printf("+----------------------------+\n");

    fp = fopen(LISTE_CHANTIER,"r+b");

    if(fp == NULL)
    {
        printf("Ajout de donnees impossible");
    }
    else
    {
        i = verificationPlaceIndexChantier(list);
        idExistantChantier(list,idInterdit);

        if(i != -1)
        {
            list[i].adresse = i;
            do
            {
                if(erreur == 1) printf("Valeur Interdite car deja utilisee !\n");
                printf("Numero de chantier (1 a 99999): ");
                tab.Numchantier = LireLong(0,99999);

                if(verifNumChantierDispo(idInterdit,tab.Numchantier) == 0)
                    erreur = 0;
                else
                    erreur = 1;

            }while(erreur == 1);
            list[i].Numchantier = tab.Numchantier;

            printf("Nom du chantier: ");
            LireChaine(tab.NomChantier,MAXNOMCHAN);
            strcpy(list[i].NomChantier,tab.NomChantier);

            printf("Rue: ");
            LireChaine(tab.rue,MAXRUE);

            printf("Code Postal: ");
            tab.CodePostal = LireShort(1000,9999);

            printf("Ville: ");
            LireNomPropre(tab.ville,MAXVILLE);

            printf("Maitre d\'ouvrage: ");
            LireChaine(tab.MaitreOuvrage,MAXMAITRE);

            printf("Montant des travaux: ");
            tab.Montant = LireFloat(0,16000000);

            printf("Duree des travaux: ");
            tab.Duree = LireShort(1,9999);

            printf("Code Gerant: ");
            LireChaine(tab.CodeGerant,MAXGERANT);

            if(fseek(fp,sizeof(Chantier)*i,SEEK_SET) == 0)
            {
                fwrite(&tab,sizeof(Chantier),1,fp);
                printf("Le chantier a bien ete ajoute\n");
            }
            else
            {
                printf("Ajout au fichier impossible !\n");
                list[i].adresse = -1;
                list[i].Numchantier = -1;
                strcpy(list[i].NomChantier," ");
            }
        }
        else
        {
            printf("Plus de place Disponible");
            system("pause");
        }
        fclose(fp);
    }
    system("pause");
}

//Affichage tous case 7
void AffichageChantierList(IndexChantier *list)
{
    short i = 0;
    long choix = 0;
    IndexChantier *tmp = list;
    Chantier otmp;
    FILE *fp;

    system("cls");
    printf("+-------------------------------------------+\n");
    printf("|                                           |\n");
    printf("|          Affichage des chantiers          |\n");
    printf("|                                           |\n");
    printf("+-------------------------------------------+\n\n");

    printf(" +-------+---------------------------+\n");
    printf(" |  id   |            nom            |\n");
    printf(" +-------+---------------------------+\n");
    while(i < MAXCHANTIER)
    {
        if(tmp->Numchantier != -1)
            printf(" | %05ld | %25s | \n",tmp->Numchantier,tmp->NomChantier);
        i++;
        tmp++;
    }
    printf(" +-------+---------------------------+\n");

    printf("Voulez-vous des informations detaille ?\n");
    printf("Choix (1 - oui, 2 - non): ");
    choix = LireLong(1,2);

    if(choix == 1)
    {
        printf("Introduisez l'id de l\'ouvrier voulu: ");
        choix = LireLong(1,99999);

        i = RechercheIndexChantier(list,choix);

        if(i == -1)
            printf("Id incorrect ou jeu non trouve !\n");
        else
        {
            fp = fopen(LISTE_CHANTIER,"r+b");

            if(fp==NULL)
            {
                printf("Impossible d'afficher les details: ouverture du fichier impossible !");
            }
            else
            {
                fseek(fp,list[i].adresse*sizeof(Chantier),SEEK_SET);
                fread(&otmp,sizeof(Chantier),1,fp);

                system("cls");
                printf("+--------------------------------------------+\n");
                printf("|                                            |\n");
                printf("|          Affichage d\'un chantier           |\n");
                printf("|                                            |\n");
                printf("+--------------------------------------------+\n\n");

                printf("+-------------------------------------------------------------+\n");
                printf("|                                   %25s |\n",otmp.NomChantier);
                printf("+------------------------+------------------------------------+\n");
                printf("| Num de chantier        | %34ld |\n",otmp.Numchantier);
                printf("| Rue                    | %34s |\n",otmp.rue  );
                printf("| Code Postal            | %34hd |\n",otmp.CodePostal);
                printf("| Ville                  | %34s |\n",otmp.ville);
                printf("| Maitre d ouvrage       | %34s |\n",otmp.MaitreOuvrage);
                printf("| Montant                | %34f |\n",otmp.Montant);
                printf("| Duree                  | %34d |\n",otmp.Duree);
                printf("| Code Gerant            | %34s |\n",otmp.CodeGerant);
                printf("+------------------------+------------------------------------+\n");
            }

        }
    }

    printf("Retour au menu principal\n");
    system("pause");
}

//Affichage unique case 8
void affichageOuvrierPourChantier(IndexChantier *listChantier,IndexOuvrier *listOuvrier)
{
    short i = 0;
    long choix = 0;
    IndexChantier *tmp = listChantier;
    Chantier otmp;
    FILE *fp;
    EstOccupe estOccupe;

    system("cls");
    printf("+------------------------------------------------------------------+\n");
    printf("|                                                                  |\n");
    printf("|      Affichage des ouvriers ayant travaille sur un chantier      |\n");
    printf("|                                                                  |\n");
    printf("+------------------------------------------------------------------+\n\n");

    printf(" +-------+---------------------------+\n");
    printf(" |  id   |            nom            |\n");
    printf(" +-------+---------------------------+\n");
    while(i < MAXCHANTIER)
    {
        if(tmp->Numchantier != -1)
            printf(" | %05ld | %25s | \n",tmp->Numchantier,tmp->NomChantier);
        i++;
        tmp++;
    }
    printf(" +-------+---------------------------+\n");

    printf("Introduisez l'id du chantier voulu: ");
    choix = LireLong(1,99999);

    i = RechercheIndexChantier(listChantier,choix);

    if(i == -1)
        printf("Id incorrect ou jeu non trouve !\n");
    else
    {
        fp = fopen(LIST_HORAIRE, "rb");

        if(fp != NULL)
        {
            printf("Liste des ouvriers: \n");
            printf(" +-------+---------------------------+--------------------------------+\n");
            printf(" |  id   |            nom            |             prenom             |\n");
            printf(" +-------+---------------------------+--------------------------------+\n");
            fread(&estOccupe,sizeof(EstOccupe), 1, fp);
            while(!feof(fp))
            {

                if(estOccupe.NumChantier == choix){
                    i = RechercheIndexOuvrier(listOuvrier,estOccupe.NumRegistre);
                    printf(" | %05ld | %25s | %30s |\n",listOuvrier[i].NumRegistre,listOuvrier[i].nom,listOuvrier[i].prenom);
                }
                fread(&estOccupe,sizeof(EstOccupe), 1, fp);
            }
            fclose(fp);
            printf(" +-------+---------------------------+--------------------------------+\n");
        }
        else
        {
            printf("Echec de l'ouverture du fichier :( \n");
        }

    }

    system("pause");
}

//Fonction
int verificationPlaceIndexChantier(IndexChantier list[MAXCHANTIER])
{
    short i, trouve = 0;
    int val = 0;

    for(i = 0;i<MAXCHANTIER && trouve == 0;i++)
    {
        if(list[i].Numchantier == -1)
        {
            trouve = 1;
            val = list[i].adresse;
        }
    }

    return val;
}
void idExistantChantier(IndexChantier list[MAXCHANTIER],long *idInterdit)
{
    short i=0;

    while(i < MAXCHANTIER)
    {
        *idInterdit = list[i].Numchantier;
        idInterdit++;
        i++;
    }
}
short verifNumChantierDispo(long *idInterdit,long id)
{
    short res = 0,i = 0;

    while(i < MAXCHANTIER && *idInterdit != id)
    {
        idInterdit++;
        i++;
    }

    if(*idInterdit == id)
    {
        res = 1;
    }
    else
    {
        res = 0;
    }

    return res;
}
short RechercheIndexChantier(IndexChantier *list,long valChercher)
{
    short i = 0,trouve=-1;

    while(i < MAXCHANTIER && trouve == -1)
    {
        if(list[i].Numchantier == valChercher)
        {
            trouve = i;
        }
        else
        {
            i++;
        }
    }

    return trouve;
}

void triIndexChantier(IndexChantier *listChantier)
{
    int i,j;
    boolean tab_en_ordre = false;
    int taille = MAXCHANTIER;

    while(!tab_en_ordre)
    {
        tab_en_ordre = true;
        for(i = 0;i < taille-1;i++)
        {
            if(listChantier[i].Numchantier != -1 && listChantier[i+1].Numchantier != -1 && strcmp(listChantier[i].NomChantier,listChantier[i+1].NomChantier) == 1)
            {
                EchangeChantier(&listChantier[i],&listChantier[i+1]);
                tab_en_ordre = false;
            }
        }
        taille--;
    }
}

void EchangeChantier(IndexChantier *tmp1,IndexChantier *tmp2)
{
    IndexChantier tmp;

    strcpy(tmp.NomChantier,tmp1->NomChantier);
    tmp.Numchantier = tmp1->Numchantier;
    tmp.adresse = tmp1->adresse;

    strcpy(tmp1->NomChantier,tmp2->NomChantier);
    tmp1->Numchantier = tmp2->Numchantier;
    tmp1->adresse = tmp2->adresse;

    strcpy(tmp2->NomChantier,tmp.NomChantier);
    tmp2->Numchantier = tmp.Numchantier;
    tmp2->adresse = tmp.adresse;
}