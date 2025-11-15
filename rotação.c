//Bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para atoi (converte string para int) e atof (converte string para float)
#include <stdbool.h>

//Máximo de plantações para rotação
#define MAX 100

//Definindo os tipos de plantação
typedef enum{
    Leguminosas = 1,
    Cereal,
    Hortalica,
    Frutifera,
    Outro
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

// --- PROTÓTIPOS ---
void criar_plantio_vazio(plantio *p);
int verifica_plantio_vazio (plantio p);
int verifica_plantio_cheio(plantio p);
void remover_newline(char *str);
void ler_plantacao(plantacao *p);
void inserir_plantacao(plantio *p, plantacao nova_cultura);
const char* categorias(categoriaPlanta tipo);
void exibe_plantacao(plantacao p); // <-- SÓ 1 ARGUMENTO
void exibe_lista_plantio (plantio p);
int consultar_plantacao_lista (plantio p, char nome_cultivo[]);
int consultar_plantacao_lista_por_cod(plantio p, int cod);
void remover_plantacao_lista(plantio *p, int i);
void alterar_plantacao_lista (plantio *p, int i);
void MENU();
void exibe_lista_por_categoria(plantio p);
void alerta_colheita_por_mes_e_ano(plantio p);
void controle_ocupacao(plantio p);
int ler_inteiro();
float ler_float();
void exibe_lista_por_nome(plantio p); 

// --- FUNÇÕES DE LEITURA SEGURA ---
void remover_newline(char *str){
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n'){
        str[len - 1] = '\0';
    }
}
int ler_inteiro() {
    char buffer[50];
    fgets(buffer, 50, stdin);
    remover_newline(buffer);
    return atoi(buffer);
}
float ler_float() {
    char buffer[50];
    fgets(buffer, 50, stdin);
    remover_newline(buffer);
    return atof(buffer); 
}

// --- FIM DAS FUNÇÕES DE LEITURA ---


// 1. Criar plantio vazio
void criar_plantio_vazio(plantio *p){
    p -> primeiro = 0;
    p -> ultimo = p -> primeiro;
}

// 2. Verificando se plantio está vazio
int verifica_plantio_vazio (plantio p){
    return (p.primeiro == p.ultimo);
}

// 3. Verificando se plantio está cheio
int verifica_plantio_cheio(plantio p){
    return (p.ultimo == MAX);
}

// 4. Ler a plantação (Segura)
void ler_plantacao(plantacao *p){
    char buffer_leitura[50]; 

    printf("\n------- Cadastro de Nova Plantacao -------\n");
    printf("Digite o Codigo (ID) da planatacao: ");
    p->cod = ler_inteiro(); 
    printf("Digite o nome do cultivo (Ex: Milho, soja): ");
    fgets(p -> cultivo, 40, stdin);
    remover_newline(p -> cultivo);
    printf("Irrigado? (S/N): ");
    fgets(buffer_leitura, 10, stdin); 
    remover_newline(buffer_leitura);
    if (buffer_leitura[0] == 'S' || buffer_leitura[0] == 's'){
        p -> irrigado = true;
    }else{
        p -> irrigado = false;
    }
    printf("Digite a categoria da plantacao:\n");
    printf("(1 = Leguminosas, 2 = Cereal, 3 = Hortalica, 4 = Frutifera, 5 = Outro): ");
    p->tipo = (categoriaPlanta)ler_inteiro(); 
    printf("Digite a data do plantio (formato DD/MM/AAAA): ");
    fgets(buffer_leitura, 50, stdin);
    remover_newline(buffer_leitura);
    sscanf(buffer_leitura, "%d/%d/%d", &p -> data_plantio.dia, &p -> data_plantio.mes, &p -> data_plantio.ano);
    printf("Digite a data prevista para a colheita (DD/MM/AAAA): ");
    fgets(buffer_leitura, 50, stdin);
    remover_newline(buffer_leitura);
    sscanf(buffer_leitura, "%d/%d/%d", &p -> colheita.dia, &p -> colheita.mes, &p -> colheita.ano);
    printf("Digite a produtividade media por ano (Ex: 120.5): ");
    p->produtividade = ler_float(); 
    printf("------------------------------------------\n");
}


// 5. Inserir plantação
void inserir_plantacao(plantio *p, plantacao nova_cultura){
    int i, j;
    if (verifica_plantio_cheio(*p) == 1){
        printf("Nao foi possivel fazer o plantio, todos os talhoes estao ocupados!\n");
        return;
    }
    i = 0;
    while (i < p -> ultimo && nova_cultura.cod > p -> elem[i].cod){
        i++;
    }
    j = p -> ultimo;
    while( j > i){
        p -> elem[j] = p -> elem[j - 1];
        j--;
    }
    p -> elem[i] = nova_cultura;
    p -> ultimo++;
    printf("\nCultivo '%s' (Cod: %d) inserido com sucesso!\n", nova_cultura.cultivo, nova_cultura.cod);
}

