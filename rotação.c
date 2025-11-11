#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Máximo de plantações para rotação
#define MAX 100

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

// --------- Funções Iniciais ---------------

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

// --------- Funções das Funcionalidades ---------------

// 1. Cadastrar plantação
void cadastrar_plantacao(plantacao *p){
    int tipo_int;
    char resposta_irrigado;

    printf("\n------- Cadastro de Nova Plantacao -------\n");

    // 1.1. Código
    printf("Digite o Codigo (ID) da planatacao: ");
    scanf("%d", &p -> cod);
    getchar();

    // 1.2 Cultivo
    printf("Digite o nome do cultivo (Ex: Milho, soja): ");
    fgets(p -> cultivo, 40, stdin);
    remover_newline(p -> cultivo);

    // 1.3 Irrigado
    printf("É irrigado? (S/N)");
    scanf("%c", &resposta_irrigado);
    getchar();

    if (resposta_irrigado == 'S' || resposta_irrigado == 's'){
        p -> irrigado = true;
    }else{
        p -> irrigado = false;
    }

    // 1.4 Categoria da plantação
    printf("Digite a categoria da plantacao:\n");
    printf(" (0 = leguminosas, 1 = Cereal, 2 = Hortalica, 3 = Frutifera, 4 = Outros): ");
    scanf("%d", &tipo_int);
    getchar();

    p -> tipo = (categoriaPlanta)tipo_int;

    // 1.5 Data plantio
    printf("Digite a data do plantio (formato DD/MM/AAAA): ");
    scanf("%d/%d/%d", &p -> data_plantio.dia, &p -> data_plantio.mes, &p -> data_plantio.ano);
    getchar();

    // 1.6 Data esperada da colheita
    printf("Digite a data prevista para a colheita (DD/MM/AAAA): ");
    scanf("%d/%d/%d", &p -> colheita.dia, &p -> colheita.mes, &p -> colheita.ano);
    getchar();

    //1.7 Produtividade
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

// 2. Consultar Plantio
void consultar_plantio(plantio p) {
    int codigo, i;
    int encontrou = 0;
    
    printf("\n====== CONSULTAR PLANTAÇÃO ======\n");
    
    // 2.1. Verificar se há plantações cadastradas
    if (verifica_plantio_vazio(p)) {
        printf("Nenhuma plantacao cadastrada no sistema.\n");
        return;
    }
    
    // 2.2. Mostrar plantações disponíveis para consulta
    printf("Plantações cadastradas:\n");
    for (i = 0; i < p.ultimo; i++) {
        printf("COD: %d - %s\n", p.elem[i].cod, p.elem[i].cultivo);
    }
    
    // 2.3. Solicitar código da plantação desejada
    printf("\nDigite o CODIGO da plantacao que deseja consultar: ");
    scanf("%d", &codigo);
    getchar();
    
    // 2.4. Buscar a plantação pelo código
    for (i = 0; i < p.ultimo; i++) {
        if (p.elem[i].cod == codigo) {
            printf("\n>>> PLANTACAO ENCONTRADA:\n");
            
            // 2.5. EXIBIR DADOS DA PLANTAÇÃO
            printf("------------------------------------------\n");
            printf("   Plantacao COD: %d\n", p.elem[i].cod);
            printf("------------------------------------------\n");
            
            printf("  Cultivo:         %s\n", p.elem[i].cultivo);
            printf("  Categoria:       %s\n", categorias(p.elem[i].tipo));
            
            printf("  Irrigado:        %s\n", p.elem[i].irrigado ? "Sim" : "Nao");
            
            printf("  Data do Plantio: %02d/%02d/%04d\n", 
                   p.elem[i].data_plantio.dia, 
                   p.elem[i].data_plantio.mes, 
                   p.elem[i].data_plantio.ano);
            
            printf("  Data da Colheita: %02d/%02d/%04d\n", 
                   p.elem[i].colheita.dia, 
                   p.elem[i].colheita.mes, 
                   p.elem[i].colheita.ano);
            
            printf("  Produtividade:   %.2f\n", p.elem[i].produtividade);
            printf("------------------------------------------\n");
            
            encontrou = 1;
            break;
        }
    }
    
    if (!encontrou) {
        printf("\n>>> ERRO: Plantacao com codigo %d nao encontrada!\n", codigo);
        printf(">>> Verifique o codigo e tente novamente.\n");
    }
}

// 3. REGISTRAR COLHEITA
void registrar_colheita_completa(plantio *p) {
    int codigo, i, j;
    
    // 3.1. Verificar se o plantio está vazio
    if (verifica_plantio_vazio(*p)) {
        printf("Nenhuma plantacao cadastrada para colher!\n");
        return;
    }
    
    // 3.2. Mostrar a lista de plantações cadastradas
    printf("\n------- REGISTRAR COLHEITA -------\n");
    printf("Plantacoes cadastradas:\n");
    for (i = 0; i < p->ultimo; i++) {
        printf("COD: %d - %s (Plantio: %02d/%02d/%04d)\n", 
               p->elem[i].cod, p->elem[i].cultivo,
               p->elem[i].data_plantio.dia, 
               p->elem[i].data_plantio.mes, 
               p->elem[i].data_plantio.ano);
    }
    
    // 3.3. Pegar o código da plantação que deseja ser registrada
    printf("\nDigite o CODIGO da plantacao a ser colhida: ");
    scanf("%d", &codigo);
    getchar();
    
    // 3.4. Buscar a plantação pelo código
    int posicao = -1;
    for (i = 0; i < p->ultimo; i++) {
        if (p->elem[i].cod == codigo) {
            posicao = i;
            break;
        }
    }
    
    if (posicao == -1) {
        printf("Plantacao com codigo %d nao encontrada!\n", codigo);
        return;
    }
    
    // 3.5. Mostrar dados da plantação
    printf("\n>>> CONFIRMAR COLHEITA <<<\n");
    exibe_plantacao(p->elem[posicao]);
    
    // 3.6. Confirmar registro da colheita
    char confirmacao;
    printf("Confirmar colheita? (S/N): ");
    scanf("%c", &confirmacao);
    getchar();
    
    if (confirmacao == 'S' || confirmacao == 's') {
        // 3.7. Registrar data real da colheita
        data data_real_colheita;
        printf("Digite a data REAL da colheita (DD/MM/AAAA): ");
        scanf("%d/%d/%d", &data_real_colheita.dia, &data_real_colheita.mes, &data_real_colheita.ano);
        getchar();
        
        // 3.8. Mostra mensagem de sucesso
        printf("\n>>> COLHEITA REGISTRADA COM SUCESSO! <<<\n");
        printf("Cultura: %s\n", p->elem[posicao].cultivo);
        printf("Data plantio: %02d/%02d/%04d\n", 
               p->elem[posicao].data_plantio.dia,
               p->elem[posicao].data_plantio.mes,
               p->elem[posicao].data_plantio.ano);
        printf("Data colheita: %02d/%02d/%04d\n",
               data_real_colheita.dia,
               data_real_colheita.mes,
               data_real_colheita.ano);
        printf("Talhao liberado para pousio/novo plantio!\n");
        
        // 3.9. REMOVER A PLANTAÇÃO DA LISTA
        // Deslocar todos os elementos uma posição para trás
        for (i = posicao; i < p->ultimo - 1; i++) {
            p->elem[i] = p->elem[i + 1];
        }
        
        // 3.10. Atualizar o contador
        p->ultimo--;
        
        printf("Total de plantacoes ativas: %d\n", p->ultimo);
        
    } else {
        printf("Colheita cancelada.\n");
    }
}

// 4. ALTERAR PLANTAÇÃO
void alterar_plantacao(plantio *p) {
    int codigo, i;
    int opcao;
    char resposta;
    
    if (verifica_plantio_vazio(*p)) {
        printf("Nenhuma plantacao cadastrada para alterar!\n");
        return;
    }
    
    printf("\n====== ALTERAR DADOS DA PLANTAÇÃO ======\n");
    
    // 4.1. Listar plantações disponíveis
    printf("Plantacoes cadastradas:\n");
    for (i = 0; i < p->ultimo; i++) {
        printf("COD: %d - %s\n", p->elem[i].cod, p->elem[i].cultivo);
    }
    
    // 4.2. Buscar plantação
    printf("\nDigite o CODIGO da plantacao a ser alterada: ");
    scanf("%d", &codigo);
    getchar();
    
    int posicao = -1;
    for (i = 0; i < p->ultimo; i++) {
        if (p->elem[i].cod == codigo) {
            posicao = i;
            break;
        }
    }
    
    if (posicao == -1) {
        printf("Plantacao com codigo %d nao encontrada!\n", codigo);
        return;
    }
    
    // 4.3. Mostrar dados atuais
    printf("\n>>> DADOS ATUAIS DA PLANTAÇÃO:\n");
    exibe_plantacao(p->elem[posicao]);
    
    // 4.4. Menu de alteração
    do {
        printf("\n--- O QUE DESEJA ALTERAR? ---\n");
        printf("1. Nome do Cultivo\n");
        printf("2. Status de Irrigacao\n");
        printf("3. Categoria\n");
        printf("4. Data de Plantio\n");
        printf("5. Data Prevista de Colheita\n");
        printf("6. Produtividade Media\n");
        printf("0. Finalizar Alteracoes\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();
        
        switch(opcao) {
            case 1:
                printf("Novo nome do cultivo: ");
                fgets(p->elem[posicao].cultivo, 40, stdin);
                remover_newline(p->elem[posicao].cultivo);
                printf("Cultivo alterado para: %s\n", p->elem[posicao].cultivo);
                break;
                
            case 2:
                printf("É irrigado? (S/N): ");
                scanf("%c", &resposta);
                getchar();
                p->elem[posicao].irrigado = (resposta == 'S' || resposta == 's');
                printf("Irrigacao alterada para: %s\n", 
                       p->elem[posicao].irrigado ? "Sim" : "Nao");
                break;
                
            case 3:
                printf("Nova categoria (0=Leguminosas, 1=Cereal, 2=Hortalica, 3=Frutifera, 4=Outro): ");
                int novoTipo;
                scanf("%d", &novoTipo);
                getchar();
                if (novoTipo >= 0 && novoTipo <= 4) {
                    p->elem[posicao].tipo = (categoriaPlanta)novoTipo;
                    printf("Categoria alterada para: %s\n", categorias(p->elem[posicao].tipo));
                } else {
                    printf("Categoria invalida!\n");
                }
                break;
                
            case 4:
                printf("Nova data de plantio (DD/MM/AAAA): ");
                scanf("%d/%d/%d", &p->elem[posicao].data_plantio.dia, 
                                  &p->elem[posicao].data_plantio.mes, 
                                  &p->elem[posicao].data_plantio.ano);
                getchar();
                printf("Data de plantio alterada para: %02d/%02d/%04d\n",
                       p->elem[posicao].data_plantio.dia,
                       p->elem[posicao].data_plantio.mes,
                       p->elem[posicao].data_plantio.ano);
                break;
                
            case 5:
                printf("Nova data prevista de colheita (DD/MM/AAAA): ");
                scanf("%d/%d/%d", &p->elem[posicao].colheita.dia, 
                                  &p->elem[posicao].colheita.mes, 
                                  &p->elem[posicao].colheita.ano);
                getchar();
                printf("Data de colheita alterada para: %02d/%02d/%04d\n",
                       p->elem[posicao].colheita.dia,
                       p->elem[posicao].colheita.mes,
                       p->elem[posicao].colheita.ano);
                break;
                
            case 6:
                printf("Nova produtividade media: ");
                scanf("%f", &p->elem[posicao].produtividade);
                getchar();
                printf("Produtividade alterada para: %.2f\n", p->elem[posicao].produtividade);
                break;
                
            case 0:
                printf("Alteracoes finalizadas.\n");
                break;
                
            default:
                printf("Opcao invalida!\n");
        }
        
    } while (opcao != 0);
    
    printf("\n>>> PLANTAÇÃO ATUALIZADA COM SUCESSO!\n");
    exibe_plantacao(p->elem[posicao]);
}

// 5. Exibir Relatório de Talhões
void exibir_resumo_talhoes(plantio p) {
    int talhoes_ocupados = p.ultimo;
    int talhoes_livres = MAX - p.ultimo;
    float percentual_ocupacao = (float)talhoes_ocupados / MAX * 100;
    float percentual_livre = (float)talhoes_livres / MAX * 100;
    
    printf("\n====== RESUMO DOS TALHÕES ======\n");
    printf("Capacidade total do sistema: %d talhões\n\n", MAX);
    
    // 5.1. Barra de progresso visual
    printf("Situação atual: [");
    int i;
    for (i = 0; i < 50; i++) {
        if (i < (percentual_ocupacao / 2)) {
            printf("█"); // Caractere para ocupado
        } else {
            printf("░"); // Caractere para livre
        }
    }
    printf("]\n\n");
    
    // 5.2. Estatísticas detalhadas
    printf("TALHÕES OCUPADOS:\n");
    printf("  Quantidade: %d talhões\n", talhoes_ocupados);
    printf("  Percentual: %.1f%%\n", percentual_ocupacao);
    
    printf("\nTALHÕES LIVRES:\n");
    printf("  Quantidade: %d talhões\n", talhoes_livres);
    printf("  Percentual: %.1f%%\n", percentual_livre);
    
    // 5.3. Status do sistema
    printf("\nSTATUS DO SISTEMA: ");
    if (talhoes_ocupados == 0) {
        printf("🟢 TODOS OS TALHÕES LIVRES\n");
        printf("   Sistema completamente disponível para novos plantios\n");
    } else if (talhoes_livres == 0) {
        printf("🔴 SISTEMA LOTADO\n");
        printf("   Todos os talhões estão ocupados\n");
    } else if (percentual_ocupacao > 80) {
        printf("🟡 SISTEMA QUASE LOTADO\n");
        printf("   Poucos talhões disponíveis\n");
    } else if (percentual_ocupacao > 50) {
        printf("🟠 SISTEMA EM USO MODERADO\n");
        printf("   Boa quantidade de talhões disponíveis\n");
    } else {
        printf("🟢 SISTEMA COM BOA CAPACIDADE\n");
        printf("   Muitos talhões disponíveis\n");
    }
    
    // 5.4. Listar plantações ativas se houver
    if (talhoes_ocupados > 0) {
        printf("\nPLANTAÇÕES ATIVAS:\n");
        for (i = 0; i < p.ultimo; i++) {
            printf("  Talhão %d: %s (COD: %d)\n", 
                   i, p.elem[i].cultivo, p.elem[i].cod);
        }
    }
    
    printf("\n=================================\n");
}

void menu_principal() {
    plantio sistema;
    int opcao;
    
    criar_plantio_vazio(&sistema);
    
    printf("=========================================\n");
    printf("    SISTEMA DE ROTACAO DE CULTURAS\n");
    printf("=========================================\n");
    
    do {
        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("1. CADASTRAR PLANTIO\n");
        printf("2. CONSULTAR PLANTIO\n");
        printf("3. REGISTRAR COLHEITA\n");
        printf("4. ATUALIZAR PLANTIO\n");
        printf("5. OBTER RELATÓRIO DE TALHÕES\n");
        printf("0. SAIR DO SISTEMA\n");
        printf("-----------------------------------\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        getchar();
        
        switch(opcao) {
            case 1:
                cadastrar_plantacao(&sistema);
                break;
            case 2:
                consultar_plantio(sistema);
                break;
            case 3:
                registrar_colheita(&sistema);
                break;
            case 4:
                alterar_plantacao(&sistema);
                break;
            case 5:
                exibir_resumo_talhoes(sistema);
                break;
            case 0:
                printf("\n>>> Obrigado por usar o Sistema de Rotacao de Culturas!\n");
                printf(">>> Encerrando programa...\n");
                break;
            default:
                printf("\n>>> ERRO: Opcao invalida! Tente novamente.\n");
        }
        
        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
        
    } while (opcao != 0);
}