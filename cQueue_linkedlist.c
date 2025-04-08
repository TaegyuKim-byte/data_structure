#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Node {
    int data;
    struct Node* nextNode;
}Node;

typedef struct Queue {
    Node* frontPtr;
    Node* rearPtr; 
}Queue;

Queue* createLinkedListQueue();
void enqueue(Queue* lQueue, int data);
int isEmpty(Queue* lQueue);
void dequeue(Queue* lQueue);
void showQueue(Queue* lQueue);

Queue* createLinkedListQueue() {
    Queue* lQueue = NULL;

    lQueue = (Queue*)malloc(sizeof(Queue));
    lQueue->frontPtr = NULL;
    lQueue->rearPtr = NULL;

    return lQueue;
}

int isEmpty(Queue* lQueue) {
    if (lQueue->frontPtr == NULL && lQueue->rearPtr == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void enqueue(Queue* lQueue, int data) {
    Node* pNewNode = NULL, *pTmpNode = NULL;

    pNewNode = (Node*)malloc(sizeof(Node));
    //pNewNode 자체는 새로 생성한 노드를 가리킴
    pNewNode->data = data;
    pNewNode->nextNode = NULL;
    printf("enqueue data %d\n", data);

    if (isEmpty(lQueue)) {
        lQueue->frontPtr = lQueue->rearPtr = pNewNode;
    } else {
        pNewNode->nextNode = lQueue->rearPtr;
        lQueue->rearPtr = pNewNode;
    }
    /*
    pNewNode->nextNode = lQueue->rearPtr;
    lQueue->rearPtr = &(pNewNode);
    pTmpNode 사용을 안해도 되지않나
    */
}

void dequeue(Queue* lQueue) {
    Node* pTmpNode = lQueue->rearPtr;

    if (isEmpty(lQueue)) {
        printf("dequeue error: Empty List\n");
        return;
    } else if (lQueue->frontPtr == lQueue->rearPtr) {
        pTmpNode = lQueue->rearPtr;
        free(pTmpNode);

        lQueue->frontPtr = NULL;
        lQueue->rearPtr = NULL;
        printf("dequeue\n");
        return;
    }
    //front의 바로 앞 까지 접근
    while (pTmpNode->nextNode->nextNode != NULL) {
        pTmpNode = pTmpNode->nextNode;
    }
    printf("dequeue\n");
    lQueue->frontPtr = pTmpNode;
    
    free(pTmpNode->nextNode);
    pTmpNode->nextNode = NULL;
}

void showQueue(Queue* lQueue) {
    Node* pTmpNode = NULL;

    if (isEmpty(lQueue)) {
        printf("========show queue========\n");
        printf("Queue is empty!\n");
        printf("==========================\n");
    } else {
        pTmpNode = lQueue->rearPtr;
        printf("========show queue========\n");
        printf("<exit>\n");
        while (pTmpNode != NULL) {
            printf("[%d]\n", pTmpNode->data);
            pTmpNode = pTmpNode->nextNode;    
        }
        printf("<entrance>\n");
        printf("==========================\n");
    }
}

int main() {
    Queue* lQueue = createLinkedListQueue();

    enqueue(lQueue, 10);
    enqueue(lQueue, 20);
    enqueue(lQueue, 30);
    showQueue(lQueue);

    dequeue(lQueue);
    dequeue(lQueue);
    dequeue(lQueue);
    dequeue(lQueue);

    showQueue(lQueue);

    return 0;
}