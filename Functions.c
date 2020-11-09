#pragma warning(disable : 4996)
#include "Functions.h"

char ExeptionList[10] = "*"; //Caracteres que não podem ser colocados em uma palavra para ser porcessado pelo automato 



int VerificarListaDeExecoes(char caracter){
    for(int i = 0; i < sizeof(ExeptionList); i++){
        if(caracter == ExeptionList[i])
            return 1;
    }

    return 0;
}

void SystemPause() { //Função utilizada para pausar a execução do código, permitindo o usuário ver com mais clareza o que está acontecendo no código
	setbuf(stdin, NULL);
	printf("\nPressione qualquer tecla para continuar.\n");
	getchar();
	setbuf(stdin, NULL);
}

int ProcessarEntradaViaArquivo(FILE* arq, char** PonteirosParaPalavras, int TAMOfPonteiros) {//Processa um arquivo .txt capturando as strings para serem processadas no automato posteiormente
    printf("Começando o processamento do Arquivo!\n"
        "Observação: Apenas caracteres fora da lista de exceções serão aceitos. Os caracteres\n"
        "dentro da lista de exceções serão ignorados automaticamente.\n"
        "Para mais informações sobre a lista, consulte o manul de utilização.");
    printf("Processando...\n");
    char caracter;
    int MAX_TAM = 256;
    int count = 0;
    char* auxiliar = (char*)calloc(MAX_TAM, sizeof(char));
    while (!feof(arq)) {
        caracter = fgetc(arq);
        if (VerificarListaDeExecoes(caracter) == 0) {//Verifica se o caracter atual lido do arquivo não é um caracters na lista de exceções
            if (count > MAX_TAM) {// Se a string que o usuário colocar no buffer de entrada exceder o tamanho máximo de "string", mais espaço é alocado
                MAX_TAM = MAX_TAM + 256;
                auxiliar = realloc(auxiliar, MAX_TAM);
            }
            auxiliar[count] = caracter;
            if (caracter == 10) {//Quebra as strings obtidas do arquivo em várias strings detectando o \n
                PonteirosParaPalavras[TAMOfPonteiros] = auxiliar;
                TAMOfPonteiros++;
                MAX_TAM = 256;
                auxiliar = (char*)calloc(MAX_TAM, sizeof(char));
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
    SystemPause();
    return TAMOfPonteiros;
}

void FuncaoProgramaAutomato(char** PonteirosParaPalavras, int TAMOfPonteiros) {
    /*O bloco de código abaixo cria várias estruturas de daodos que representam os estados do autômato*/
    Estado** Automato = (Estado**)malloc(sizeof(Estado*) * 7);
    Automato[0] = (Estado*)malloc(sizeof(Estado) * 1);
    Automato[0]->CaracteresAceitos = (char*)calloc(256, sizeof(char));
    Automato[1] = (Estado*)malloc(sizeof(Estado) * 1);
    Automato[1]->CaracteresAceitos = (char*)calloc(256, sizeof(char));
    Automato[2] = (Estado*)malloc(sizeof(Estado) * 1);
    Automato[2]->CaracteresAceitos = (char*)calloc(256, sizeof(char));
    Automato[3] = (Estado*)malloc(sizeof(Estado) * 1);
    Automato[3]->CaracteresAceitos = (char*)calloc(256, sizeof(char));
    Automato[4] = (Estado*)malloc(sizeof(Estado) * 1);
    Automato[4]->CaracteresAceitos = (char*)calloc(256, sizeof(char));
    Automato[5] = (Estado*)malloc(sizeof(Estado) * 1);
    Automato[5]->CaracteresAceitos = (char*)calloc(256, sizeof(char));
    Automato[6] = (Estado*)malloc(sizeof(Estado) * 1);
    Automato[6]->CaracteresAceitos = (char*)calloc(256, sizeof(char));
   /*Fim da criação dos estados-------------------------------------------------------------------------*/
    /*O bloco de código a seguir define qual estado será cada estrutura de dados e quais são os estados alcançáveis e os caracteres aceitos para leitura*/
    sprintf(Automato[0]->name, "%s", "Q0");
    sprintf(Automato[0]->CaracteresAceitos, "%s", "m");
    Automato[0]->EstadosAlcancaveis[0] = Automato[1];
    Automato[0]->Hierarquia = 0;

    sprintf(Automato[1]->name, "%s", "Q1");
    sprintf(Automato[1]->CaracteresAceitos, "%s", "1");
    Automato[1]->EstadosAlcancaveis[0] = Automato[2];
    Automato[1]->Hierarquia = 2;

    sprintf(Automato[2]->name, "%s", "Q2");
    sprintf(Automato[2]->CaracteresAceitos, "%s", "02");
    Automato[2]->EstadosAlcancaveis[0] = Automato[3];
    Automato[2]->EstadosAlcancaveis[1] = Automato[6];
    Automato[2]->Hierarquia = 2;

    sprintf(Automato[3]->name, "%s", "Q3");
    sprintf(Automato[3]->CaracteresAceitos, "%s", "6");
    Automato[3]->EstadosAlcancaveis[0] = Automato[4];
    Automato[3]->Hierarquia = 2;

    sprintf(Automato[4]->name, "%s", "Q4");
    sprintf(Automato[4]->CaracteresAceitos, "%s", "a");
    Automato[4]->EstadosAlcancaveis[0] = Automato[5];
    Automato[4]->Hierarquia = 2;

    sprintf(Automato[5]->name, "%s", "Q5");
    sprintf(Automato[5]->CaracteresAceitos, "%s", "t");
    Automato[5]->EstadosAlcancaveis[0] = Automato[2];
    Automato[5]->Hierarquia = 2;

    sprintf(Automato[6]->name, "%s", "Q6");
    Automato[6]->Hierarquia = 1;
    /*Fim da definição*/

    Estado* EstadoAtual; //Usado para controla o estado atual em que se econtra o processamento 

    for (int i = 0; i < TAMOfPonteiros; i++) {
        char auxiliar;
        int aceitaM = 0;
        EstadoAtual = Automato[0];
        printf("Palavra a ser processada: %s", PonteirosParaPalavras[i]);
        Sleep(500);
        printf("Processando...");
        Sleep(700);

        for (int j = 0; j < strlen(PonteirosParaPalavras[i]); j++) {//Laço de repetição usado para percorrer todas as palvras salvas no buffer
            auxiliar = PonteirosParaPalavras[i][j];
            char CaracterDoAutomatoAtual = EstadoAtual->CaracteresAceitos[0];

            for (int m = 0; m < strlen(EstadoAtual->CaracteresAceitos); m++) //Laço de repetição usado para para ver se um determinado caracter da palvra é aceita pelo estado atual
            {
                if (auxiliar == CaracterDoAutomatoAtual) {//Se o caracter da palavra for aceita
                    EstadoAtual = EstadoAtual->EstadosAlcancaveis[m]; //O próximo estado é alcançado através do acesso do vetor Estados Alcançáveis acessando na posição referente à posição do vetor caracteres aceitos
                    printf("Estado alcançado: %s\n", EstadoAtual->name);
                    printf("Caracter lido: %c\n", auxiliar);
                    Sleep(200);
                    aceitaM = 1;
                    break;
                }
                else { aceitaM = 0; }
                CaracterDoAutomatoAtual = EstadoAtual->CaracteresAceitos[m + 1];
            }

            if (aceitaM == 0) {
                printf("Essa palavra foi rejeitado por indefinição devido ao caracter %c no estado %s\n Palavra: %s", auxiliar, EstadoAtual->name, PonteirosParaPalavras[i]);
                break;
            }
        }
        if (EstadoAtual->Hierarquia != 1 && aceitaM == 1) {
            printf("Essa palavra foi rejeitada pois o estado atingido após o processamento\n do último símbolo, o estado atingido foi um estado não final.\n Estado: %s\n Palavra: %s", EstadoAtual->name, PonteirosParaPalavras[i]);
        }
        else if (aceitaM == 1)
        {
            printf("Palavra Aceita!\n Estado Final: %s\nPalavra: %s", EstadoAtual->name, PonteirosParaPalavras[i]);
        }
        SystemPause();
    }
    printf("Processamento finalizado");
    SystemPause();
}