#ifndef SOCOTRA_OUVRIER_H
#define SOCOTRA_OUVRIER_H

#include "struct.h"
#include "Chantier.h"

//Ajout d'ouvrier
void AjoutOuvrier(IndexOuvrier *list);

//Modifier ouvrier
void ModifierOuvrier(IndexOuvrier *list);

//supprimer ouvrier
void SuppresionOuvrier(IndexOuvrier *list);

//Affichage ouvrier
void AffichageOuvrierList(IndexOuvrier *list);
void AffichageOuvrierDetails(IndexOuvrier *list,IndexChantier *listChantier);

//Fonction
int verificationPlaceIndexOuvrier(IndexOuvrier *list);
void idExistantOuvrier(IndexOuvrier *list,long *idInterdit);
short verifNumOuvrierDispo(long *idInterdit,long id);
short RechercheIndexOuvrier(IndexOuvrier *list,long valChercher);
short verificationUtilisation(long val);
short comparaisonDate(Date dt1,Date dt2);
void triIndexOuvrier(IndexOuvrier *listOuvrier);
void EchangeOuvrier(IndexOuvrier *tmp1,IndexOuvrier *tmp2);

#endif
