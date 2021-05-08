#include "saisie.h"

/**
 * Input: min et max maximum de la valeur voulue
 * Process: appel et demande une valeur à l'utilisateur
 * Output: la valeur convertie
 */
long LireLong(long min,long max)
{
    long nombre = 0;
    fflush(stdin);
    scanf("%ld",&nombre);

    while(nombre < min || nombre > max)
    {
        printf("Saisiser un nombre entre %ld et %ld:",min,max);
        fflush(stdin);
        scanf("%ld",&nombre);
    }

    return nombre;
}

/**
 * Input: min et max maximum de la valeur voulue
 * Process: appel et demande une valeur à l'utilisateur
 * Output: la valeur convertie
 */
short LireShort(short min,short max)
{
    short nombre = 0;

    fflush(stdin);
    scanf("%hd",&nombre);

    while(nombre < min || nombre > max)
    {
        printf("Saisiser un nombre entre %hd et %hd:",min,max);
        fflush(stdin);
        scanf("%hd",&nombre);
    }

    return nombre;
}

/**
 * Input: min et max maximum de la valeur voulue
 * Process: appel et demande une valeur à l'utilisateur
 * Output: la valeur convertie
 */
float LireFloat(float min,float max)
{
    float nombre = 0;

    fflush(stdin);
    scanf("%f",&nombre);

    while(nombre < min || nombre > max)
    {
        printf("Saisiser un nombre entre %f et %f:",min,max);
        fflush(stdin);
        scanf("%f",&nombre);
    }

    return nombre;
}

/**
 * Input: pointeur sur chaine de caractères, longueur max
 * Process: lit et stocke une chaine de caractères à l'adresse indiqué par *pv
 * Output: -
 */
void LireChaine(char *pv, short lng)
{
    short i;

    fflush(stdin);
    char c = getchar();

    for(i = 0;c != '\n' && i < lng-1; i++, pv++)
    {
        *pv = c;

        c = getchar();
    }
    *pv = '\0';
}

/**
 * Input: pointeur sur une structure de type liste
 * Process: lit et stocke une date dans la structure pointe
 * Output: -
 */
void VerificationDate(short *PJour,short *PMois,short*PAnnee)
{
    short jour = 0,mois = 0,annee = 0,vali = 0,i=0,j=0,etat = 0;
    char date[11],tmp[5];

    while(vali == 0)
    {
        printf("Introduisez la date ('jj/mm/aaaa'):");
        LireChaine(date,MAXDATE);

        while(i < MAXDATE)
        {
            if(date[i] != '/' && date[i] != '\0')
            {
                tmp[j] = date[i];
                j++;
            }
            else
            {
                tmp[j] = '\0';
                switch(etat)
                {
                    case 0:
                        jour = (short)atoi(tmp);
                        break;

                    case 1:
                        mois = (short)atoi(tmp);
                        break;

                    case 2:
                        annee = (short)atoi(tmp);
                        break;
                }
                etat++;
                j=0;
            }
            i++;
        }

        switch(mois)
        {
            case 2:
                if((annee % 4 == 0 && annee % 100 != 0) || annee % 400 == 0)
                {
                    if(jour <= 29)
                    {
                        vali = 1;
                    }
                }
                else
                {
                    if(jour <= 28)
                    {
                        vali = 1;
                    }
                }
                break;

            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if(jour <= 31 && jour >= 1)
                {
                    vali = 1;
                }
                break;

            default:
                if (jour <= 30 && jour >= 1)
                {
                    vali = 1;
                }
                break;
        }
    }

    *PJour = jour;
    *PMois = mois;
    *PAnnee = annee;
}

/**
 * Input: pointeur sur chaine de caractères, longueur max
 * Process: lit et stocke une chaine de caractères contennant une nom propre à l'adresse indiqué par *pv
 * Output: -
 */
void LireNomPropre (char *pc, short LgMax)
{
    char c, *pTmp;
    short i, erreur=0;

    pTmp = pc;

    do
    {
        if(erreur == 1)
        {
            printf("Introduisez un nom propre valide: ");
        }

        pc = pTmp;
        i = 0;
        erreur = 0;

        fflush(stdin);
        c=getchar();

        while((i<LgMax-1)&&(c!='\n')&& erreur == 0)
        {
            if(i==0 && c==' ')
            {
                erreur=1;
            }
            else
            {
                if(isalpha(c)||c == ' '||c == '-')
                {
                    if(i != 0 && ((*(pc-1)==' '||*(pc-1)=='-') && ((*pc==' ') || (*pc=='-'))))
                    {
                        erreur = 1;
                    }
                    else
                    {
                        if(i==0 || *(pc-1)==' ' || *(pc-1)=='-')
                            *pc = toupper(c);
                        else
                            *pc = tolower(c);

                        pc++;
                        i++;
                        c=getchar();
                    }
                }
                else
                {
                    erreur = 1;
                }
            }
        }
        *pc='\0';
    }while(erreur == 1);
}

