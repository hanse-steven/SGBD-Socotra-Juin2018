#include "struct.h" //contient les structures
#include "init.h" // contient les initialisations & define
#include "ouvrier.h" //contient les fonctions des ouvriers
#include "chantier.h" //contient les fonctions des chantiers
#include "horaire.h" //Contient les fonctions des heures presté pour la struct EstOccupe

int main() {
    IndexChantier listChantier[MAXCHANTIER];
    IndexOuvrier listOuvrier[MAXOUVRIER];
    int choix = 10;

    initialisationChantier(listChantier);
    initialisationOuvrier(listOuvrier);
    triIndexOuvrier(listOuvrier);
    triIndexChantier(listChantier);

    while(choix)
    {
        system("cls");
        puts("\t0. Quitter");
        puts("Gestion des Ouvriers **********************************************************************");
        puts("\t1. Ajout d'un ouvrier");
        puts("\t2. Modifier un ouvrier");
        puts("\t3. Supprimer un ouvrier");
        puts("\t4. Lister les ouvriers");
        puts("\t5. Affichage horaire d'un ouvrier");
        puts("Gestion des chantiers *********************************************************************");
        puts("\t6. Ajouter un chantier");
        puts("\t7. Afficher le(s) chantier(s)");
        puts("\t8. Afficher le(s) ouvriers(s) ayant travailler sur un chantier specifique");
        puts("Gestion horaire ouvrier *******************************************************************");
        puts("\t9. Ajouter une prestation");
        puts("\t10. Affichage des prestations");
        puts("Choix: ");
        scanf("%d",&choix);

        switch (choix)
        {
            case 0:
                puts("Fin du programme !");
                break;

            case 1:
                AjoutOuvrier(listOuvrier);
                triIndexOuvrier(listOuvrier);
                break;

            case 2:
                ModifierOuvrier(listOuvrier);
                triIndexOuvrier(listOuvrier);
                break;

            case 3:
                SuppresionOuvrier(listOuvrier);
                triIndexOuvrier(listOuvrier);
                break;

            case 4:
                AffichageOuvrierList(listOuvrier);
                break;

            case 5:
                AffichageOuvrierDetails(listOuvrier,listChantier);
                break;

            case 6:
                AjoutChantier(listChantier);
                triIndexChantier(listChantier);
                break;

            case 7:
                AffichageChantierList(listChantier);
                break;

            case 8:
                affichageOuvrierPourChantier(listChantier,listOuvrier);
                break;

            case 9:
                ajoutHoraire(listChantier,listOuvrier);
                break;

            case 10:
                affichageHoraires();
                break;

            default:
                puts("Valeur inconnue");
        }
    }
    return 0;
}
