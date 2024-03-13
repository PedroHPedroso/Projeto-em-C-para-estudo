#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MATERIAS 5

typedef struct aluno {
    int quant;
    char materias[MAX_MATERIAS][30];
    int notas[MAX_MATERIAS][4];
    char nomeAluno[256];
    int idade;
    int numeroMatricula;
    int total[MAX_MATERIAS];
    int media[MAX_MATERIAS];
} Aluno;

void informacoesAluno(){
    Aluno aluno;
    FILE* arquivo;
    arquivo = fopen("arquivo.bin", "ab");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo \n");
    }

    else {
        printf("Insira o nome do aluno: \t");
        fgets(aluno.nomeAluno, sizeof(aluno.nomeAluno),stdin);
        printf("Insira a idade do aluno:\t");
        scanf("%d", &aluno.idade);
        printf("Insira o numero de matricula do aluno:\t");
        scanf("%d", &aluno.numeroMatricula);
        printf("Qual a quantidade de materias que o aluno possui:\n");
        scanf("%d", &aluno.quant);
        printf("");
        printf("OK, ALUNO REGISTRADO COM SUCESSO\n");
        for (int i = 0; i < aluno.quant; i++) {
            printf("Digite o nome da materia %d: ", i + 1);
            getchar();
            fgets(aluno.materias[i], sizeof(aluno.materias[i]), stdin);

            printf("Insira as 4 notas do aluno na materia %s:\n", aluno.materias[i]);
            // Inicializar total e media
            aluno.total[i] = 0;
            aluno.media[i] = 0;
            for (int j = 0; j < 4; j++) {
                printf("Nota %d: ", j + 1);
                scanf("%d", &aluno.notas[i][j]);
                aluno.total[i] += aluno.notas[i][j];
            }
            aluno.media[i] = aluno.total[i] / 4 ;
            printf("Media do aluno %s :\t%d\n", aluno.nomeAluno, aluno.media[i]);
            printf("\n");

            if(aluno.media[i] >= 70){
                printf("O aluno esta aprovado.\n");
            }
            if(aluno.media[i] <= 39){
                printf("O aluno esta reprovado.\n");
            }
            if(aluno.media[i] >= 40 && aluno.media[i] < 70){
                printf("O aluno esta de exame.\n");
            }
        }
        fwrite(&aluno, sizeof(Aluno), 1, arquivo);
    }
    fclose(arquivo);
}


void mostrarAlunos(){
    Aluno aluno;
    FILE* arquivo;
    arquivo = fopen("arquivo.bin", "rb");
    if(arquivo == NULL){
        printf("Arquivo nao encontrado");
    }

    else{
        while(fread(&aluno, sizeof(Aluno),1,arquivo)){
            printf("Nome do aluno:\t%s\n", aluno.nomeAluno);
            printf("Idade do aluno:\t%d\n",aluno.idade);
            printf("Numero de matricula:\t%d\n",aluno.numeroMatricula);
            for (int i = 0; i < aluno.quant; i++) {
                printf("Materia: %s\n", aluno.materias[i]);
                printf("Notas: ");
                for (int j = 0; j < 4; j++) {
                    printf("%d ", aluno.notas[i][j]);
                }
                printf("\n");
                printf("Media: %d\n", aluno.media[i]);
                printf("\n");
            }
        }
        fseek(arquivo,0,SEEK_SET);
        fclose(arquivo);
    }
}

