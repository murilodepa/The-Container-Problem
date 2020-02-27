/* DESCRIPTION: THE CONTAINER PROBLEM.

            PONTIFICAL CATHOLIC UNIVERSITY OF CAMPINAS - PUCC
            STUDENT NAME: MURILO DE PAULA ARAUJO
            RA: 17747775
            TEACHER: GILBERTO SHIGUEO NAKAMITI
            COURSE: COMPUTER ENGINEERING     PERIOD: 4º SEMESTER
            SUBJECT: DATA STRUCTURES B

             (OPTIONAL WORK) - FINAL WORK - "THE CONTAINER PROBLEM"
*/
//################################### LIBRARY ###################################
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

using namespace std;
//###############################################################################

//################################### DEFINE'S ##################################
#define blue 1
#define green 10
#define red 4
#define white 15
//###############################################################################

//###############################################################################

/// DECLARING STRUCT GOODS WITH YOURS FIELDS
typedef struct
{
    char code        [200];
    char description [200];
    int  value;
    int  weight;
} merchandise;
//###############################################################################

/// DECLARING AND INCLUDING QUEUE LIBRARY
typedef merchandise queueElement;
#include "queue.h"
//###############################################################################

//#################### PROTOTYPE OF FUNCTIONS USED IN MAIN ######################
/// CHANGES COLOR OF PRINTED CHARACTERS
void chooseColor (int );

/// GO TO POSITION (LINES AND COLUMNS)
void Goto_xy (int , int );

/// VALIDATE FILE AND RETURN ONLY READ FILE
FILE * validatingTheFile ();

/// EXIT THE PROGRAM! EXCEEDED THE NUMBER OF ITEMS OR WEIGHT ALLOWED
void exceedingLimit ();

/// PRINT NO PRODUCTS IN FILE
void printWithoutProducts ();

/// PRINT THE CONTAINER DOES NOT SUPPORT ANY PRODUCTS
void printHeavierProducts ();

/// PRINT ERROR! CODE WITH MORE THAN 5 DIGITS!
void errorInCode ();

/// PRINT ERROR! DESCRIPTION WITH MORE THAN 20 DIGITS!
void errorInDescription ();

/// READ FILE PRODUCTS AND STORE IN STRUCT GOODS
void readFileProducts (merchandise **, int * , int * );

/// ANALYZE THE PRODUCTS THAT WILL BE IMPORTED
Queue analyzeTheProducts (merchandise * , int , int , int * );

/// PRINT THE CONTENTS OF THE QUEUE
void printQueueOfProducts (Queue );

/// RETURN THE RESULT OF THE TOTAL VALUE
int totalValue (Queue );

/// RETURN THE RESULT OF THE TOTAL WEIGHT
int totalWeight (Queue );

/// PRINT THE TOTAL VALUE AND WEIGHT
void printValueAndWeight (Queue, int );

/// CLEANING THE FIELDS OF THE STRUCT
void clearStruct (merchandise **, int * , int * );
//###############################################################################

//#################################### MAIN #####################################
int main()
{
    merchandise *products;
    Queue queueOfProducts;
    int quantityOfProducts, maximumWeight, quantityOfProductImported;

    readFileProducts (&products, &quantityOfProducts, &maximumWeight);
    initQueue (queueOfProducts);
    queueOfProducts = analyzeTheProducts (products, quantityOfProducts, maximumWeight, &quantityOfProductImported);
    printQueueOfProducts (queueOfProducts);
    printValueAndWeight (queueOfProducts, quantityOfProductImported);

    clearStruct (&products, &quantityOfProducts, &maximumWeight);

    // Print file in string format /
    cout << endl << " " << quantityOfProducts << " - " << maximumWeight;

    for (int cont1 = 0; cont1 < quantityOfProducts; cont1++)
    {
        cout << endl << endl << " CODE: " << products[cont1].code;
        cout << endl << " DESCRIPTION: "  << products[cont1].description;
        cout << endl << " VALUE: "        << products[cont1].value;
        cout << endl << " WEIGHT: "       << products[cont1].weight << endl << endl;
    }

    return 0;
}
//###############################################################################

