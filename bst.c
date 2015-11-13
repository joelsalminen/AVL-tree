/*Joel Salminen
Opiskelijanumero: 0401495

Kääntämiskomento:
gcc -o 0401495 0401495.c -W -Wall -std=c99*/


#include <stdio.h>
#include <stdlib.h>


struct node{
	int key;
	int height;
	struct node *ptrLeft;
	struct node *ptrRight;
};
typedef struct node Node;


/* Aliohjelmien esittelyt: */
Node* left_rotate(Node* tree);
Node* right_rotate(Node* tree);
Node* read_file(char filename [30], Node* tree);
Node* memory_allocate(Node *ptr);
int max(int i, int j);
int get_height(Node* tree);
Node* avl_insert(int k, Node* tree);
void get_node(int i, Node *tree);
void print_tree(Node *tree, int tabs);
void free_memory(Node* tree);


Node* right_rotate(Node* tree){
	/* R-rotaatio */
	Node *temp, *newRoot;
	temp = tree->ptrLeft->ptrRight; /* otetaan vasemman lapsen oikea lapsi talteen temp-muuttujaan */
	tree->ptrLeft->ptrRight = NULL;
	newRoot = tree->ptrLeft; /* otetaan vasen lapsi talteen muuttujaan newRoot */
	tree->ptrLeft = temp; /* alkuperäisen alipuun juuren vasemmaksi lapseksi temp */
	newRoot->ptrRight = tree; /* alkuperäisen alipuun juuri uuden juuren oikeaksi lapseksi */

	/* Korjataan solmujen korkeudet: */
	tree->height = max(get_height(tree->ptrLeft), get_height(tree->ptrRight)) + 1;
	newRoot->height = max(get_height(newRoot->ptrLeft), get_height(newRoot->ptrRight)) + 1;
	return (newRoot);
}


Node* left_rotate(Node* tree){
	/* L-rotaatio, peilikuva R-rotaatiolle. */
	Node *temp, *newRoot;
	temp = tree->ptrRight->ptrLeft;
	tree->ptrRight->ptrLeft = NULL;
	newRoot = tree->ptrRight;
	tree->ptrRight = temp;
	newRoot->ptrLeft = tree;

	tree->height = max(get_height(tree->ptrLeft), get_height(tree->ptrRight)) + 1;
	newRoot->height = max(get_height(newRoot->ptrLeft), get_height(newRoot->ptrRight)) + 1;
	return (newRoot);
}


Node* read_file(char filename [30], Node* tree){
	/* Lukee tiedoston ja lisää tiedostosta haetut alkiot puuhun. */
	FILE* entry_file;
	int key;
	if ((entry_file = fopen(filename, "r")) == NULL) {
		perror("Tiedoston avaaminen epäonnistui\n");
		return NULL;
	}
	while (fscanf(entry_file, "%d", &key) == 1) {
		tree = avl_insert(key, tree);
	}
	fclose(entry_file);
	return tree;
}


Node* memory_allocate(Node *ptr){
	/* Varaa muistia uudelle solmulle. */
	if ((ptr = (Node*)malloc(sizeof(Node))) == NULL) {
            perror("Muistin varaus epäonnistui");
            exit(1);
	}
	return(ptr);
	
}


int max(int i, int j){
	/* Palauttaa annetuista parametreista suuremman. */
	if (i>j){
		return i;
	}
	else{
		return j;
	}
}


int get_height(Node* tree){
	/* Hakee puun korkeuden. Palauttaa arvon 0, jos puu on tyhjä. */
	if (tree == NULL)
		return 0;
	else
		return tree->height;
}


