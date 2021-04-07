#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

//stack구조체 선언 (linked list)
typedef struct StackNode {
	int data;
	struct StackNode* next;
} StackNode;

//stack관련 함수
void pushLinkedStack(StackNode** top, int data) {
	StackNode* pNode = NULL;
	
	pNode = (StackNode*)malloc(sizeof(StackNode));
	pNode->data = data;
	pNode->next = NULL;

	if(isEmpty(*top)){
		*top = pNode;
	}
	else {
		pNode->next = *top;
		*top = pNode;
	}
}

StackNode* popLinkedStack(StackNode** top){//쓸여지가 남아있기 때문에 free안함
	StackNode* pNode = NULL;

	if(isEmpty(*top)) {
		printf("the Stack is empty\n");
		return NULL;
	}

	pNode = *top;
	*top = pNode->next;
	pNode->next = NULL;

	return pNode;
}

StackNode* topLinkedStack(StackNode* top){
	StackNode* pNode = NULL;

	if(!isEmpty(top)){
		pNode = top;
	}

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

/*void deleteLinkedStack(StackNode** top){ 에러여지있으므로 top은 stack과 무관하게 참조만....?
	StackNode* pNode = NULL;

	while(!isEmpty(*top)){
		pNode = *top;
		*top = pNode->next;
		free(pNode);
		pNode = NULL;
	}
}*/


int isEmpty(StackNode* top) {
	if (top == NULL)
		return TRUE;
	else
		return FALSE;
}

void showLInkedStack(StackNode* top) {
	StackNode* pNode = NULL;
	if (isEmpty(top)) {
		printf("the stack is empty\n");
		return;
	}

	pNode = top;
	printf("==============Show Stack===============\n");
	while (pNode != NULL) {
		printf("[%d]\n", pNode->data);
		pNode = pNode->next;
	}
	printf("=======================================\n");
}

int main() {
	//가장 윗 부분을 가리키는 top 포인터 선언

	StackNode* top = NULL;
	StackNode* pNode;

	printf("Push 10, 20, 30 called.\n");
	pushLinkedStack(&top, 10);
	pushLinkedStack(&top, 20);
	pushLinkedStack(&top, 30);
	showLInkedStack(top);

	printf("Pop() called.\n");
	pNode = popLinkedStack(&top);
	if (pNode) {
		free(pNode);
		showLInkedStack(top);
	}

	printf("Top() called.\n");
	pNode = topLinkedStack(top);
	if (pNode)
		printf("Top node's data: %d\n", pNode->data);
	else
		printf("The stack is empty.\n");
	showLInkedStack(top);

	deleteLinkedStack(&top);

	return 0;
}