#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



struct TreeNode
{
    char avain[25];
    int arvo;
    struct TreeNode *leftPtr, *rightPtr;
};


typedef struct TreeNode treeNode;
typedef treeNode * treeNodePtr;

void insertNode(treeNodePtr * treePtr, char sana[]);
void sortHigh(treeNodePtr treePtr);

int main()
{
    char tekstitiedosto[25];
    char sana[20];
    int c;
    treeNodePtr rootPtr = NULL;
    treeNodePtr sortedPtr = NULL;

    printf("Anna tekstitiedoston nimi (Esim. text123.txt)\n");
    scanf("%s", tekstitiedosto);

    FILE * tiedosto;
    tiedosto = fopen(tekstitiedosto, "r");

    do{
    c = fscanf(tiedosto, "%s", sana);
    if (c != EOF){
        removeNumbers(sana);
        cleanWord(sana);
        insertNode(&rootPtr, sana);
    }
    }while (c != EOF);
    fclose(tiedosto);

    sortHigh(rootPtr);
    printf("\n%d\n",find_max(rootPtr));

    return 0;
}


void insertNode(treeNodePtr * treePtr, char sana[25])
{
    treeNode * temp = NULL;

    if(*treePtr == NULL){
        temp = (treeNode *)malloc(sizeof(treeNode));
        temp->leftPtr = NULL;
        temp->rightPtr = NULL;
        strcpy(temp->avain,sana);
        temp->arvo=0;
        *treePtr = temp;
    }
    else if (strcmp(sana, (*treePtr)->avain) < 0)
        insertNode(&((*treePtr)->leftPtr), sana);
    else if (strcmp(sana, (*treePtr)->avain) > 0)
        insertNode(&((*treePtr)->rightPtr), sana);
    else
        (*treePtr)->arvo+=1;
}

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

void cleanWord(char *sana)
{
    char a;
    int i=0, j=0;

    while((a = sana[i++]) != '\0'){
        if(isalnum(a)){
            sana[j++] = tolower(a);
        }
    }
    sana[j]='\0';
}

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
        *dest++ = *src++;
    }
    *dest = '\0';

}

int find_max(treeNodePtr treePtr) {
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

void maxHeapify()
{

}
