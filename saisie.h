#ifndef SOCOTRA_SAISIE_H
#define SOCOTRA_SAISIE_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "struct.h"

#define MAXDATE 11

short LireShort(short min,short max);
long LireLong(long min,long max);
float LireFloat(float min,float max);
void LireChaine(char *pv, short lng);
void VerificationDate(short *PJour,short *PMois,short*PAnnee);
void LireNomPropre (char *pc, short LgMax);
short ValideTelephone(char *ch);
void LireEmail(char *pv, short lgMax);

short LireDate(struct _date *pdate,char *ch);
short ValideDate(struct _date *date);

#endif
