#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


// Luodaan oma tietotyyppi, jota käytetään taulukkona top 100 sanojen laatimiseen
struct arrayNode
{
    char avain[200];
    int arvo;
};

struct arrayNode top100[100]= {{0}};

// Luodaan puun solmu
struct TreeNode
{
    char avain[200];
    int arvo;
    struct TreeNode *leftPtr, *rightPtr, *parent;
};

typedef struct TreeNode treeNode;
typedef treeNode * treeNodePtr;

void insertNode(treeNodePtr * treePtr, char sana[]);
void sortHigh(treeNodePtr treePtr);

// Funktio, jolla lisätään avain puuhun
void insertNode(treeNodePtr * treePtr, char sana[200])
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

// Funktio, joka etsii minimi arvon oman tietotyypin arrayNode taulukosta
int findMinimum(struct arrayNode arr[100])
{
    int i, minimum=arr[0].arvo, taulukonKohta=0;

    for(i=0; i < 100; i++){
        if(arr[i].arvo<minimum){
            taulukonKohta = i;
            minimum = arr[i].arvo;
        }
    }

    return taulukonKohta;
}

// Funktio, joka etsii paikan arrayNode tyypin taulukkoon
void findPlace2(struct arrayNode keyNode)
{
    int i=0, j;
    while(top100[i].arvo != NULL)
        i++;
    if(i<100){
        top100[i].arvo = keyNode.arvo;
        strcpy(top100[i].avain, keyNode.avain);
    }
    else if(i>=100) {
        j = findMinimum(top100);
        if(top100[j].arvo < keyNode.arvo){
            top100[j].arvo = keyNode.arvo;
            strcpy(top100[j].avain, keyNode.avain);
        }
    }
}



// Käydään läpi kaikki puun avaimet, sekä etsitään avaimille paikka top 100 sanojen taulukkoon
void sortHigh(treeNodePtr treePtr)
{
    if (treePtr != NULL )
  {
        sortHigh(treePtr->rightPtr);
        //printf("%s ", treePtr->avain);
        //printf("%d\n", treePtr->arvo);
        sortHigh(treePtr->leftPtr);
        //findPlace(treePtr->arvo, treePtr->avain);
        struct arrayNode node;
        if(strcmp(treePtr->avain, "") != 0){
            node.arvo = treePtr->arvo;
            strcpy(node.avain, treePtr->avain);
            findPlace2(node);
        }
  }
}

// Poistetaan non-alphabetical merkit, kuten esimerkiksi (,"%
void cleanWord(char *sana)
{
    char a;
    int i=0, j=0;

    while((a = sana[i++]) != '\0'){             // Kun sanaa on jäljellä vielä, niin algoritmi toimii
        if(isalnum(a)){                         // Jos merkki on kirjain, niin laitetaan se lowercaseksi, ja kopioidaan sanaan.
            sana[j++] = toupper(a);
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

// Funktio, jolla qsort vertailee arvoja, jonka avulla se voi järjestää ne
int compare(const void * a, const void * b)
{
    int aTulos = ((struct arrayNode *)a)->arvo;
    int bTulos = ((struct arrayNode *)b)->arvo;
    int tulos = bTulos - aTulos;

    return tulos;
}

// Main
int main()
{
    char tekstitiedosto[25];
    char sana[200];
    int c,i=0;
    treeNodePtr rootPtr = NULL;

    printf("Anna tekstitiedoston nimi (Esim. text123.txt)\n");
    scanf("%s", tekstitiedosto);

    FILE * tiedosto;                                // Avataan annettu tiedosto, syötteen perusteella
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

    qsort(top100, 100, sizeof(struct arrayNode), compare );

    printf("\nThe 100 most common words:\nWORD NUMBER OF OCCURENCES");
    i=0;
    while(i<100){
        printf("\n");
        printf("%s ",top100[i].avain);
        printf("%d", top100[i].arvo);
        i++;
    }

    return 0;
}


// Tästä alaspäin on turhat funktiot, joiden avulla yritin kehitellä eri ratkaisuja

/*void findPlace(int x, char *y)
{
    int i=0;
    while(top100sanat[i][0] != NULL)
        i++;
    if(i<100){
        strcpy(top100sanat[i], y);
        top100arvot[i]= x;
    }
    printf("\nWrote ");
    printf("%s", top100sanat[i]);
    printf(" to table!\n");
}
*//*
int findValueByKey(treeNodePtr treePtr, char etsittava[200])
{
    treeNodePtr y = treePtr;
    int palautusArvo=0;

    while(y != NULL && strcmp(etsittava, y->avain) != 0)
    {
        if(strcmp( y->avain, etsittava) == 0){
            //printf("\n Found Match! \n");
            palautusArvo = y->arvo;
            return palautusArvo;
        }
        if(strcmp(etsittava, y->avain) < 0)
            y = y->leftPtr;
        else if(strcmp(etsittava, y->avain) > 0)
            y = y->rightPtr;
    }

    return 0;

}
*/
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

/*
char traverseTree(treeNodePtr treePtr)
{
    if(treePtr != NULL)
    {
        traverseTree(treePtr->rightPtr);
        traverseTree(treePtr->leftPtr);
    }
    return treePtr;
}
*/


