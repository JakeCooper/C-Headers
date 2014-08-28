/*
 *  Author:      Jake Cooper
 *  Date:        November 29th, 2013
 *  File name:   LinkedLists.c
 *  Description: Includes a variety of node functions. Call to create, manipulate and delete nodes. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <linkedlib.h>

typedef int Info;
typedef struct {
	Info info;
} Item;
typedef Item* ItemRef;

typedef struct NodeStruct* NodeRef;
typedef struct NodeStruct {
	ItemRef item;
	NodeRef next;
	NodeRef prev;
} Node;

typedef struct {
	NodeRef head;
	NodeRef tail;
	int size;
} Dlist;
typedef Dlist* DlistRef;

ItemRef initializeItem(Info g){
	/* allocates storage to store one item and sets it to value g */
	 Item* item;
	 item = malloc (sizeof(Item));
	 	 if (item == NULL){
	 		 //malloc failed case
	 		 printf("Item malloc() failed\n");
	 		 exit (EXIT_FAILURE);
	 	 }/*if*/
	 //malloc success
	 item->info = g;
	 return item;
}/*initializeItem*/

NodeRef initializeNode(Info g){
	/* allocates storage to store one node with item value g and NULL links pointers*/
	Node* node;
	node = (Node*) malloc (sizeof(Node));
	if (node == NULL){
		//malloc failed case
		printf("Node malloc() failed\n");
		exit (EXIT_FAILURE);
	}/*if*/
	//malloc success case
	node->item = initializeItem(g);
	node->next = NULL;
	node->prev = NULL;
	return node;
}/*initializeNode*/

DlistRef initializeDlist(void){
	/* allocates storage to for a list header with NULL head and tail and item count 0 */
	Dlist* list;
	list = (Dlist*) malloc (sizeof(Dlist));
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return list;
}/*initializeDlist*/

void printListForward(DlistRef dl, char* title){
/* print list items in forward order starting at head */
/* title can be used to add a descriptive title for the list output */
	printf("Forward: "); //printing the list forwards
	if (dl->head == NULL){
		//list empty case
        printf("Empty list");
    } /*if*/

	NodeRef current = dl->head;

    while (current != NULL){
        printf("%d ", current->item->info); //printing list forwards
        current = current->next;
    }/*while*/
    printf("\n"); //append newline
}/*printListForward*/

void printListBackward(DlistRef dl, char* title){
	/* print list items in backward order starting at tail */
	/* title can be used to add a descriptive title for the list output */
	printf("Backward: "); //printing the list backwards
	if (dl->head == NULL){
		//list empty case
		printf("Empty list");
	} /*if*/

	NodeRef current = dl->tail;
	while (current != NULL){
		printf("%d ", current->item->info); //printing list backwards
		current = current->prev;
	}/*while*/
	printf("\n"); //append newline
}/*printListForward*/

void insertNodeAtHead(DlistRef dl, Info g){
/* insert a new node with value g at the beginning of the list */
	NodeRef n = initializeNode(g);
	if (dl->head == NULL){
		//Empty list case
		dl->head = n;
		dl->tail = n;
		dl->size++;
	}else{
		//Not empty list case
		n->next = dl->head;
		dl->head->prev = n;
		dl->head = n;
		dl->size++;
	}/*if+else*/
}/*insertNodeAtHead*/

void insertNodeAtTail(DlistRef dl, Info g){
/* insert a new node at the end of the list with value g */
	NodeRef n = initializeNode(g);
	if (dl->head == NULL){
		//Empty list case
		dl->tail = n;
		dl->head = n;
		dl->size++;
	} else {
		//Not empty list case
		n->prev = dl->tail;
		dl->tail->next = n;
		dl->tail = n;
		dl->size++;
	}
}

NodeRef findNode(DlistRef dl, Info g){
/* find the node with value g in the list and return its reference */
/* returns NULL if not found*/

	NodeRef c = dl->head;

	while(c != NULL){
		//check if node info matches g
		if (c->item->info == g){
			return c;
		}
		c = c->next; //move to next node
	}/*while*/
	return NULL; //return NULL if nothing matches
}/*findNode*/

