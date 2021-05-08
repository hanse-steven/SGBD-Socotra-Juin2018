#ifndef SOCOTRA_CHANTIER_H
#define SOCOTRA_CHANTIER_H

#include "struct.h"
#include "ouvrier.h"

//Ajout Chantier
void AjoutChantier(IndexChantier *list);

//Affiche tous
void AffichageChantierList(IndexChantier *list);

//Affichage pour un chantier données
void affichageOuvrierPourChantier(IndexChantier *listChantier,IndexOuvrier *listOuvrier);

//Fonction
int verificationPlaceIndexChantier(IndexChantier *list);
void idExistantChantier(IndexChantier *list,long *idInterdit);
short verifNumChantierDispo(long *idInterdit,long id);
short RechercheIndexChantier(IndexChantier *list,long valChercher);
void triIndexChantier(IndexChantier *listChantier);
void EchangeChantier(IndexChantier *tmp1,IndexChantier *tmp2);

#endif
