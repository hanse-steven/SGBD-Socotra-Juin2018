#ifndef SOCOTRA_HORAIRE_H
#define SOCOTRA_HORAIRE_H

#include "struct.h"
#include "Chantier.h"
#include "Ouvrier.h"

void ajoutHoraire(IndexChantier *listChantier,IndexOuvrier *listOuvrier);
void ecrirePartieFichiers(EstOccupe *tab);
short verificationUnicite(EstOccupe *tab);

void affichageHoraires();

#endif
