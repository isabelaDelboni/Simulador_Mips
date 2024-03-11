//bibliotecas
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//nao existe o uso de defines, pois prefiri o uso da comparacao e conversao do opcode para codigo na codificacao

//dados da instrucao
struct instrucao {
    char opcode[4];
    long long int binario;
    int rt;
    int rd;
    char endereco[6];
    char imediato[6];
    int pc;
    int sp;
};

//inicialização das etapas do processador
int etapaAtual = 0;

//constante com array para os nomes das etapas
const char *nomeEtapa[5] = {
        "Inicializacao",
        "Leitura",
        "Decodificacao",
        "Execucao",
        "Exibicao_de_Resultados"
};

//prototipos das funcoes
void imprimirEtapas();
int leituraInstrucao(struct instrucao *instrucao, int opcao);
void imprimirFormaEstrutural(struct instrucao *instrucao, int opcao);
int executarInstrucao(struct instrucao *instrucao);
void exibirResposta(struct instrucao *instrucao, int opcao, int result);
void decodificar(struct instrucao *instrucao);

int main(){

    //declaracoes
    struct instrucao instrucao;
    int opcao, resultado;

    //opcoes de formato
    printf("\n Voce deseja um instrucao no formato R, I ou J: ");
    printf("\n 1 - Formato R (ex: ADD $s1, $s2, $s3): ");
    printf("\n 2 - Formato I (ex: LW $s1, 100 ($s2): ");
    printf("\n 3 - Formato J (ex: J label): \n");
    scanf("%d", &opcao);
    fflush(stdin);

    system("cls");

    //etapa 1
    etapaAtual = 0;
    imprimirEtapas();
    //invoca a funcao

    //funcao para leitura
    leituraInstrucao(&instrucao, opcao);

    //"delay"
    system("cls");//apaga a tela anterior

    //funcao das impressoes
    imprimirFormaEstrutural(&instrucao, opcao);

    sleep(3);
    system("cls");

    //etapa 2
    etapaAtual = 1;
    imprimirEtapas();
    fflush(stdin);

    sleep(3);
    system("cls");

    //etapa 3
    etapaAtual = 2;
    imprimirEtapas();
    fflush(stdin);

    //decodificacao da instrucao
    decodificar(&instrucao);

    sleep(3);
    system("cls");

    //etapa 4
    etapaAtual = 3;
    imprimirEtapas();

    //funcao para execucao da instrucao, voltando o resultado
    resultado = executarInstrucao(&instrucao);

    sleep(3);
    system("cls");

    //etapa 5
    etapaAtual = 4;
    imprimirEtapas();
    fflush(stdin);

    //funcao para imprimir os valores
    exibirResposta(&instrucao, opcao, resultado);

    return 0;
};

void imprimirEtapas(){

  //impressao da impressao na tela
  printf("\n Etapa %d (%s) ! ", etapaAtual + 1, nomeEtapa[etapaAtual]);
  printf("\n");

};

int leituraInstrucao(struct instrucao *instrucao, int opcao){

    //opcao de escolha para os 3 formatos
    switch (opcao) {
        case 1:
            printf("\n Digite o opcode da instrucao: ");
            scanf("%s", instrucao->opcode);
            fflush(stdin);

            printf("\n Valor de Rt: ");
            scanf("%d", &instrucao->rt);

            printf("\n Valor de Rd: ");
            scanf("%d", &instrucao->rd);
            break;

        case 2:
            printf("\n Digite o opcode da instrucao: ");
            scanf("%s", instrucao->opcode);
            fflush(stdin);

            printf("\n Valor de Rt: ");
            scanf("%d", &instrucao->rt);

            printf("\n Valor de Rd: ");
            scanf("%d", &instrucao->rd);

            printf("\n Valor imediato: ");
            scanf("%s", instrucao->imediato);
            fflush(stdin);
            break;

        case 3:
            printf("\n Digite o opcode da instrucao: ");
            scanf("%s", instrucao->opcode);
            fflush(stdin);

            printf("\n Valor de endereco: ");
            scanf("%s", instrucao->endereco);
            fflush(stdin);
            break;
    };

};