//Função auxiliar para ler a plantação
const char* categorias(categoriaPlanta tipo){
    switch(tipo){
        case Leguminosas:   return "Leguminosa";
        case Cereal:        return "Cereal";
        case Hortalica:     return "Hortalica";
        case Frutifera:     return "Frutifera";
        case Outro:         return "Outro";
        default:            return "Desconhecido";
    }
}

// (Bónus) Consulta por CÓDIGO (para exibir o talhão)
int consultar_plantacao_lista_por_cod(plantio p, int cod){
    int i;
    if(verifica_plantio_vazio(p) == 1){
        return -1;
    }
    i = p.primeiro;
    while(i < p.ultimo){
        if(p.elem[i].cod == cod){
            return i; // Retorna o índice
        }
        i++;
    }
    return -1;
}


// 6. Exibir uma plantação (Definição com 1 argumento)
void exibe_plantacao(plantacao p){
 
    printf("------------------------------------------\n");
    // Mostra o Talhão (posição 1-based) e o Código
    // Se não encontrar (improvável), mostra -1+1 = 0
    printf("   Plantacao COD: %d\n", p.cod);
    printf("------------------------------------------\n");
    printf("  Cultivo:       %s\n", p.cultivo);
    printf("  Categoria:     %s\n", categorias(p.tipo));
    printf("  Irrigado:      %s\n", p.irrigado ? "Sim" : "Nao");
    printf("  Data do Plantio: %02d/%02d/%d\n", p.data_plantio.dia, p.data_plantio.mes, p.data_plantio.ano);
    printf("  Data da Colheita: %02d/%02d/%d\n", p.colheita.dia, p.colheita.mes, p.colheita.ano);
    printf("  Produtividade:  %.2f Kg\n", p.produtividade);
    printf("------------------------------------------\n");
}

// 7. Exibir a lista de plantio
void exibe_lista_plantio (plantio p){
    int i;
    if(verifica_plantio_vazio(p) == 1){
        printf("\n==================================\n");
        printf(" A LISTA DE PLANTIO ESTA VAZIA.");  
        printf("\n==================================\n\n");
    }else{
        printf("\n******** RELATORIO DA LISTA DE PLANTIO *************\n");
        i = p.primeiro;
        while (i < p.ultimo){
            // CORREÇÃO: Chamada com 1 argumento
            exibe_plantacao(p.elem[i]); 
            i++;
        }
        printf("************ FIM DO RELATORIO *************\n\n");
    }
}

// 8. Consultar plantação (POR NOME - Retorna o PRIMEIRO índice)
int consultar_plantacao_lista (plantio p, char nome_cultivo[]){
    int i;
    if(verifica_plantio_vazio(p) == 1){
        return -1;
    }
    i = p.primeiro;
    while(i < p.ultimo){
        if(strcmp(nome_cultivo, p.elem[i].cultivo) == 0){
            return i; // Retorna o índice
        }
        i++;
    }
    return -1;
}

// 9. Remover plantação
void remover_plantacao_lista(plantio *p, int i){
    int j;
    j = i;
    while(j < p -> ultimo -1){
        p -> elem[j] = p -> elem[j+1];
        j++;
    }
    p -> ultimo--;
}

// 10. Alterar plantação
void alterar_plantacao_lista (plantio *p, int i){
    plantacao cultura_nova;
    int cod_antigo;
    printf("\n--- Alterando Cultivo ---\n");
    printf("Dados atuais:\n");
    // CORREÇÃO: Chamada com 1 argumento
    exibe_plantacao(p->elem[i]); 
    cod_antigo = p->elem[i].cod;
    printf("\nDigite os NOVOS dados para este cultivo:\n");
    ler_plantacao(&cultura_nova);
    if(cultura_nova.cod == cod_antigo){
        p ->elem[i] = cultura_nova;
        printf("Cultivo alterado com sucesso (mantido na mesma posicao).\n");
    }else{
        printf("Aviso: O codigo foi alterado. Reordenando a lista...\n");
        remover_plantacao_lista(p, i);
        inserir_plantacao(p, cultura_nova);
        printf("Cultivo alterado e realocado com sucesso.\n");
    }
}