/**
 * Input: pointeur sur chaine de caractères, longueur max
 * Process: lit et vérifie le numero de tel. à l'adresse indiqué par *ch
 * Output: retourne si la valeur est valide ou pas
 */
short ValideTelephone(char *ch)
{
    short i = 0, valide, genre = 0;

    do
    {
        valide = 0;
        if(!genre)
        {
            if(i <= 3 && isalnum(*ch)) valide = 1;
            else if(i == 2 && *ch == '/')
            {
                genre = 1;
                i = 0;
                valide = 1;
            }
            else if((i == 3 || i == 4) && *ch == '/')
            {
                genre = 2;
                i = 0;
                valide = 1;
            }
        }
        else
        {
            if(genre == 1 &&((i <= 3 && isalnum(*ch)) || (i == 4 && *ch == '.') || (i >  4 && i < 7 && isalnum(*ch)) || (i == 7 && *ch == '.') || (i >  7 && i < 10 && isalnum(*ch))))
            {
                valide = 1;
            }
            else if(genre == 2 &&((i <= 2 && isalnum(*ch)) || (i == 3 && *ch == '.') || (i >  3 && i < 6 && isalnum(*ch)) || (i == 6 && *ch == '.') || (i >  6 && i < 9 && isalnum(*ch))))
            {
                valide = 1;
            }
        }

        i++;
        ch++;
    } while(*ch != '\0' && valide);

    if(!(genre == 1 && i == 10) && !(genre == 2 && i == 9))
    {
        valide = 0;
    }

    return valide;
}

/**
 * Input: pointeur sur chaine de caractères, longueur max
 * Process: lit et stocke une adresse mail à l'adresse indiqué par *pv
 * Output: -
 */
void LireEmail(char *pv, short lgMax)
{
    short i, erreur = 0, arobase, pointFinal, cpt;
    char c, *pTmp;

    pTmp = pv;

    do
    {
        if(erreur == 1)
        {
            printf("Veuillez saisir une adresse mail valide: ");
        }

        pv = pTmp;
        erreur = 0;
        arobase = 0;
        pointFinal = 0;
        cpt = 0;

        fflush(stdin);

        c = getchar();

        for(i=0; i <= lgMax-1 && c !='\n' && erreur == 0; i++, pv++)
        {
            if(i == 0 && isalpha(c))//1er caractères
            {
                *pv = c;
            }
            else if((isalpha(c)|| isdigit(c) || c == '.' || c == '-' || c == '@') && arobase == 0)//jusqu'a @
            {
                if(c == '@')
                {
                    arobase = 1;
                }
                if(*(pv-1) == '.' && c == '.')
                {
                    erreur = 1;
                }
                *pv = c;
            }
            else if((isalpha(c)|| isdigit(c) || c == '-' || c == '.') && pointFinal == 0)//entre @ et .
            {
                if(c == '.')
                {
                    pointFinal = 1;
                }
                *pv = c;
            }
            else if(isalpha(c) && cpt <= 4 && pointFinal == 1 )//Terminaison dns
            {
                cpt++;
                *pv = c;
            }
            else
            {
                erreur = 1;
            }
            c = getchar();
        }

        if(cpt <= 1)
        {
            erreur = 1;
        }

        *pv = '\0';

    }while(erreur == 1);
}

short LireDate(struct _date *pdate,char *ch)
{
    short i = 0, valide = 0;
    char *ch_tmp = ch;

    do
    {
        if(isdigit(*ch) && (i < 2 || (i > 2 && i < 5) || i > 5)) valide = 1;
        else if((i == 2 || i == 5) && *ch == '/')
            valide = 1;

        ch++;
        i++;
    } while(*ch != '\0' && valide);

    if(valide)
    {
        valide = 0;
        ch = ch_tmp;
        pdate->jour = (short)(*ch-'0')*10 +(short)(*(ch+1)-'0');

        ch += 3;
        pdate->mois = (short)(*ch-'0')*10
                      +(short)(*(ch+1)-'0');

        ch += 3;
        if(i == 8)
        {
            valide = 1;
            pdate->annee = (short)(*ch-'0')*10
                           +(short)(*(ch+1)-'0');
        }
        else if(i == 10)
        {
            valide = 1;
            pdate->annee = (short)(*ch-'0')*1000
                           +(short)(*(ch+1)-'0')*100
                           +(short)(*(ch+2)-'0')*10
                           +(short)(*(ch+3)-'0');
        }
    }

    return valide;
}

short ValideDate(Date *date)
{
    short valide = 0;
    short annee = date->annee;
    short mois  = date->mois;
    short jour  = date->jour;

    if(annee >= 0 && annee<=2017 && mois <= 12 && mois >= 1 && jour > 0){
        switch (mois)
        {
            case 2:
                if((((annee % 4 == 0 && annee % 100 != 0) || annee % 400 == 0) && jour <= 29) || jour <= 28)
                    valide = 1;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                if(jour <= 30)
                    valide = 1;
                break;
            default:
                if(jour <= 31)
                    valide = 1;
        }
    }
    return valide;
}