/// CHANGES COLOR OF PRINTED CHARACTERS
void chooseColor (int color)
{
    /*
    0 = Black		 8  = Grey
    1 = Blue		 9  = Light Blue
    2 = Green		 10 = Light Green
    3 = Green-Water	 11 = Light Green-Water
    4 = Red      	 12 = Light Red
    5 = Purple		 13 = Lilac
    6 = Yellow		 14 = Light Yellow
    7 = White		 15 = Bright White
    */
    HANDLE output;
    output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(output,color);
}
//###############################################################################

//FUNÇÃO PARA REFERENCIAR LINHAS E COLUNAS PARA IMPRESSÃO
void Goto_xy(int row, int column)
{
    HANDLE Saida;

    COORD Posicao;

    Saida = GetStdHandle(STD_OUTPUT_HANDLE);

    Posicao.X = column;
    Posicao.Y = row;

    SetConsoleCursorPosition(Saida, Posicao);
}
//###############################################################################

/// VALIDATE FILE AND RETURN ONLY READ FILE
FILE * validatingTheFile ()
{
    FILE *inputFile;
    int cont;
    char fileName[100];

    chooseColor(green);
    cout << " ENTER FILE NAME: ";
    chooseColor(white);
    cin >> fileName;

    strcat(fileName, ".txt");

    // Opening file to read the data
    inputFile = fopen(fileName, "r");

    if(inputFile == NULL)
    {
        do
        {
            system("cls");

            chooseColor(blue);
            cout << endl << "   \332";

            for(cont = 0; cont < 8; cont++)
                cout << "\304\304\304\304\304\304";

            cout << "\277 " << endl << "   \263";

            chooseColor(red);
            cout << "\t     ERROR!!! IN OPENING THE FILE!!!";

            chooseColor(blue);
            cout << "\t    \263 \n   \300";

            for(cont = 0; cont < 8; cont++)
                cout << "\304\304\304\304\304\304";

            cout << "\331 \n\n";

            chooseColor(green);
            cout << " ENTER FILE NAME AGAIN: ";
            chooseColor(white);
            cin >> fileName;

            strcat(fileName, ".txt");

            // Opening file to read the data
            inputFile = fopen(fileName, "r");
            // exit(1);
        }
        while (inputFile == NULL);
    }

    system("cls");
    return inputFile;
}
//###############################################################################

