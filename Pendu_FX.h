//
//  Pendu_FX.h
//  Pendu
//
//  Created by Nicolas Fordoxcel on 27/10/2022.
//

#ifndef Pendu_FX_h
#define Pendu_FX_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <curses.h>

void MenuPendu(void);
void TraitementMenu(int);
void JeuSolo(void);
void JeuDuo(void);
void AjouterDico(void);
void AfficherScore(void);
int lire(char *chaine, int longueur);
void EntrerMotDeviner(char *pMotDeviner);
void CacherMot(char *pMot, int nbLettres);
void Jouer(char *pMotCache, char *pMotDevine, int nbLettres);
bool VerifierLettre(char *pmot, char *pmotDeviner, char lettre, int nbLettre);
char LireCaractere(void);
int CalculScore(int nbCoupRestant, int nbLettres);
void OuvrirFichier(char modeLecture);
#endif /* Pendu_FX_h */
