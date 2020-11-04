#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <windows.h>
#include <locale.h>
#include <malloc.h>
#include <crtdbg.h>
#include <unistd.h> //Linux

const char ExeptionList[] = {27, "/", "*", "-", "+", ".", ",", "=", "\\"};

typedef struct Estado{
    char name[5];
    char CaracteresAceitos[256];
    struct Estado *EstadosAlcancaveis[5];
    int Hierarquia;
} Estado;

int ProcessarEntradaViaArquivo(FILE *arq, char* PonteirosParaPalavras, int TAMOfPonteiros);
void FuncaoProgramaAutomato(char *PonteirosParaPalavras, int TAMOfPonteiros);


