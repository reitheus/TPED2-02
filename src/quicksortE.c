#include "../include/quicksortE.h"

void leSup(FILE **ArqlEs,Registro *UltLido,int *Ls,bool *ondeler){
    fseek(*ArqlEs,(*Ls - 1) * sizeof(Registro),SEEK_SET);
    if(fread(UltLido,sizeof(Registro), 1,*ArqlEs) != 1){
        printf("Erro na leitura superior.\n");
    }
    (*Ls)--;
    *ondeler = false;
}

void leInf(FILE **Arqlei,Registro *UltLido,int *Li,bool *ondeler){
    fseek(*Arqlei,(*Li - 1) * sizeof(Registro),SEEK_SET);
    if(fread(UltLido,sizeof(Registro), 1,*Arqlei) != 1){
        printf("Erro na leitura inferior.\n");
    }
    (*Li)++;
    *ondeler = true;
}

void insArea(TipoA *Area,Registro *UltLido,int *NRArea){
    int i;
    for(i = *NRArea;i > 0 && UltLido->notas < Area->itens[i - 1].notas;i--){
        Area->itens[i] = Area->itens[i-1];
    }
    Area->itens[i] = *UltLido;
    Area->NumCelOcupadas++;
}

void escreveMax(FILE **ArqlEs,Registro reg,int *Es){
    fseek(*ArqlEs,(*Es - 1) * sizeof(Registro),SEEK_SET);
    if(fwrite(&reg,sizeof(Registro),1,*ArqlEs) != 1){
        printf("Erro na escrita superior\n");
    }
    (*Es)--;
}

void escreveMin(FILE **ArqEi,Registro reg,int *Ei){
    fseek(*ArqEi,(*Ei - 1) * sizeof(Registro),SEEK_SET);
    if(fwrite(&reg,sizeof(Registro),1,*ArqEi) != 1){
        printf("Erro na escrita inferior\n");
    }
    (*Ei)++;
}

void retiraMax(TipoA *area,Registro *reg,int *NRArea){
    *reg = area->itens[*NRArea - 1];
    area->NumCelOcupadas--;

}

void retiraMin(TipoA *area,Registro *reg,int *NRArea){
    *reg = area->itens[0];
    area->NumCelOcupadas--;
    for(int i = 0;i < area->NumCelOcupadas;i++){
        area->itens[i] = area->itens[i + 1];
    }
}

void partitionE(FILE **ArqLi,FILE **ArqEi,FILE **ArqlEs,TipoA area, int esq,int dir,int *i,int *j,Analise *dados){
    int LeS = dir, EscS = dir, LeI = esq, EscI = esq;
    float Linf = INT_MIN,Lsup = INT_MAX;
    bool OndeLe = true;
    Registro UltLido, Reg;
    dados->numTransLeitura += 2;
    fseek(*ArqLi,(LeI - 1) * sizeof(Registro),SEEK_SET);
    fseek(*ArqEi,(EscI - 1) * sizeof(Registro),SEEK_SET);
    *i = esq - 1;
    *j = dir + 1;
    while(LeS >= LeI){
        if(area.NumCelOcupadas < M - 1){

            if(OndeLe){
                leSup(ArqlEs,&UltLido,&LeS,&OndeLe);
                dados->numTransLeitura+=2;

            }else{
                leInf(ArqLi,&UltLido,&LeI,&OndeLe);
                dados->numTransLeitura+=2;

            } 
            insArea(&area,&UltLido,&area.NumCelOcupadas);
            continue;
            
        }

        if(LeS == EscS){
            leSup(ArqlEs,&UltLido,&LeS,&OndeLe);
            dados->numTransLeitura+=2;

        }else if(LeI == EscI){
            leInf(ArqLi,&UltLido,&LeI,&OndeLe);
            dados->numTransLeitura+=2;

        }else if(OndeLe){
            leSup(ArqlEs,&UltLido,&LeS,&OndeLe);
            dados->numTransLeitura+=2;
        }else{
            leInf(ArqLi,&UltLido,&LeI,&OndeLe);
            dados->numTransLeitura+=2;
        }

        if(UltLido.notas > Lsup){
            *j = EscS;
            escreveMax(ArqlEs,UltLido,&EscS);
            dados->numTransEscrita++;
            dados->numTransLeitura++;
            continue;
        }
        
        if(UltLido.notas < Linf){
            *i = EscI;
            escreveMin(ArqEi,UltLido,&EscI);
            dados->numTransEscrita++;
            dados->numTransLeitura++;
            continue;
        }

        insArea(&area,&UltLido,&area.NumCelOcupadas);

        if(EscI - esq < dir - EscS){
            retiraMin(&area,&Reg,&area.NumCelOcupadas);
            escreveMin(ArqEi,Reg,&EscI);
            dados->numTransEscrita++;
            dados->numTransLeitura++;
            Linf = Reg.notas;
        }else{
            retiraMax(&area,&Reg,&area.NumCelOcupadas);
            escreveMax(ArqlEs,Reg,&EscS);
            dados->numTransEscrita++;
            dados->numTransLeitura++;
            Lsup = Reg.notas;
        }
        

    }
    while(EscI <= EscS){

        retiraMin(&area,&Reg,&area.NumCelOcupadas);
        escreveMin(ArqEi,Reg,&EscI);
        dados->numTransEscrita++;
        dados->numTransLeitura++;

    }
}

void quicksortExterno(FILE **ArqLi,FILE **ArqEi,FILE **ArqlEs,int esq, int dir,Analise *dados){
    int i,j;
    TipoA area;
    if(dir - esq < 1) return;
    area.NumCelOcupadas = 0;
    partitionE(ArqLi,ArqEi,ArqlEs,area,esq,dir,&i,&j,dados);
    if(i - esq < dir - j){
        quicksortExterno(ArqLi,ArqEi,ArqlEs,esq,i,dados);
        quicksortExterno(ArqLi,ArqEi,ArqlEs,j,dir,dados);
    }else{
        quicksortExterno(ArqLi,ArqEi,ArqlEs,j,dir,dados);
        quicksortExterno(ArqLi,ArqEi,ArqlEs,esq,i,dados);
    }
}

void quick(FILE *ArqP,DadosPesquisa *info){
    info->analise.time = (double)clock();
    quicksortExterno(&ArqP,&ArqP,&ArqP,1,info->quant,&info->analise);
    info->analise.time = (((double)clock()) - info->analise.time)/CLOCKS_PER_SEC;
}