#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


struct node{
	int value;
	int height;
	struct node *ptrLeft;
	struct node *ptrRight;
};
typedef struct node Node;


Node* read_file(char filename [30], Node* tree);
Node* add_node(int i, Node* tree);
Node* memory_allocate(Node *ptr);
void get_node(int i, Node *tree);
void print_inorder(Node *tree);
void free_memory(Node* tree);
Node* left_rotate(Node* tree);
Node* right_rotate(Node* tree);
void set_height(Node* tree);


Node* left_rotate(Node* tree){
	Node *temp, *newRoot;
	temp = tree->ptrLeft->ptrRight;
	tree->ptrLeft->ptrRight = NULL;
	newRoot = tree->ptrLeft;
	tree->ptrLeft = temp;
	newRoot->ptrRight = tree;
	set_height(newRoot);
	set_height(tree);
	return (newRoot);
}


Node* right_rotate(Node* tree){
	Node *temp, *newRoot;
	temp = tree->ptrRight->ptrLeft;
	tree->ptrRight->ptrLeft = NULL;
	newRoot = tree->ptrRight;
	tree->ptrRight = temp;
	newRoot->ptrLeft = tree;
	set_height(newRoot);
	set_height(tree);
	return (newRoot);
}


Node* read_file(char filename [30], Node* tree){
	FILE* entry_file;
	int key;
	if ((entry_file = fopen(filename, "r")) == NULL) {
		perror("Tiedoston avaaminen epäonnistui\n");
		return NULL;
	}
	while (fscanf(entry_file, "%d", &key) == 1) {
		tree = add_node(key, tree);
	}
	fclose(entry_file);
	return tree;
}


Node* memory_allocate(Node *ptr){
	//varaa muistia uudelle solmulle
	if ((ptr = (Node*)malloc(sizeof(Node))) == NULL) {
            perror("Muistin varaus epäonnistui");
            exit(1);
	}
	return(ptr);
	
}


int max(int i, int j){
	if (i>j){
		return i;
	}
	else{
		return j;
	}
}


void set_height(Node* tree){
	if (tree->ptrLeft == NULL && tree->ptrRight == NULL){
		tree->height = 0;
	}
	else if(tree->ptrLeft != NULL && tree->ptrRight == NULL){
		tree->height = tree->ptrLeft->height + 1;
	}
	else if(tree->ptrLeft == NULL && tree->ptrRight != NULL){
		tree->height = tree->ptrRight->height + 1;
	}
	else {
		tree->height = max(tree->ptrRight->height, tree->ptrLeft->height) + 1;
	}
}


int get_height(Node* tree){
	if (tree == NULL)
		return -1;
	else
		return tree->height;
}


Node* add_node(int i, Node* tree){
	//Lisää uuden solmun puuhun
	if (tree == NULL){
		tree = memory_allocate(tree);
		tree->value = i;
		tree->ptrLeft = NULL;
		tree->ptrRight = NULL;
	}
	//Vasempaan haaraan lisääminen
	else if (tree->value > i){
		if (tree->ptrLeft == NULL)
			printf("Arvo %d asetetaan solmun %d vasemmanpuoleiseksi lapseksi.\n\n", i, tree->value);
		tree->ptrLeft = add_node(i, tree->ptrLeft);
		//tasapainottaminen:
		if(get_height(tree->ptrLeft) == get_height(tree->ptrRight)+ 2){
			if(i < tree->ptrLeft->value){
				tree = left_rotate(tree);
				printf("L\n");
			}
			else{
				tree->ptrLeft = right_rotate(tree->ptrLeft);
				tree = left_rotate(tree);
				printf("LR\n");
			}
		}
	}

	else if (tree->value < i){
		if (tree->ptrRight == NULL)
			printf("Arvo %d asetetaan solmun %d oikeanpuoleiseksi lapseksi.\n\n", i, tree->value);
		tree->ptrRight = add_node(i, tree->ptrRight);
		//tasapainottaminen:
		if (get_height(tree->ptrRight) == get_height(tree->ptrLeft) + 2){
			if (i > tree->ptrRight->value){
				tree = right_rotate(tree);
				printf("R\n");
			}
			else{
				tree->ptrRight =  left_rotate(tree->ptrRight);
				tree = right_rotate(tree);
				printf("RL\n");
			}
		}
	}
	else{
		printf("arvo on jo puussa\n");
	}
	//puun korkeuden määrittäminen
	set_height(tree);
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


void print_reverse_inorder(Node* tree){
	if (tree){
		print_reverse_inorder(tree->ptrRight);
		printf("%d(%d)\n", tree->value, tree->height);
		print_reverse_inorder(tree->ptrLeft);
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


int main (int argc, char *argv[]){
	Node *root = NULL;
	int valinta;
	int i;
	int j;

	while (1){
		if (argc > 1){
			root = read_file(argv[1], root);
		}

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
			print_reverse_inorder(root);
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