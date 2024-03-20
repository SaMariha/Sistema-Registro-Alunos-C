#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *registrar(char **dado, char *tipoDado, int indice);
int buscar(char **dadoNome, char **dadoMatricula, int indice, char *dadoDaBusca, int escolhaNomeMatricula);
char* editar(int dadoEditar, int indice,char **dadoNome, char **dadoMatricula, char **dadoNascimento, char **dadoCurso);
int excluir(char **nomeAluno,char **matriculaAluno,char **nascimentoAluno,char **cursoAluno,int resultado, int contador);


int main(int argc, char *argv[]) {
    printf("SISTEMA DE REGISTRO DE ALUNOS - UNIVERSIDADE\n");
    char *nomeAluno[15]; // Array de ponteiros para char
    char *matriculaAluno[15];
	char *nascimentoAluno[15]; 
	char *cursoAluno[15]; // Array de ponteiros para char
    int servico = 0;
    int maximoRegistros = 15;
    char *tipoDado;
    int contQuantidadeAlunos = 0;
    int i=0;
    char continuar[2];
    int indice=0;
    int escolhaBuscaExclusao=0;
    char matricula[15];
    char nome[30];
    int dadoEditar=0;
    int matriculaInicial = 25664874;
    
    //Alocando memória para as strings
    for (i = 0; i < maximoRegistros; i++) {
        nomeAluno[i] = (char *)malloc(100 * sizeof(char));
        if (nomeAluno[i] == NULL) {
            printf("Erro ao alocar memória para a string %d.\n", i + 1);
            return 1;
        }
    }
	for (i = 0; i < maximoRegistros; i++) {
        matriculaAluno[i] = (char *)malloc(30 * sizeof(char));
        if (matriculaAluno[i] == NULL) {
            printf("Erro ao alocar memória para a string %d.\n", i + 1);
            return 1;
        }
    }
    for (i = 0; i < maximoRegistros; i++) {
        nascimentoAluno[i] = (char *)malloc(20 * sizeof(char));
        if (nascimentoAluno[i] == NULL) {
            printf("Erro ao alocar memória para a string %d.\n", i + 1);
            return 1;
        }
    }
    for (i = 0; i < maximoRegistros; i++) {
        cursoAluno[i] = (char *)malloc(100 * sizeof(char));
        if (cursoAluno[i] == NULL) {
            printf("Erro ao alocar memória para a string %d.\n", i + 1);
            return 1;
        }
    }

    //menu de opções
	do{
    printf("Digite a opcao que voce deseja: \n1: Registrar novos alunos.\n2: Buscar aluno pelo nome.\n3: Excluir algum aluno pelo nome ou matricula.\n4: Listar todos os alunos.\n5: Editar dados do aluno pelo nome ou matricula.\n6: Sair.\n");
    scanf("%d", &servico);

	getchar();
	
    switch (servico) {
            case 1:
                if (contQuantidadeAlunos < maximoRegistros) {
                    printf("\nVoce escolheu Registrar novos alunos.\n");
                    tipoDado = "nome";
                    registrar(nomeAluno, tipoDado, contQuantidadeAlunos); // Chama a função registrar passando o índice atual
                    sprintf(matriculaAluno[contQuantidadeAlunos], "%d", matriculaInicial++);
                    tipoDado = "data de nascimento no formato (dia/mes/ano)";
                    registrar(nascimentoAluno, tipoDado, contQuantidadeAlunos);
                    tipoDado="curso";
                    registrar(cursoAluno, tipoDado, contQuantidadeAlunos);
                    contQuantidadeAlunos++;
                    printf("Deseja continuar? 'S' para sim e 'N' para nao\n");
                    scanf(" %s", continuar);
                } else {
			    printf("Limite de registros atingido.\n");
				}
            break;
			case 2:
                printf("\nVoce escolheu buscar alunos. Digite 1 para inserir a matricula e 2 para inserir o nome\n");
                scanf("%d", &escolhaBuscaExclusao);
                
                if(escolhaBuscaExclusao==1){
                    printf("Digite a matricula: \n");
   					 getchar(); // Limpa o buffer do teclado
  					 fgets(matricula, sizeof(matricula), stdin); // Lê a matricula incluindo espaços em branco
   					 matricula[strcspn(matricula, "\n")] = '\0'; // Remove o caractere de nova linha
   					 int resultado = buscar(nomeAluno, matriculaAluno, contQuantidadeAlunos, matricula, escolhaBuscaExclusao);
   					 if(resultado == -1){
      					  printf("Aluno não encontrado\n");
   					 }else{
       						 printf("Matricula %s: %s\nData de nascimento: %s\nCurso: %s\n\n", matriculaAluno[resultado], nomeAluno[resultado],nascimentoAluno[resultado],cursoAluno[resultado]);
    				}
                }else if(escolhaBuscaExclusao==2){
                	printf("Digite o nome: \n");
    				getchar(); // Limpa o buffer do teclado
    				fgets(nome, sizeof(nome), stdin); // Lê o nome incluindo espaços em branco
    				nome[strcspn(nome, "\n")] = '\0'; 
                    int resultado=buscar(nomeAluno, matriculaAluno,contQuantidadeAlunos,nome,escolhaBuscaExclusao);
                    if(resultado==-1){
                        printf("Aluno não encontrado");
                    }else{
                        printf("Matricula %s: %s\nData de nascimento: %s\nCurso: %s\n\n", matriculaAluno[resultado], nomeAluno[resultado],nascimentoAluno[resultado],cursoAluno[resultado]);
                    }
				}else{
					printf("Opcao invalida");
				}
			break;
            case 3:
						printf("\nVoce escolheu excluir o registro de um aluno. Digite 1 para inserir a matricula e 2 para inserir o nome do aluno desejado\n");
						scanf("%d", &escolhaBuscaExclusao);
                		if(escolhaBuscaExclusao==1){
	                		printf("Digite a matricula: \n");
		                    scanf("%s", matricula);
		                    int resultado=buscar(nomeAluno, matriculaAluno,contQuantidadeAlunos,matricula, escolhaBuscaExclusao);
	                    if(resultado==-1){
	                        printf("Aluno não encontrado");
	                    }else{  
	                    	printf("Matricula %s: %s, data de nascimento: %s, curso: %s\n\n", matriculaAluno[resultado], nomeAluno[resultado],nascimentoAluno[resultado],cursoAluno[resultado]);
						contQuantidadeAlunos = excluir(nomeAluno, matriculaAluno, nascimentoAluno, cursoAluno,resultado,contQuantidadeAlunos);
						}
						}
                    break;
            case 4:
            	    printf("\nAlunos registrados:\n");
				    for (i = 0; i < contQuantidadeAlunos; i++) {
				        printf("Matricula %s: %s\nData de nascimento: %s\nCurso: %s\n\n", matriculaAluno[i], nomeAluno[i],nascimentoAluno[i],cursoAluno[i]);
				    }
				    printf("Deseja continuar? 'S' para sim e 'N' para nao\n");
                    scanf(" %s", continuar);
			break;
			case 5:
					printf("\nVoce escolheu editar dados dos alunos. Digite 1 para inserir a matricula e 2 para inserir o nome do aluno desejado\n");
                	scanf("%d", &escolhaBuscaExclusao);
                	if(escolhaBuscaExclusao==1){
                		printf("Digite a matricula: \n");
	                    scanf("%s", matricula);
	                    int resultado=buscar(nomeAluno, matriculaAluno,contQuantidadeAlunos,matricula, escolhaBuscaExclusao);
	                    if(resultado==-1){
	                        printf("Aluno não encontrado");
	                    }else{
	                        printf("Matricula %s: %s, data de nascimento: %s, curso: %s\n\n", matriculaAluno[resultado], nomeAluno[resultado],nascimentoAluno[resultado],cursoAluno[resultado]);
                    		printf("1: Nome.\n2: Data de nascimento.\n3: Curso do aluno.\nO que deseja editar: ");
                    		scanf("%d", &dadoEditar);
                    		getchar();
							editar(dadoEditar,resultado, nomeAluno, matriculaAluno, nascimentoAluno, cursoAluno);
							printf("Registro editado com sucesso!");
							printf("Matricula %s: %s\nData de nascimento: %s\nCurso: %s\n\n", matriculaAluno[resultado], nomeAluno[resultado],nascimentoAluno[resultado],cursoAluno[resultado]);	
						}
					}else if(escolhaBuscaExclusao==2){
						printf("Digite o nome: \n");
	                    scanf("%s", nome);
	                    int resultado=buscar(nomeAluno, matriculaAluno,contQuantidadeAlunos,nome, escolhaBuscaExclusao);
	                    if(resultado==-1){
	                        printf("Aluno não encontrado");
	                    }else{
	                        printf("Matricula %s: %s, data de nascimento: %s, curso: %s\n\n", matriculaAluno[resultado], nomeAluno[resultado],nascimentoAluno[resultado],cursoAluno[resultado]);
                    		printf("1: Nome.\n2: Data de nascimento.\n3: Curso do aluno.\nO que deseja editar: ");
                    		scanf("%d", &dadoEditar);
                    		getchar();
							editar(dadoEditar,resultado, nomeAluno, matriculaAluno, nascimentoAluno, cursoAluno);
							printf("Registro editado com sucesso!");
							printf("Matricula %s: %s\nData de nascimento: %s\nCurso: %s\n\n", matriculaAluno[resultado], nomeAluno[resultado],nascimentoAluno[resultado],cursoAluno[resultado]);	
						}
					}else{
						printf("Opcao invalida");
					}
				break;
					
				case 6:
						printf("Encerrando o programa...\n");
    					continuar[0] = 'N';
						continuar[1]='\0'; 
				break;
					
	}
    }while (strcmp(continuar, "S") == 0);
    // Libera memória alocada para nomeAluno
    for (i = 0; i < maximoRegistros; i++) {
        free(nomeAluno[i]);
    }
    for (i = 0; i < maximoRegistros; i++) {
        free(matriculaAluno[i]);
    }
    for (i = 0; i < maximoRegistros; i++) {
        free(nascimentoAluno[i]);
    }
	for (i = 0; i < maximoRegistros; i++) {
        free(cursoAluno[i]);
    }
    return 0;	
}

