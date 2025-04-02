/* 
front == rear -> empty임
값 1개 -> rear에 저장
front : 값 없음

Circular queue:
모듈러 연산이 필요하다

insert:
    rear 부분에 삽입

delete:
    front 부분에 있는 것 제거

시험에는 Queue Linked List가 자주 나왔었음!
꼭 이걸로 실습해보기
*/

#include <stdio.h>
#include <stdlib.h>

#define Capacity 5
#define TRUE 1
#define FALSE 0

typedef struct circularQueue {
    int data[Capacity];
    int front;
    int rear;
}cQueue;

cQueue* createCircularQueue();
void enqueue(cQueue* cQueue, int data);
int isFull(cQueue* cQueue);
void showQueue(cQueue* cQueue);
int isEmpty(cQueue* cQueue);
void dequeue(cQueue* cQueue);

cQueue* createCircularQueue() {
    cQueue* pCQueue = NULL;
    int i; //이새낀 왜있음?

    pCQueue = (cQueue*)malloc(sizeof(cQueue));
    pCQueue->front = 0;
    pCQueue->rear = 0;

    return pCQueue;
}

void showQueue(cQueue* cQueue) {
    int i;
    if (isEmpty(cQueue) == TRUE) {
        printf("Circular Queue is Empty!\n");
        return;
    }
    printf("========show queue========\n");
    for (i = cQueue->front + 1; i != cQueue->rear; i = (i+1)%Capacity) {
        printf("[%d]\n", cQueue->data[i]);
    }
    printf("[%d]\n", cQueue->data[i]);
    printf("==========================\n");
}

void enqueue(cQueue* cQueue, int data) {
    if (isFull(cQueue) == TRUE) {
        printf("Circular Queue is full!\n");
        return;
    }
    //Circular Queue의 뒷 부분에 data 추가
    cQueue->rear += 1;
    cQueue->rear %= Capacity;
    cQueue->data[cQueue->rear] = data;
}

void dequeue(cQueue* cQueue) {
    if (isEmpty(cQueue)) {
        printf("Circular Queue is Empty!\n");
        return;
    }
    //Circular Queue의 앞 부분을 다음 칸으로 이동
    cQueue->front += 1;
    cQueue->front %= Capacity;
    return;
}

int isFull(cQueue* cQueue) {
    if ((cQueue->rear + 1) % Capacity == cQueue->front) {
        return TRUE;
    } else  {
        return FALSE;
    }
}
//front와 rear가 같을 때 우리는 empty로 정의했기에
//꽉 찼을 때의 확인법이 front == rear가 아님
//생각해보기

int isEmpty(cQueue* cQueue) {
    if (cQueue->rear == cQueue->front) 
        return TRUE;
    else 
        return FALSE;
}

int main() {
    cQueue* cQueue;
    //Circular Queue 초기화
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
    printf("front: %d, rear: %d\n", cQueue->front, cQueue->rear);
    printf("enqueue data 50\n");
    enqueue(cQueue, 50);
    printf("front: %d, rear: %d\n", cQueue->front, cQueue->rear);
    printf("enqueue data 60\n");
    enqueue(cQueue, 60);
    showQueue(cQueue);
    printf("front: %d, rear: %d\n", cQueue->front, cQueue->rear);
    printf("enqueue data 70\n");
    enqueue(cQueue, 70);
    printf("front: %d, rear: %d\n", cQueue->front, cQueue->rear);
    showQueue(cQueue);
    return 0;
}