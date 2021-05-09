#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node* leftChild;
	struct Node* rightChild;
}Node;

void insertTreeNode(Node** p, int value);
void printTreePreorder(Node* pNode);
void printTreeInorder(Node* pNode);
void printTreePostorder(Node* pNode);

Node* searchTreeNode(Node* p, int value);
Node* searchTreeParentNode(Node* p, int value);
void deleteTreeNode(Node** p, int value);
void copyTreeNode(Node* src, Node** dst);
int compareTwoTree(Node* t1, Node* t2);

int main()
{
	Node* pParentNode = NULL;
	Node* cParentNode = NULL;

	///Insert Data into Tree(pParentNode)
	insertTreeNode(&pParentNode, 4);
	insertTreeNode(&pParentNode, 2);
	insertTreeNode(&pParentNode, 6);
	insertTreeNode(&pParentNode, 1);
	insertTreeNode(&pParentNode, 3);
	insertTreeNode(&pParentNode, 5);
	insertTreeNode(&pParentNode, 7);

	///Print Data in Tree(pParentNode)
	printf("Tree(pParentNode)\n");
	printf("Preorder\t:");
	printTreePreorder(pParentNode);
	printf("\nInorder\t\t:");
	printTreeInorder(pParentNode);
	printf("\nPostorder\t:");
	printTreePostorder(pParentNode);
	printf("\n\n");

	///Search Data in Tree(pParentNode) 
	printf("Search Data 3\n");
	if (searchTreeNode(pParentNode, 3) != NULL)
		printf("3 is existed\n\n");
	else
		printf("3 is not existed\n\n");

	///Delete Data in Tree(pParentNode)
	//printf("Delete data 3\n");
	//deleteTreeNode(&pParentNode, 3);
	//printf("Delete data 2\n");
	//deleteTreeNode(&pParentNode, 2);
	printf("Delete data 6\n");
	deleteTreeNode(&pParentNode, 6);

	///Search Data in Tree(pParentNode) 
	printf("Search Data 6\n");
	if (searchTreeNode(pParentNode, 6) != NULL)
		printf("6 is existed\n\n");
	else
		printf("6 is not existed\n\n");

	///Print Data in Tree(pParentNode)
	printf("Tree(pParentNode)\n");
	printf("Preorder\t:");
	printTreePreorder(pParentNode);
	printf("\nInorder\t\t:");
	printTreeInorder(pParentNode);
	printf("\nPostorder\t:");
	printTreePostorder(pParentNode);
	printf("\n\n");

	///Copy Tree(pParentNode) into Tree(cParentNode)
	copyTreeNode(pParentNode, &cParentNode);

	///Print Data in Tree(cParentNode)
	printf("Preorder\t:");
	printTreePreorder(cParentNode);
	printf("\nInorder\t\t:");
	printTreeInorder(cParentNode);
	printf("\nPostorder\t:");
	printTreePostorder(cParentNode);
	printf("\n\n");

	///Compare Data between two Trees
	if (compareTwoTree(pParentNode, cParentNode))
		printf("Two trees are equal\n");
	else
		printf("Two trees are different\n");

	return 0;
}


void insertTreeNode(Node** p, int value)
{
	if ((*p) == NULL)
	{
		// Create TreeNode with value
		(*p) = (Node*)malloc(sizeof(Node));
		(*p)->data = value;
		(*p)->leftChild = NULL;
		(*p)->rightChild = NULL;
	}
	else if ((*p)->data > value)
	{
		// Recursive call to leftChild
		insertTreeNode(&((*p)->leftChild), value);
	}
	else
	{
		// Recursive call to rightChild
		insertTreeNode(&((*p)->rightChild), value);
	}
}

void printTreePreorder(Node* pNode)
{
	if (pNode == NULL)
		return;

	printf("%3d", pNode->data);
	printTreePreorder(pNode->leftChild);
	printTreePreorder(pNode->rightChild);
}

void printTreeInorder(Node* pNode)
{
	if (pNode == NULL)
		return;

	printTreeInorder(pNode->leftChild);
	printf("%3d", pNode->data);
	printTreeInorder(pNode->rightChild);
}

void printTreePostorder(Node* pNode)
{
	if (pNode == NULL)
		return;

	printTreePostorder(pNode->leftChild);
	printTreePostorder(pNode->rightChild);
	printf("%3d", pNode->data);
}

Node* searchTreeNode(Node* p, int value)
{
	//p ����� �����Ͱ� value�� ���� ������ Ž��
	while (p != NULL && p->data != value)
	{
		//���� p ����� �����Ϳ� ���� ���� ���
		//BST�� ������ �°� Ž��
		if(p->data < value)
			p = p->rightChild;
		else if(p->data > value)
			p = p->leftChild;
	}
	//ã������ �ش� ����� �ּҸ� ��ȯ
	//��ã������ NULL�� ��ȯ
	return p;
}

