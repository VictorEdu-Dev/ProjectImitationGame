#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#define TamMax 500

int varControl = 0;
char ArqCript[50] = "MensagensCript.txt";
char ArqDescript[50] = "MensagensDescript.txt";
char file[50], file2[50];

/* Fun��o para Criptografar. Foi escrita de maneira recursiva,
de tal forma a ser um fun��o que invoca a si mesma e trabalha
caractere por caractere de uma string at� chegar num \0, por
exemplo.*/
void criptografar(char *str, FILE *arquivo_saida) {
	   if (*str == '\0') {
      fprintf(arquivo_saida, "\n");
      return;
	  }
    char caracteres = toupper(*str);
	if (caracteres >= 'A' && caracteres <= 'Z') {
        int caractereCriptografado = caracteres - 'A' + 1;
        fprintf(arquivo_saida, "%02d", caractereCriptografado);
		if(*(str+1) != '\0' && *(str+1) != ' ')
		{
        	fprintf(arquivo_saida, "_");
		}
    }
	else if (caracteres == ' ') {
        fprintf(arquivo_saida, " ");
    }
    criptografar(++str, arquivo_saida);
    varControl = 1;
}

/* Fun��o para descriptografar. Foi escrita de maneira recursiva,
de tal forma a ser um fun��o que invoca a si mesma e trabalha
caractere por caractere de uma string at� chegar num \0, por
exemplo.*/
void descriptografar(char *str, FILE *arquivo_saida) {
    char *caractere = str;
    while (*caractere == str[0]) {
            int valor = 0;
            while (*caractere >= '0' && *caractere <= '9') {
                valor = valor * 10 + (*caractere - '0');
                caractere++;
            }
            if (valor >= 1 && valor <= 26) {
                fprintf(arquivo_saida, "%c", valor + 'A' - 1);
            }
            if(*caractere == ' ') {
        	fprintf(arquivo_saida, " ");
		}
    }
    while (*caractere == str[1] || *caractere != '\0') {
            int valor = 0;
            while (*caractere >= '0' && *caractere <= '9') {
                valor = valor * 10 + (*caractere - '0');
                caractere++;
            }
            if (valor >= 1 && valor <= 26) {
                fprintf(arquivo_saida, "%c", valor + 'a' - 1);
            }
            if(*caractere == ' ') {
        	fprintf(arquivo_saida, " ");
		}
        caractere++;
    }
    fprintf(arquivo_saida, "\n");
	varControl = 2;
}

