#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NODES 50

typedef struct Heap
{
	int nodes[MAX_NODES];
	int lastIndex;
} Heap;

void initHeap(Heap* heap);
void insertData(Heap* heap, int data);
void printHeap(Heap heap);
void deleteData(Heap* heap);

int main() {
	Heap heap;
	initHeap(&heap);

	insertData(&heap, 1);
	insertData(&heap, 3);
	insertData(&heap, 8);
	insertData(&heap, 13);
	insertData(&heap, 4);
	insertData(&heap, 10);
	insertData(&heap, 6);

	printHeap(heap);

	deleteData(&heap);
	printHeap(heap);

	deleteData(&heap);
	printHeap(heap);

	return 0;
}


void initHeap(Heap* heap) {
	int i;
	for (i = 1; i < MAX_NODES; i++) {
		heap->nodes[i] = 0;
	}
	heap->lastIndex = 0;
}

void printHeap(Heap heap) {
	int i, count, newLineIndex;

	count = 1;
	newLineIndex = 0;

	for (i = 1; i <= heap.lastIndex; i++) {
		printf("%d\t", heap.nodes[i]);

		if (pow(2.0, newLineIndex) == count) {
			printf("\n");
			newLineIndex++;
			count = 0;
		}
		count++;
	}
	printf("\n\n");
}

void insertData(Heap* heap, int data) {
	int index;

	//heap�� �� ���ִ��� �˻�
	if (heap->lastIndex == MAX_NODES - 1) {
		printf("Heap is full\n");
		return;
	}

	//heap�� node�� Ȯ����� �����͸� �߰�
	heap->lastIndex++;
	index = heap->lastIndex;

	//�θ� node�� �����͸� Ȯ���ϸ鼭 ������Ʈ
	while ((index != 1) && (data > heap->nodes[index/2])){//data> heap->nodes[index/2]) { �Ӹ� �ƴ϶� root�ƴ����� Ȯ���������
		heap->nodes[index] = heap->nodes[index/2];//�θ� ��ĭ�� ������/
		index /= 2;
	}
	heap->nodes[index] = data;//�ڽ��� �������� �ø���
}

void deleteData(Heap* heap) {
	int temp, parentIndex, childIndex;

	//heap�� ����ִ��� �˻�
	if (heap->lastIndex == 0) {
		printf("Heap is empty\n");
		return;
	}

	//root node���� �����Ͱ� �����ϴ� ���
	if (heap->lastIndex == 1) {
		heap->nodes[heap->lastIndex] = 0;
		heap->lastIndex = 0;
		return;
	}

	//heap�� ������ node�� �����͸� �ӽ� ������ ����
	temp = heap->nodes[heap->lastIndex];
	heap->nodes[heap->lastIndex] = 0;//*����ֱ��ʿ�*
	heap->lastIndex--;

	parentIndex = 1;
	childIndex = 2;

	//root node���� �����Ͽ� �ڽ� ����� ���� ���ϸ� ������Ʈ
	while (childIndex <= heap->lastIndex) {
		//sibling node �߿��� ���� ���� ū node�� ����
		if (heap->nodes[childIndex] < heap->nodes[childIndex + 1])
			childIndex++;
		//�ӽú����� ����� ���� ��
		if (temp > heap->nodes[childIndex])
			break;
		//�ڽ� node�� ���� �� ū ��쿡�� �θ� node�� ��ü
		heap->nodes[parentIndex] = heap->nodes[childIndex];
		parentIndex = childIndex;
		childIndex *= 2;
	}
	heap->nodes[parentIndex] = temp;//*heap->nodes[childIndex] = temp�ƴ�*
}