char *registrar(char **dado, char *tipoDado, int indice) {
    char temp[100];
	printf("%s do novo aluno: ", tipoDado);
    fgets(temp, sizeof(temp), stdin);

    // Removendo o caractere de nova linha ('\n') do final do nome, se presente
    size_t length = strlen(temp);
    if (temp[length - 1] == '\n') {
        temp[length - 1] = '\0';
    }

    strcpy(dado[indice], temp); // Copia a string para o índice indicado
    return dado[indice];
}

int buscar(char **dadoNome, char **dadoMatricula,int indice, char *dadoDaBusca, int escolhaNomeMatricula){
int i = 0;
int matriculaAtual, matriculaBuscada;   
    if (escolhaNomeMatricula == 1 || escolhaNomeMatricula == 2) {
        for (i = indice; i >= 0; i--) {
            if (escolhaNomeMatricula == 1) {
                if (strcmp(dadoMatricula[i], dadoDaBusca) == 0) {			
                    return i;
                }
            } else if (escolhaNomeMatricula == 2) {
                if (strcmp(dadoNome[i], dadoDaBusca) == 0) {
                    return i;
                }
            }
        }
    }
    return -1; // Retornar -1 caso a matrícula não seja encontrada
}

char* editar(int dadoEditar, int indice,char **dadoNome, char **dadoMatricula, char **dadoNascimento, char **dadoCurso){
	char temp[100];
	switch (dadoEditar){
		case 1:
			printf("Digite o novo nome do aluno: ");
			fgets(temp, sizeof(temp),stdin);
			
			size_t length = strlen(temp);
			if (temp[length - 1]=='\n'){
				temp[length -1] = '\0';
			}
	
    		strcpy(dadoNome[indice],temp);
    		
    		return (dadoNome[indice]);
    	break;
    	
    	case 2:
    		printf("Digite a nova data de nascimento do aluno: ");
			fgets(temp, sizeof(temp),stdin);
			
			length = strlen(temp);
			if (temp[length - 1]=='\n'){
				temp[length -1] = '\0';
			}
	
    		strcpy(dadoNascimento[indice],temp);
    		
    		return (dadoNascimento[indice]);
    	break;

		case 3:
    		printf("Digite o novo curso do aluno: ");
			fgets(temp, sizeof(temp),stdin);
			
			length = strlen(temp);
			if (temp[length - 1]=='\n'){
				temp[length -1] = '\0';
			}
	
    		strcpy(dadoCurso[indice],temp);
    		
    		return (dadoCurso[indice]);
    	break;
	}
    
}

