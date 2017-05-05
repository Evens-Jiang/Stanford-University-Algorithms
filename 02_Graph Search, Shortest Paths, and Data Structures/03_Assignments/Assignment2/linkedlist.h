#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

typedef struct linked_list_node{
	int vertex;
	struct list_list_node *next;
}listNode, *listNodePtr;

listNodePtr createNode(){
	listNodePtr linkedList = (listNodePtr)malloc(sizeof(listNode));
	return linkedList;
}

void addtNode(listNodePtr headNode, int vertex){
	listNodePtr newNode = createNode(), nodePtr;
	newNode->vertex = vertex;
	newNode->next = NULL;
	if(headNode->next == NULL)
		headNode->next = newNode;
	else{
		nodePtr = headNode->next;
		while(nodePtr->next != NULL)
			nodePtr = nodePtr->next;
		nodePtr->next = newNode;
	}
}

void removeNode(listNodePtr headNode, int vertex){
	listNodePtr nodePtr = headNode, tempNode;
	if(nodePtr->vertex == vertex){
		headNode = nodePtr->next;
		free(nodePtr);
	}
	else{
		while((nodePtr->next)->vertex != vertex)
			nodePtr = nodePtr->next;
		nodePtr->next = (nodePtr->next)->next;
		free(nodePtr->next);
	}
}
#endif