void alterarAluno(int matricula){
    Aluno aluno;
    FILE *arquivo;
    arquivo = fopen("arquivo.bin", "rb+");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo \n");
    } else {
        while(fread(&aluno, sizeof(Aluno), 1, arquivo)){
            if(aluno.numeroMatricula == matricula){
                int opcao;
                printf("Escolha o dado que deseja alterar:\n");
                printf("1 - Nome\n");
                printf("2 - Idade\n");
                printf("3 - Numero de matricula\n");
                printf("4 - Notas e materias\n");
                printf("Opcao: ");
                scanf("%d", &opcao);
                switch(opcao){
                    case 1:
                        printf("Digite o novo nome: ");
                        getchar(); // Limpar o buffer do teclado
                        fgets(aluno.nomeAluno, sizeof(aluno.nomeAluno), stdin);
                        break;
                    case 2:
                        printf("Digite a nova idade: ");
                        scanf("%d", &aluno.idade);
                        break;
                    case 3:
                        printf("Digite o novo numero de matricula: ");
                        scanf("%d", &aluno.numeroMatricula);
                        break;
                    case 4:
                        printf("Digite a quantidade de materias que o aluno possui: ");
                        scanf("%d", &aluno.quant);
                        for (int i = 0; i < aluno.quant; i++) {
                            printf("Digite o nome da materia %d: ", i + 1);
                            getchar();
                            fgets(aluno.materias[i], sizeof(aluno.materias[i]), stdin);

                            printf("Insira as 4 notas do aluno na materia %s:\n", aluno.materias[i]);
                            for (int j = 0; j < 4; j++) {
                                printf("Nota %d: ", j + 1);
                                scanf("%d", &aluno.notas[i][j]);
                                aluno.total[i] += aluno.notas[i][j];
                            }
                            aluno.media[i] = aluno.total[i] / 4 ;
                            printf("Media do aluno %s :\t%d\n", aluno.nomeAluno, aluno.media[i]);
                            printf("\n");

                            if(aluno.media[i] >= 70){
                                printf("O aluno esta aprovado.\n");
                            }
                            if(aluno.media[i] <= 39){
                                printf("O aluno esta reprovado.\n");
                            }
                            if(aluno.media[i] >= 40 && aluno.media[i] < 70){
                                printf("O aluno esta de exame.\n");
                            }
                        }
                        break;
                    default:
                        printf("Opcao invalida.\n");
                        break;
                }
                fseek(arquivo, -sizeof(Aluno), SEEK_CUR);
                fwrite(&aluno, sizeof(Aluno), 1, arquivo);
                break;
            }
        }
        fclose(arquivo);
        printf("Registro alterado com sucesso\n");
    }
}

void mostrarAlunosMatriz(){
    Aluno aluno;
    FILE* arquivo;
    arquivo = fopen("arquivo.bin", "rb");
    if(arquivo == NULL){
        printf("Arquivo nao encontrado");
    }

    else{
        while(fread(&aluno, sizeof(Aluno),1,arquivo)){
            printf("Nome do aluno:\t%s\n", aluno.nomeAluno);
            printf("Idade do aluno:\t%d\n",aluno.idade);
            printf("Numero de matricula:\t%d\n",aluno.numeroMatricula);
            printf("Materias\tNota1\tNota2\tNota3\tNota4\tMedia\n");
            for (int i = 0; i < aluno.quant; i++) {
                printf("%s\t", aluno.materias[i]);
                for (int j = 0; j < 4; j++) {
                    printf("%d\t", aluno.notas[i][j]);
                }
                printf("%d\n", aluno.media[i]);
            }
        }
        fseek(arquivo,0,SEEK_SET);
        fclose(arquivo);
    }
}

void deletarAluno(int matricula){
    Aluno aluno;
    FILE* arquivo;
    FILE* arquivoTemp;
    arquivo = fopen("arquivo.bin","rb");
    arquivoTemp = fopen("arquivoTemp.bin","wb");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo \n");
    } else {
        while(fread(&aluno, sizeof(Aluno), 1, arquivo)){
            if(aluno.numeroMatricula != matricula){
                fwrite(&aluno, sizeof(Aluno), 1, arquivoTemp);
            }
            else{
                printf("Aluno %s excluido com sucesso\n", aluno.nomeAluno);
            }
        }
    }
    fclose(arquivo);
    fclose(arquivoTemp);
    remove("arquivo.bin");
    rename("arquivoTemp.bin", "arquivo.bin");
}

int main()
{
    int opcao = 0;
    int matricula = 0;

    while(1){
        printf("Digite a opcao que deseja:\n");
        printf("0 - Para parar\n");
        printf("1 - Para adicionar mais alunos\n");
        printf("2 - Para mostrar os alunos cadastrados\n");
        printf("3 - Alterar registro de aluno por matricula\n");
        printf("4 - Mostrar alunos em forma de matriz\n");
        printf("5 - Para deletar um aluno por completo\n");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 0:
                return 0;
            break;

            case 1:
                informacoesAluno();
            break;

            case 2:
                mostrarAlunos();
            break;

            case 3:
                printf("Digite a matricula do aluno que deseja alterar: ");
                scanf("%d", &matricula);
                alterarAluno(matricula);
            break;

            case 4:
                mostrarAlunosMatriz();
            break;

            case 5:
                printf("Indique a matricula do aluno para ser deletado:\t");
                scanf("%d",&matricula);
                deletarAluno(matricula);
            break;

            default:
            printf("Opcao Invalida\n");
            break;
        }
    }

    return 0;
}
