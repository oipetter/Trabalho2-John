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
void po_print(NO *root);
NO *inser(NO *root, int valor);
NO *balanc(NO *root, int valor);
NO *balanc_remove(NO * root);
int altarv(NO * root);
int fatb (NO * root);
NO *ROT_SIMPLES_DIR(NO *root);
NO *ROT_SIMPLES_ESQ(NO *root);
NO * remove_valor(NO *root, int valor);
NO * menor_folha_esq(NO* root);
void deleta_arvore(NO *root);

int main(){
    NO *root=NULL;
    int op, valor;
    for(;;){
        printf("\n[1] - Para inserir um valor\n[2] - Apagar um valor\n[3] - Apagar a arvore\n[4] - Imprimir arvore\n[5] - Sair\nInforme valor:  ");
        scanf("%d",&op);
  
        switch (op){
            case 1:
                printf("Informe o valor:  ");
                scanf("%d",&valor);
                root=inser(root, valor);
                break;
            case 2:
                printf("\nInforme valor que deseja apagar:  ");
                scanf("%d",&valor);
                root = remove_valor(root, valor);
                break;
            case 3:
                deleta_arvore(root);
                printf("\nVALORES REMOVIDOS");
                root=NULL;
                break;
            case 4:
                printf("\n\n\n");
                printf("Lista por pre-ordem: ");
                po_print(root);
                printf("\n\n");
                break;
            case 5:
                deleta_arvore(root);
                free(root);
                return (1);
                break;    
        }; 
    };
    return (0);
}

void deleta_arvore(NO *root){     // APAGA A ARVORE TODA
	NO *auxiliar= root;
	if( auxiliar != NULL){
		deleta_arvore(auxiliar->esquerda);
    	deleta_arvore(auxiliar->direita);
	};
	free(auxiliar);
	return;
}

NO * remove_valor(NO *root, int valor){
	NO *auxiliar;

	if (root == NULL){    // CASO A ARVORE NÃO TENHA NENHUMA INFORMAÇÃO
	  printf("\nARVORE SEM DADOS A SEREM DELETADOS.\n\n");
      return root;
	}else{
		if (valor < root->dado){
			root->esquerda = remove_valor(root->esquerda, valor);  // FICAM PERCORRENDO OS NÓS DA ESQUERDA
        }else{
            if (valor > root->dado){
			root->direita = remove_valor(root->direita, valor); // FICAM PERCORRENDO OS NÓS DA DIREITA
	        }else{
                if(valor == root->dado){   // SITUAÇÃO ONDE O VALOR A SER REMOVIDO É ENCONTRADO
			        if (root->esquerda == NULL) {
				        auxiliar = root->direita;
				        free(root);
				        return auxiliar;  // APAGA O NÓ SE ELE FOR FOLHA
			        }else{
                        if (root->direita == NULL) {
				            auxiliar = root->esquerda;
				            free(root);
				            return auxiliar;    // APAGA O NÓ SE ELE FOR FOLHA
			            };
                    };
	
			        auxiliar = menor_folha_esq(root->direita);	// CASO O DADO A SER APAGADO NÃO SEJA UMA FOLHA OU POSSUA MAIS DE UM NÓ FILHO 		
			        root->dado = auxiliar->dado;  // ROOT RECEBE O DADO ENCONTRADO NA LINHA SUPERIOR
			        root->direita = remove_valor(root->direita, auxiliar->dado);
		        
                };
            };
		    root = balanc_remove(root);
		    return root;
	    };
    };
}

NO * menor_folha_esq(NO* root){ // FUNÇÃO QUE PERCORRE A ARVORE ATÉ CHEGAR NA FOLHA A ESQUERDA
    NO *auxiliar = root;
    while (auxiliar && auxiliar->esquerda != NULL){ // SAIRA DO LOOP ASSIM QUE CHEGAR NA ULTIMA FOLHA A ESQUERDA
        auxiliar = auxiliar->esquerda;
    };
    return auxiliar;
}


NO *balanc_remove(NO * root){  // FUNÇÃO QUE ORGANIZA A ARVORE APÓS UMA EXCLUSÃO
    int auxiliar = fatb(root);

    if (auxiliar > 1 && fatb( root->esquerda ) >= 0){
        root = ROT_SIMPLES_DIR(root);
    };
    if (auxiliar > 1 && fatb( root->esquerda ) < 0){
        root->esquerda =  ROT_SIMPLES_ESQ(root->esquerda);
        root = ROT_SIMPLES_DIR(root);
    };
    if (auxiliar < -1 && fatb( root->direita ) <= 0){
        root = ROT_SIMPLES_ESQ(root);
    };
    if (auxiliar < -1 && fatb( root->direita ) > 0){
        root->direita = ROT_SIMPLES_DIR(root->direita);
        root = ROT_SIMPLES_ESQ(root);
    };
    return root;
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


void po_print(NO *root){    // PRÉORDEM IMPRESSÃO
    if (root == NULL)
        return;
    printf(" %d ", root->dado);
    po_print(root->esquerda);
    po_print(root->direita);
}