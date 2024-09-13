#include "../include/quicksortE.h"

void FAVazia(TipoA *Area){ 
    int i; 
    Area->NumCelOcupadas = 0;
    Area->Primeiro = -1;
    Area->Ultimo = -1;
    Area->CelulasDisp = 0;
    for ( i = 0; i < M; i++){ 
        Area->itens[i].Ant = -1;
        Area->itens[i].Prox = i+1; 
    }
}

int ObterNumCelOcupadas(TipoA *Area){ 
    return (Area->NumCelOcupadas); 
}
void InsereItem(Item dado,TipoA *Area){ 
    int Pos , Disp , IndiceInsercao ; 
    if (Area->NumCelOcupadas == M){ 
        printf ("Tentativa de insercao em l i s ta cheia .\n" );
        return;
    } 
    Disp = Area->CelulasDisp;
    Area->CelulasDisp = Area->itens[Area->CelulasDisp].Prox; 
    Area->itens[Disp].chave = dado; 
    Area->NumCelOcupadas++; 
    if(Area->NumCelOcupadas == 1) /* Insercao do primeiro item */ { 
        Area->Primeiro = Disp;
        Area->Ultimo = Area->Primeiro;
        Area->itens[Area->Primeiro].Prox = -1;
        Area->itens [Area->Primeiro].Ant = -1; 
        return;
    } 
    Pos = Area->Primeiro;
    if(dado.notas < Area->itens[Pos].chave.notas) { /* Insercao realizada na primeira posicao */ 
        Area->itens[Disp].Ant = -1; 
        Area->itens[Disp].Prox = Pos; 
        Area->itens[Pos].Ant = Disp; 
        Area->Primeiro = Disp; 
        return;
    } 
    IndiceInsercao = Area->itens[Pos].Prox; 
    while ( IndiceInsercao != -1 && Area->itens[IndiceInsercao].chave.notas < dado.notas){
        Pos = IndiceInsercao; 
        IndiceInsercao = Area->itens[Pos].Prox;
    } 
    if( IndiceInsercao == -1) { 
        /*Insercao realizada na ultima posicao*/ 
        Area->itens[Disp].Ant = Pos;
        Area->itens[Disp].Prox = -1; 
        Area->itens[Pos].Prox = Disp; 
        Area->Ultimo = Disp; 
        return;
    }
    Area->itens[Disp].Ant = Pos;
    Area->itens[Disp].Prox = Area->itens[Pos].Prox;
    Area->itens[Pos].Prox = Disp; 
    Pos = Area->itens[Disp].Prox; 
    Area->itens[Pos].Ant = Disp;

} 

void RetiraPrimeiro(TipoA *Area,Item *Item){ 
    Apontador ProxTmp; 
    if(Area->NumCelOcupadas == 0){ 
        printf ("Erro - Lista vazia\n" ); 
        return;
    } 
    *Item = Area->itens[Area->Primeiro].chave;
    ProxTmp = Area->itens[Area->Primeiro].Prox;
    Area->itens[Area->Primeiro].Prox = Area->CelulasDisp;
    Area->CelulasDisp = Area->Primeiro; 
    Area->Primeiro = ProxTmp; 
    if((unsigned int)Area->Primeiro < M) Area->itens[Area->Primeiro].Ant = -1;
    Area->NumCelOcupadas--;
} 

void RetiraUltimo(TipoA *Area, Item *Item){ 
    Apontador AntTmp; 
    if(Area->NumCelOcupadas == 0){ 
        /* Area vazia */ 
        printf ("Erro - Lista vazia\n"); 
        return;
    } 
    *Item = Area->itens[Area->Ultimo].chave; 
    AntTmp = Area->itens[Area->Ultimo].Ant; 
    Area->itens[Area->Ultimo].Prox = Area->CelulasDisp; 
    Area->CelulasDisp = Area->Ultimo; 
    Area->Ultimo = AntTmp; 
    if((unsigned int)Area->Ultimo < M) Area->itens[Area->Ultimo].Prox = -1; 
    Area->NumCelOcupadas--;
}

void leSup(FILE **ArqlEs,Registro *UltLido,int *Ls,short *ondeler){
    fseek(*ArqlEs,(*Ls - 1)* sizeof(Registro),SEEK_SET);
    fread(UltLido,sizeof(Registro), 1,*ArqlEs);
    (*Ls)--;
    *ondeler = false;
}

