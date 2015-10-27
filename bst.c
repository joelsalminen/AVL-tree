#include <stdio.h>
#include <stdlib.h>


struct node{
	int value;
	struct node *ptrLeft;
	struct node *ptrRight;
};
typedef struct node Node;


void read_file(char filename [30]){
	FILE* entry_file;
	char entry[5];
	if ((entry_file = fopen(filename, "r")) == NULL) {
		perror("Tiedoston avaaminen epäonnistui.");
		//exit(1);
	}
	while (fgets(entry, 5, entry_file) != NULL) {
		printf("%s\n", entry);

	}
}


Node* memory_allocate(Node *ptr){
	//varaa muistia uudelle solmulle
	if ((ptr = (Node*)malloc(sizeof(Node))) == NULL) {
            perror("Muistin varaus epäonnistui");
            exit(1);
	}
	return(ptr);
	
}


Node* add_node(int i, Node* tree){
	//Lisää uuden solmun puuhun
	if (tree == NULL){
		tree = memory_allocate(tree);
		tree->value = i;
		tree->ptrLeft = NULL;
		tree->ptrRight = NULL;
	}
	else{
		if (tree->value>=i){
			if (tree->ptrLeft == NULL)
				printf("Arvo %d asetetaan solmun %d vasemmanpuoleiseksi lapseksi.\n\n", i, tree->value);
			tree->ptrLeft = add_node(i, tree->ptrLeft);
		}
		else{
			if (tree->ptrRight == NULL)
				printf("Arvo %d asetetaan solmun %d oikeanpuoleiseksi lapseksi.\n\n", i, tree->value);
			tree->ptrRight = add_node(i, tree->ptrRight);
		}
	}

	return (tree);
}


void get_node(int i, Node *tree){
	//Etsii kysytyn avaimen puusta
	if (tree == NULL){
		printf("\nKysyttyä alkiota ei löydy!\n\n");
	}

	else{
		if (tree->value > i){
			printf("%d->vasen->", tree->value);
			get_node(i, tree->ptrLeft);
		}
		else if (tree->value < i){
			printf("%d->oikea->",tree->value);
			get_node(i, tree->ptrRight);
		}
		else if (tree->value == i){
			printf("%d\n",tree->value);
		}
	}
}


void print_inorder(Node *tree){
	//Tulostaa solmuen arvot järjestyksessä vasen lapsi, solmu, oikea lapsi
	if (tree){
		print_inorder(tree->ptrLeft);
		printf("%d ", tree->value);
		print_inorder(tree->ptrRight);
	}
}


void free_memory(Node* tree){
	//vapauttaa mallocilla varatun muistin ohjelman lopussa
	if (tree){
		if (tree->ptrLeft != NULL)
			free_memory(tree->ptrLeft);
		if (tree->ptrRight != NULL)
			free_memory(tree->ptrRight);
		free(tree);

	}
}


int main (void){
	Node *root = NULL;
	int valinta;
	int i;
	int j;

	while (1){
		read_file("alkiot.txt");
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
			root = add_node(i, root);
		}
		else if (valinta==2){
			printf("Anna haettava alkio: ");
			scanf("%d", &j);
			get_node(j, root);
		}
		else if (valinta == 3){
			print_inorder(root);
			printf("\n");
		}
		else if (valinta==0){
			free_memory(root);
			break;
		}
		else{
			printf("Anna kelvollinen syöte!\n\n");
		}
	}
	
	return 0;
}