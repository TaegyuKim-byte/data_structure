#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NODES 50
typedef struct Heap {
    int nodes[MAX_NODES];
    int lastIndex;
}Heap;

void initHeap (Heap* heap);
void insertData (Heap* heap, int data);
void printHeap (Heap heap);
void deleteData (Heap* heap);

//배열 기반 heap은 부모 자식의 index 관계를 위해
//[0]은 비워두고 [1]부터 루트 노드로 시작함.
void initHeap (Heap* heap)
{
    int i;
    for (i = 1; i < MAX_NODES; i++) 
        heap->nodes[i] = 0;
    heap->lastIndex = 0;
}

void printHeap (Heap heap)
{
    int i, count, newLineIndex;
    count = 1;
    newLineIndex = 0;
    for (i = 1; i <= heap.lastIndex; i++) {
        printf("%d\t", heap.nodes[i]);
        //heap tree의 각 level은 한 줄에 출력되도록 함
        //한 level당 노드 개수대로 끊어서 \n 출력력
        if (pow(2, newLineIndex) == count) {
            printf("\n");
            newLineIndex++;
            count = 0;
        }
        count++;
    }
    printf("\n\n");
}

void insertData (Heap* heap, int data)
{
    int index;

    //heap이 꽉 차있는지 검사
    if (heap->lastIndex == MAX_NODES - 1) {
        printf("Heap is full\n");
        return;
    }

    //heap에 node를 확장(lastInedex 중가)
    //your code
    heap->lastIndex += 1;


    //올바른 위치를 저장하기 위한 변수에 
    //complete 를 만족하기 위한 위치 일단 저장
    index = heap->lastIndex;

    //부모 인덱스 = 자식 인덱스 / 2
    //인덱스를 통해 data 비교 & 조건 만족하도록 값 업데이트 & index 업데이트
    while (index != 1 && data > heap->nodes[index / 2]) {
        //your code
        heap->nodes[index] = heap->nodes[index / 2];
        index /= 2;
    }

    //올바른 index에 값 저장장
    //your code
    heap->nodes[index] = data;
}

void deleteData (Heap* heap) 
{
    int temp, parentIndex, childIndex;
    //heap이 비어있는지 검사
    if (heap->lastIndex == 0) {
        printf("Heap is empty\n");
        return;
    }

    //root node에만 데이터가  존재하는 경우
    if (heap->lastIndex == 1) {
        heap->nodes[heap->lastIndex] = 0;
        heap->lastIndex = 0;
        return;
    }

    //heap의 마지막 노드의 데이터를 임시 변수(temp)에 저장
    //your code
    //내 코드: temp = heap->nodes[(heap->lastIndex)--];
    temp = heap->nodes[heap->lastIndex];
    heap->nodes[heap->lastIndex] = 0; //얘를 빼먹음. 정적 배열이라 0으로 만들수 있음
    heap->lastIndex --;


    parentIndex = 1;
    childIndex = 2;
    //root node부터 시작해서 자식 노드들의 데이터 값과 비교하여 업데이트
    while (childIndex <= heap->lastIndex) {
        //sibling node 중 값이 큰 node를 선택
        if (heap->nodes[childIndex] < heap->nodes[childIndex + 1])  
            //your code
            childIndex++;
        //임시 변수에 저장된 값과 비교
        if (temp > heap->nodes[childIndex])
            break;

        //자식 node의 값이 더 클 경우 부모 node와 교체
        //your code
        heap->nodes[parentIndex] = heap->nodes[childIndex];
        parentIndex = childIndex;
        childIndex = childIndex * 2;
    }
    //your code
    heap->nodes[parentIndex] = temp;
    return;
}

int main() 
{
    //Max heap
    Heap heap;

    initHeap(&heap);

    insertData(&heap, 1);
    insertData(&heap, 3);
    insertData(&heap, 8);
    insertData(&heap, 13);
    insertData(&heap, 4);
    insertData(&heap, 10);
    insertData(&heap, 6);

    printHeap(heap);

    deleteData(&heap);
    printHeap(heap);

    deleteData(&heap);
    printHeap(heap);

    return 0;
}