Node* searchTreeParentNode(Node* p, int value)
{
	//p ����� ���� ����� �θ� ��� ����
	Node* parentNode = NULL;
	//p ����� �����Ͱ� value�� ���� ������ Ž��
	while (p != NULL && p->data != value)
	{
		//�θ� ��尡 p ��带 ����Ű��
		//p ���� ���� �ڽ� ���� �̵�
		parentNode = p;
		if(value < p->data)
			p = p->leftChild;
		else if(value > p->data)
			p = p->rightChild;
	}
	return parentNode;
}

void deleteTreeNode(Node** p, int value)/*****************/
{
	Node* parentNode; //���� ����� �θ� ���
	Node* delNode;	  //value ���� ���� �ִ� ���� ���
	Node* childNode;  //���� ����� �ڽ� ���
	Node* succNode;   //Degree 2 ��带 ���� �� �ʿ��� successor ���
	
	parentNode = searchTreeParentNode(*p, value);
	delNode = searchTreeNode(*p, value);
	if (delNode==NULL)
	{
		printf("There is no %d\n", value);
		return;
	}
	//Case 1. �ڽ� ��尡 �ϳ��� ���� ���
	if (delNode->leftChild == NULL && delNode->rightChild == NULL)
	{
		//���� ��尡 root ����� ���
		if (parentNode == NULL)//if (delNode == (*p)) ������
		{
			*p = NULL;
		}
		else
		{
			//���� ��尡 �θ� ����� ��� �ʿ� �ִ��� Ȯ���ϰ� NULL�� ����
			if (parentNode->leftChild == delNode)
				parentNode->leftChild = NULL;
			else
				parentNode->rightChild = NULL;
		}
	}
	//Case 2. �ڽ� ��尡 �ϳ� �ִ� ���
	else if (delNode->leftChild == NULL || delNode->rightChild == NULL)
	{
		//���� ����� �ڽ� ��带 childNode ������ �̿��� ����Ű���� ��
		childNode = (delNode->leftChild != NULL) ? delNode->leftChild : delNode->rightChild;
		//���� ��尡 root ����� ���
		if (parentNode == NULL)
		{
			*p = childNode;
		}
		else
		{
			//���� ��尡 �θ� ����� ��� �ʿ� �ִ��� Ȯ���ϰ� �ڽ� ��带 ����
			if(parentNode->leftChild == delNode)
				parentNode->leftChild = childNode;
			else
				parentNode->rightChild = childNode;
		}
	}
	//Case 3. �ڽ� ��尡 �� �� �ִ� ���
	else
	{
		//left subtree�� �ִ��� �ø��� ���
		childNode = delNode->leftChild;
		
		//left subtree�� �ִ��� ����Ű�� succNode
		succNode = childNode;
		while(succNode->rightChild != NULL){
			succNode = succNode->rightChild;
		}
		
		if (childNode == succNode)
			succNode->leftChild == NULL;
		else {
			childNode->rightChild = succNode->leftChild;
			succNode->leftChild = delNode->leftChild;
		}
		succNode->rightChild = delNode->rightChild;
		
		//���� ��尡 root ����� ���
		if (parentNode == NULL) {
			*p = succNode;
		}
		else
		{
			//���� ��尡 �θ� ����� ��� �ʿ� �ִ��� Ȯ���ϰ� �ڽ� ��带 ����
			if(parentNode->leftChild == delNode)
				parentNode->leftChild = succNode;
			else
				parentNode->rightChild = succNode;
		}
	}
	free(delNode);
}

void copyTreeNode(Node* src, Node** dst)
{
	if(src == NULL)
		return;
	(*dst) = (Node*)malloc(sizeof(Node));
	(*dst)->data = src->data;
	(*dst)->leftChild = NULL;
	(*dst)->rightChild = NULL;
	copyTreeNode(src->leftChild, &((*dst)->leftChild));
	copyTreeNode(src->rightChild, &((*dst)->rightChild));
}

int compareTwoTree(Node* t1, Node* t2)/*****************����Լ��̿�*/
{
	if(t1 == NULL && t2 == NULL)
		return 1;
	else if(t1 == NULL || t2 == NULL)//���� �ϳ��� null�� ��� ���� ����
		return 0;

	if(t1->data != t2->data)
		return 0;

	if (compareTwoTree(t1->leftChild, t2->leftChild) == 0 || compareTwoTree(t1->rightChild, t2->rightChild) == 0)
		return 0;

	return 1;
}