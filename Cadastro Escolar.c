#include <stdio.h>  //bibliotecas usadas
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_INICIAL 100  //define a quantidade maxima de cadastros

//estrutura que representa os dados de um aluno
typedef struct {
	char nome[100];
	char data[100];
	char telefone[100];
	char curso[100];
	char turma[100];
	char unidade[100];
	char endereco[100];
	int matricula;
	float notas[4]; //as tres primeiras sao provas e a quarta a media
} Aluno;

int compararPorNome(const void *a, const void *b) {
	return strcmp(((Aluno*)a)->nome, ((Aluno*)b)->nome);
}
int compararPorData(const void *a, const void *b) {
	return strcmp(((Aluno*)a)->data, ((Aluno*)b)->data);
}
int main() {
	setlocale(LC_ALL, "Portuguese"); //define a lingua para portugues

	//alocacao de memoria para os alunos
	Aluno *alunos = (Aluno *)malloc(MAX_INICIAL * sizeof(Aluno));
	int capacidade = MAX_INICIAL;
	int cadastros = 0; //quantidade de alunos cadastrados
	int opcao, i, j, k;

	//verifica se a alocacao funcionou corretamente
	if (alunos == NULL) {
		printf("erro ao alocar memoria.\n");
		return 1;
	}

	//loop do menu
	do {
		printf("\ncadastro escolar\n\n");
		printf("1 - cadastrar aluno\n");
		printf("2 - editar cadastro\n");
		printf("3 - excluir cadastro\n");
		printf("4 - consultar cadastro\n");
		printf("5 - sair\n");
		printf("6 - ordenar cadastros\n\n");
		printf("digite a opcao desejada: ");
		scanf("%d", &opcao);//opcoes de escolha no cadastro
		getchar();

		switch (opcao) {
		case 1: { //inicio do cadastro do aluno
			int acao;
			printf("deseja realizar o cadastro?\n");
			printf("1 - sim    0 - naon");
			scanf("%d", &acao);
			getchar();

			if (acao == 1) {
				//se o numero de cadastros ultrapassar a capacidade ele coloca mais memoria
				if (cadastros >= capacidade) {
					capacidade += MAX_INICIAL;
					Aluno *temp = (Aluno *)realloc(alunos, capacidade * sizeof(Aluno));
					if (temp == NULL) {
						printf("erro ao redimensionar memoria!\n");
						free(alunos);
						return 1;
					}
					alunos = temp;
				}

				//coleta os dados do aluno
				printf("\npreencha as informacoes:\n");

				printf("nome do aluno: ");
				fgets(alunos[cadastros].nome, 100, stdin);
				alunos[cadastros].nome[strcspn(alunos[cadastros].nome, "\n")] = 0;

				printf("data de nascimento: ");
				fgets(alunos[cadastros].data, 100, stdin);
				alunos[cadastros].data[strcspn(alunos[cadastros].data, "\n")] = 0;

				printf("numero de telefone: ");
				fgets(alunos[cadastros].telefone, 100, stdin);
				alunos[cadastros].telefone[strcspn(alunos[cadastros].telefone, "\n")] = 0;

				printf("curso: ");
				fgets(alunos[cadastros].curso, 100, stdin);
				alunos[cadastros].curso[strcspn(alunos[cadastros].curso, "\n")] = 0;

				printf("turma: ");
				fgets(alunos[cadastros].turma, 100, stdin);
				alunos[cadastros].turma[strcspn(alunos[cadastros].turma, "\n")] = 0;

				printf("unidade curricular: ");
				fgets(alunos[cadastros].unidade, 100, stdin);
				alunos[cadastros].unidade[strcspn(alunos[cadastros].unidade, "\n")] = 0;

				printf("endereco: ");
				fgets(alunos[cadastros].endereco, 100, stdin);
				alunos[cadastros].endereco[strcspn(alunos[cadastros].endereco, "\n")] = 0;

				printf("matricula: ");
				scanf("%d", &alunos[cadastros].matricula);
				getchar();

				//coleta as notas
				printf("nota da primeira prova: ");
				scanf("%f", &alunos[cadastros].notas[0]);
				printf("nota da segunda prova: ");
				scanf("%f", &alunos[cadastros].notas[1]);
				printf("nota da terceira prova: ");
				scanf("%f", &alunos[cadastros].notas[2]);
				getchar();

				//faz o calculo da media
				alunos[cadastros].notas[3] =
				    (alunos[cadastros].notas[0] + alunos[cadastros].notas[1] + alunos[cadastros].notas[2]) / 3.0;

				//mostra a situacao do aluno
				if (alunos[cadastros].notas[3] >= 7.0) {
					printf("esse aluno esta: aprovado\n");
				} else if (alunos[cadastros].notas[3] > 4.0) {
					printf("esse aluno esta: em recuperaocao\n");
				} else {
					printf("esse aluno esta: reprovado\n");
				}

				cadastros++; //incrementa o numero de cadastros
				printf("\ncadastro feito!\n");
			}
			break;
		}

		case 2: { //edicao de cadastro
			if (cadastros > 0) {
				int matriculaBusca, acao;
				printf("digite o numero da matricula para editar: ");
				scanf("%d", &matriculaBusca);
				getchar();

				for (i = 0; i < cadastros; i++) {
					if (alunos[i].matricula == matriculaBusca) {
						printf("deseja editar este cadastro?\n");
						printf("1 - sim    0 - nao\n");
						scanf("%d", &acao);
						getchar();

						if (acao == 1) {
							printf("\nqual das informacoes deseja editar?\n");
							printf("0 - nome\n1 - data\n2 - telefone\n3 - curso\n4 - turma\n5 - unidade\n6 - endereco\n7 - matricula\n8 - nota 1\n9 - nota 2\n10 - nota 3\n");
							scanf("%d", &acao);
							getchar();

							//edicao conforme escolha
							switch (acao) {
							case 0:
								printf("digite o novo nome: ");
								fgets(alunos[i].nome, 100, stdin);
								alunos[i].nome[strcspn(alunos[i].nome, "\n")] = 0;
								break;
							case 1:
								printf("digite a nova data: ");
								fgets(alunos[i].data, 100, stdin);
								alunos[i].data[strcspn(alunos[i].data, "\n")] = 0;
								break;
							case 2:
								printf("digite o novo telefone: ");
								fgets(alunos[i].telefone, 100, stdin);
								alunos[i].telefone[strcspn(alunos[i].telefone, "\n")] = 0;
								break;
							case 3:
								printf("digite o novo curso: ");
								fgets(alunos[i].curso, 100, stdin);
								alunos[i].curso[strcspn(alunos[i].curso, "\n")] = 0;
								break;
							case 4:
								printf("digite a nova turma: ");
								fgets(alunos[i].turma, 100, stdin);
								alunos[i].turma[strcspn(alunos[i].turma, "\n")] = 0;
								break;
							case 5:
								printf("digite a nova unidade: ");
								fgets(alunos[i].unidade, 100, stdin);
								alunos[i].unidade[strcspn(alunos[i].unidade, "\n")] = 0;
								break;
							case 6:
								printf("digite o novo endereco: ");
								fgets(alunos[i].endereco, 100, stdin);
								alunos[i].endereco[strcspn(alunos[i].endereco, "\n")] = 0;
								break;
							case 7:
								printf("digite a nova matricula: ");
								scanf("%d", &alunos[i].matricula);
								getchar();
								break;
							case 8:
								printf("digite a nova nota 1: ");
								scanf("%f", &alunos[i].notas[0]);
								getchar();
								break;
							case 9:
								printf("digite a nova nota 2: ");
								scanf("%f", &alunos[i].notas[1]);
								getchar();
								break;
							case 10:
								printf("digite a nova nota 3: ");
								scanf("%f", &alunos[i].notas[2]);
								getchar();
								break;
							}

							//atualiza a media
							alunos[i].notas[3] =
							    (alunos[i].notas[0] + alunos[i].notas[1] + alunos[i].notas[2]) / 3.0;

							if (alunos[i].notas[3] >= 7.0) {
								printf("esse aluno esta: aprovado\n");
							} else if (alunos[i].notas[3] > 4.0) {
								printf("esse aluno esta: em recuperacao\n");
							} else {
								printf("esse aluno esta: reprovado\n");
							}

							printf("\ncadastro editado com sucesso!\n");
						}

						break;
					}
				}

				if (i == cadastros) {
					printf("\nnumero de matricula nao encontrada!\n");
				}
			} else {
				printf("\nnenhum cadastro foi encontrado!\n");
			}
			break;
		}

		case 3: { //exclusao de cadastro
			if (cadastros > 0) {
				int matriculaBusca, acao;
				printf("digite o numero da matricula para excluir: ");
				scanf("%d", &matriculaBusca);
				getchar();

				for (i = 0; i < cadastros; i++) {
					if (alunos[i].matricula == matriculaBusca) {
						printf("deseja excluir esse cadastro?\n");
						printf("1 - sim    0 - nao\n");
						scanf("%d", &acao);
						getchar();

						if (acao == 1) {
							for (j = i; j < cadastros - 1; j++) {
								alunos[j] = alunos[j + 1]; //move os cadastros para cima
							}
							cadastros--; //reduz o total
							printf("\ncadastro excluido.\n");
						}

						break;
					}
				}

				if (i == cadastros) {
					printf("\nmatricula nao encontrada.\n");
				}
			} else {
				printf("\nnenhum cadastro foi encontrado.\n");
			}
			break;
		}

		case 4: { //consulta de todos os cadastros
			if (cadastros > 0) {
				printf("\nlista de cadastros\n");

				for (i = 0; i < cadastros; i++) {
					printf("\ncadastro %d\n", i + 1);
					printf("nome: %s\n", alunos[i].nome);
					printf("data: %s\n", alunos[i].data);
					printf("telefone: %s\n", alunos[i].telefone);
					printf("curso: %s\n", alunos[i].curso);
					printf("turma: %s\n", alunos[i].turma);
					printf("unidade: %s\n", alunos[i].unidade);
					printf("endereco: %s\n", alunos[i].endereco);
					printf("matricula: %d\n", alunos[i].matricula);
					printf("nota 1: %.2f\n", alunos[i].notas[0]);
					printf("nota 2: %.2f\n", alunos[i].notas[1]);
					printf("nota 3: %.2f\n", alunos[i].notas[2]);
					printf("media: %.2f\n", alunos[i].notas[3]);

					if (alunos[i].notas[3] >= 7.0) {
						printf("esse aluno esta: aprovado.\n");
					} else if (alunos[i].notas[3] > 4.0) {
						printf("esse aluno esta: em recuperacao.\n");
					} else {
						printf("esse aluno esta: reprovado.\n");
					}
				}
			} else {
				printf("\nnenhum cadastro foi encontrado\n");
			}
			break;
		}

		case 5: {
			printf("\nsalvando dados no arquivo...\n");
			FILE *arquivo = fopen("cadastros.txt", "w"); //abre um arquivo txt para armazenar

			if (arquivo == NULL) { //verifica se esta sendo aberto corretamente
				printf("erro ao criar o arquivo!\n");
			} else {
				for (i = 0; i < cadastros; i++) {
					fprintf(arquivo, "Cadastro %d\n", i + 1);
					fprintf(arquivo, "Nome: %s\n", alunos[i].nome);
					fprintf(arquivo, "Data: %s\n", alunos[i].data);
					fprintf(arquivo, "Telefone: %s\n", alunos[i].telefone);
					fprintf(arquivo, "Curso: %s\n", alunos[i].curso);
					fprintf(arquivo, "Turma: %s\n", alunos[i].turma);
					fprintf(arquivo, "Unidade: %s\n", alunos[i].unidade);
					fprintf(arquivo, "Endereco: %s\n", alunos[i].endereco);
					fprintf(arquivo, "Matricula: %d\n", alunos[i].matricula);
					fprintf(arquivo, "Nota 1: %.2f\n", alunos[i].notas[0]);
					fprintf(arquivo, "Nota 2: %.2f\n", alunos[i].notas[1]);
					fprintf(arquivo, "Nota 3: %.2f\n", alunos[i].notas[2]);
					fprintf(arquivo, "Media: %.2f\n", alunos[i].notas[3]);
					fprintf(arquivo, "---------------------------\n");
				}
				fclose(arquivo); //o fclose garante que o arquivo seja fechado apos o final do programa
				printf("dados salvos com sucesso em 'cadastros.txt'.\n");
			}

			printf("\nmuito obrigado, adios!\n");
			break;
		}


		case 6: {
			if (cadastros > 0) {
				int criterio;
				printf("\nordenar cadastros por:\n");
				printf("1 - nome\n");
				printf("2 - data de nascimento\n");
				printf("digite a opcao: ");
				scanf("%d", &criterio);
				getchar();

				if (criterio == 1) {
					qsort(alunos, cadastros, sizeof(Aluno), compararPorNome);
					printf("cadastros ordenados por nome!\n");
				} else if (criterio == 2) {
					qsort(alunos, cadastros, sizeof(Aluno), compararPorData);
					printf("cadastros ordenados por data de nascimento!\n");
				} else {
					printf("opcao invalida!\n");
				}
			} else {
				printf("nenhum cadastro foi encontrado para ordenar.\n");
			}
			break;
		}

		default: {
			printf("\nopcao invalida!\n");
		}
		}

	} while (opcao != 5); //repete ate o usuario escolher sair

	free(alunos); //libera a memoria alocada
	return 0;
}