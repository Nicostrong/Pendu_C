//
//  Pendu_FX.c
//  Pendu
//
//  Created by Nicolas Fordoxcel on 27/10/2022.
//

#define NBCOUP      10
//#define FICHIER     "User//nicolasfordoxcel//c//Pendu//Pendu//Dico//Dico2.txt"
//#define FICHIER "Dico//Dico.txt"
#include "Pendu_FX.h"

void MenuPendu(void)
{
    int choix = 0;
    
    printf("Pour jouer en Solo tapez 1\n\
Pour jouer à Deux tapez 2\n\
Pour entrer des nouveaux mots dans le dictionnaire tapez 3\n\
Pour voir les meilleurs score tapez 4\n\
Pour quitter tapez 0\n");
    scanf("%d", &choix);
    fgetc(stdin);
    TraitementMenu(choix);
}

void TraitementMenu(int choix)
{
    switch (choix)
    {
        case 0:
            _Exit(0);
            break;
        case 1:
            JeuSolo();
            break;
        case 2:
            JeuDuo();
            break;
        case 3:
            AjouterDico();
            break;
        case 4:
            AfficherScore();
            break;
        default:
            MenuPendu();
            break;
    }
}

void JeuSolo(void)
{
    printf("Vous jouez en SOLO\n");
    OuvrirFichier("r");
    
}

void JeuDuo(void)
{
    unsigned short nbLettres = 0;
    char motDeviner[26] = {""};
    void *pMotDevine = &motDeviner;
    
    printf("Vous jouez en DUO\n");
    
    EntrerMotDeviner(pMotDevine);
   
    nbLettres = strlen(motDeviner);
    char *pMotCache = malloc(sizeof(char) * nbLettres);
    
    if(pMotCache == NULL)
    {
        printf("Erreur d'allocution pour pointeur MotCache.\n");
        EXIT_FAILURE;
    }
    else
    {
        CacherMot(pMotCache, nbLettres);
    }
    
    Jouer(pMotCache, pMotDevine, nbLettres);
    
    free(pMotCache);
}

void AjouterDico(void)
{
    printf("Vous ajoutez un mot au dico\n");
}

void AfficherScore(void)
{
    printf("Voiçi la liste des meilleur scores\n");
}

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;
    
    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        return 1;
    }
    else
    {
        return 0;
    }
}


void EntrerMotDeviner(char *pMotDeviner)
{
    printf("Joueur 1, Entrez le mot à deviner :\n");
    if (!lire(pMotDeviner, 26))
        printf("ERREUR de lecture du mot à deviner");
}

void CacherMot(char *p, int nbLettres)
{
    for(int i = 0; i<nbLettres; i++)
    {
        p[i] = '*';
    }
}

char LireCaractere(void)
{
    char caractere = 0;
    caractere = getchar();
    caractere = toupper(caractere);
    while(getchar() != '\n');
    return caractere;
}

bool VerifierLettre(char *pmot, char *pmotdev, char lettre, int nbChar)
{
    bool ret = false;
    for(int i = 0; i < nbChar; i++)
    {
        if(toupper(pmotdev[i]) == lettre)
        {
            pmot[i] = lettre;
            ret = true;
        }
    }
    return ret;
}

void Jouer(char *pMotCache, char *pMotDevine, int nbLettres)
{
    int nbCoup = NBCOUP;
    int score = 0;
    int i = 0;
    char LettrePropose[26] = {};
    while (nbCoup != 0)
    {
        printf("Le mot mystère comporte %d lettres.\n", nbLettres);
        printf("le mot a trouver  est :\t\t %s\n", pMotCache);
        printf("Lettres déjà proposées : %s \n", LettrePropose);
        printf("Il vous reste encore %d coups avant d'être pendu !!!\n", nbCoup);
        
        printf("proposez une lettre : \n");
        
        char lettre = LireCaractere();
        LettrePropose[i] = lettre;
        i++;
        LettrePropose[i] = '-';
        i++;
        
        if (!VerifierLettre(pMotCache, pMotDevine, lettre, nbLettres))
        {
            nbCoup --;
            
        }
        if(strchr(pMotCache, '*') == NULL)
        {
            printf("Félicitation vous avez trouvé le mot mystère qui était\t\"%s\"\n\n\n", pMotDevine);
            score = CalculScore(nbCoup, nbLettres);
            printf("Votre score est de %d points.", score);
            fgetc(stdin);
            MenuPendu();
        }
        if(nbCoup == 0)
        {
            printf("Désolé, vous avez perdu. Le mot a trouver était\t\"%s\"\n\n\n",pMotDevine);
            printf("Votre score est de %d point.", score);
            fgetc(stdin);
            MenuPendu();
        }
    }
}

int CalculScore(int nbCoupRestant, int nbLettres)
{
    return nbCoupRestant * nbLettres;
}

void OuvrirFichier(char modeLecture)
{
    FILE *fichier = NULL;
    char fichierLire = "Users//nicolasfordoxcel//c/Pendu/Pendu/Dico.txt";
    fichier = fopen(fichierLire, "a+");
    if (fichier != NULL)
    {
        printf("Lecture du dico.\n");
        fclose(fichier);
    }
    else
    {
        printf("ERREUR de la lecture du fichier.\n");
    }
}
