#include <stdio.h>
#include <stdlib.h>

#define Capacity 5
#define TRUE 1
#define FALSE 0

//Circular Queue ����ü ����
typedef struct circularQueue {
	int data[Capacity];
	int front;
	int rear;
}cQueue;

//Circular Queue ���� �Լ�
cQueue* createCircularQueue();
void enqueue(cQueue* cQueue, int data);
int isFull(cQueue* cQueue);
void showQueue(cQueue* cQueue);
int isEmpty(cQueue* cQueue);
void dequeue(cQueue* cQueue);

int main() {
	cQueue* cQueue;
	//Circular Queue�ʱ�ȭ
	cQueue = createCircularQueue();

	printf("front: %d, rear: %d\n", cQueue->front, cQueue->rear);

	printf("enqueue data 10\n");
	printf("enqueue data 20\n");
	printf("enqueue data 30\n");
	enqueue(cQueue, 10);
	enqueue(cQueue, 20);
	enqueue(cQueue, 30);
	showQueue(cQueue);
	printf("front: %d, rear: %d\n", cQueue->front, cQueue->rear);

	printf("dequeue\n");
	printf("dequeue\n");
	dequeue(cQueue);
	dequeue(cQueue);
	showQueue(cQueue);
	printf("front: %d, rear: %d\n", cQueue->front, cQueue->rear);

	printf("enqueue data 40\n");
	enqueue(cQueue, 40);
	showQueue(cQueue);
	printf("front: %d, rear: %d\n", cQueue->front, cQueue->rear);

	printf("enqueue data 50\n");
	enqueue(cQueue, 50);
	showQueue(cQueue);
	printf("front: %d, rear: %d\n", cQueue->front, cQueue->rear);

	printf("enqueue data 60\n");
	enqueue(cQueue, 60);
	showQueue(cQueue);
	printf("front: %d, rear: %d\n", cQueue->front, cQueue->rear);

	printf("enqueue data 70\n");
	enqueue(cQueue, 70);
	showQueue(cQueue);
	printf("front: %d, rear: %d\n", cQueue->front, cQueue->rear);

	return 0;
}

cQueue* createCircularQueue(){
	cQueue* pCQueue = NULL;

	pCQueue = (cQueue*)malloc(sizeof(cQueue));
	pCQueue->front = 0;
	pCQueue->rear = 0;

	return pCQueue;
}
void enqueue(cQueue* cQueue, int data){
	if(isFull(cQueue)==TRUE) {
		printf("Circular Queue is full!\n");
		return;
	}
	cQueue->rear = (cQueue->rear + 1) % Capacity;
	cQueue->data[cQueue->rear] = data;
}
int isFull(cQueue* cQueue){
	if((cQueue->rear+1) % Capacity == cQueue->front)
		return TRUE;
	else
		return FALSE;
}
void showQueue(cQueue* cQueue){
	int i;
	if(isEmpty(cQueue) == TRUE){
		printf("Circular Queue is Empty!\n");
		return;
	}
	printf("=======show queue==========\n");
	for(i = cQueue->front + 1; i != cQueue->rear; i = (i+1)%Capacity) {// �� i = front + 1����
		printf("[%d]\n",cQueue->data[i]);
	}
	printf("[%d]\n", cQueue->data[i]);
	printf("===========================\n");
}
int isEmpty(cQueue* cQueue){
	if(cQueue->front == cQueue->rear)
		return TRUE;
	else
		return FALSE;
}
void dequeue(cQueue* cQueue){
	if(isEmpty(cQueue)==TRUE) {
		printf("Circular Queue is empty!\n");
		return;
	}
	//cQueue->data[cQueue->front] = NULL; ���� �迭���� �����͸� ���� �ʿ� ����
	cQueue->front = (cQueue->front + 1) % Capacity;
}