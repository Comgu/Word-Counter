#include "string.h"
#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
    char avain[25];
    int arvo;
    struct TreeNode *leftPtr, *rightPtr;
};

typedef struct TreeNode treeNode;
typedef treeNode * treeNodePtr;

int numero = 1;
void insertNode(treeNodePtr * treePtr, char sana[]);
void alphabetic(treeNodePtr treePtr);

void insertNode(treeNodePtr * treePtr, char sana[25])
{
    treeNode * tempsana = NULL;

    if(*treePtr == NULL){
        tempsana = (treeNode *)malloc(sizeof(treeNode));
        tempsana->leftPtr = NULL;
        tempsana->rightPtr = NULL;
        strcpy(tempsana->avain,sana);
        *treePtr = tempsana;
    }
    else if (strcmp(sana, (*treePtr)->avain) < 0)
        insertNode(&((*treePtr)->leftPtr), sana);
    else if (strcmp(sana, (*treePtr)->avain) > 0)
        insertNode(&((*treePtr)->rightPtr), sana);


}

void alphabetic(treeNodePtr treePtr)
{
  if (treePtr != NULL ){
    alphabetic(treePtr->leftPtr);
    printf("%s\n", treePtr->avain);
    alphabetic(treePtr->rightPtr);
  }
}

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
        if (c != EOF)
            insertNode(&rootPtr, sana);
    }while (c != EOF);

  fclose(tiedosto);
  printf("%s", rootPtr->rightPtr->leftPtr->avain);


    return 0;
}
