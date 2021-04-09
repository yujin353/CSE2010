#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FALSE -1
#define TRUE 1

typedef struct StackNode {
	int data;
	struct StackNode* next;
} StackNode;

typedef struct Node {
	int data;
	struct Node* nextNode;
} Node;

typedef struct LinkedList {
	int curCount;
	Node headNode;
} LinkedList;

int addNode(LinkedList* pList, int pos, int data);
int removeNode(LinkedList* pList, int pos);
void showNode(LinkedList* pList);
int isEmpty(LinkedList* pList);
void makeEmpty(LinkedList* pList);

void pushLinkedStack(StackNode** top, int data);
StackNode* popLinkedStack(StackNode** top);
void deleteLinkedStack(StackNode** top);
int isEmptyStack(StackNode* top);
StackNode* topLinkedStack(StackNode* top);

void reverseList(LinkedList* pList, StackNode** top){
	Node *pNode = NULL;
	StackNode *sNode = NULL;
	int i = 0;

	printf("Reverse Linked List!\n");
	//Stack에 List 저장
	pNode = &(pList->headNode);
	while(pNode != NULL) {
		pushLinkedStack(&sNode, pNode->data);
		pNode = pNode->nextNode;
	}
	*top = sNode;
	makeEmpty(pList);

	//List에 Stack 저장
	while(sNode->next != NULL) {
		addNode(pList, i, topLinkedStack(sNode)->data);
		popLinkedStack(&sNode);
		i++;
	}
	deleteLinkedStack(top);
}

int main() {
	int pos;
	LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));
	StackNode* top = NULL;
	StackNode* pNode;

	linkedList->curCount = 0;
	linkedList->headNode.nextNode = NULL;

	addNode(linkedList, 0, 10);
	addNode(linkedList, 5, 100);
	addNode(linkedList, 1, 20);
	addNode(linkedList, 2, 30);
	addNode(linkedList, 1, 50);
	addNode(linkedList, 1, 70);
	addNode(linkedList, 1, 40);

	showNode(linkedList);

	reverseList(linkedList, &top);

	showNode(linkedList);

	makeEmpty(linkedList);
	showNode(linkedList);

	return 0;
}


int addNode(LinkedList* pList, int pos, int data) {
	int i = 0;
	Node* pNewNode = NULL, *pTmpNode = NULL;

	if (pList == NULL) {
		printf("addNode() error\n");
		return FALSE;
	}
	if (pos < 0 || pos > pList->curCount) {
		printf("addNode() error2: 추가 범위 초과\n");
		return FALSE;
	}

	pNewNode = (Node*)malloc(sizeof(Node));
	if(!pNewNode) {//공간 부족으로 인해? malloc 공간 할당이 안된경우
		printf("addNode error3\n");
		return FALSE;
	}

	pNewNode->data = data;
	pNewNode->nextNode = NULL;//초기화

	pTmpNode = &(pList->headNode);//pTmpNode = pList->headNode.nextNode; <내가 쓴 답 오류 남
	for(i = 0; i < pos; i++)
		pTmpNode = pTmpNode->nextNode;

	pNewNode->nextNode = pTmpNode->nextNode;
	pTmpNode->nextNode = pNewNode;
	pList->curCount++;

	return TRUE;
}
int removeNode(LinkedList* pList, int pos) {
	int i = 0;
	Node* pDelNode = NULL, *pTmpNode = NULL;

	if (pList == NULL) {
		printf("removeNode() error\n");
		return FALSE;
	}

	pTmpNode = &(pList->headNode);
	for(i = 0; i < pos; i++)
		pTmpNode = pTmpNode->nextNode;

	pDelNode = pTmpNode->nextNode;
	pTmpNode->nextNode = pDelNode->nextNode;

	free(pDelNode);
	pList->curCount--;

	return TRUE;
}

void showNode(LinkedList* pList) {
	int i = 0;
	Node *pNode = NULL;

	if(pList == NULL) {//예외 처리
		printf("showNode() error\n");
		return;
	}

	printf("현재 Node 개수 : %d \n", pList->curCount);
	pNode = pList->headNode.nextNode;

	while(pNode != NULL) {//pNode가 LinkedList의 마지막 노드까지 이동
		printf("[%d]\n", pNode->data);
		pNode = pNode->nextNode;//pNode가 LinkedList의 다음 노드로 이동
	}
	printf("---------------------\n");
}

int isEmpty(LinkedList* pList) {
	if (pList == NULL) {
		printf("isEmpty() error\n");
		return -1;
	}

	if (pList->headNode.nextNode == NULL)//head 노드가 가리키는 next 노드가 존재하는가
		return TRUE;
	else
		return FALSE;
}

void makeEmpty(LinkedList* pList) {
	Node* pDummyNode = NULL, *pTmpNode = NULL;
	if (pList != NULL) {
		pTmpNode = pList->headNode.nextNode;

		while(pTmpNode != NULL) {
			pDummyNode = pTmpNode;
			pTmpNode = pTmpNode->nextNode;
			free(pDummyNode);
		}
		pList->headNode.nextNode = NULL;
		pList->curCount = 0;
	}
}

void pushLinkedStack(StackNode** top, int data) {
	StackNode* pNode = NULL;
	
	pNode = (StackNode*)malloc(sizeof(StackNode));
	pNode->data = data;
	pNode->next = NULL;

	if(isEmptyStack(*top)){
		*top = pNode;
	}
	else {
		pNode->next = *top;
		*top = pNode;
	}
}

StackNode* popLinkedStack(StackNode** top){//쓸여지가 남아있기 때문에 free안함
	StackNode* pNode = NULL;

	if(isEmptyStack(*top)) {
		printf("the Stack is empty\n");
		return NULL;
	}

	pNode = *top;
	*top = pNode->next;
	pNode->next = NULL;

	return pNode;
}

void deleteLinkedStack(StackNode** top){
	StackNode* pNode = NULL, *pDelNode = NULL;
	pNode = *top;

	while(pNode != NULL){
		pDelNode = pNode;
		pNode = pNode->next;
		free(pDelNode);
	}
	*top = NULL;
}

StackNode* topLinkedStack(StackNode* top){
	StackNode* pNode = NULL;

	if(!isEmptyStack(top)){
		pNode = top;
	}

	return pNode;
}

int isEmptyStack(StackNode* top) {
	if (top == NULL)
		return 1;
	else
		return 0;
}