Node* avl_insert(int k, Node* tree){
	/* Lisää uuden solmun puuhun. */
	if (tree == NULL){
		tree = memory_allocate(tree);
		tree->key = k;
		tree->ptrLeft = NULL;
		tree->ptrRight = NULL;
	}
	/* Vasempaan haaraan lisääminen. */
	else if (tree->key > k){
		if (tree->ptrLeft == NULL)
			printf("Arvo %d asetetaan solmun %d vasemmanpuoleiseksi lapseksi.\n", k, tree->key);
		tree->ptrLeft = avl_insert(k, tree->ptrLeft);
		/* tasapainottaminen: */
		if(get_height(tree->ptrLeft) == get_height(tree->ptrRight)+ 2){
			if(k < tree->ptrLeft->key){
				tree = right_rotate(tree);
				printf("R-rotaatio\n");
			}
			else{
				tree->ptrLeft = left_rotate(tree->ptrLeft);
				tree = right_rotate(tree);
				printf("LR-rotaatio\n");
			}
		}
	}
	/* Oikeaan haaraan lisääminen */
	else if (tree->key < k){
		if (tree->ptrRight == NULL)
			printf("Arvo %d asetetaan solmun %d oikeanpuoleiseksi lapseksi.\n", k, tree->key);
		tree->ptrRight = avl_insert(k, tree->ptrRight);
		/* tasapainottaminen: */
		if (get_height(tree->ptrRight) == get_height(tree->ptrLeft) + 2){
			/* R-rotaatio */
			if (k > tree->ptrRight->key){
				tree = left_rotate(tree);
				printf("L-rotaatio\n");
			}
			else{
				/* RL-rotaatio */
				tree->ptrRight =  right_rotate(tree->ptrRight);
				tree = left_rotate(tree);
				printf("RL-rotaatio\n");
			}
		}
	}
	else{
		printf("Arvo on jo aikaisemmin lisätty puuhun!\n");
	}
	/* Korjataan solmum korkeus. */
	tree->height = max(get_height(tree->ptrLeft), get_height(tree->ptrRight)) + 1;
	return (tree);
}


void get_node(int i, Node *tree){
	/* Etsii kysytyn avaimen puusta. */
	if (tree == NULL){
		printf("Kysyttyä alkiota ei löytynyt.\n");
	}

	else{
		if (tree->key > i){
			printf("Etsitään avaimen %d sisältävän solmun vasemmasta haarasta.\n", tree->key);
			get_node(i, tree->ptrLeft);
		}
		else if (tree->key < i){
			printf("Etsitään avaimen %d sisältävän solmun oikeasta haarasta.\n",tree->key);
			get_node(i, tree->ptrRight);
		}
		else if (tree->key == i){
			printf("Alkio %d löytyi.\n",tree->key);
		}
	}
}


void print_tree(Node* tree, int tabs){
	/* Tulostaa puurakenteen käänteisessä sisäjärjestyksessä. Puurakenne muodostuu
	tulostamalla sopiva määrä sisennysmerkkejä ennen jokaista avainarvoa. Parametri 
	tabs pitää sisällään sisennysmerkkien lukumäärän */
	int i = tabs;
	if (tree){
		print_tree(tree->ptrRight, tabs + 1);
		while (i>0){
			printf("\t");
			i--;
		}
		printf("%d(%d)\n", tree->key, tree->height);
		print_tree(tree->ptrLeft, tabs + 1);
	}
}


void free_memory(Node* tree){
	/* Vapauttaa dynaamisesti varatun muistin. */
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

	/* Luetaan komentoriviltä tiedostonimi ja tallennetaan tiedostosta löytyvät 
	kokonaisluvut puuhun. */
	if (argc > 1){
		root = read_file(argv[1], root);
	}

	while (1){
		printf("\nPäävalikko\n\n");
		printf("1) Lisää alkio puuhun\n");
		printf("2) Etsi alkio puusta\n");
		printf("3) Tulosta kaikki alkiot\n");
		printf("0) Lopeta\n");
		printf("Valinta: ");
		scanf("%d", &valinta);
		if (valinta==1){
			printf("Anna lisättävä alkio: ");
			scanf("%d", &i);
			root = avl_insert(i, root);
		}
		else if (valinta == 2){
			printf("Anna haettava alkio: ");
			scanf("%d", &i);
			get_node(i, root);
		}
		else if (valinta == 3){
			if (root){
				printf("\n");
				print_tree(root, 0);
				printf("\n");
			}
			else {
				printf("Lisää ensin alkioita puuhun!\n");
			}
		}
		else if (valinta == 0){
			free_memory(root);
			break;
		}
		else{
			printf("Anna kelvollinen syöte!\n");
		}
	}
	return 0;
}
