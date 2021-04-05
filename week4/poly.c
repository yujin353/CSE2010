//초기 버전으로 작성했습니다.
#define _CRT_SECURE_NO_WARNINGS

#define TESTCASE_FILE_NAME "testCases.txt"
#define BUFFSIZE 1024
#define MAX_EXP 100

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct polyTerm_ {
	int exp;
	int coeff;
	struct polyTerm_* next;
} polyTerm;

typedef struct poly_ {
	polyTerm* head;
} poly;

void clearPoly(poly* A) {
	polyTerm* pTmpPoly = NULL;
	int i = MAX_EXP;
	if (A != NULL) {
		pTmpPoly = A->head;

		while(pTmpPoly != NULL) {
			pTmpPoly->coeff = 0;
			pTmpPoly->exp = i;
			pTmpPoly = pTmpPoly->next;
			i--;
		}
	}
}

poly createPoly(void) {
	int i;
	polyTerm* pnew = (polyTerm*)malloc(sizeof(polyTerm));
	polyTerm* ptmp;
	poly res;
	res.head = pnew;
	pnew->coeff = 0;
	pnew->exp = 0;
	pnew->next = NULL;

	for (i = 1; i < MAX_EXP + 1; i++) {
		ptmp = (polyTerm*)malloc(sizeof(polyTerm));
		ptmp->coeff = 0;
		ptmp->exp = i;
		ptmp->next = pnew;
		res.head = ptmp;
		pnew = ptmp;
	}
	return res;
}

void printPoly_impl(poly A, char* buffer) {
	polyTerm* tmp = A.head;
	int isFirst = 1;
	int noTermFlag = 1;

	while(tmp != NULL) {
		char buffTemp[BUFFSIZE] = "";
		if (tmp->coeff == 0) {
			tmp = tmp->next;
		}
		else { 
			noTermFlag = 0;
			if(isFirst == 1 || tmp->coeff < 0) {
				sprintf(buffTemp, "%dx^%d", tmp->coeff, tmp->exp);
				strcat(buffer, buffTemp);
				isFirst = 0;
			}
			else if (tmp->coeff > 0) {
				sprintf(buffTemp, "+%dx^%d", tmp->coeff, tmp->exp);
				strcat(buffer, buffTemp);
			}
			tmp = tmp->next;
		}
	}

	if (noTermFlag == 1) {
		sprintf(buffer, "0");
	}
}

void printPoly(poly A) {
	char buffer[BUFFSIZE] = "";
	printPoly_impl(A, buffer);
	printf(buffer);
}

void addTerm(poly* A, int exp, int coeff) {
	polyTerm* add = A->head;
	while(add->exp != exp) {
		add = add->next;
	}
	add->coeff += coeff;
}

poly multiPoly(poly A, poly B) {
	int i, j;
    poly res = createPoly();
    polyTerm* tmpA;
    polyTerm* tmpB;
    tmpA = A.head;
    tmpB = B.head;

	for (i = MAX_EXP; tmpA != NULL;--i) {
        if (tmpA->coeff == 0) {
            tmpA = tmpA->next;
            continue;
        }
		for (j = MAX_EXP; tmpB != NULL;--j) {
            if (tmpB->coeff == 0) {
                tmpB = tmpB->next;
                continue;
            }
            addTerm(&res, i + j, tmpA->coeff*tmpB->coeff);
			tmpB = tmpB->next;
        }
		tmpA = tmpA->next;
		tmpB = B.head;
    }
    return res;
}

void testPoly(const char* testCaseFileName) {
	int breakFlag = 0;
	int breakPoint = -1;
	FILE* fp = fopen(testCaseFileName, "r");
	poly A = createPoly();
	poly B = createPoly();
	char lastTrue[BUFFSIZE] = "";
	char lastAnswer[BUFFSIZE] = "";

	int T;
	fscanf(fp, "%d\n", &T);


	while (T--) {
		char inputOp0, inputOp1;
		char inputStr[BUFFSIZE] = "";
		char buffer[BUFFSIZE] = "";
		int caseNum;

		fscanf(fp, "%d %c ", &caseNum, &inputOp0);

		if (inputOp0 == 'a') {
			int exp, coeff;
			fscanf(fp, "%c %d %d\n", &inputOp1, &exp, &coeff);
			if (inputOp1 == 'A') {
				addTerm(&A, exp, coeff);
			}
			else if (inputOp1 == 'B') {
				addTerm(&B, exp, coeff);
			}
		}

		else if (inputOp0 == 'p') {
			fscanf(fp, "%c\n%s\n", &inputOp1, inputStr);
			if (inputOp1 == 'A') {
				printPoly_impl(A, buffer);
			}
			else if (inputOp1 == 'B') {
				printPoly_impl(B, buffer);
			}

			if (strcmp(inputStr, buffer) != 0) {
				breakFlag = 1;
				breakPoint = caseNum;
				strcpy(lastTrue, inputStr);
				strcpy(lastAnswer, buffer);
				break;
			}
		}

		else if (inputOp0 == 'c') {
			fscanf(fp, "%c\n", &inputOp1);
			if (inputOp1 == 'A') {
				clearPoly(&A);
			}
			else if (inputOp1 == 'B') {
				clearPoly(&B);
			}
		}

		else if (inputOp0 == 'm') {
			fscanf(fp, "%s\n", inputStr);
			printPoly_impl(multiPoly(A, B), buffer);
			if (strcmp(inputStr, buffer) != 0) {
				breakFlag = 1;
				breakPoint = caseNum;
				strcpy(lastTrue, inputStr);
				strcpy(lastAnswer, buffer);
				break;
			}
		}
	}

	fclose(fp);

	if (breakFlag) {
		printf("Test failed on case# %d\n", breakPoint);
		printf("True: %s\nAnswer: %s", lastTrue, lastAnswer);
	}
	else {
		printf("TEST DONE.\n");
	}
}

int main() {
	/*poly A,B;	
	A = createPoly();
	B = createPoly();

	addTerm(&A, 1, 1);
	addTerm(&A, 0, 1);
	printf("poly A: ");
	printPoly(A);
	printf("\n");

	addTerm(&B, 1, 1);
	addTerm(&B, 0, -1);
	printf("poly B: ");
	printPoly(B);
	printf("\n");

	printf("A*B: ");
	printPoly(multiPoly(A, B));*/

	testPoly(TESTCASE_FILE_NAME);

	return 0;
}
