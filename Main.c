#include "Functions.h"

void ClearScreen() {
	setbuf(stdin, NULL);
	//setvbuf(stdin, NULL, _IONBF, 0);
	system("clear");
}

char* LerStringDinamicamente(int ASCIIcodeStopCondition){
	char caracter;
	int MAX_TAM = 256;
	char *string = (char*) malloc(sizeof(char) * MAX_TAM);
	int count = 0;
	while ((caracter = getchar()) != ASCIIcodeStopCondition) //10 é o ASCII code para a tecla Enter.
	{
		if(count > MAX_TAM){
			MAX_TAM = MAX_TAM + 256;
			string = realloc(string, MAX_TAM);
		}
		string[count] = caracter;
		count++;
	}

	return string;
	
}
void PushForVetorChar(char vetor[], char String[]){
	vetor[sizeof(vetor)] = String;
}

void LimparPonteirosParaPalavras(char **PonteirosParaPalavras){
	PonteirosParaPalavras = realloc(PonteirosParaPalavras, 1);
}


void main(){

    int option;
	int TAMOfPonteiros = 1;
	char **PonteirosParaPalavras = (char**) malloc(sizeof(char*) * TAMOfPonteiros);

    while (1)
    {
        ClearScreen();
		printf(
			"*********************************************************************\n"
			"*ESCOLHA UMA OPÇÃO:                                                 *\n"
			"*********************************************************************\n"
			"*0 - Sair do programa                                               *\n"
			"*1 - Importar Entrada(s) de um arquivo TXT                          *\n"
			"*2 - Inserir entrada(s) manualmente com processamento imediato      *\n"
			"*3 - Inserir entrada(s) manualmente                                 *\n"
			"*4 - Processar palavras Salvas					                     *\n"
			"*5 - Definir nome do arquivo de gravação                            *\n"
			"*6 - Gerar todas as possibilidades                                  *\n"
			"*********************************************************************\n"
		);
        scanf("%d", &option);

        switch (option)
        {
        case 0:
            exit(1);
            break;
		case 1:
			ClearScreen();
			char name[256]; //Em geral, os sistemas de arquivos limitam o nome de arquivos em 256 caracters, por isso, esse valor fixo é o suficiente.
			printf("Digite o nome do arquivo sem a extensão.");
			strcat(name, ".txt");
			FILE *arq = fopen(name, "w+");
			TAMOfPonteiros = ProcessarEntradaViaArquivo(arq, PonteirosParaPalavras, TAMOfPonteiros);
			free(arq);
			break;
		case 2:
			ClearScreen();
			printf("Digite uma palavra e pressione Enter para verificar se a palavra é aceita ou não.");
			char *palavra = LerStringDinamicamente(10); // ASCII code para a tecla Enter.
			char **PonteiroParaPalavra = (char**) malloc(sizeof(char*) * 1);
			PonteirosParaPalavras[0] = palavra;
			// PushForVetorChar(PonteirosParaPalavras, palavra);
			// TAMOfPonteiros++;
			// PonteirosParaPalavras = realloc(PonteirosParaPalavras, TAMOfPonteiros);
			FuncaoProgramaAutomato(PonteiroParaPalavra, TAMOfPonteiros);
			LimparPonteirosParaPalavras(PonteirosParaPalavras);
			free(palavra);
			free(PonteiroParaPalavra);
			break;
		case 3:
			ClearScreen();
			printf("Digite uma palvra e em seguida digite Enter para digitar a próxima.\n"
			"Se desejar parar a digitação de palavras, pressione ESC e em seguida pressione Enter.\n");
			char *palavra = LerStringDinamicamente(27); //ASCII code para a tecla ESC.
			int MAX_TAM = 256;
			char *auxiliar = (char*) malloc(sizeof(char) * MAX_TAM);
			int count = 0;
			for(int i = 0; palavra[i] != 27; i++){
				if(count > MAX_TAM){
					MAX_TAM = MAX_TAM + 256;
					auxiliar = realloc(auxiliar, MAX_TAM);
				}
				auxiliar[i] = palavra[i];
				if(auxiliar[i] == 10){
					PushForVetorChar(PonteirosParaPalavras, auxiliar);
					TAMOfPonteiros++;
					PonteirosParaPalavras = realloc(PonteirosParaPalavras, TAMOfPonteiros);
					MAX_TAM = 256;
					auxiliar = (char*) malloc(sizeof(char) * MAX_TAM);
				}
				count++;
			}
			free(palavra);
			free(auxiliar);
			break;
		case 4:
			ClearScreen();
			FuncaoProgramaAutomato(PonteiroParaPalavra, TAMOfPonteiros);
        default:
            break;
        }

    }
}