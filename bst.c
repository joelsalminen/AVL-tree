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
		tree = memory_allocate(tree);
		tree->value = i;
		tree->ptrLeft = NULL;
		tree->ptrRight = NULL;
	}
	else{
		if (tree->value>=i){
			tree->ptrLeft = create_node(i, tree->ptrLeft);
		}
		else{
			tree->ptrRight = create_node(i, tree->ptrRight);
		}
	}

	return (tree);

}


int main (void){
	Node *root = NULL;
	root = create_node(5, root);
	root = create_node(2, root);
	root = create_node(6, root);
	printf("%d\n",root->value);
	printf("%d\n", root->ptrLeft->value);
	printf("%d\n", root->ptrRight->value);
	return 0;
}



