void leInf(FILE **Arqlei,Registro *UltLido,int *Li,short *ondeler){
    fseek(*Arqlei,(*Li - 1)* sizeof(Registro),SEEK_SET);
    fread(UltLido,sizeof(Registro), 1,*Arqlei);
    (*Li)--;
    *ondeler = false;
}

void insArea(TipoA *area,Registro *UltLido,int *NRArea){
    InsereItem(*UltLido,area);
    *NRArea = ObterNumCelOcupadas(area);
}

void escreveMax(FILE **ArqlEs,Registro reg,int *Es){
    fseek(*ArqlEs,(*Es - 1)* sizeof(Registro),SEEK_SET);
    fwrite(&reg,sizeof(Registro),1,*ArqlEs);
    (*Es)--;
}

void escreveMin(FILE **ArqEi,Registro reg,int *Ei){
    fseek(*ArqEi,(*Ei - 1)* sizeof(Registro),SEEK_SET);
    fwrite(&reg,sizeof(Registro),1,*ArqEi);
    (*Ei)--;
}

void retiraMax(TipoA *area,Registro *reg,int *NRArea){
    RetiraUltimo(area,reg);
    *NRArea = ObterNumCelOcupadas(area);
}

void retiraMin(TipoA *area,Registro *reg,int *NRArea){
    RetiraPrimeiro(area,reg);
    *NRArea = ObterNumCelOcupadas(area);
}

void partitionE(FILE **ArqLei,FILE **ArqEi,FILE **ArqEs,TipoA area, int dir,int esq,int *i,int *j){
    int LeS = dir, EscS = dir, LeI = esq, EscI = esq, NRArea = 0, Linf = INT_MIN,Lsup = INT_MAX;
    short OndeLe = true;
    Registro UltLido, Reg;
    fseek(*ArqLei,(LeI - 1)* sizeof(Registro),SEEK_SET);
    fseek(*ArqEi,(EscI - 1)* sizeof(Registro),SEEK_SET);
    *i = esq - 1;
    *j = dir + 1;
    while(LeS >= LeI){
        if(NRArea < M - 1){
            if(OndeLe)
            leSup(ArqEi,&UltLido,&LeS,&OndeLe);
            else leInf(ArqLei,&UltLido,&LeI,&OndeLe);
            insArea(&area,&UltLido,&NRArea);
            continue;
        }
        if(LeS == EscS){
            leSup(ArqEs,&UltLido,&LeS,&OndeLe);

        }else if(LeI == EscI){
            leInf(ArqLei,&UltLido,&LeS,&OndeLe);
        }else if(OndeLe){
            leSup(ArqEs,&UltLido,&LeS,&OndeLe);
        }else{
            leInf(ArqLei,&UltLido,&LeI,&OndeLe);
        }
        if(UltLido.notas > LeS){
            *j = EscS;
            escreveMax(ArqEs,UltLido,&EscS);
            continue;
        }
        if(UltLido.notas < Linf){
            *i = EscI;
            escreveMin(ArqEi,UltLido,&EscI);
            continue;
        }
        insArea(&area,&UltLido,&NRArea);
        if(EscI - esq < dir - EscS){
            retiraMin(&area,&Reg,&NRArea);
            escreveMin(ArqEi,Reg,&EscI);
            Linf = Reg.notas;
        }else{
            retiraMax(&area,&Reg,&NRArea);
            escreveMax(ArqEs,Reg,&EscS);
            Lsup = Reg.notas;
        }
    }
    while(EscI <= EscS){
        retiraMin(&area,&Reg,&NRArea);
        escreveMin(ArqEi,Reg,&EscI);
    }
}

void quicksortExterno(FILE **ArqLi,FILE **ArqEi,FILE **ArqlEs,int dir, int esq){
    int i,j;
    TipoA area;
    if(dir - esq < 1) return;
    FAVazia(&area);
    partitionE(ArqLi,ArqEi,ArqlEs,area,dir,esq,&i,&j);
    if(i - esq < dir - j){
        quicksortExterno(ArqLi,ArqEi,ArqlEs,esq,i);
        quicksortExterno(ArqLi,ArqEi,ArqlEs,j,dir);
    }else{
        quicksortExterno(ArqLi,ArqEi,ArqlEs,j,dir);
        quicksortExterno(ArqLi,ArqEi,ArqlEs,esq,i);
    }
}