/// EXIT THE PROGRAM! EXCEEDED THE NUMBER OF ITEMS OR WEIGHT ALLOWED
void exceedingLimit ()
{
    int cont;

    system("cls");

    chooseColor(blue);
    cout << endl << "   \332";

    for (cont = 0; cont < 8; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\277 " << endl << "   \263";

    chooseColor(red);
    cout << "  EXCEEDED 100 ITEMS OR THE WEIGHT (1000000g)!";

    chooseColor(blue);
    cout << "  \263 \n   \300";

    for (cont = 0; cont < 8; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\331 "<< endl << endl << endl;

    chooseColor(white);
    exit(1);
}
//###############################################################################

/// PRINT NO PRODUCTS IN FILE
void printWithoutProducts()
{
    int cont;

    system("cls");

    chooseColor(blue);
    cout << endl << "   \332";

    for (cont = 0; cont < 8; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\277 " << endl << "   \263";

    chooseColor(red);
    cout << "\t\t NO PRODUCTS IN FILE!!!";

    chooseColor(blue);
    cout << "\t\t    \263 \n   \300";

    for (cont = 0; cont < 8; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\331 "<< endl << endl << endl;

    chooseColor(white);
    exit(1);
}
//###############################################################################

/// PRINT THE CONTAINER DOES NOT SUPPORT ANY PRODUCTS
void printHeavierProducts()
{
    int cont;

    system("cls");

    chooseColor(blue);
    cout << endl << "   \332";

    for (cont = 0; cont < 8; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\277 " << endl << "   \263";

    chooseColor(red);
    cout << "   THE CONTAINER DOESN'T SUPPORT ANY PRODUCTS";

    chooseColor(blue);
    cout << "   \263 \n   \300";

    for (cont = 0; cont < 8; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\331 "<< endl << endl << endl;

    chooseColor(white);
    exit(1);
}
//###############################################################################

/// PRINT ERROR! CODE WITH MORE THAN 5 DIGITS!
void errorInCode()
{
    int cont;

    system("cls");

    chooseColor(blue);
    cout << endl << "   \332";

    for (cont = 0; cont < 8; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\277 " << endl << "   \263";

    chooseColor(red);
    cout << "      ERROR! CODE WITH MORE THAN 5 DIGITS!";

    chooseColor(blue);
    cout << "      \263 \n   \300";

    for (cont = 0; cont < 8; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\331 "<< endl << endl << endl;

    chooseColor(white);
    exit(1);
}
//###############################################################################

/// PRINT ERROR! DESCRIPTION WITH MORE THAN 20 DIGITS!
void errorInDescription()
{
    int cont;

    system("cls");

    chooseColor(blue);
    cout << endl << "   \332";

    for (cont = 0; cont < 8; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\277 " << endl << "   \263";

    chooseColor(red);
    cout << "  ERROR! DESCRIPTION WITH MORE THAN 20 DIGITS!";

    chooseColor(blue);
    cout << "  \263 \n   \300";

    for (cont = 0; cont < 8; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\331 "<< endl << endl << endl;

    chooseColor(white);
    exit(1);
}
//###############################################################################

/// READ FILE PRODUCTS AND STORE IN STRUCT GOODS
void readFileProducts (merchandise ** products, int * quantityOfProducts, int * maximumWeight)
{
    int cont1 = 0, cont2 = 0;
    char character;
    bool structProductsEmpty = true;

    FILE *inputFile; /* Defining a file type variable */

    inputFile = validatingTheFile();

    /* Reading of the quantity of products and maximum weight */
    fscanf(inputFile,"%d %d", quantityOfProducts, maximumWeight);

    if ((*quantityOfProducts) == 0)
        printWithoutProducts();

    character = fgetc(inputFile);

    while (character == ' ' || character == ',' || character == '\n')
        character = fgetc(inputFile);

    if ((*quantityOfProducts) <= 100 && (*maximumWeight) <= 1000000)
    {
        *products = (merchandise *) malloc((*quantityOfProducts) * sizeof(merchandise));

        while (cont1 < (*quantityOfProducts))
        {
            while ((character != ' ') && (character != ','))
            {
                if (cont2 == 5)
                    errorInCode();

                (*products)[cont1].code[cont2] = character;
                cont2+=1;
                character = fgetc(inputFile);
            }

            ((*products)[cont1].code[cont2]) = '\0';

            while (character == ' ' || character == ',')
                character = fgetc(inputFile);

            cont2 = 0;

            while (character != ',')
            {
                if (cont2 == 20)
                    errorInDescription();

                (*products)[cont1].description[cont2] = character;
                cont2 += 1;
                character = fgetc(inputFile);
            }

            ((*products)[cont1].code[cont2]) = '\0';
            cont2=0;

            fscanf(inputFile,"%d", &(*products)[cont1].value);

            character = fgetc(inputFile);

            fscanf(inputFile,"%d", &(*products)[cont1].weight);

            while (character == ' ' || character == ',' || character == '\n')
                character = fgetc(inputFile);

            /* Implementing first heuristics */
            if ((*products)[cont1].weight <= *maximumWeight)
            {
                cont1 += 1;
                structProductsEmpty = false;
            }
            else
                (*quantityOfProducts -= 1);
        }

        /* Print file in string format /
        cout << endl << " " << (*quantityOfProducts) << " - " << (*maximumWeight);

        for (cont1 = 0; cont1 < (*quantityOfProducts); cont1++)
        {
            cout << endl << endl << " CODE: " << (*products)[cont1].code;
            cout << endl << " DESCRIPTION: "  << (*products)[cont1].description;
            cout << endl << " VALUE: "        << (*products)[cont1].value;
            cout << endl << " WEIGHT: "       << (*products)[cont1].weight << endl << endl;
        }
        */

        if (structProductsEmpty == true)
            printHeavierProducts();
    }
    else
        exceedingLimit();

    fclose(inputFile);
}
//###############################################################################

/// ANALYZE THE PRODUCTS THAT WILL BE IMPORTED
Queue analyzeTheProducts (merchandise * products, int quantityOfProducts, int maximumWeight, int * quantityOfProductImported)
{
    Queue queueOfProducts;
    initQueue (queueOfProducts);

    (*quantityOfProductImported) = 0;

    int cont1 = 0, sizeContainer = 0, result = 0, *positions, ProductImported = 0;

    int **productMatrix = new int * [quantityOfProducts + 1];

    for (cont1 = 0; cont1 < quantityOfProducts+1; cont1++)
        productMatrix[cont1] = new int[maximumWeight + 1];

    positions = (int *) malloc(quantityOfProducts * sizeof(int));

    for (cont1 = 0; cont1 <= quantityOfProducts; cont1++)
    {
        for (sizeContainer = 0; sizeContainer <= maximumWeight; sizeContainer++)
        {
            if (cont1 == 0 || sizeContainer == 0)
                productMatrix[cont1][sizeContainer] = 0;
            else if (products[cont1-1].weight <= sizeContainer)
                productMatrix[cont1][sizeContainer] = max (products[cont1 - 1].value + productMatrix[cont1 - 1][sizeContainer - products[cont1 - 1].weight], productMatrix[cont1 - 1][sizeContainer]);
            else
                productMatrix[cont1][sizeContainer] = productMatrix[cont1 - 1][sizeContainer];
        }
    }

    result = productMatrix[quantityOfProducts][maximumWeight];
    sizeContainer = maximumWeight;

    for (cont1 = quantityOfProducts; cont1 > 0 && result > 0; cont1--)
    {
        if (result == productMatrix[cont1 - 1][sizeContainer])
            continue;
        else
        {
            // Include product in vector
            positions[(*quantityOfProductImported)] = (cont1 - 1);
            (*quantityOfProductImported)++;

            result = (result - products[cont1 - 1].value);
            sizeContainer = sizeContainer - products[cont1 - 1].weight;
        }
    }

    for (ProductImported = (*quantityOfProductImported); ProductImported > 0; ProductImported--)
        insertQueue (queueOfProducts, products[positions[ProductImported - 1]]);

    return queueOfProducts;
}
//###############################################################################

/// PRINT THE CONTENTS OF THE QUEUE
void printQueueOfProducts (Queue queueOfProducts)
{
    merchandise products;
    int cont;

    chooseColor(blue);
    printf("\n   \332");

    for (cont = 0; cont < 9; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\304\277" << endl << "   \263";

    chooseColor(green);
    cout << "\t\t  PRODUCTS CHOSEN FOR IMPORT";

    chooseColor(blue);
    cout << "\t\t   \263 \n   \303\304\304\304\304\304\304\302";

    for (cont = 0; cont < 4; cont++)
        cout << "\304\304\304\304\304";

    cout << "\304\302";

    for (cont = 0; cont < 3; cont++)
        cout << "\304\304\304\304";

    cout << "\304\302";

    for (cont = 0; cont < 3; cont++)
        cout << "\304\304\304\304";

    cout << "\264" << endl << "   \263";

    chooseColor(red);
    cout << " CODE ";

    chooseColor(blue);
    cout << "\263";

    chooseColor(red);
    cout << "     DESCRIPTION     ";

    chooseColor(blue);
    cout << "\263";

    chooseColor(red);
    cout << " VALUE (USD) ";

    chooseColor(blue);
    cout << "\263";

    chooseColor(red);
    cout << " WEIGHT (g) ";

    chooseColor(blue);
    cout << "\263" << endl << "   \303\304\304\304\304\304\304\301";

    for (cont = 0; cont < 4; cont++)
        cout << "\304\304\304\304\304";

    cout << "\304\301";

    for (cont = 0; cont < 3; cont++)
        cout <<"\304\304\304\304";

    cout << "\304\301";

    for (cont = 0; cont < 3; cont++)
        cout <<"\304\304\304\304";

    cout << "\264";

    cout << endl << "   \263 \t\t\t\t\t\t\t   \263" << endl << "   \303\304\304\304\304\304\304\302";

    for (cont = 0; cont < 4; cont++)
        cout <<"\304\304\304\304\304";

    cout << "\304\302";

    for (cont = 0; cont < 3; cont++)
        cout <<"\304\304\304\304";

    cout << "\304\302";

    for (cont = 0; cont < 3; cont++)
        cout <<"\304\304\304\304";

    cout << "\264";

    while (!isEmptyQueue(queueOfProducts))
    {
        products = eliminate(queueOfProducts);

        chooseColor(blue);
        cout << endl << "   \263";

        chooseColor(red);
        printf("%-6s", products.code);

        chooseColor(blue);
        cout << "\263";

        chooseColor(red);
        printf("%-21s", products.description);

        chooseColor(blue);
        cout << "\263";

        chooseColor(red);
        printf("%-13d", products.value);

        chooseColor(blue);
        cout << "\263";

        chooseColor(red);
        printf("%-12d", products.weight);

        chooseColor(blue);
        cout << "\263";

        if (!isEmptyQueue(queueOfProducts))
        {
            cout << endl << "   \303\304\304\304\304\304\304\305";

            for (cont = 0; cont < 4; cont++)
                cout <<"\304\304\304\304\304";

            cout << "\304\305";

            for (cont = 0; cont < 3; cont++)
                cout <<"\304\304\304\304";

            cout << "\304\305";

            for (cont = 0; cont < 3; cont++)
                cout <<"\304\304\304\304";

            cout << "\264";
        }
        else
        {
            cout << endl << "   \300\304\304\304\304\304\304\301";

            for (cont = 0; cont < 4; cont++)
                cout <<"\304\304\304\304\304";

            cout << "\304\301";

            for (cont = 0; cont < 3; cont++)
                cout <<"\304\304\304\304";

            cout << "\304\301";

            for (cont = 0; cont < 3; cont++)
                cout <<"\304\304\304\304";

            cout << "\331";
        }
    }
}
//###############################################################################

/// RETURN THE RESULT OF THE TOTAL VALUE
int totalValue (Queue queueOfProducts)
{
    merchandise products;
    int resultTotalValue = 0;

    while (!isEmptyQueue (queueOfProducts))
    {
        products = eliminate (queueOfProducts);
        resultTotalValue += products.value;
    }
    return resultTotalValue;
}
//###############################################################################

/// RETURN THE RESULT OF THE TOTAL WEIGHT
int totalWeight (Queue queueOfProducts)
{
    merchandise products;
    int resultTotalWeight = 0;

    while (!isEmptyQueue (queueOfProducts))
    {
        products = eliminate (queueOfProducts);
        resultTotalWeight += products.weight;
    }
    return resultTotalWeight;
}
//###############################################################################

/// PRINT THE TOTAL VALUE AND WEIGHT
void printValueAndWeight(Queue queueOfProducts, int quantityOfProductImported)
{
    int cont;

    chooseColor(blue);
    cout << endl << endl << "\t     \332";

    for (cont = 0; cont < 2; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\304\304\304\302";

    for (cont = 0; cont < 3; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\304\277" << endl << "\t     \263";

    chooseColor(green);
    cout << " TOTAL AMOUNT: ";

    chooseColor(blue);
    cout << "\263";

    chooseColor(red);
    printf(" USD %-13d", totalValue(queueOfProducts));

    chooseColor(blue);
    cout << " \263" << endl << "\t     \303";

    for (cont = 0; cont < 2; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\304\304\304\305";

    for (cont = 0; cont < 3; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\304\264" << endl << "\t     \263";

    chooseColor(green);
    cout << " TOTAL WEIGHT: ";

    chooseColor(blue);
    cout << "\263";

    chooseColor(red);
    printf (" %d g", totalWeight(queueOfProducts));

    chooseColor(blue);
    Goto_xy ((12 + (2 * quantityOfProductImported)), 46);
    cout << "   \263" << endl << "\t     \300";

    for (cont = 0; cont < 2; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\304\304\304\301";

    for (cont = 0; cont < 3; cont++)
        cout << "\304\304\304\304\304\304";

    cout << "\304\331" << endl << endl << endl << endl;
    chooseColor(white);
}
//###############################################################################

/// CLEANING THE FIELDS OF THE STRUCT
void clearStruct (merchandise **products, int * quantityOfProducts, int * maximumWeight)
{

    int cont = 0, cont2 = 0;

    while (cont < (*quantityOfProducts))
    {
        (*products)[cont].code[cont2] = '\0';
        (*products)[cont].description[cont2] = '\0';
        (*products)[cont].value = 0;
        (*products)[cont].weight = 0;
        cont++;
    }

  //  (*quantityOfProducts) = 0;
    (*maximumWeight) = 0;
}