// 11. Menu
void MENU(){
    printf("\n* * * * * GESTAO DE PLANTIO * * * * *\n");
    printf("+--------------------------------------+\n");
    printf("| 1 - Inserir Nova Plantacao\n");
    printf("| 2 - Alterar Plantacao\n");
    printf("| 3 - Remover Plantacao (Colher)\n");
    printf("| 4 - Consultar Plantacao (por nome)\n");
    printf("| 5 - Exibir 1 Plantacao (por posicao)\n");
    printf("| 6 - Exibir Todas Plantacoes\n");
    printf("| 7 - Filtrar por Categoria\n");
    printf("| 8 - Alerta de Colheita (por Mes/Ano)\n");
    printf("| 9 - Resumo de Ocupacao\n");
    printf("| 10 - Sair\n");
    printf("+--------------------------------------+\n");
    printf("Opcao: ");
}


// --- Funções de Relatório (Novas do PDF) ---

// (Chamada pelo CASE 4)
void exibe_lista_por_nome(plantio p) {
    char nome_busca[40];
    int i, contador;

    printf("\n--- 4. Consultar Plantacao (por nome) ---\n");
    if (verifica_plantio_vazio(p) == 1) {
        printf("ERRO: A lista esta VAZIA! Nada para consultar.\n");
        return;
    }
    
    printf("Digite o nome do cultivo que deseja CONSULTAR: ");
    fgets(nome_busca, 40, stdin);
    remover_newline(nome_busca);
    
    printf("\n******** RELATORIO: Plantios com o nome '%s' *************\n", nome_busca);
    
    i = p.primeiro;
    contador = 0;
    
    while(i < p.ultimo) {
        if(strcmp(nome_busca, p.elem[i].cultivo) == 0) {
            // CORREÇÃO: Chamada com 1 argumento
            exibe_plantacao(p.elem[i]); 
            contador++;
        }
        i++;
    }
    
    if(contador == 0) {
        printf("\nNenhum plantio encontrado com o nome '%s'.\n", nome_busca);
    } else {
        printf("\n%d plantio(s) encontrado(s) com o nome '%s'.\n", contador, nome_busca);
    }
    printf("************ FIM DO RELATORIO *************\n\n");
}


void exibe_lista_por_categoria(plantio p) {
    int i, contador;
    
    printf("\n--- 7. Filtrar por Categoria ---\n");
    if (verifica_plantio_vazio(p) == 1) {
        printf("ERRO: A lista esta VAZIA! Nada para filtrar.\n");
        return;
    }
    
    printf("Digite a categoria que deseja filtrar:\n");
    printf("(1=Leguminosas, 2=Cereal, 3=Hortalica, 4=Frutifera, 5=Outro): ");
    categoriaPlanta tipo_procurado = (categoriaPlanta)ler_inteiro(); 
    
    const char* nome_categoria = categorias(tipo_procurado);
    
    printf("\n******** RELATORIO: Plantios da Categoria '%s' *************\n", nome_categoria);
    
    i = p.primeiro;
    contador = 0;
    
    while(i < p.ultimo) {
        if(p.elem[i].tipo == tipo_procurado) {
            // CORREÇÃO: Chamada com 1 argumento
            exibe_plantacao(p.elem[i]); 
            contador++;
        }
        i++;
    }
    
    if(contador == 0) {
        printf("\nNenhum plantio encontrado para a categoria '%s'.\n", nome_categoria);
    } else {
        printf("\n%d plantio(s) encontrado(s) para a categoria '%s'.\n", contador, nome_categoria);
    }
    printf("************ FIM DO RELATORIO *************\n\n");
}

// (Função MODIFICADA Mês/Ano)
void alerta_colheita_por_mes_e_ano(plantio p) {
    int mes_procurado, ano_procurado, i, contador;
    
    printf("\n--- 8. Alerta de Colheita por Mes e Ano ---\n");
    if (verifica_plantio_vazio(p) == 1) {
        printf("ERRO: A lista esta VAZIA! Nada para consultar.\n");
        return;
    }
    
    printf("Digite o numero do mes que deseja verificar (1-12): ");
    mes_procurado = ler_inteiro(); 
    
    printf("Digite o ano que deseja verificar (Ex: 2025): ");
    ano_procurado = ler_inteiro();
    
    if(mes_procurado < 1 || mes_procurado > 12) {
        printf("ERRO: Mes invalido. Digite um numero entre 1 e 12.\n");
        return;
    }
    if(ano_procurado < 2000 || ano_procurado > 2100) {
        printf("ERRO: Ano invalido. (Permitido entre 2000 e 2100).\n");
        return;
    }
    
    printf("\n** RELATORIO: Colheitas previstas para %02d/%d **\n", mes_procurado, ano_procurado);
    
    i = p.primeiro;
    contador = 0;
    
    while(i < p.ultimo) {
        if(p.elem[i].colheita.mes == mes_procurado && p.elem[i].colheita.ano == ano_procurado) {
            // CORREÇÃO: Chamada com 1 argumento
            exibe_plantacao(p.elem[i]); 
            contador++;
        }
        i++;
    }
    
    if(contador == 0) {
        printf("\nNenhuma colheita prevista para %02d/%d.\n", mes_procurado, ano_procurado);
    } else {
        printf("\n%d colheita(s) prevista(s) para %02d/%d.\n", contador, mes_procurado, ano_procurado);
    }
    printf("************ FIM DO RELATORIO *************\n\n");
}

