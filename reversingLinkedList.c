#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Node {
    int data;
    struct Node* nextNode;
}Node;

typedef struct LinkedList {
    int curCount;
    Node headNode;
}LinkedList;

typedef struct StackNode {
    struct StackNode* nextNode;
    Node* data;
}StackNode;

int addNode(LinkedList* plist, int pos, int data);
int removeNode(LinkedList* plist, int pos);
int showNode(LinkedList* plist);
void makeEmpty(LinkedList* plist);
void reverseList(LinkedList* plist, StackNode** top);
int findPos(LinkedList* plist, int data);

int addNode(LinkedList* plist, int pos, int data) {
    //범위 검사
    if (plist == NULL) {
        printf("addNode() error1: 잘못된 리스트\n");
        return FALSE;
    }
    if (pos < 0 || pos > plist->curCount) {
        printf("addNode() error2: 추가 범위 초과\n");
        return FALSE;
    }
    
    //새 노드 생성
    Node* pNewNode = (Node*)malloc(sizeof(Node));
    pNewNode->data = data;
    pNewNode->nextNode = NULL;

    //직전 노드로 이동
    Node* pTmpNode = &(plist->headNode);
    for (int i = 0; i < pos; i++) {
        pTmpNode = pTmpNode->nextNode;
    }

    //link 변경
    pNewNode->nextNode = pTmpNode->nextNode;
    pTmpNode->nextNode = pNewNode;

    //관제탑 정보 변경경
    (plist->curCount)++;
    return TRUE;
}

int removeNode(LinkedList* plist, int pos) {
    //범위 검사
    if (plist == NULL) {
        printf("removeNode() error1: 잘못된 리스트\n");
        return FALSE;
    } 
    if (pos < 0 || pos >= plist->curCount) {
        printf("removeNode() error2: 삭제 범위 초과\n");
        return FALSE;
    }

    //free를 위한 포인터 생성
    Node* pDelNode = NULL;

    //직전 노드로 이동
    Node* pTmpNode = &(plist->headNode);
    for (int i = 0; i < pos; i++) {
        pTmpNode = pTmpNode->nextNode;
    }

    //link 변경 및 메모리 해제제
    pDelNode = pTmpNode->nextNode;
    pTmpNode->nextNode = pDelNode->nextNode;
    free(pDelNode);

    //관제탑 정보 변경경
    (plist->curCount)--;
    return TRUE;
}

int showNode(LinkedList* plist) {
    Node *pNode = NULL;

    if (plist == NULL) {
        printf("showNode() error: 잘못된 리스트\n");
        return FALSE;
    }

    printf("현재 Node 개수: %d\n", plist->curCount);
    pNode = plist->headNode.nextNode;

    while(pNode != NULL) {
        printf("[%d]\n", pNode->data);
        pNode = pNode->nextNode;
    }
    printf("-----------------\n");
     
    return TRUE;
}

void makeEmpty(LinkedList* plist) {
    Node* pDummyNode = NULL, *pTmpNode = NULL;

    if (plist == NULL)
        printf("makeEmpty() error: 잘못된 리스트\n");
    else {
        pTmpNode = plist->headNode.nextNode;
        //그럼 headNode에 있는 값은 못지우나?
        //값이 없음
        while(pTmpNode != NULL) {
            pDummyNode = pTmpNode;
            pTmpNode = pTmpNode->nextNode;
            free(pDummyNode);
        }
        plist->headNode.nextNode = NULL;
    }

    plist->curCount = 0;
}

void reverseList(LinkedList* plist, StackNode** top) {
    Node *pNode = NULL;
    StackNode* sNode = NULL;

    printf("Reverse Linked List!\n");
    //Stack에 list 저장
    pNode = plist->headNode.nextNode;
    while(pNode != NULL) {
        //stack의 노드 생성 & 값 할당 & 연결
        sNode = (StackNode*)malloc(sizeof(StackNode));
        sNode->data = pNode;
        sNode->nextNode = *top;
        *top = sNode;

        //리스트 옮김
        pNode = pNode->nextNode;
    }
    pNode = NULL;
    sNode = NULL;
    //List에 stack 저장
    plist->headNode.nextNode = NULL;
    while(*top != NULL) {
        sNode = *top;
        *top = (*top)->nextNode;

        //빈 리스트인지 아닌지에 따라 다르게 작업
        if (plist->headNode.nextNode == NULL) {
            plist->headNode.nextNode = sNode->data;
            pNode = plist->headNode.nextNode;
            pNode->nextNode = NULL;
        } else {
            pNode->nextNode = sNode->data;
            pNode = pNode->nextNode;
            pNode->nextNode = NULL;
        }

        //Stack에 list를 저장할때 만든 동적할당 스택 구조체를 
        //while문 내부에서 해제제
        free(sNode);
    }

    
}

int findPos(LinkedList* plist, int data) {
    int n = 0;
    Node* pNode = plist->headNode.nextNode;
    
    while(pNode != NULL) {
        if (pNode->data == data) {
            return n;
        }
        pNode = pNode->nextNode;
        n++;
    }
    return -1;
}

int main() {
    int pos;
    LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));
    linkedList->curCount = 0;
    linkedList->headNode.nextNode = NULL;

    StackNode* top = NULL;
    StackNode* pNode;

    //showNode(linkedList);
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

    //removeNode(linkedList, 1);
    //showNode(linkedList);

    //pos = findPos(linkedList, 30);
    //printf("the location of node with data 30: %d\n", pos);

    makeEmpty(linkedList);
    showNode(linkedList);
    return 0;
}