void imprimirFormaEstrutural(struct instrucao *instrucao, int opcao) {

    switch(opcao){
        case 1:
            printf("\n Forma Estrutural: %s $t0, $t1, $t2 ", instrucao->opcode);

            printf("\n Forma Estrutural com valores decimais: %s 0, %d, %d ", instrucao->opcode, instrucao->rt, instrucao->rd);
            //O rs está com o valor 0, pois como ainda não foi executada

            break;

        case 2:
            printf("\n Forma Estrutural: %s $t0, 000 ($t2) ", instrucao->opcode);

            printf("\n Forma Estrutural com valores decimais: %s 0, %d (%s) ", instrucao->opcode, instrucao->rt, instrucao->imediato);
            //O rs está com o valor 0, pois como ainda não foi executada

            break;

        case 3:
            printf("\n Forma Estrutural: %s %s ", instrucao->opcode, instrucao->endereco);

            break;
    };

};
void decodificar(struct instrucao *instrucao){

    //comparacao para confirmar o opcode com os seus devidos códigos
    if(strcmp("ADD", instrucao->opcode)==0) {
        instrucao->binario = 0x00; //salvamento do opcode como cosigo para conseguir executar na proxima etapa
    }
    else if (strcmp("SUB", instrucao->opcode)==0) {
        instrucao->binario = 0x01;
    }
    else if (strcmp("AND", instrucao->opcode)==0) {
        instrucao->binario = 0x02;
    }
    else if (strcmp("DIV", instrucao->opcode)==0) {
        instrucao->binario = 0x03;
    }
    else if (strcmp("MUL", instrucao->opcode)==0) {
        instrucao->binario = 0x04;
    }
    else if (strcmp("SLT", instrucao->opcode)==0) {
        instrucao->binario = 0x05;
    }
    else if (strcmp("SLL", instrucao->opcode)==0) {
        instrucao->binario = 0x06;
    }
    else if (strcmp("SRL", instrucao->opcode)==0) {
        instrucao->binario = 0x07;
    }
    else if (strcmp("ADDI", instrucao->opcode)==0) {
        instrucao->binario = 0x08;
    }
    else if (strcmp("ANDI", instrucao->opcode)==0) {
        instrucao->binario = 0x09;
    }
    else if (strcmp("ORI", instrucao->opcode)==0) {
        instrucao->binario = 0x0a;
    }
    else if (strcmp("XORI", instrucao->opcode)==0) {
        instrucao->binario = 0x0b;
    }
    else if (strcmp("SLTI", instrucao->opcode)==0) {
        instrucao->binario = 0x0c;
    }
    else if (strcmp("SLLI", instrucao->opcode)==0) {
        instrucao->binario = 0x0d;
    }
    else if (strcmp("SLRI", instrucao->opcode)==0) {
        instrucao->binario = 0x0e;
    }
    else if (strcmp("LW", instrucao->opcode)==0) {
        instrucao->binario = 0x23;
    }
    else if (strcmp("SW", instrucao->opcode)==0) {
        instrucao->binario = 0x2b;
    }
    else if (strcmp("J", instrucao->opcode)==0) {
        instrucao->binario = 0x25;
    }
    else if (strcmp("JAL", instrucao->opcode)==0) {
        instrucao->binario = 0x26;
    };

};

