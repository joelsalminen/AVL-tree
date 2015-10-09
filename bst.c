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


Node* create_node(int i, Node* tree){
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
			tree->ptrLeft = create_node(i, tree->ptrLeft);
		}
		else{
			printf("%d->oikea->",tree->value);
			tree->ptrRight = create_node(i, tree->ptrRight);
		}
	}

	return (tree);

}


int main (void){
	Node *root = NULL;
	int i;
	printf("Anna lisättävä luku (ctrl+d lopettaa): ");
	while (scanf("%d", &i)!=EOF){
		root = create_node(i, root);
	}
	return 0;
}