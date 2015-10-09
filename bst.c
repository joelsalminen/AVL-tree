#include <stdio.h>
#include <stdlib.h>


struct node{
	int value;
	struct node *ptrLeft;
	struct node *ptrRight;
};
typedef struct node Node;


Node* memory_allocate(Node *ptr){
	if ((ptr = (Node*)malloc(sizeof(Node))) == NULL) {
            perror("Muistin varaus epäonnistui");
            exit(1);
	}
	return(ptr);
	
}


Node* add_node(int i, Node* tree){
	//
	if (tree == NULL){
		printf("%d\n", i);
		tree = memory_allocate(tree);
		tree->value = i;
		tree->ptrLeft = NULL;
		tree->ptrRight = NULL;
	}
	else{
		if (tree->value>=i){
			printf("%d->vasen->", tree->value);
			tree->ptrLeft = add_node(i, tree->ptrLeft);
		}
		else{
			printf("%d->oikea->",tree->value);
			tree->ptrRight = add_node(i, tree->ptrRight);
		}
	}

	return (tree);
}


void get_node(int i, Node *tree){
	//Etsii kysytyn avaimen puusta
	if (tree == NULL){
		printf("Kysyttyä alkiota ei löydy!\n");
	}

	else{
		if (tree->value > i){
			printf("%d ", tree->value);
			get_node(i, tree->ptrLeft);
		}
		else if (tree->value < i){
			printf("%d ",tree->value);
			get_node(i, tree->ptrRight);
		}
		else if (tree->value == i){
			printf("%d\n",tree->value);
		}
	}
}


void print_inorder(Node *tree){
	//Tulostaa solmuen arvot järjestyksessä vasen lapsi, solmu, oikea lapsi
	//
	if (tree != NULL){
		print_inorder(tree->ptrLeft);
		printf("%d ", tree->value);
		print_inorder(tree->ptrRight);
	}
}


int main (void){
	Node *root = NULL;
	int valinta;
	int i;
	int j;

	while (1){
		printf("Päävalikko\n\n");
		printf("1) Lisää alkio puuhun\n");
		printf("2) Etsi alkio puusta\n");
		printf("3) Tulosta kaikki alkiot\n");
		printf("0) Lopeta\n");
		printf("Valinta: ");
		scanf("%d", &valinta);
		if (valinta==1){
			printf("Anna lisättävä alkio: ");
			scanf("%d", &i);
			printf("Lisätään alkio %d puuhun paikalle\n", i);
			root = add_node(i, root);
		}
		else if (valinta==2){
			printf("Anna haettava alkio: ");
			scanf("%d", &j);
			get_node(j, root);
		}
		else if (valinta == 3){
			print_inorder(root);
		}
		else if (valinta==0){
			break;
		}
	}
	
	return 0;
}