void controle_ocupacao(plantio p) {
    int plantados = p.ultimo;
    int livres = MAX - plantados;
    float porcentagem_ocupada = ((float)plantados / MAX) * 100.0; 
    
    printf("\n--- 9. Resumo de Ocupacao dos Talhoes ---\n");
    printf("+--------------------------------------+\n");
    printf("| Capacidade Total: %d talhoes\n", MAX);
    printf("| Talhoes Plantados: %d\n", plantados);
    printf("| Talhoes Livres:    %d\n", livres);
    printf("| Ocupacao:          %.2f %%\n", porcentagem_ocupada);
    printf("+--------------------------------------+\n\n");
}


// 12. Função principal
int main(){

    plantio meu_plantio;
    plantacao cultura_temp;
    char nome_busca[40];
    int op;
    int pos;

    criar_plantio_vazio(&meu_plantio);

    do{
        MENU();
        op = ler_inteiro(); 

        switch (op) {
            case 1:
                printf("\n--- 1. Inserir Plantacao ---\n");
                if (verifica_plantio_cheio(meu_plantio) == 1) { 
                    printf("ERRO: A lista de plantio esta CHEIA!\n");
                } else {
                    ler_plantacao(&cultura_temp); 
                    inserir_plantacao(&meu_plantio, cultura_temp);
                }
                break;
            case 2:
                printf("\n--- 2. Alterar Plantacao ---\n");
                if (verifica_plantio_vazio(meu_plantio) == 1) {
                    printf("ERRO: A lista esta VAZIA! Nada para alterar.\n");
                    break;
                }
                printf("Digite o nome do cultivo que deseja ALTERAR: ");
                fgets(nome_busca, 40, stdin);
                remover_newline(nome_busca);
                pos = consultar_plantacao_lista(meu_plantio, nome_busca); 
                if (pos == -1) {
                    printf("ERRO: Cultivo '%s' nao foi encontrado.\n", nome_busca);
                } else {
                    alterar_plantacao_lista(&meu_plantio, pos);
                }
                break;
            case 3:
                printf("\n--- 3. Remover Plantacao (Colher) ---\n");
                if (verifica_plantio_vazio(meu_plantio) == 1) {
                    printf("ERRO: A lista esta VAZIA! Nada para remover.\n");
                    break;
                }
                printf("Digite o nome do cultivo que foi COLHIDO (remover): ");
                fgets(nome_busca, 40, stdin);
                remover_newline(nome_busca);
                pos = consultar_plantacao_lista(meu_plantio, nome_busca);
                if (pos == -1) {
                    printf("ERRO: Cultivo '%s' nao foi encontrado.\n", nome_busca);
                } else {
                    cultura_temp = meu_plantio.elem[pos];
                    remover_plantacao_lista(&meu_plantio, pos);
                    printf("Colheita do '%s' (Cod: %d) registrada com sucesso. Talhao livre.\n", cultura_temp.cultivo, cultura_temp.cod);
                }
                break;
            case 4:
                exibe_lista_por_nome(meu_plantio);
                break;
            case 5:
                printf("\n--- 5. Exibir 1 Plantacao (por Posicao) ---\n");
                if (verifica_plantio_vazio(meu_plantio) == 1) {
                    printf("ERRO: A lista esta VAZIA!\n");
                    break;
                }
                printf("Digite a POSICAO (talhao) que deseja ver (1 a %d): ", meu_plantio.ultimo);
                pos = ler_inteiro(); 
                if (pos >= 1 && pos <= meu_plantio.ultimo) {
            
                    exibe_plantacao(meu_plantio.elem[pos - 1]); 
                } else {
                    printf("ERRO: Posicao %d invalida ou nao existe.\n", pos);
                }
                break;
            case 6:
                printf("\n--- 6. Exibir Todas Plantacoes ---\n");
                exibe_lista_plantio(meu_plantio);
                break;
            case 7:
                exibe_lista_por_categoria(meu_plantio);
                break;
            case 8:
                alerta_colheita_por_mes_e_ano(meu_plantio); 
                break;
            case 9:
                controle_ocupacao(meu_plantio);
                break;
            case 10:
                printf("\nObrigado por usar o sistema de Gestao de Plantio. Ate logo!\n");
                break;
            default:
                printf("\nERRO: Opcao invalida. Por favor, digite um numero de 1 a 10.\n");
                break;
        } 
    }while (op != 10);

    return 0;
}
