#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>
#include <locale.h>
#include <malloc.h>
#include <crtdbg.h>


typedef struct Estado{ //Estrutura de dados que representa os estados do autômato 
    char name[5];
    char* CaracteresAceitos;
    struct Estado *EstadosAlcancaveis[5];
    int Hierarquia;
} Estado;

int ProcessarEntradaViaArquivo(FILE *arq, char** PonteirosParaPalavras, int TAMOfPonteiros);
void FuncaoProgramaAutomato(char **PonteirosParaPalavras, int TAMOfPonteiros);
void SystemPause();