int excluir(char **nomeAluno, char **matriculaAluno, char **nascimentoAluno, char **cursoAluno, int resultado, int contQuantidadeAlunos) {
    if (contQuantidadeAlunos > 0) {
        // Ajusta o índice para a última posição do array
        int posicao = resultado,i=0;

        
        // Move todos os elementos antes da última posição uma posição para trás
        for (i = posicao; i < contQuantidadeAlunos - 1; i++) {
        strcpy(nomeAluno[i], nomeAluno[i + 1]);
        strcpy(matriculaAluno[i], matriculaAluno[i + 1]);
        strcpy(nascimentoAluno[i], nascimentoAluno[i + 1]);
        strcpy(cursoAluno[i], cursoAluno[i + 1]);
    }
		// Libera a memória associada aos dados do último aluno
        free(nomeAluno[contQuantidadeAlunos-1]);
        free(matriculaAluno[contQuantidadeAlunos-1]);
        free(nascimentoAluno[contQuantidadeAlunos-1]);
        free(cursoAluno[contQuantidadeAlunos-1]);

        // Decrementa o contador de quantidade de alunos
        contQuantidadeAlunos--;

        printf("\nRegistro do aluno excluido com sucesso!\n\n");
        return contQuantidadeAlunos;
    } else {
        printf("Não há alunos para excluir.\n");
        return -1;
    }
}