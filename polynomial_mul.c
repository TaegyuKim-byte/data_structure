#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)

#define BUFFSIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct polyTerm {
    int order;
    int coeff;
    struct polyTerm* nextNode;
    //별칭 설정 이전 줄이라 struct polyTerm을 써야하는 건가?
}polyTerm;

typedef struct poly {
    polyTerm headNode;
}poly;

void clearPoly(poly* A) {
    polyTerm* pTmpTerm = NULL, *pTmp2Term = NULL;
    //다음 노드의 주소를 저장할 변수 하나 더 만들기
    pTmpTerm = A->headNode.nextNode;

    while (pTmpTerm != NULL) {
        pTmp2Term = pTmpTerm;
        free(pTmpTerm);
        pTmpTerm = pTmpTerm->nextNode;
    }

    A->headNode.nextNode = NULL;
}

void printPoly_impl(poly A, char* buffer) {
    polyTerm* pTmpTerm = A.headNode.nextNode;
    char term[64];
    int isFirst = 1;

    while (pTmpTerm != NULL) {
        // 계수, 차수 포함한 문자열 생성
        if(pTmpTerm->coeff != 0) {   
            if (isFirst) {
                // 첫 항일 땐 부호 없이
                sprintf(term, "%dx^%d", pTmpTerm->coeff, pTmpTerm->order);
                isFirst = 0;
            } else {
                // 이후 항부터는 부호 포함
                sprintf(term, "%+dx^%d", pTmpTerm->coeff, pTmpTerm->order);
            }

            strcat(buffer, term);
        }
        pTmpTerm = pTmpTerm->nextNode;
    }
}

void printPoly(poly A) {
    char buffer[BUFFSIZE] = "";
    printPoly_impl(A, buffer);
    printf(buffer);
}

void addTerm(poly* A, int exp, int coeff) { //(다항식, 차수, 계수)
    polyTerm* pNewTerm = NULL, *pTmpTerm = NULL;
    pTmpTerm = &(A->headNode);

    while (pTmpTerm->nextNode != NULL && exp < pTmpTerm->nextNode->order) {
        //계속 이동하다가 마지막항에 가면 NULL일 수도 있음
        pTmpTerm = pTmpTerm->nextNode;
    }

    if (pTmpTerm->nextNode != NULL && exp == pTmpTerm->nextNode->order) {
        pTmpTerm= pTmpTerm->nextNode;
        pTmpTerm->coeff += coeff;
    } else {
        pNewTerm = (polyTerm*)malloc(sizeof(polyTerm));
        pNewTerm->coeff = coeff;
        pNewTerm->order = exp;
        
        pNewTerm->nextNode = pTmpTerm->nextNode;
        pTmpTerm->nextNode = pNewTerm;
    }
}

poly multiPoly(poly A, poly B) {
    poly result;
    result.headNode.nextNode = NULL;

    polyTerm* aTerm = A.headNode.nextNode;
    while(aTerm != NULL) {
        polyTerm* bTerm = B.headNode.nextNode;
        while(bTerm != NULL) {
            int exp = aTerm->order + bTerm->order;
            int coeff = aTerm->coeff * bTerm->coeff;
            addTerm(&result, exp, coeff);

            bTerm = bTerm->nextNode;
        }
    aTerm = aTerm->nextNode;
    }

    return result;
}

int main() {
    poly A, B;
    A.headNode.nextNode = NULL;
    B.headNode.nextNode = NULL;
    //GPT에게 물어본 구간 (NULL로 초기화 vs 초기화 X의 차이)

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
    printPoly(multiPoly(A, B));
    
    return 0;
}