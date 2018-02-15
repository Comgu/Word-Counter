#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


// Luodaan puun solmu
struct TreeNode
{
    char avain[25];
    int arvo;
    struct TreeNode *leftPtr, *rightPtr, *parent;
};

typedef struct TreeNode treeNode;
typedef treeNode * treeNodePtr;

void insertNode(treeNodePtr * treePtr, char sana[]);
void sortHigh(treeNodePtr treePtr);



// Lisätään avain puuhun
void insertNode(treeNodePtr * treePtr, char sana[25])
{
    treeNode * temp = NULL;

    if(*treePtr == NULL){               // Uusi solmu
        temp = (treeNode *)malloc(sizeof(treeNode));
        temp->leftPtr = NULL;
        temp->rightPtr = NULL;
        temp->parent = *treePtr;
        strcpy(temp->avain,sana);
        temp->arvo=1;
        *treePtr = temp;
    }
    else if (strcmp(sana, (*treePtr)->avain) < 0)   // Etsitään paikka aakkosten mukaan
        insertNode(&((*treePtr)->leftPtr), sana);
    else if (strcmp(sana, (*treePtr)->avain) > 0)
        insertNode(&((*treePtr)->rightPtr), sana);
    else                                            // Jos avain löytyi jo, niin lisätään määrään yksi
        (*treePtr)->arvo+=1;
}

void transplantNode(treeNodePtr * treePtr, treeNode node1, treeNode node2)
{
}
// Käydään läpi kaikki puun avaimet ja tulostetaan järjestetyksessä
void sortHigh(treeNodePtr treePtr)
{
  if (treePtr != NULL )
  {
    sortHigh(treePtr->rightPtr);
    printf("%s ", treePtr->avain);
    printf("%d\n", treePtr->arvo);
    sortHigh(treePtr->leftPtr);
  }
}
// Poistetaan non-alphabetical merkit, kuten esimerkiksi (,"%
void cleanWord(char *sana)
{
    char a;
    int i=0, j=0;

    while((a = sana[i++]) != '\0'){             // Kun sanaa on jäljellä vielä, niin algoritmi toimii
        if(isalnum(a)){                         // Jos merkki on kirjain, niin laitetaan se lowercaseksi, ja kopioidaan sanaan.
            sana[j++] = tolower(a);
        }
    }
    sana[j]='\0';                               // Päätetään sana kohtaan j
}
// Poistetaan numerot kaikista sanoista
void removeNumbers(char* sana)
{
    char* dest = sana;
    char* src = sana;

    while(*src)
    {
        if (isdigit(*src)){
            src++;
            continue;
        }
        *dest++ = *src++;           // Kopioidaan numerot ja myöhemmin poistetaan ne päättämällä sana aikaisemmin
    }
    *dest = '\0';

}

// Main
int main()
{
    char tekstitiedosto[25];
    char sana[20];
    int c;
    treeNodePtr rootPtr = NULL;

    printf("Anna tekstitiedoston nimi (Esim. text123.txt)\n");
    scanf("%s", tekstitiedosto);

    FILE * tiedosto;
    tiedosto = fopen(tekstitiedosto, "r");

    do{
    c = fscanf(tiedosto, "%s", sana);
    if (c != EOF){                                      // Otetaan sanoja siihen asti, kunnes tiedosto päättyy
        removeNumbers(sana);
        cleanWord(sana);
        insertNode(&rootPtr, sana);
    }
    }while (c != EOF);
    fclose(tiedosto);

    sortHigh(rootPtr);

    return 0;
}
/* Maksimin etsiminen KESKEN
int find_max(treeNodePtr treePtr)
{
    int max = treePtr->arvo;
    treeNode * temp = treePtr;


    if (treePtr == NULL) {
        return 0;
    }
    while (treePtr->rightPtr != NULL) {
        treePtr = treePtr->rightPtr;
        if(treePtr->arvo > max)
            max = treePtr->arvo;
    }
    treePtr = temp;
    while (treePtr->leftPtr != NULL) {
        treePtr = treePtr->leftPtr;
        if(treePtr->arvo > max)
            max = treePtr->arvo;
    }

    return max;
}
*/
