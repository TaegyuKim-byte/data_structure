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

Queue* createCircularQueue();
void enqueue(Queue* cQueue, int data);
int isEmpty(Queue* cQueue);
void dequeue(Queue* cQueue);
void showQueue(Queue* cQueue);

Queue* createCircularQueue() {
    Queue* cQueue = NULL;

    cQueue = (Queue*)malloc(sizeof(Queue));
    cQueue->frontPtr = NULL;
    cQueue->rearPtr = NULL;

    return cQueue;
}

int isEmpty(Queue* cQueue) {
    if (cQueue->frontPtr == NULL && cQueue->rearPtr == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void enqueue(Queue* cQueue, int data) {
    Node* pNewNode = NULL, *pTmpNode = NULL;

    pNewNode = (Node*)malloc(sizeof(Node));
    pNewNode->data = data;
    pNewNode->nextNode = NULL;
    printf("enqueue data %d\n", data);

    if (isEmpty(cQueue)) {
        cQueue->frontPtr = cQueue->rearPtr = pNewNode;
    } else {
        pNewNode->nextNode = cQueue->rearPtr;
        cQueue->rearPtr = pNewNode;
    }
    /*
    pNewNode->nextNode = cQueue->rearPtr;
    cQueue->rearPtr = &(pNewNode);
    pTmpNode 사용을 안해도 되지않나
    */
}

void dequeue(Queue* cQueue) {
    Node* pTmpNode = cQueue->rearPtr;

    if (isEmpty(cQueue)) {
        printf("dequeue error: Empty List\n");
        return;
    } else if (cQueue->frontPtr == cQueue->rearPtr) {
        pTmpNode = cQueue->rearPtr;
        free(pTmpNode);

        cQueue->frontPtr = NULL;
        cQueue->rearPtr = NULL;
    }
    //front의 바로 앞 까지 접근
    while (pTmpNode->nextNode->nextNode != NULL) {
        pTmpNode = pTmpNode->nextNode;
    }
    printf("dequeue\n");
    cQueue->frontPtr = pTmpNode;
    
    free(pTmpNode->nextNode);
    pTmpNode->nextNode = NULL;
}

void showQueue(Queue* cQueue) {
    Node* pTmpNode = NULL;

    if (isEmpty(cQueue)) {
        printf("Queue is empty!\n");
    } else {
        pTmpNode = cQueue->rearPtr;
        printf("========show queue========\n");
        while (pTmpNode != NULL) {
            printf("[%d]\n", pTmpNode->data);
            pTmpNode = pTmpNode->nextNode;    
        }
        printf("==========================\n");
    }
}

int main() {
    Queue* Queue = createCircularQueue();

    enqueue(Queue, 10);
    enqueue(Queue, 20);
    enqueue(Queue, 30);
    showQueue(Queue);

    //dequeue(Queue);
    //dequeue(Queue);
    dequeue(Queue);
    dequeue(Queue);

    showQueue(Queue);

    return 0;
}