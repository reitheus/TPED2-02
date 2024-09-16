#include "../include/menu.h"
#include "../include/item.h"
#include "../include/quicksortE.h"


#define TAMCOPIA 1000
#define TAMREAD 101


int copiaFile(FILE *pFile, FILE *pFile2, DadosPesquisa entrada){
    int i = 0;
    int quant = TAMCOPIA;
    Item itens[TAMCOPIA];
    fseek(pFile, 0, SEEK_SET);
    fseek(pFile2, 0, SEEK_SET);
    while(i < entrada.quant ){
        if((entrada.quant - i) < TAMCOPIA){
            quant = (entrada.quant - i);
        }
        
        fread(itens, sizeof(Item), quant, pFile);
        fwrite(itens, sizeof(Item), quant, pFile2);
        i += quant;

    }
    return 0;
}


//converte os itens de um vetor linha para uma struct
//entrada: linha lida do texto, item passado por ponteiro que vai ser retornado
int converteLinhaEmStruct(char *linha, Item *item){
    int i = 0, j = 0;
    char texto[5][51];//matriz de textos
    //texto[0] é numero de inscrição
    //texto[1] é nota do aluno
    // texto[2] estado do aluno
    // texto[3] é Cidade do aluno
    // texto[4] éCurso do aluno
    j = 0;
    //Os loops abaixo copiam o dado em questão em sequência para uma matriz temporaria
    while(i < 8){//copia os dados do número de inscrição da linha lida para uma matriz temporaria
        texto[0][j] = linha[i];
        i++;
        j++;
    }
    i = 10;
    j = 0;
    while(i < 15){// copia a nota do aluno para matriz
        texto[1][j] = linha[i];
        i++;
        j++;
    }
    i = 15;
    j = 0;
    while(i < 17){//copia o estado do aluno para matriz
        texto[2][j] = linha[i];
        i++;
        j++;
    }
    i = 19;
    j = 0;
    while(i < 68){//copia  a cidade do aluno para matriz
        texto[3][j] = linha[i];
        i++;
        j++;
    }
    i = 69;
    j = 0;
    while(i < 99){// copia o curso do aluno para matriz
        texto[4][j] = linha[i];
        i++;
        j++;
    }

    //o proximo passo é pegar os dados e colocar na struct
    item->numInscricao = atoi(texto[0]);//converte o dado para inteiro e atribui na struct
    item->notas = atof(texto[1]);//converte o dado para float e atribui na struct
    strcpy(item->estado, texto[2]);//copia o dado para struct
    strcpy(item->cidade, texto[3]);
    strcpy(item->curso, texto[4]);
    return 0;
}

//Parametros:Arquivo original que vai ser convertido, arquivo que foi convertido e vai retornar, entrada de dados
int conversorBinToTxt(FILE *pFile, DadosPesquisa entrada){
    FILE *pFile2;
    pFile2 = fopen("ordenado.txt", "w");
    Item item;
    for(int i = 0; i < entrada.quant ; i++){

        fread(&item, sizeof(Item), 1, pFile2);
        fprintf(pFile2, "%8ld %4.1f %s %s %s \n",item.numInscricao, item.notas, item.estado, item.cidade, item.curso);
    }
    return 0;
    fclose(pFile2);
}



//converte o arquivo pFile do tipo txt no arquivo pFile2 do tipo binario
//pFile arquivo txt, pFile arquivo Binario, dados de entrada
int conversor(FILE *pFile, FILE *pFile2, DadosPesquisa entrada){
   char linha[TAMREAD];
   Item item;

    for(int i = 0; i < entrada.quant ; i++){

        fgets(linha, TAMREAD, pFile);
        converteLinhaEmStruct(linha, &item);
        fwrite(&item, sizeof(Item), 1, pFile2);

    }
    return 0;
}

int inverte(FILE *pFile,FILE *pFile2,DadosPesquisa  entrada){
    Item item;
    int i, j = entrada.quant;

    for(i = 0; i < entrada.quant; i++){
        j--;
        fseek(pFile,j * sizeof(Item), SEEK_SET);
        fread(&item,sizeof(Item), 1, pFile);
        fwrite(&item,sizeof(Item), 1, pFile2);
    }
    return 0;
}


//arquivo que vai ser gerado por stream, Os dados de entrada
int converte(FILE *pFile, DadosPesquisa entrada){
    FILE *pFile2;
    

    switch(entrada.situacao){
        case 1:
            pFile = fopen("aleatorio.bin", "r+b");
            pFile2 = fopen("ascendente.bin", "w+b");
            
            fseek(pFile, 0, SEEK_SET);
            fseek(pFile2, 0, SEEK_SET);
            copiaFile(pFile, pFile2, entrada);
            fseek(pFile, 0, SEEK_SET);
            fseek(pFile2, 0, SEEK_SET);

            quicksortExterno(&pFile2, &pFile2, &pFile2, 1, entrada.quant, &entrada.analise);
       
        break;
        case 2:
            pFile = fopen("ascendente.bin", "r+b");
            pFile2 = fopen("descendente.bin", "w+b");
            inverte(pFile, pFile2, entrada);
 
        break;
        case 3:
            pFile = fopen("PROVAO.TXT", "r");
            if(pFile == NULL){
                printf("Não abriu arquivo");
                exit(1);

            }
            
            pFile2 = fopen("aleatorio.bin", "wb");
            conversor(pFile, pFile2, entrada);
            //printArquivo(entrada.quant, pFile);
            
        break;
        default:
            printf("\nOpção incorreta\n");

    }

    fclose(pFile);
    fclose(pFile2);
    return 0;
}