int executarInstrucao(struct instrucao *instrucao){
    int result;
    int efetivo;
    instrucao->pc = 0;
//sistema de opcao por switch para ser mais facil e flexivel a mudancas
        switch (instrucao->binario) {
            case 0x00://aqui comeca as execucoes das instrucoes do tipo R
                instrucao->pc += 4; // adicionando ao valor do PC
                result = instrucao->rt+ instrucao->rd; //operacao, podendo algumas instrucoes voltarem com valor 0,
                break;                              //pois precisaria de mais do que uma instrucao (foi pedida apenas uma), mas se
            case 0x01:                              //necessario e so    adicionar um laco no main de repeticao e dependendo ate um vetor
                instrucao->pc += 4;
                result = instrucao->rt - instrucao->rd;
                break;
            case 0x02:
                instrucao->pc += 4;
                result = instrucao->rt & instrucao->rd;
                break;
            case 0x03:
                instrucao->pc += 4;
                result = instrucao->rt / instrucao->rd;
                break;
            case 0x04:
                instrucao->pc += 4;
                result = instrucao->rt * instrucao->rd;
                break;
            case 0x05:
                instrucao->pc += 4;
                result = (instrucao->rt < instrucao->rd) ? 1 : 0;
                break;
            case 0x06:
                instrucao->pc += 4;
                result = instrucao->rt << instrucao->rd;
                break;
            case 0x07:
                instrucao->pc += 4;
                result = instrucao->rt >> instrucao->rd;
                break;
            case 0x08:      //aqui ja comeca a exucucao das instrucoes do tipo i
                instrucao->pc += 4;
                result = instrucao->rd + atoi(instrucao->imediato);
                break;//funcao atoi transforma string em numero inteiro
            case 0x09:
                instrucao->pc += 4;
                result = instrucao->rd & atoi(instrucao->imediato);
                break;
            case 0x0a:
                instrucao->pc += 4;
                result = instrucao->rd | atoi(instrucao->imediato);
                break;
            case 0x0b:
                instrucao->pc += 4;
                result = instrucao->rd ^ atoi(instrucao->imediato);
                break;
            case 0x0c:
                instrucao->pc += 4;
                result = instrucao->rd < atoi(instrucao->imediato) ? 1 : 0 ;
                break;
            case 0x0d:
                instrucao->pc += 4;
                result = instrucao->rd << atoi(instrucao->imediato);
                break;
            case 0x0e:
                instrucao->pc += 4;
                result = instrucao->rd >> atoi(instrucao->imediato);
                break;
            case 0x23:
                instrucao->pc += 4;
                efetivo = instrucao->rt + atoi(instrucao->imediato);
                result = *(int *) (efetivo);
                break;
            case 0x2b:
                instrucao->pc += 4;
                efetivo = instrucao->rt + atoi(instrucao->imediato);
                *(int *) (efetivo) = instrucao->rd;
                result = instrucao->rd;
                break;
            case 0x25:      //aqui comeca a execucao das instrucoes do tipo j
                instrucao->pc += 4;
                instrucao->pc = atoi(instrucao->endereco);//Resultados das instrucoes do tipo j salvas no pc
                break;
            case 0x26:
                instrucao->pc = atoi(instrucao->endereco);
                instrucao->sp -= 4;
                *(int *) (instrucao->sp) = instrucao->pc + 4;
                instrucao->pc += 4;
                break;
        };
    return result;//voltando valor dos resultados

};

void exibirResposta(struct instrucao *instrucao, int opcao, int result){
    //impressao dos resultados
    fflush(stdin);
    switch (opcao) {
        case 1:
            printf("\n Forma Estrutural em forma final: %s %d, %d, %d ", instrucao->opcode, result, instrucao->rt, instrucao->rd);
            printf("\n Resultado final da instrucao: %d", result);//resultado da operacao
            printf("\n Valor atual do PC: %d", instrucao->pc);
            break;

        case 2:
        	fflush(stdin);
            printf("\n Forma Estrutural em forma final: %s %d, %d (%s) ", instrucao->opcode, result, instrucao->rt, instrucao->imediato);
            printf("\n Valor atual do PC: %d", instrucao->pc);
            break;

        case 3:
            printf("\n Forma Estrutural final: %s %s ", instrucao->opcode, instrucao->endereco);
            fflush(stdin);
            printf("\n Valor atual do PC: %d ", instrucao->pc);
            break;
    }
};
