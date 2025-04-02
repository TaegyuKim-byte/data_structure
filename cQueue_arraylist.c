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