void insertNodeAt(DlistRef dl, Info oldval, Info newval){
/* insert a new node with value newval after the node with value oldval */
/* if oldval is not found in the list, insert newval at the end of the list */
/* use findNode() to implement this function */
	NodeRef current = findNode(dl, oldval); //get node with oldval
	NodeRef new = initializeNode(newval); //create node with newval
		if (current == NULL){
			//No node found case
			printf("Node not found, inserting at tail\n"); //error message
			insertNodeAtTail(dl, newval); //response to error by adding node to end
			dl->size++;
		}else{
			//Node found case
			current->next->prev = new;
			new->next = current->next; //Find node pointers
			current->next = new;
			new->prev = current;
			dl->size++;
		}/*if+else*/
}/*insertNodeAt*/

NodeRef updateNode(DlistRef dl, Info oldval, Info newval){
/* find the first node with value oldval and update the value to newval */
/* use findNode() to implement this function */
	NodeRef current = findNode(dl, oldval);
	if (current == NULL){
		//No node found case
		printf("Node not found\n");
		exit(EXIT_FAILURE);
	}else{
		current->item->info = newval; //put newval in info
	}/*if+else*/
	return current;
}/*updateNode*/

Info sumAllNodes(DlistRef dl){
/* computes the sum of the Info values of all the nodes in the list */
	Info sum = 0;
	NodeRef current = dl->head;
	while(current != NULL){
		//Read from head to tail
		sum += current->item->info; //add the value of the node to sum
		current = current->next; //shift nodes
	}
	return sum;
}
void deallocateNode(NodeRef x){
/* deallocate storage for node x and the item it points to */
	free(x->item);
	free(x);
}

bool deleteNodeAtHead(DlistRef dl, Info* g){
/* delete node at the head of the list including deallocating the space */
/* for the node and the item it points to by calling deallocateNode */
/* return false if list is empty and true otherwise */
/* return value of deleted item in g */
	NodeRef current = dl->head;
	if (current == NULL){
		//empty list case
		printf("List Empty\n");
		return false;
	} else if(current->next == NULL) {
		//1 item list case
		*g = current->item->info;
		dl->head = NULL;
		dl->tail = NULL;
		deallocateNode(current);
		dl->size--;
		return true;
	} else {
		//list has more than 1 item
		*g = current->item->info;
		current->next->prev = NULL;
		dl->head = current->next;
		dl->size--;
		deallocateNode(current);
	}
	return true;
}

bool deleteNodeAtTail(DlistRef dl, Info* g){
/* delete node at the tail of the list including deallocating the space */
/* for the node and the item it points to by calling deallocateNode */
/* return false if list is empty and true otherwise */
/* return value of deleted item in g */
	NodeRef current = dl->tail;
	if (current == NULL){
		//empty list case
		printf("List Empty\n");
		return false;
	} else if(current->prev == NULL) {
		//1 item list case
		*g = current->item->info;
		dl->head = NULL;
		dl->tail = NULL;
		deallocateNode(current);
		dl->size--;
		return true;
	} else {
		//list has more than 1 item
		*g = current->item->info;
		current->prev->next = NULL;
		dl->tail = current->prev;
		deallocateNode(current);
		dl->size--;
	}
	return true;
}

bool deleteNodeAt(DlistRef dl, Info g){
/* delete the first node with value g in the list */
/* return false if list is empty or item is not found; true otherwise */
	NodeRef current = findNode(dl, g);

	if (current != NULL){
		if (current->next == NULL && current->prev == NULL){
			//1 item in list
			dl->head = NULL;
			dl->tail = NULL;
		} else if (current->prev == NULL){
			//first item
			current->next->prev = NULL;
			dl->head = current->next;
		} else if (current->next == NULL){
			//Last item
			current->prev->next = NULL;
			dl->tail = current->prev;
		} else {
			//Middle item
			current->next->prev = current->prev;
			current->prev->next = current->next;
		}
		dl->size--;
		deallocateNode(current);//delete Node here
		return true;

	}
	printf("Node not found\n");
	return false;
}