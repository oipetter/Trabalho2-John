#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct no{
    int dado;
    struct no *esquerda;
    struct no *direita;
};
typedef struct no NO;

void print(NO *root);
NO *inser(NO *root, int valor);
NO *balanc(NO *root, int valor);
int altarv(NO * root);
int fatb (NO * root);
NO *ROT_SIMPLES_DIR(NO *root);
NO *ROT_SIMPLES_ESQ(NO *root);

int main(){
    NO *root=NULL;
    int qtd;
    do{
        printf("\nQuantos (NOS) deseja incluir?  ");
        scanf("%d",&qtd);
    }while(qtd<=0);

    int i,x;
    for(i=0; i<qtd; i++){
       printf("valor:");
       scanf("%d",&x);
        root=inser(root, x);
    };
    printf("\n\n");
    po_print(root);
    return (0);
}


NO *inser(NO *root, int valor){
    if(root == NULL){
        NO *temp=(NO *)malloc(sizeof(NO));
        temp->dado=valor;
        temp->direita=NULL;
        temp->esquerda=NULL;
        return temp;
    }else{
        if(valor>root->dado){
           root->direita = inser(root->direita, valor);
        } else{
            if(valor<root->dado){
                root->esquerda = inser(root->esquerda, valor);
            };
        };
    root = balanc(root, valor);
    return root;
    };
}

NO *ROT_SIMPLES_DIR(NO *root){
    NO *FILHO_ESQUERDA = root->esquerda;
	NO *NETO_DIREITA = FILHO_ESQUERDA->direita;
	FILHO_ESQUERDA->direita = root;
	root->esquerda = NETO_DIREITA;
	return FILHO_ESQUERDA;
}


NO *ROT_SIMPLES_ESQ(NO *root){
	NO *FILHO_DIREITA = root->direita;
	NO *NETO_ESQUERDA = FILHO_DIREITA->esquerda;
    FILHO_DIREITA->esquerda = root;
    root->direita = NETO_ESQUERDA;
    return FILHO_DIREITA;
}


int fatb (NO * root){  // FATOR DE BALANCEAMENTO DA INSERÇÃO
	if (root == NULL)
		return 0;
	return altarv(root->esquerda) - altarv(root->direita);
}


int altarv(NO * root){
	int var_direita;
    int var_esquerda;
	if (root == NULL){
		return 0;
    };

    var_direita = altarv(root->direita);	
	var_esquerda = altarv(root->esquerda);
	
    if( var_esquerda > var_direita ){
		return var_esquerda + 1;
    }else{
		return var_direita + 1;
    };
}


NO *balanc(NO *root, int valor){   
    int auxiliar = fatb(root);

    if (auxiliar < -1 && valor < root->direita->dado){ // ROTAÇÃO DUPLA ESQUERDA
        root->direita = ROT_SIMPLES_DIR(root->direita);
        return ROT_SIMPLES_ESQ(root);
    };
    if (auxiliar > 1 && valor > root->esquerda->dado){  // ROTAÇÃO DUPLA DIREITA
        root->esquerda =  ROT_SIMPLES_ESQ(root->esquerda);
        return ROT_SIMPLES_DIR(root);
    };
    if (auxiliar < -1 && valor > root->direita->dado){ // ROTAÇÃO SIMPLES A ESQUERDA
        return ROT_SIMPLES_ESQ(root);
    };
    if (auxiliar> 1 && valor < root->esquerda->dado){  // ROTAÇÃO SIMPLES A DIREITA
        return ROT_SIMPLES_DIR(root);
    };
    return root;
}

void print(NO *root){
    if(root!=NULL){
        printf("  %d  ",root->dado);
        print(root->esquerda);
        print(root->direita);
    };
}

void po_print(NO *root){    // PRÉORDEM IMPRESSÃO
    if (root == NULL)
        return;
    printf(" %d ", root->dado);
    po_print(root->esquerda);
    po_print(root->direita);
}