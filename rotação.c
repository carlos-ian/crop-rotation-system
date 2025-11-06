//Bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Máximo de plantações para rotação
#define MAX 100

/* Sugestão de futura implementaão
typedef enum {
    ANUAL,      // Completa o ciclo em 1 ano (Soja)
    BIENAL,     // Completa o ciclo em 2 anos (Cenoura)
    PERENE      // Vive por muitos anos (Laranja)
} CicloVida; */

//Definindo os tipos de plantação
typedef enum{
    Leguminosas,    // Definido para 0
    Cereal,         // Definido para 1
    Hortaliça,      // Definido para 2
    Frutifera,      // Definido para 3
    Outro           // Definido para 4
} categoriaPlanta;

//Struct para data
typedef struct {
 int dia;
 int mes;
 int ano;
}data;


//Definindo os dados de plantação
typedef struct{
    int cod;
    char cultivo [40];
    bool irrigado;
    categoriaPlanta tipo;
    data data_plantio;
    data colheita;
    float produtividade;
}plantacao;

//lista que será armazenada o plantio
typedef struct {
    plantacao elem[MAX];
    int primeiro;
    int ultimo;
}plantio;

//Funções para o projeto

// 1. Criar plantio vazio
void criar_plantio_vazio(plantio *p){
    p -> primeiro = 0;
    p -> ultimo = p -> primeiro;
} /* atribuindo o valor de 0 para ambos */

// 2. Verificando se plantio está vazio
int verifica_plantio_vazio (plantio p){
    if (p.primeiro == p.ultimo){
        return 1;
    }else{
        return 0;
    }
}

// 3. Verificando se plantio está cheio
int verifica_plantio_cheio(plantio p){
    if (p.ultimo == MAX){
        return 1;
    }else{
        return 0;
    }
}

// Função de limpeza
void remover_newline(char *str){
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n'){
        str[len - 1] = '\0';
    }
}

// 4. Ler a plantação
void ler_plantacao(plantacao *p){
    int tipo_int;
    char resposta_irrigado;

    printf("\n------- Cadastro de Nova Plantacao -------\n");

    // 4.1. Código
    printf("Digite o Codigo (ID) da planatacao: ");
    scanf("%d", &p -> cod);
    getchar();

    // 4.2 Cultivo
    printf("Digite o nome do cultivo (Ex: Milho, soja): ");
    fgets(p -> cultivo, 40, stdin);
    remover_newline(p -> cultivo);

    // 4.3 Irrigado
    printf("É irrigado? (S/N)");
    scanf("%c", &resposta_irrigado);
    getchar();

    if (resposta_irrigado == 'S' || resposta_irrigado == 's'){
        p -> irrigado = true;
    }else{
        p -> irrigado = false;
    }

    // 4.4 Categoria da plantação
    printf("Digite a categoria da plantacao:\n");
    printf(" (0 = leguminosas, 1 = Cereal, 2 = Hortalica, 3 = Frutifera, 4 = Outros): ");
    scanf("%d", &tipo_int);
    getchar();

    p -> tipo = (categoriaPlanta)tipo_int;

    // 4.5 Data plantio
    printf("Digite a data do plantio (formato DD/MM/AAAA): ");
    scanf("%d/%d/%d", &p -> data_plantio.dia, &p -> data_plantio.mes, &p -> data_plantio.ano);
    getchar();

    // 4.6 Data esperada da colheita
    printf("Digite a data prevista para a colheita (DD/MM/AAAA): ");
    scanf("%d/%d/%d", &p -> colheita.dia, &p -> colheita.mes, &p -> colheita.ano);
    getchar();

    //4.7 Produtividade
    printf("Digite a produtividade média (Ex: 120.5): ");
    scanf("%d", &p -> produtividade);
    getchar();

    printf("------------------------------------------\n");
}

void inserir_plantacao(plantio *p, plantacao nova_cultura){
    int i, j;

    // 1. Verificando se tem espaço para plantar
    if (verifica_plantio_cheio(*p) == 1){
        printf("Nao foi possivel fazer o plantio, todos os talhoes estao ocupados!/n");
        return;
    }

    // 2. Encontrando o espaço para plantar
    i = 0;
    while (i < p -> ultimo && nova_cultura.cod > p -> elem[i].cod){
        i++;
    }

    // 3. Abrindo vaga para a cultura (se necessário)
    j = p -> ultimo;
    while( j > i){
        p -> elem[j] = p -> elem[j - 1];
        j--;
    }

    // 4. Inserir a nova cultura
    p -> elem[i] = nova_cultura;

    // 5. Atualizar o contador
    p -> ultimo++;
}

//Função auxiliar para ler a plantação
const char* categorias(categoriaPlanta tipo){
    switch(tipo){
        case Leguminosas:   return "Leguminosa";
        case Cereal:        return "Cerela";
        case Hortaliça:     return "Hortaliça";
        case Frutifera:     return "Frutifera";
        case Outro:         return "Outro";
        default:            return "Desconhecido";
    }

}

void exibe_plantacao(plantacao p){
    printf("------------------------------------------\n");
    printf("   Plantacao COD: %d\n", p.cod);
    printf("------------------------------------------\n");

    printf("  Cultivo:         %s\n", p.cultivo);
    printf("  Caterogira:      %s\n", p.cultivo);

    printf("  Irrigado:        %s\n", p.irrigado ? "Sim" : "Nao");

    printf("  Data do Plantio: %02d/%02d/%02d\n", p.data_plantio.dia, p.data_plantio.mes, p.data_plantio.ano);
    printf("  Data do Plantio: %02d/%02d/%02d\n", p.colheita.dia, p.colheita.mes, p.colheita.ano);

    printf("  Produtividade:   %.2f\n", p.produtividade);
    printf("------------------------------------------\n");
}
