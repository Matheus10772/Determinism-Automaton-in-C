#include "Functions.h"

char ExeptionList[10] = "/*-+.=";



int VerificarListaDeExecoes(char caracter){
    for(int i = 0; i < sizeof(ExeptionList); i++){
        if(caracter == ExeptionList[i])
            return 1;
    }

    return 0;
}

void SystemPause() {
	setbuf(stdin, NULL);
	//setvbuf(stdin, NULL, _IONBF, 0);
	printf("\nPressione qualquer tecla para continuar.\n");
	getchar();
	setbuf(stdin, NULL);
	//setvbuf(stdin, NULL, _IONBF, 0);
}

int ProcessarEntradaViaArquivo(FILE *arq, char** PonteirosParaPalavras, int TAMOfPonteiros){
    printf("Começando o processamento do Arquivo!\n"
    "Observação: Apenas caracteres fora da lista de exceções serão aceitos. Os caracteres\n"
    "dentro da lista de exceções serão ignorados automaticamente.\n"
    "Para mais informações sobre a lista, consulte o manul de utilização.");
    //usleep(999999);
    // usleep(999999);
    // usleep(999999);
    printf("Processando...");
    char caracter;
    int MAX_TAM = 256;
    int count = 0;
    char *auxiliar = (char*) malloc(sizeof(char) * MAX_TAM);
    while (!feof(arq))
    {
        caracter = fgetc(arq);
        if(VerificarListaDeExecoes(caracter) == 0){
            if(count > MAX_TAM){
                MAX_TAM = MAX_TAM + 256;
                auxiliar = realloc(auxiliar, MAX_TAM);
            }
            auxiliar[count] = caracter;
            if(caracter == 10){
                PonteirosParaPalavras[TAMOfPonteiros] = auxiliar;
                TAMOfPonteiros++;
                PonteirosParaPalavras = realloc(PonteirosParaPalavras, TAMOfPonteiros);
                MAX_TAM = 256;
                auxiliar = (char*) malloc(sizeof(char) * MAX_TAM);
                count = 0;
            }
            else
            {
                count++;
            }
            
        }
        else
        {
            printf("Caracter ignorado: %c", caracter);
        }
        

    }
    printf("Processamento finalizado!\n");
    // usleep(999999);
    // usleep(999999);
    // usleep(999999);
    return TAMOfPonteiros;
}

void FuncaoProgramaAutomato(char **PonteirosParaPalavras, int TAMOfPonteiros){
    Estado **Automato = (Estado**) malloc(sizeof(Estado*) * 6);
    Automato[0] = (Estado*) malloc(sizeof(Estado) * 1);
    // Automato[0]->EstadosAlcancaveis =(Estado**) malloc(sizeof(Estado*) * 5);
    Automato[1] = (Estado*) malloc(sizeof(Estado) * 1);
    // Automato[1]->EstadosAlcancaveis = malloc(sizeof(Estado*) * 5);
    Automato[2] = (Estado*) malloc(sizeof(Estado) * 1);
    // Automato[2]->EstadosAlcancaveis = malloc(sizeof(Estado*) * 5);
    Automato[3] = (Estado*) malloc(sizeof(Estado) * 1);
    // Automato[3]->EstadosAlcancaveis = malloc(sizeof(Estado*) * 5);
    Automato[4] = (Estado*) malloc(sizeof(Estado) * 1);
    // Automato[4]->EstadosAlcancaveis = malloc(sizeof(Estado*) * 5);
    Automato[5] = (Estado*) malloc(sizeof(Estado) * 1);
    // Automato[5]->EstadosAlcancaveis = malloc(sizeof(Estado*) * 5);

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 256; j++){
            sprintf(&(Automato[i]->CaracteresAceitos[j]), "%s", "*");
        }
    }

    sprintf(Automato[0]->name,"%s", "Q0");
    sprintf(Automato[0]->CaracteresAceitos,"%s", "m");
    Automato[0]->EstadosAlcancaveis[0] = Automato[1];
    Automato[0]->Hierarquia = 0;

    sprintf(Automato[1]->name, "%s", "Q1");
    sprintf(Automato[1]->CaracteresAceitos, "%s", "1");
    Automato[1]->EstadosAlcancaveis[0] = Automato[2];
    Automato[1]->Hierarquia = 2;

    sprintf(Automato[2]->name, "%s", "Q2");
    sprintf(Automato[2]->CaracteresAceitos, "%s", "02a");
    Automato[2]->EstadosAlcancaveis[0] = Automato[3];
    Automato[2]->EstadosAlcancaveis[1] = Automato[5];
    Automato[2]->EstadosAlcancaveis[2] = Automato[4];
    Automato[2]->Hierarquia = 2;

    sprintf(Automato[3]->name, "%s", "Q3");
    sprintf(Automato[3]->CaracteresAceitos, "%s", "4");
    Automato[3]->EstadosAlcancaveis[0] = Automato[2];
    Automato[3]->Hierarquia = 2;

    sprintf(Automato[4]->name, "%s", "Q4");
    sprintf(Automato[4]->CaracteresAceitos, "%s", "t");
    Automato[4]->EstadosAlcancaveis[0] = Automato[2];
    Automato[4]->Hierarquia = 2;

    sprintf(Automato[5]->name, "%s", "Q5");
    //Automato[5]->EstadosAlcancaveis = "\0";
    Automato[5]->Hierarquia = 1;

    Estado *EstadoAtual = Automato[0];

    for(int i = 0; i < TAMOfPonteiros; i++){
        int MAX_TAM = 256;
        char *auxiliar = (char*) malloc(sizeof(char) * MAX_TAM);

        for(int j = 0; j < strlen(PonteirosParaPalavras[i]); j++){
            if(j > MAX_TAM){
                MAX_TAM = MAX_TAM + 256;
                auxiliar = realloc(auxiliar, MAX_TAM);
            }

            auxiliar[j] = PonteirosParaPalavras[i][j];
            int count = 0;
            char CaracterDoAutomatoAtual = EstadoAtual->CaracteresAceitos[count];
            int aceitaM = 0;

            while (CaracterDoAutomatoAtual != "*")
            {
                if(auxiliar[j] == CaracterDoAutomatoAtual){
                    EstadoAtual = EstadoAtual->EstadosAlcancaveis[count];
                    aceitaM = 1;
                    break;
                }
                count++;
                CaracterDoAutomatoAtual = EstadoAtual->CaracteresAceitos[count];
            }

            if(aceitaM == 0){
                printf("Essa palavra foi rejeitado por indefinição devido ao caracter %c no estado %s\n Palavra: %s", auxiliar[j], EstadoAtual->name, PonteirosParaPalavras[i]);
                break;
            }   
        }
        if(EstadoAtual->Hierarquia != 1){
            printf("Essa palavra foi rejeitada pois o estado atingido após o processamento\n do último símbolo, o estado atingido foi um estado não final.\n Estado: %s\n Palavra: %s", EstadoAtual->name, PonteirosParaPalavras[i]);
        }
        else
        {
            printf("Palavra Aceita!\n Estado Final: %s\nPalavra: %s",  EstadoAtual->name, PonteirosParaPalavras[i]);
        }
                
    }
    SystemPause();
}