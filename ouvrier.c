#include <stdbool.h>
#include "ouvrier.h"

//Relatif Ajout case 1
void AjoutOuvrier(IndexOuvrier list[MAXOUVRIER])//Incomplet, manque saisie date
{
    short erreur = 0,vali = 0;
    long idInterdit[MAXOUVRIER];
    char pch[MAXDATE];
    int i;
    Ouvrier tab;
    FILE *fp;
    Date date;

    system("cls");
    printf("+---------------------------+\n");
    printf("|     Ajouter un ouvrier    |\n");
    printf("+---------------------------+\n");

    fp = fopen(LISTE_OUVRIER,"r+b");

    if(fp == NULL)
    {
        printf("Ajout de donnees impossible");
    }
    else
    {
        i = verificationPlaceIndexOuvrier(list);
        idExistantOuvrier(list,idInterdit);

        if(i != -1)
        {
            printf("Adresse: %hd\n",i);
            list[i].adresse = i;
            do
            {
                if(erreur == 1) printf("Valeur Interdite car deja utilisee !\n");
                printf("ID (1 a 99999): ");
                tab.NumRegistre = LireLong(0,99999);

                if(verifNumOuvrierDispo(idInterdit,tab.NumRegistre) == 0)
                    erreur = 0;
                else
                    erreur = 1;

            }while(erreur == 1);
            list[i].NumRegistre = tab.NumRegistre;

            printf("Nom: ");
            LireChaine(tab.nom,MAXNOM);
            strcpy(list[i].nom,tab.nom);

            printf("Prenom: ");
            LireChaine(tab.prenom,MAXPRENOM);
            strcpy(list[i].prenom,tab.prenom);

            printf("Rue: ");
            LireChaine(tab.rue,MAXRUE);

            printf("Code Postal: ");
            tab.CodePostal = LireShort(1000,9999);

            printf("Ville: ");
            LireNomPropre(tab.ville,MAXVILLE);

            printf("Specialite: ");
            LireChaine(tab.specialite,MAXSPE);

            do
            {
                printf("Date de naissance:");
                LireChaine(pch,MAXDATE);
                if(!LireDate(&date, pch) || !ValideDate(&date)
                   ||!(date.annee < 2000 ||(date.annee==2000 &&(date.mois<05||(date.mois==05 && date.jour<=21)))))
                {
                    vali = 0;
                    printf("Veuillez encoder une date valide\n");
                }
                else
                {
                    vali = 1;
                }
            }while(!vali);

            tab.d_naiss.jour = date.jour;
            tab.d_naiss.mois = date.mois;
            tab.d_naiss.annee = date.annee;

            do
            {
                printf("Date d engagement:");
                LireChaine(pch,MAXDATE);
                if(!LireDate(&date, pch) || !ValideDate(&date)
                   ||!(date.annee > tab.d_naiss.annee ||(date.annee == tab.d_naiss.annee &&(date.mois > tab.d_naiss.mois||(date.mois==tab.d_naiss.mois && date.jour>=tab.d_naiss.jour)))))
                {
                    vali = 0;
                    printf("Veuillez encoder une date valide\n");
                }
                else
                {
                    vali = 1;
                }
            }while(!vali);

            tab.d_engag.jour = date.jour;
            tab.d_engag.mois = date.mois;
            tab.d_engag.annee = date.annee;

            if(fseek(fp,sizeof(Ouvrier)*i,SEEK_SET) == 0)
            {
                fwrite(&tab,sizeof(Ouvrier),1,fp);
                printf("L\'ouvrier a bien ete ajoute\n");
            }
            else
            {
                printf("Ajout au fichier impossible !\n");
                list[i].adresse = -1;
                list[i].NumRegistre = -1;
                strcpy(list[i].nom," ");
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

//Relatif Modification case 2
void ModifierOuvrier(IndexOuvrier *list)//Incomplet, manque saisie date
{
    short i = 0;
    long choix = 0;
    IndexOuvrier *itmp = list;
    FILE *fp;
    Ouvrier tab;

    system("cls");
    printf("+-----------------------------------------+\n");
    printf("|                                         |\n");
    printf("|            Modifier un ouvrier          |\n");
    printf("|                                         |\n");
    printf("+-----------------------------------------+\n\n");

    printf(" +-------+---------------------------+--------------------------------+\n");
    printf(" |  id   |            nom            |             prenom             |\n");
    printf(" +-------+---------------------------+--------------------------------+\n");

    while(i < MAXOUVRIER)
    {
        if(itmp->NumRegistre != -1)
            printf(" | %05ld | %25s | %30s |\n",itmp->NumRegistre,itmp->nom,itmp->prenom);
        i++;
        itmp++;
    }

    printf(" +-------+---------------------------+--------------------------------+\n");

    printf("Jeu a modifier (introduire id): ");
    choix = LireLong(1,99999);

    i = RechercheIndexOuvrier(list,choix);

    if(i!=-1)
    {
        fp = fopen(LISTE_OUVRIER,"r+b");

        if(fp==NULL)
        {
            printf("Erreur d'ouverture du fichier");
        }
        else
        {
            fseek(fp,(list[i].adresse)*sizeof(Ouvrier),SEEK_SET);
            fread(&tab,sizeof(Ouvrier),1,fp);

            system("cls");
            printf("+--------------------------------------+\n");
            printf("|                                      |\n");
            printf("|            Modifier un ouvrier          |\n");
            printf("|                                      |\n");
            printf("+--------------------------------------+\n\n");

            printf("+----------------------------------------------------------+\n");
            printf("| %25s %30s |\n",tab.nom,tab.prenom);
            printf("+---------------------+------------------------------------+\n");
            printf("| Num Registre        | %34ld |\n",tab.NumRegistre);
            printf("| Specialite          | %34s |\n",tab.specialite);
            printf("| Date Naissance      | %29hd-%hd-%hd |\n",tab.d_naiss.jour,tab.d_naiss.mois,tab.d_naiss.annee);
            printf("| Date Engagement     | %29hd-%hd-%hd |\n",tab.d_engag.jour,tab.d_engag.mois,tab.d_engag.annee);
            printf("| Rue                 | %34s |\n",tab.rue);
            printf("| Code Postal         | %34hd |\n",tab.CodePostal);
            printf("| Ville               | %34s |\n",tab.ville);
            printf("+---------------------+------------------------------------+\n");

            printf("1 - Nom\n");
            printf("2 - Prenom\n");
            printf("3 - Specalite\n");
            printf("6 - Rue\n");
            printf("7 - Code Postal\n");
            printf("8 - Ville\n");
            printf("9 - Retour au menu principal");

            do
            {
                printf("\nChoix: ");
                scanf("%ld",&choix);
            }while(choix < 1 || choix > 10);

            switch(choix)
            {
                case 1:
                    printf("Nom: ");
                    LireNomPropre(tab.nom,MAXNOM);
                    strcpy(list[i].nom,tab.nom);
                    break;

                case 2:
                    printf("Prenom: ");
                    LireNomPropre(tab.prenom,MAXPRENOM);
                    strcpy(list[i].prenom,tab.prenom);
                    break;

                case 3:
                    printf("Specialite: ");
                    LireChaine(tab.specialite,MAXSPE);
                    break;

                case 6:
                    printf("Rue: ");
                    LireChaine(tab.rue,MAXRUE);
                    break;

                case 7:
                    printf("Code Postal: ");
                    LireShort(1000,9999);
                    break;

                case 8:
                    printf("Ville: ");
                    LireNomPropre(tab.ville,MAXVILLE);
                    break;

                case 9:
                    printf("\nRetour au menu principal\n");
                    break;

                default:
                    printf("\nAucun choix detecte\n");
            }
            strcpy(list[i].nom,tab.nom);
            fseek(fp,(list[i].adresse)*sizeof(Ouvrier),SEEK_SET);
            fwrite(&tab,sizeof(Ouvrier),1,fp);
            fclose(fp);
        }
    }
}

//Relatif Suppresion case 3
void SuppresionOuvrier(IndexOuvrier list[MAXOUVRIER])//Nécésite de faire les horaires pour achever le code
{
    short i = 0,indice;
    IndexOuvrier *tmp = list;
    Ouvrier otmp;
    FILE *fp;
    long choix = 0;

    system("cls");
    printf("+------------------------------------------+\n");
    printf("|                                          |\n");
    printf("|          Affichage des ouvriers          |\n");
    printf("|                                          |\n");
    printf("+------------------------------------------+\n\n");

    printf(" +-------+---------------------------+--------------------------------+\n");
    printf(" |  id   |            nom            |             prenom             |\n");
    printf(" +-------+---------------------------+--------------------------------+\n");

    while(i < MAXOUVRIER)
    {
        if(tmp->NumRegistre != -1)
            printf(" | %05ld | %25s | %30s |\n",tmp->NumRegistre,tmp->nom,tmp->prenom);
        i++;
        tmp++;
    }

    printf(" +-------+---------------------------+--------------------------------+\n");

    printf("Introduisez l'id de l\'ouvrier voulu: ");
    choix = LireLong(1,99999);

    indice = RechercheIndexOuvrier(list,choix);

    if(indice != -1)
    {
        fp = fopen(LISTE_OUVRIER,"r+b");

        if(fp==NULL)
        {
            printf("Erreur d'ouverture du fichier: impossible de supprimer un ouvrier ! \n");
        }
        else
        {
            fseek(fp,list[indice].adresse*sizeof(Ouvrier),SEEK_SET);
            fread(&otmp,sizeof(Ouvrier),1,fp);

            system("cls");
            printf("+-------------------------------------------+\n");
            printf("|                                           |\n");
            printf("|          Supprimer d\'un ouvrier           |\n");
            printf("|                                           |\n");
            printf("+-------------------------------------------+\n\n");

            printf("+----------------------------------------------------------+\n");
            printf("| %25s %30s |\n",otmp.nom,otmp.prenom);
            printf("+---------------------+------------------------------------+\n");
            printf("| Num Registre        | %34ld |\n",otmp.NumRegistre);
            printf("| Specialite          | %34s |\n",otmp.specialite);
            printf("| Date Naissance      | %29hd-%hd-%hd |\n",otmp.d_naiss.jour,otmp.d_naiss.mois,otmp.d_naiss.annee);
            printf("| Date Engagement     | %29hd-%hd-%hd |\n",otmp.d_engag.jour,otmp.d_engag.mois,otmp.d_engag.annee);
            printf("| Rue                 | %34s |\n",otmp.rue);
            printf("| Code Postal         | %34hd |\n",otmp.CodePostal);
            printf("| Ville               | %34s |\n",otmp.ville);
            printf("+---------------------+------------------------------------+\n");

            do
            {
                printf("Etes-vous certain de le supprimer ? (1 - oui, 2 - non): ");
                choix = LireLong(1,2);
            }while(choix != 1 && choix != 2);

            if(choix == 2)
            {
                printf("Suppresion annulee !\n");
            }
            else
            {
                if(verificationUtilisation(otmp.NumRegistre) == 0 || verificationUtilisation(otmp.NumRegistre) == 2)
                {
                    otmp.NumRegistre = -1;
                    fseek(fp,list[indice].adresse*sizeof(Ouvrier),SEEK_SET);
                    fwrite(&otmp,sizeof(Ouvrier),1,fp);

                    list[indice].NumRegistre = -1;

                    printf("Suppresion effectue avec succes !\n");
                }
            }
        }
    }
    system("pause");
}

short verificationUtilisation(long val)
{
    short res = 0;
    FILE *fp = fopen(LIST_HORAIRE, "r+b");
    EstOccupe tmp;

    if(fp == NULL)
    {
        res = 2;
    }
    else
    {
        fread(&tmp,sizeof(EstOccupe), 1, fp);
        while(!feof(fp) && res != 1)
        {
            if(tmp.NumRegistre == val)
            {
                printf("Des horaires sont associes a cet ouvriers: suppresion impossible !\n");
                res = 1;
            }

            fread(&tmp,sizeof(EstOccupe), 1, fp);
        }
        fclose(fp);
    }

    return res;
}

//Relatif Affichage tous case 4
void AffichageOuvrierList(IndexOuvrier *list)
{
    short i = 0;
    IndexOuvrier *tmp = list;
    Ouvrier otmp;
    FILE *fp;
    long choix = 0;

    system("cls");
    printf("+------------------------------------------+\n");
    printf("|                                          |\n");
    printf("|          Affichage des ouvriers          |\n");
    printf("|                                          |\n");
    printf("+------------------------------------------+\n\n");

    printf(" +-------+---------------------------+--------------------------------+\n");
    printf(" |  id   |            nom            |             prenom             |\n");
    printf(" +-------+---------------------------+--------------------------------+\n");

    while(i < MAXOUVRIER)
    {
        if(tmp->NumRegistre != -1)
            printf(" | %05ld | %25s | %30s |\n",tmp->NumRegistre,tmp->nom,tmp->prenom);
        i++;
        tmp++;
    }

    printf(" +-------+---------------------------+--------------------------------+\n");

    printf("Voulez-vous des informations detaille ?\n");
    printf("Choix (1 - oui, 2 - non): ");
    choix = LireLong(1,2);

    if(choix == 1)
    {
        printf("Introduisez l'id de l\'ouvrier voulu: ");
        choix = LireLong(1,99999);

        i = RechercheIndexOuvrier(list,choix);

        if(i == -1)
            printf("Id incorrect ou jeu non trouve !\n");
        else
        {
            fp = fopen(LISTE_OUVRIER,"r+b");

            if(fp==NULL)
            {
                printf("Impossible d'afficher les details: ouverture du fichier impossible !");
            }
            else
            {
                fseek(fp,list[i].adresse*sizeof(Ouvrier),SEEK_SET);
                fread(&otmp,sizeof(Ouvrier),1,fp);

                system("cls");
                printf("+-------------------------------------------+\n");
                printf("|                                           |\n");
                printf("|          Affichage d\'un ouvrier           |\n");
                printf("|                                           |\n");
                printf("+-------------------------------------------+\n\n");

                printf("+----------------------------------------------------------+\n");
                printf("| %25s %30s |\n",otmp.nom,otmp.prenom);
                printf("+---------------------+------------------------------------+\n");
                printf("| Num Registre        | %34ld |\n",otmp.NumRegistre);
                printf("| Specialite          | %34s |\n",otmp.specialite);
                printf("| Date Naissance      | %29hd-%hd-%hd |\n",otmp.d_naiss.jour,otmp.d_naiss.mois,otmp.d_naiss.annee);
                printf("| Date Engagement     | %29hd-%hd-%hd |\n",otmp.d_engag.jour,otmp.d_engag.mois,otmp.d_engag.annee);
                printf("| Rue                 | %34s |\n",otmp.rue);
                printf("| Code Postal         | %34hd |\n",otmp.CodePostal);
                printf("| Ville               | %34s |\n",otmp.ville);
                printf("+---------------------+------------------------------------+\n");
            }

        }
    }

    printf("Retour au menu principal\n");
    system("pause");
}

//Relatif Affichage unique case 5
void AffichageOuvrierDetails(IndexOuvrier *list,IndexChantier *listChantier)
{
    short i = 0, vali = 0;
    char pch[MAXDATE];
    IndexOuvrier *tmp = list;
    EstOccupe estOccupe;
    Date date1,date2;
    FILE *fp;
    long choix = 0;


    system("cls");
    printf("+------------------------------------------------------------------+\n");
    printf("|                                                                  |\n");
    printf("|                 Affichage des horaires d un ouvrier              |\n");
    printf("|                                                                  |\n");
    printf("+------------------------------------------------------------------+\n\n");

    printf(" +-------+---------------------------+--------------------------------+\n");
    printf(" |  id   |            nom            |             prenom             |\n");
    printf(" +-------+---------------------------+--------------------------------+\n");

    while(i < MAXOUVRIER)
    {
        if(tmp->NumRegistre != -1)
            printf(" | %05ld | %25s | %30s |\n",tmp->NumRegistre,tmp->nom,tmp->prenom);
        i++;
        tmp++;
    }

    printf(" +-------+---------------------------+--------------------------------+\n");


    printf("Introduisez l'id de l\'ouvrier voulu: ");
    choix = LireLong(1,99999);

    i = RechercheIndexOuvrier(list,choix);

    if(i == -1)
        printf("Id incorrect ou ouvrier non trouve !\n");
    else
    {
        do
        {
            printf("Date de debut:");
            LireChaine(pch,MAXDATE);
            if(!LireDate(&date1, pch) || !ValideDate(&date1))
            {
                vali = 0;
                printf("Veuillez encoder une date valide\n");
            }
            else
            {
                vali = 1;
            }
        }while(!vali);

        do
        {
            printf("Date de fin:");
            LireChaine(pch,MAXDATE);
            if(!LireDate(&date2, pch) || !ValideDate(&date2)
               ||!(date2.annee > date1.annee ||(date2.annee==date1.annee &&(date2.mois > date1.mois||(date2.mois==date1.mois&& date2.jour>=date1.jour)))))
            {
                vali = 0;
                printf("Veuillez encoder une date valide et/ou superieur à la date de debut\n");
            }
            else
            {
                vali = 1;
            }
        }while(!vali);

        fp = fopen(LIST_HORAIRE, "rb");

        if(fp != NULL)
        {
            printf("Liste des chantiers: \n");
            printf(" +-------+---------------------------+\n");
            printf(" |  id   |            nom            |\n");
            printf(" +-------+---------------------------+\n");
            fread(&estOccupe,sizeof(EstOccupe), 1, fp);
            while(!feof(fp))
            {
                if(estOccupe.NumRegistre == choix && comparaisonDate(date1,estOccupe.date) <= 0 && comparaisonDate(date2,estOccupe.date) >= 0){
                    i = RechercheIndexChantier(listChantier,estOccupe.NumChantier);
                    printf(" | %05ld | %25s | \n",listChantier[i].Numchantier,listChantier[i].NomChantier);
                }
                fread(&estOccupe,sizeof(EstOccupe), 1, fp);
            }
            fclose(fp);
            printf(" +-------+---------------------------+\n");
        }
        else
        {
            printf("Echec de l'ouverture du fichier :( \n");
        }

    }

    printf("\n\nRetour au menu principal\n");
    system("pause");
}


//Fonction
int verificationPlaceIndexOuvrier(IndexOuvrier list[MAXOUVRIER])
{
    short i, trouve = 0;
    int val = 0;

    for(i = 0;i<MAXOUVRIER && trouve == 0;i++)
    {
        if(list[i].NumRegistre == -1)
        {
            trouve = 1;
            val = list[i].adresse;
        }
    }

    return val;
}
void idExistantOuvrier(IndexOuvrier list[MAXOUVRIER],long *idInterdit)
{
    short i=0;

    while(i < MAXOUVRIER)
    {
        *idInterdit = list[i].NumRegistre;
        idInterdit++;
        i++;
    }
}
short verifNumOuvrierDispo(long *idInterdit,long id)
{
    short res = 0,i = 0;

    while(i < MAXOUVRIER && *idInterdit != id)
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
short RechercheIndexOuvrier(IndexOuvrier *list,long valChercher)
{
    short i = 0,trouve=-1;

    while(i < MAXOUVRIER && trouve == -1)
    {
        if(list[i].NumRegistre == valChercher)
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
void triIndexOuvrier(IndexOuvrier *listOuvrier)
{
    int i,j;
    boolean tab_en_ordre = false;
    int taille = MAXOUVRIER;

    while(!tab_en_ordre)
    {
        tab_en_ordre = true;
        for(i = 0;i < taille-1;i++)
        {
            if(listOuvrier[i].NumRegistre != -1 && listOuvrier[i+1].NumRegistre != -1 && ((strcmp(listOuvrier[i].nom,listOuvrier[i+1].nom) == 1)|| (strcmp(listOuvrier[i].nom,listOuvrier[i+1].nom) == 0 && strcmp(listOuvrier[i].prenom,listOuvrier[i+1].prenom) == 1)))
            {
                EchangeOuvrier(&listOuvrier[i],&listOuvrier[i+1]);
                tab_en_ordre = false;
            }
        }
        taille--;
    }
}

void EchangeOuvrier(IndexOuvrier *tmp1,IndexOuvrier *tmp2)
{
    IndexOuvrier tmp;

    strcpy(tmp.nom,tmp1->nom);
    strcpy(tmp.prenom,tmp1->prenom);
    tmp.NumRegistre = tmp1->NumRegistre;
    tmp.adresse = tmp1->adresse;

    strcpy(tmp1->nom,tmp2->nom);
    strcpy(tmp1->prenom,tmp2->prenom);
    tmp1->NumRegistre = tmp2->NumRegistre;
    tmp1->adresse = tmp2->adresse;

    strcpy(tmp2->nom,tmp.nom);
    strcpy(tmp2->prenom,tmp.prenom);
    tmp2->NumRegistre = tmp.NumRegistre;
    tmp2->adresse = tmp.adresse;
}


short comparaisonDate(Date dt1,Date dt2)
{
    if(dt1.annee < dt2.annee)
        return -1;
    else if(dt1.annee > dt2.annee)
        return 1;
    else
    {
        if(dt1.mois < dt2.mois)
            return -1;
        else if(dt1.mois > dt2.mois)
            return 1;
        else
        {
            if(dt1.jour < dt2.jour)
                return -1;
            else if(dt1.jour > dt2.jour)
                return 1;
            else
                return 0;
        }
    }
}