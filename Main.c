#pragma warning(disable : 4996)
#include "Functions.h"


void ClearScreen() { //Função utilizada para Limpar o terminal 
	setbuf(stdin, NULL);
	system("cls");
}

char* LerStringDinamicamente(int ASCIIcodeStopCondition){ //Essa função permite ao programa ler quantos caracteres forem digitados sem limitar o tamanho da string previamente
	char caracter;
	int MAX_TAM = 256;
	char *string = (char*) calloc(MAX_TAM, sizeof(char));
	int count = 0;
	while ((caracter = getchar()) != ASCIIcodeStopCondition) //ASCIIcodeStopCondition contém o caracter que fará a leitura do buffer de entrada parar
	{
		if(count > MAX_TAM){//Se a string que o usuário colocar no buffer de entrada exceder o tamanho máximo de "string", mais espaço é alocado
			MAX_TAM = MAX_TAM + 256;
			string = realloc(string, MAX_TAM);
		}
		string[count] = caracter;
		count++;
	}

	if (count > MAX_TAM) { //Para inserir o último caracter
		MAX_TAM = MAX_TAM + 2;
		string = realloc(string, MAX_TAM);
	}
	string[count] = caracter;

	return string;
	
}

void LimparPonteirosParaPalavras(char **PonteirosParaPalavras){ //Função utilizada para limpar o buffer que armazena as palavras para serem processaas no automato
	free(PonteirosParaPalavras);
	PonteirosParaPalavras = (char**)calloc(1024, sizeof(char*));
}


void main(){

	setlocale(LC_ALL, "portugues"); //código para definir o idioma do cmd para portugês idependente do idoma do sistema do usuário
	system("chcp 65001");//definir a codificação de caracters para UTF-8

    int option;
	int TAMOfPonteiros = 0;
	char **PonteirosParaPalavras = (char**) calloc(1024, sizeof(char*));//Esse será o buffer que armazenará as palavras desejadas pelo usuário

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
			"*4 - Processar palavras Salvas	                                    *\n"
			"*6 - Limpar todas as entradas	                                    *\n"
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
			printf("Digite o nome do arquivo sem a extensão.\n");
			scanf("%s", name);
			strcat(name, ".txt");
			FILE* arq = fopen(name, "r+");
			if (arq == NULL) {
				printf("Erro");
				SystemPause();
			}
			else {
				TAMOfPonteiros = ProcessarEntradaViaArquivo(arq, PonteirosParaPalavras, TAMOfPonteiros);
				fclose(arq);
			}
			break;
		case 2:
			ClearScreen();
			printf("Digite uma palavra e pressione Enter para verificar se a palavra é aceita ou não.\n");
			char *palavra = LerStringDinamicamente(10); // 10 é o ASCII code para a tecla Enter.
			char **PonteiroParaPalavra = (char**) malloc(sizeof(char*) * 1);
			PonteiroParaPalavra[0] = palavra;
			FuncaoProgramaAutomato(PonteiroParaPalavra, 1);
			free(palavra);
			free(PonteiroParaPalavra);
			break;
		case 3:
			ClearScreen();
			printf("Digite uma palvra e em seguida digite Enter para digitar a próxima.\n"
			"Se desejar parar a digitação de palavras, pressione * e em seguida pressione Enter.\n");
			char *palavra1 = LerStringDinamicamente(42); //42 é o ASCII code para a tecla *.
			int count2 = 0;
			int MAX_TAM = 256;
			int letras = 0;
			PonteirosParaPalavras[TAMOfPonteiros] = (char*)_malloca(sizeof(char) * MAX_TAM); //Aloca um vetor string em uma posição no vetor de ponteiros char
			TAMOfPonteiros++;
			for(int i = 0; palavra1[i] != 42; i++){
				if (letras > MAX_TAM) {// Se a string que o usuário colocar no buffer de entrada exceder o tamanho máximo de "string", mais espaço é alocado
					MAX_TAM = MAX_TAM + 256;
					PonteirosParaPalavras[TAMOfPonteiros - 1] = realloc(PonteirosParaPalavras[TAMOfPonteiros - 1], MAX_TAM);
				}
				PonteirosParaPalavras[TAMOfPonteiros - 1][count2] = palavra1[i];
				if(palavra1[i] == 10){//Quebra a string palavra1 em várias strings detectando o \n(enter)
					MAX_TAM = 256;
					PonteirosParaPalavras[TAMOfPonteiros] = (char*)_malloca(MAX_TAM * sizeof(char));
					TAMOfPonteiros++;
					letras = -1;
					count2 = -1;
				}
				letras++;
				count2++;
			}
			free(palavra1);
			break;
		case 4:
			ClearScreen();
			if (PonteirosParaPalavras[0] != NULL) {
				FuncaoProgramaAutomato(PonteirosParaPalavras, TAMOfPonteiros);
			}
			else
			{
				printf("Nenhuma palavra armazenada\n");
				SystemPause();
			}
			break;
		case 6:
			ClearScreen();
			LimparPonteirosParaPalavras(PonteirosParaPalavras);
        default:
			printf("Opção inválida\n");
            break;
        }

    }
}