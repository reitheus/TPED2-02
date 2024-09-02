#include "../include/arvorebEst.h"

void iniciaArvoreBE(TipoPagina **Arvore) { // Cria apontador para a árvore
    *Arvore = NULL;
}

// Função para liberar a árvore inteira
void liberaArvoreBE(TipoPagina **Arvore) {
    if((*Arvore)->UU.U0.filho[0]->Pt == Externa){//se for folha libera se não faz recursão
        for(int i = 0; i <= (*Arvore)->UU.U0.quant;i++){
            free((*Arvore)->UU.U0.filho[i]);
        }
        free((*Arvore));
    }else{
        for(int i = 0;i <= (*Arvore)->UU.U0.quant;i++){
            liberaArvoreBE(&(*Arvore)->UU.U0.filho[i]);
        }
        free(*Arvore);
    }
}


// Função para pesquisar um dado na árvore
void pesquisaArvorebEst(Item *dado, TipoPagina *arvore, Analise* info, bool *achou) {
    int i;
    TipoPagina Pg;
    Pg = *arvore;

    // Se o nó é interno
    if (arvore->Pt == Interna) {
        i = 1;
        // Encontra o filho adequado para seguir a busca
        info->comppesquisa += 1;
        while (i < Pg.UU.U0.quant && dado->chave > Pg.UU.U0.pai[i-1]) {
            i++;
            info->comppesquisa += 1;
        }
        // Chama a função recursivamente no filho adequado
        info->transpesquisa += 1;
        if (dado->chave < Pg.UU.U0.pai[i-1]) {
            
            pesquisaArvorebEst(dado, Pg.UU.U0.filho[i-1], info, achou);
        } else {
            
            pesquisaArvorebEst(dado, Pg.UU.U0.filho[i], info, achou);
        }
        return;
    }

    // Se o nó é externo (folha)
    i = 1;
   info->comppesquisa += 1;
    while (i < Pg.UU.U1.ne && dado->chave > Pg.UU.U1.re[i-1].chave) {
        i++;
        info->comppesquisa += 1;
    }
    // Verifica se o dado foi encontrado
    info->comppesquisa += 1;
    if (dado->chave == Pg.UU.U1.re[i-1].chave) {
        *achou = true;
    } else {
        *achou = false;
    }
}

//Função para inserir um registro em uma pagina externa
void inserenaPaginaBE(TipoPagina *Ap, Item *dados, Analise* analise){
    int k;
    k = Ap->UU.U1.ne;
    analise->transpre++;
    analise->comppre++;
    //Percorre o vetor para ver onde ira inserir a chave corretamente
    while (k > 0 && Ap->UU.U1.re[k-1].chave > dados->chave) {
        analise->comppre++;
        Ap->UU.U1.re[k] = Ap->UU.U1.re[k-1];
        k--;
    }
    //adiciona o registro
    Ap->UU.U1.re[k] = *dados;
    Ap->UU.U1.ne++;
    analise->transpre++;
    
}

// Função para inserir um registro em uma página interna
void inserenaPaginaBI(TipoPagina *arvore, TipoChave dados, TipoPagina *ApDir, Analise *analise) {
    short int k;
    k = arvore->UU.U0.quant;

    analise->transpre++;
    analise->comppre++;
    // Insere o registro na posição correta
    while (k > 0 && arvore->UU.U0.pai[k-1] > dados) {
        analise->comppre++;
        arvore->UU.U0.pai[k] = arvore->UU.U0.pai[k-1];
        arvore->UU.U0.filho[k + 1] = arvore->UU.U0.filho[k];
        analise->transpre += 2;
        k--;
    }
    //adiciona no registro
    arvore->UU.U0.pai[k] = dados;
    arvore->UU.U0.filho[k + 1] = ApDir; 
    arvore->UU.U0.quant++;
    analise->transpre += 2;

}
    

