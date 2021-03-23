#include <stdio.h>

void hanoi(int n, char from, char middle, char to, int* m);

int main() {
	int n, move = 0;
	printf("������ ������ �Է��Ͻÿ�:");
	scanf("%d", &n);

	hanoi(n, 'A', 'B', 'C', &move);

	printf("�� �̵� Ƚ��: %d\n", move);

	return 0;
}

void hanoi(int n, char from, char middle, char to, int* m){
	(*m)++;

	if (n == 1) {
		printf("%d�� ������ %c���� %c�� �̵�\n", n, from, to);
		return;
	}
	
	hanoi(n - 1, from, to, middle, m);
	printf("%d�� ������ %c���� %c�� �̵�\n", n, from, to);
	hanoi(n - 1, middle, from, to, m);
}