int main() {
    char str[100000], str2[100000];
    int opcao;
    FILE *arquivo;
	time_t tempo;
	time(&tempo);
	char tempo_str[30];
	strftime(tempo_str, sizeof(tempo_str), "%d/%b/%Y - %H:%M", localtime(&tempo));


    do {
    	
    	/* Este do-while exibe o menu principal do game,
		de tal forma que o usu�rio escolha uma das op��es
		e o programa execute uma das condicionais que
		existem a seguir. */
    	
    	do {
    	setlocale(LC_ALL, "");
    	puts("=====================================");
	   	puts("== JOGO DA IMITA��O - Criptografia ==");
        puts("=====================================");
        puts("1. Criptografar");
        puts("2. Descriptografar");
        puts("3. Instru��es adicionais");
        puts("4. Mais op��es");
        puts("5. Sair");
        puts("Escolha uma op��o: ");
		while (scanf("%d", &opcao)==0)
		fflush(stdin);
		
		    if (opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4 && opcao != 5) {
			   system("cls");
			   printf("Selecione uma op��o v�lida!\nPressione Enter...");
			   fflush(stdin);
			   while (getchar() != '\n');
			   system("cls");
			   break;
			   } else {
			   	continue;
			   }
		} while (opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4 && opcao != 5);
		system("cls");
		
		/* OP��O 1 - Criptografar. Recebe do usu�rio uma string,
		crie e abre um arquivo, aramazena a string nele usando
		a fun��o criptografar e exibe um menu de op��es. */
		
        if (opcao == 1) {
        	int continuar2 = 1;
        	do {

            printf("Informe a mensagem que deseja criptografar: ");
            fflush(stdin);
			fgets(str, sizeof(str), stdin);
			fflush(stdin);
			system("cls");
			str[strcspn(str, "\n")] = '\0';

			arquivo = fopen(ArqCript, "a");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo.\n");
                return 1;
            }

            fprintf(arquivo, "Mensagem criptografada (%s): \n", tempo_str);
            criptografar(str, arquivo);
            fclose(arquivo);

            if(varControl==1) {
			puts("Mensagem criptografada com sucesso!");
			puts("===================================");
			printf("Pressione Enter para continuar...");
			while (getchar() != '\n');
			fflush(stdin);
   			system("cls");
			} else {
				printf("Erro ao criptografar. Tente novamente!\n");
				getchar();
				system("cls");
			}
			
			/* Este menu � complementar a condicional que se refere a
			op��o 1. Ele visualiza ou criptografa ou retona ao menu
			inicial. */

			int continuar = 1;
			do {
			    int opcaoAdicional;

			    printf("Op��es:\n");
			    printf("1. Visualizar mensagem criptografada\n");
			    printf("2. Criptografar novamente\n");
			    printf("3. Voltar ao menu principal\n");
			    printf("Escolha uma op��o: ");
			    while(scanf("%d", &opcaoAdicional)==0)
			    fflush(stdin);

				    switch (opcaoAdicional) {
				        case 1:
				        	system("cls");
				            printf("Mensagem criptografada: ");
				            criptografar(str, stdout);
				            puts("Pressione Enter para continuar...");
				            getchar();
							while (getchar() != '\n');
							fflush(stdin);
				            system("cls");
				            break;
				        case 2:
				            system("cls");
				            continuar = 0;
				            break;
				        case 3:
				            system("cls");
				            continuar = 0;
				            continuar2 = 0;
				            break;
				        default:
				        	system("cls");
				            printf("Op��o inv�lida. Tente novamente!\nPressione Enter...\n");
							while (getchar() != '\n');
							fflush(stdin);
				            system("cls");
				            break;
	                }
				} while (continuar);
			} while(continuar2);
		}

		/* OP��O 2 - Descriptografar. Recebe do usu�rio uma string,
		crie e abre um arquivo, aramazena a string nele usando
		a fun��o descriptografar e exibe um menu de op��es. */
		else if (opcao == 2) {
			
			int continuar4 = 1;
			
			do {
				
			printf("Informe uma mensagem criptografada para descriptografar: ");
			fflush(stdin);
            fscanf(stdin, " %[^\n]s", str2);
            fflush(stdin);
            system("cls");
            str2[strcspn(str2, "\n")] = '\0';

			arquivo = fopen(ArqDescript, "a");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo.\n");
                system("pause");
                system("cls");
                return 1;
            }

			fprintf(arquivo, "Mensagem descriptografada (%s): \n", tempo_str);
            descriptografar(str2, arquivo);
            fclose(arquivo);

			/* Este menu � complementar a condicional que se refere a
			op��o 2. Ele visualiza ou descriptografa ou retona ao menu
			inicial. */

			if(varControl==2) {
                puts("Mensagem descriptografada com sucesso!");
                puts("======================================");
				puts("Pressione Enter para continuar...");
				while (getchar() != '\n');
				fflush(stdin);
				system("cls");
			} else {
				printf("Erro ao descriptografar. Tente novamente!\n");
				system("pause");
				system("cls");
			}

			/* Este menu � complementar a condicional que se refere a
			op��o 2. Ele visualiza ou descriptografa ou retona ao menu
			inicial. */
			
			int continuar3 = 1;
			do {
			    int opcaoAdicional;

			    printf("Op��es:\n");
			    printf("1. Visualizar mensagem descriptografada\n");
			    printf("2. Descriptografar novamente\n");
			    printf("3. Voltar ao menu principal\n");
			    printf("Escolha uma op��o: ");
			    while(scanf("%d", &opcaoAdicional)==0)
			    fflush(stdin);

				    switch (opcaoAdicional) {
				        case 1:
				        	system("cls");
				            printf("Mensagem descriptografada: ");
				            descriptografar(str2, stdout);
				            puts("Pressione Enter para continuar...");
				            getchar();
							while (getchar() != '\n');
							fflush(stdin);
				            system("cls");
				            break;
				        case 2:
				            system("cls");
				            continuar3 = 0;
				            system("cls");
				            break;
				        case 3:
				            system("cls");
				            continuar3 = 0;
				            continuar4 = 0;
				            break;
				        default:
				        	system("cls");
				            printf("Op��o inv�lida. Tente novamente!\nPressione Enter...\n");
							while (getchar() != '\n')
							fflush(stdin);
				            system("cls");
				            break;
	                }
				} while (continuar3);
			} while(continuar4);
			
        }
		/* OP��O 3 - Informa��es adicionais. Exibe ao usu�rio textos de
		orienta��o simples quanto a utiliza��o do programa. */
		else if (opcao == 3) {
        	system("cls");
        	puts("===========================================================");
			puts("Utiliza��o do software:");
			puts("-----------------------------------------------------------");
			printf("1. Ao utilizar a fun��o \"criptografar\", o programa ler�\napenas caracteres simples e ignorar� qualquer caractere\nespecial. Ex.:\"�, �, �, #, !, ?\".\n");
			puts("-----------------------------------------------------------");
			printf("2. Se desejar visualizar uma mensagem descriptografada,\nela nunca poder� ser visualizada como foi escrita\nanteriormente pelo usu�rio;\npor�m, sempre poder� ser lida em PT-BR.\n");
			puts("-----------------------------------------------------------");
			printf("3. Para visualizar mensagens criptografas ou descriptografadas\nbasta entrar no diret�rio onde o execut�vel do programa \nest� armazenado.\n");
			puts("===========================================================");
			printf("Pressione Enter para continuar...");
			getchar();
			while (getchar() != '\n')
			fflush(stdin);
			system("cls");
		}
		/* OP��O 4 - Mais op��es. Dependendo da op��o escolhida,
		a condicional abrir� um arquivo, ler� strings contidas
		e exibe-as ao usu�rio. */
		else if (opcao == 4) {
			int opcao3;
			do {
			puts ("1. Mensagens Criptografadas");
			puts ("2. Mensagens Descriptografadas");
			puts ("3. Novo Arquivo de Destino");
			puts ("4. Voltar ao Menu Principal");
			puts("Escolha uma op��o: ");
			while(scanf("%d", &opcao3)==0)
			fflush(stdin);
			system("cls");

				if (opcao3 == 1) {
					FILE *arquivo = fopen(ArqCript, "r");
						if (arquivo == NULL) {
						   printf("Erro ao abrir o arquivo.\n");
						   getchar();
						   while(getchar() != '\n')
						   fflush(stdin);
						   system("cls");
						}
					char linha[TamMax];
					while (fgets(linha, TamMax, arquivo) != NULL) {
					   printf("%s", linha);
					}
					fclose(arquivo);
					printf("\nPressione Enter para voltar ao menu anterior...");
					getchar();
					while(getchar()==0)
					/*system("pause");*/
					fflush(stdin);
					system("cls");
					continue;
					}
					else if (opcao3 == 2) {
					FILE *arquivo = fopen(ArqDescript, "r");
						if (arquivo == NULL) {
						   printf("Erro ao abrir o arquivo.\n");
						   getchar();
						   while(getchar() != '\n')
						   fflush(stdin);
						   system("cls");
						}
					char linha[TamMax];
					while (fgets(linha, TamMax, arquivo) != NULL) {
					printf("%s", linha);
					}
					fclose(arquivo);
					printf("\nPressione Enter para voltar ao menu anterior...");
					getchar();
					while(getchar()==0)
					/*system("pause");*/
					fflush(stdin);
					system("cls");
					}
					else if (opcao3 == 3) {
						int op;
						int ret = 0;
						do {
							puts("1. Cripto");
							puts("2. Decrifrado");
							puts("3. Voltar");
							puts("Escolha uma op��o: ");
							while (scanf("%d", &op)==0)
							fflush(stdin);
							system("cls");
							
							if (op == 1) {
								puts ("Atribua um nome ao arquivo: ");
								scanf("%s", file);
								strcpy(ArqCript, file);
								ret = 1;
								system("cls");
								if (ret == 1) {
									puts("Novo arquivo criado com sucesso!");
									getchar();
									while(getchar() != '\n')
									fflush(stdin);
									system("cls");
								} else {
									puts("Falha ao criar novo arquivo. Tente novamente!");
									getchar();
									while(getchar() !='\n')
									fflush(stdin);
									system("cls");
								}
							}
							else if (op == 2) {
								puts ("Atribua um nome ao arquivo: ");
								scanf("%s", file2);
								strcpy(ArqDescript, file2);
								ret = 1;
								system("cls");
								if (ret == 1) {
									puts("Novo arquivo criado com sucesso!");
									getchar();
									while(getchar() != '\n')
									fflush(stdin);
									system("cls");
								} else {
									puts("Falha ao criar novo arquivo. Tente novamente!");
									getchar();
									while(getchar() !='\n')
									fflush(stdin);
									system("cls");
								}
							}
						} while (op != 3);
					}
					else if (opcao3 == 4) {
						continue;
					}
					else {
						puts("Op��o inv�lida. Tente novamente!");
						getchar();
						while(getchar() != '\n')
						fflush(stdin);
						system("cls");
					}
			} while (opcao3 != 4);
		}
        printf("\b");
    } while (opcao != 5);
    return 0;
}