// Função para inserir um registro na árvore B* e lidar com a divisão de páginas
void insBE(Item *registro, TipoPagina* Arvore, short *cresceu, TipoChave *registroretorno, TipoPagina **ApRetorno, Analise* analise) {
    int i;
    if(Arvore->Pt == Externa){

    
        // Se a página não precisa ser dividida
       
        if (Arvore->UU.U0.quant < 2 * M) {
            
            analise->transpre++;
            inserenaPaginaBE(Arvore,registro,analise);
            *cresceu = 0;
            return;
        }
        //se precisar cria uma nova página
        TipoPagina *ApTemp = (TipoPagina*)malloc(sizeof(TipoPagina));
        
        if(ApTemp != NULL){//verifica se foi criado corretamente
            ApTemp->Pt = Externa;
            ApTemp->UU.U1.ne = 0;
            
            //se o registro for ser colocado no meio do vetor se não executa a outra condição
            analise->comppre++;
            if(registro->chave <= Arvore->UU.U1.re[M].chave){
                
                inserenaPaginaBE(ApTemp, &Arvore->UU.U1.re[2 * M - 1],analise);
                Arvore->UU.U1.ne--;
                inserenaPaginaBE(Arvore,registro,analise);
                analise->transpre+=2;
            }else{
                inserenaPaginaBE(ApTemp,registro,analise);
                
            }
            //faz os ajustes na nova pagina
            for(int j = M; j < 2 * M;j++){
                inserenaPaginaBE(ApTemp,&Arvore->UU.U1.re[j],analise);
                analise->transpre++;
            }

            //faz os ajustes finais para a inserção: retorno da chave e tratamento de ponteiros
            *cresceu = 1;
            Arvore->UU.U1.ne = M;
            *registroretorno = Arvore->UU.U1.re[M].chave;
            *ApRetorno = ApTemp;
            ApTemp->UU.U1.prox = Arvore->UU.U1.prox;
            Arvore->UU.U1.prox = ApTemp;
            analise->transpre+=4;
        }  
        return;
    }
    //Inserção interna
    i = 1;  
    //busca onde deve ser colocado  
    analise->comppre++;
    while(i < Arvore->UU.U0.quant && registro->chave > Arvore->UU.U0.pai[i-1]){
        analise->comppre++;
        i++;
    }
    //busca onde colocar
    analise->comppre++;
    if(Arvore->UU.U0.pai[i-1] > registro->chave){
        analise->transpre++;
        insBE(registro,Arvore->UU.U0.filho[i - 1],cresceu,registroretorno,ApRetorno,analise);
    }else{
        analise->transpre++;
        insBE(registro,Arvore->UU.U0.filho[i],cresceu,registroretorno,ApRetorno,analise);
    }
    //se cresceu faz os tratamentos de verificar se tem espaço e caso contrario dividir e tratar
    if(*cresceu){
        if(Arvore->UU.U0.quant < 2 * M){
            analise->transpre++;
            inserenaPaginaBI(Arvore,*registroretorno,*ApRetorno,analise);
            *cresceu = 0;
            return;
        }

        //divisão mesmo processo da divisão de pagina folha porem no indice
        TipoPagina *ApTemp = (TipoPagina*)malloc(sizeof(TipoPagina));
        if(ApTemp != NULL){
            ApTemp->Pt = Interna;
            ApTemp->UU.U0.quant = 0;

            if(i <= M + 1){
                
                inserenaPaginaBI(ApTemp,Arvore->UU.U0.pai[2 * M - 1],Arvore->UU.U0.filho[2 * M],analise);
                Arvore->UU.U0.quant--;
                inserenaPaginaBI(Arvore,*registroretorno,*ApRetorno,analise);
                analise->transpre+=2;
            }else{
                inserenaPaginaBI(ApTemp,*registroretorno,*ApRetorno,analise);
                analise->transpre++;
            }

            for(int j = M + 1;j < 2 * M;j++){
                inserenaPaginaBI(ApTemp,Arvore->UU.U0.pai[j],Arvore->UU.U0.filho[j + 1],analise);
                analise->transpre++;
            }
            //tratativa de ponterios e retornos
            ApTemp->UU.U0.filho[0] = Arvore->UU.U0.filho[M + 1];
            Arvore->UU.U0.quant = M;
            *registroretorno = Arvore->UU.U0.pai[M];
            *ApRetorno = ApTemp;
            analise->transpre+=3;
        }
    }
}

// Função para inserir um registro na árvore B* e lidar com o caso em que a raiz precisa ser dividida
void insereBE(Item *reg,TipoPagina **Arvore, Analise* analise) {
    short cresceu;
    TipoChave registroretorno;
    TipoPagina *ApRetorno, *ApTemp;

    if(*Arvore != NULL){

        insBE(reg,*Arvore,&cresceu,&registroretorno,&ApRetorno,analise);
        // Se a raiz foi dividida e precisa de uma nova raiz
        if (cresceu) {

            ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina));
            ApTemp->Pt = Interna;
            ApTemp->UU.U0.quant = 1;
            ApTemp->UU.U0.pai[0] = registroretorno;
            ApTemp->UU.U0.filho[1] = ApRetorno;
            ApTemp->UU.U0.filho[0] = *Arvore;
            *Arvore = ApTemp;
            analise->transpre+=5;
            
        }
    }else{
        //se a arvore ta vazia cria a raiz
        ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina));
        ApTemp->Pt = Externa;
        ApTemp->UU.U1.ne = 1;
        ApTemp->UU.U1.re[0] = *reg;
        ApTemp->UU.U1.prox = NULL;
        *Arvore = ApTemp;
        analise->transpre+=4;
        
    }
}

// Função para criar a árvore B* a partir de dados de um arquivo e realizar pesquisas
void criaarvoreBE(FILE *arquivo, Item *registro, DadosPesquisa *dados) {
    TipoPagina *Arvore;
    int i = 0;
    iniciaArvoreBE(&Arvore);
    dados->analise.timepre = (double)clock(); // Marca o tempo de início do processamento
    dados->analise.comppre += 1;
    // Lê os dados do arquivo e insere na árvore
    while ((fread(registro, sizeof(Item), 1, arquivo) == 1) && i < dados->quant) {

        insereBE(registro, &Arvore, &dados->analise);
        i++;
        dados->analise.transpre += 1;

    }
    dados->analise.timepre = (((double)clock() - dados->analise.timepre) / CLOCKS_PER_SEC); // Marca o tempo de fim do processamento

    // Realiza pesquisa na árvore
    dados->analise.timepesquisa = (double)clock();
    bool pesq;
    registro->chave = dados->chave;
    pesquisaArvorebEst(registro, Arvore, &dados->analise, &pesq);
    dados->analise.timepesquisa = (((double)clock() - dados->analise.timepesquisa) / CLOCKS_PER_SEC);

    // Imprime o resultado da pesquisa
    impreResultado(pesq, dados, registro);

    // Libera a memória da árvore
    liberaArvoreBE(&Arvore);
}
