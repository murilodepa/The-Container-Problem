/* DESCRIPTION: THE CONTAINER PROBLEM.

            PONTIFICAL CATHOLIC UNIVERSITY OF CAMPINAS - PUCC
            STUDENT NAME: MURILO DE PAULA ARAUJO
            RA: 17747775
            TEACHER: GILBERTO SHIGUEO NAKAMITI
            COURSE: COMPUTER ENGINEERING     PERIOD: 4º SEMESTER
            SUBJECT: DATA STRUCTURES B

                    FINAL WORK - "THE CONTAINER PROBLEM"
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
typedef struct goods
{
    char code        [300];
    char description [300];
    int  value;
    int  weight;
} merchandise;
//###############################################################################

//#################### PROTOTYPE OF FUNCTIONS USED IN MAIN ######################
/// CHANGES COLOR OF PRINTED CHARACTERS
void chooseColor (int );

/// GO TO POSITION (LINES AND COLUMNS)
void Goto_xy (int lin, int col);

/// VALIDATE FILE AND RETURN ONLY READ FILE
FILE * validatingTheFile ();

/// EXIT THE PROGRAM! EXCEEDED THE NUMBER OF ITEMS OR WEIGHT ALLOWED
void exceedingLimit ();

/// PRINT NO PRODUCTS IN FILE
void printWithoutProducts();

/// READ FILE PRODUCTS AND STORE IN STRUCT GOODS
void readFileProducts (merchandise **, int *, int *);
//###############################################################################

//#################################### MAIN #####################################
int main()
{
    merchandise *products;

    int quantityOfProducts, maximumWeight, quantityOfProductImported;

    readFileProducts (&products, &quantityOfProducts, &maximumWeight);

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
void Goto_xy(int lin, int col)
{
    HANDLE Saida;

    COORD Posicao;

    Saida = GetStdHandle(STD_OUTPUT_HANDLE);

    Posicao.X = col;
    Posicao.Y = lin;

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

/// READ FILE PRODUCTS AND STORE IN STRUCT GOODS
void readFileProducts (merchandise **products, int *quantityOfProducts, int *maximumWeight)
{
    int cont1=0, cont2=0;
    char character;

    FILE *inputFile; /* Defining a file type variable */

    inputFile = validatingTheFile();

    /* Reading of the quantity of products and maximum weight */
    fscanf(inputFile,"%d %d", quantityOfProducts, maximumWeight);

    if ((*quantityOfProducts) == 0)
        printWithoutProducts();

    character = fgetc(inputFile);

    while (character == ' ' || character == ',' || character == '\n')
        character = fgetc(inputFile);

    if (*quantityOfProducts <=100 && *maximumWeight <= 1000000)
    {
        *products = (merchandise *) malloc((*quantityOfProducts) * sizeof(merchandise));

        while (cont1 < (*quantityOfProducts))
        {
            while ((character != ' ') && (character != ','))
            {
                (*products)[cont1].code[cont2]=character;
                cont2+=1;
                character = fgetc(inputFile);
            }

            ((*products)[cont1].code[cont2])='\0';

            while (character == ' ' || character == ',')
                character = fgetc(inputFile);

            cont2=0;

            while (character != ',')
            {
                (*products)[cont1].description[cont2]=character;
                cont2+=1;
                character = fgetc(inputFile);
            }

            ((*products)[cont1].code[cont2])='\0';
            cont2=0;

            fscanf(inputFile,"%d", &(*products)[cont1].value);

            character = fgetc(inputFile);

            fscanf(inputFile,"%d", &(*products)[cont1].weight);

            while (character == ' ' || character == ',' || character == '\n')
                character = fgetc(inputFile);

            /* Implementing first heuristics */
            if ((*products)[cont1].weight <= *maximumWeight)
                cont1+=1;
            else
                (*quantityOfProducts-=1);
        }

        /* Print file in string format */
        cout << endl << " " << (*quantityOfProducts) << " - " << (*maximumWeight);

        for (cont1 = 0; cont1 < (*quantityOfProducts); cont1++)
        {
            cout << endl << endl << " CODE: " << (*products)[cont1].code;
            cout << endl << " DESCRIPTION: "  << (*products)[cont1].description;
            cout << endl << " VALUE: "        << (*products)[cont1].value;
            cout << endl << " WEIGHT: "       << (*products)[cont1].weight << endl << endl;
        }


    }
    else
        exceedingLimit();

    fclose(inputFile);
}
//###############################################################################
