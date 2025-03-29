#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

//stack 구조체 선언
typedef struct StackNode {
    int data;
    struct StackNode* nextNode;
}StackNode;

//왜 맨 처음 노드를 가리키는 애는 없지?
//같은 구조체로 다르게 두개 선언하려나?

//답변: top가 맨 위 노드를 가리키고 있음.

void pushLinkedStack(StackNode** top, int data);
StackNode* popLinkedStack(StackNode** top);
void showLinkedStack(StackNode* top);
StackNode* topLinkedStack(StackNode* top);
void deleteLinkedStack(StackNode ** top);
int isEmpty(StackNode* top);
//call by reference가 많아서 포인터 개수는 그런 의미를 의식하고 봐야함

int isEmpty(StackNode* top) {
    if (top == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void showLinkedStack(StackNode* top) {
    StackNode* pNode = NULL;

    if (isEmpty(top)) {
        printf("The stack is empty. \n");
    } 

    pNode = top;
    printf("==========Show Stack==========\n");
    while(pNode != NULL) {
        printf("[%d]\n", pNode->data);
        pNode = pNode->nextNode;
    }
    printf("==========Show Stack==========\n");
}

void pushLinkedStack(StackNode** top, int data) {
    StackNode* pNewNode = NULL;

    pNewNode = (StackNode*)malloc(sizeof(StackNode));
    pNewNode->data = data;

    if (*top == NULL) {
        *top = pNewNode;
    } else {
        pNewNode->nextNode = top;
        *top = pNewNode;
    }
}

StackNode* popLinkedStack(StackNode** top) {
    StackNode* pNode = NULL;

    if (*top == NULL) {
        return *top;
    } else {
        

    }

    return pNode;
}

int main() {
    //가장 윗부분을 가리키는 포인터 변수 선언
    StackNode* top = NULL;
    StackNode* pNode;

    printf("Push(10, 20, 30) called. \n");
    pushLinkedStack(&top, 10);
    pushLinkedStack(&top, 20);
    pushLinkedStack(&top, 30);
    showLinkedStack(top);

    printf("Pop() called. \n");
    pNode = popLinkedStack(&top);
    if (pNode != NULL) {
        free(pNode);
        showLinkedStack(top);
    }
    /*pNode는 함수의 리턴값이 StackNode의 주소여서 
    일부러 받아주고 해제한 것 같은데 굳이 그래야하나?
    void로 리턴받고 call by reference를 이용해 top
    자체를 바꾸면 안되나?*/

    /**/
    printf("Top() called. \n");
    pNode = topLinkedStack(top);
    if (pNode) {
        printf("Top node's data: %d\n", pNode->data);
    } else {
        printf("The stack is empty\n");
    }
    showLinkedStack(top);

    deleteLinkedStack(&top);
    return 0;
}