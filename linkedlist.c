#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE -1
#define TRUE 1

typedef struct Node {
	int data;
	struct Node* nextNode;
}Node;

typedef struct LinkedList {
	int curCount; //현재 이 List에 들어있는 노드 개수
	Node headNode; //List의 시작 Node (포인터가 아니네?)
}LinkedList;

//typedef가 없으면 struct Node, struct LinkedList로 계속 써야됨
//typedef를 통해 저들을 간단하게 쓸 수 있는 별칭을 만듦
//-> Node, LinkedList

int addNode(LinkedList* pList, int pos, int data);
int removeNode(LinkedList* pList, int pos);
int showNode(LinkedList* pList);
int isEmpty(LinkedList* pList);
int findPos(LinkedList* pList, int data);
void makeEmpty(LinkedList* pList);

int addNode(LinkedList* pList, int pos, int data) 
{
	int i = 0;
    Node* pNewNode = NULL, *pTmpNode = NULL;
    
    if (pList == NULL) {
        printf("addNode() error1: 잘못된 리스트\n");
        return FALSE;
    }

    if (pos < 0 || pos > pList->curCount) {
        printf("addNode() error2: 추가 범위 초과\n");
        return FALSE;
    }

    pNewNode = (Node*)malloc(sizeof(Node));
    if (!pNewNode) {
        printf("addNode() error3 \n");
        return FALSE;
    }

    pNewNode->data = data;
    pNewNode->nextNode = NULL;

    pTmpNode = &(pList->headNode);
    for (int i = 0; i < pos; i++)
    //여기서 pos-1이 아닌 이유
    //처음 pTmpNode는 인덱스 0이 아니라 그 앞의 headNode라서
        pTmpNode = pTmpNode->nextNode;

    pNewNode->nextNode = pTmpNode->nextNode;
    pTmpNode->nextNode = pNewNode;

    pList->curCount++;

    return TRUE;
}
	
	
int removeNode(LinkedList* pList, int pos)
{
	int i = 0;
	Node* pDelNode = NULL, *pTmpNode = NULL;
	
	if (pList == NULL) {
		printf("removeNode() error1: 잘못된 리스트\n");
		return FALSE;
	}
	
	if (pos < 0 || pos >= pList->curCount) {
        printf("removeNode() error2: 삭제 범위 초과\n");
        //pos -> (index)0부터 시작, pList->curCount -> (개수)1부터 시작
        return FALSE;
    }
	
	//삭제될 노드 직전 위치로 이동
	pTmpNode = &(pList->headNode);
	for (int i = 0; i < pos; i++) 
		pTmpNode = pTmpNode->nextNode;
		
	//삭제할 노드 = 직전 노드의 nextNode
	//직전 노드의 nextNode = 삭제할 노드의 nextNode
	pDelNode = (pTmpNode->nextNode);
    pTmpNode->nextNode = pDelNode->nextNode;
    
    free(pDelNode);
    //free 왜함?
    //linked list 를 만들 때 각 노드가 동적할당 이기 때문에 
    //종료 시 각 칸을 해제해줘야함함
 
    (pList->curCount)--;
    
    return TRUE;
}
	
int showNode(LinkedList* pList)
{
    int i = 0; //이 분 왜 계시는거임??????
    Node *pNode = NULL;

    if (pList == NULL) {
        printf("showNode() error: 잘못된 리스트\n");
    }

    printf("현재 Node 개수: %d\n", pList->curCount);
    pNode = pList->headNode.nextNode;

    while(pNode != NULL) {
        printf("[%d]\n", pNode->data);
        pNode = pNode->nextNode;
    }
    printf("-----------------\n");
    
}

int isEmpty(LinkedList* pList)
//비었으면 TRUE , 안 비었으면 FALSE
{
    if (pList == NULL) {
        printf("isEmpty() error: 잘못된 리스트\n");
        return FALSE;
    }

    if (pList->headNode.nextNode == NULL) 
        return TRUE;
    else 
        return FALSE;
}

int findPos(LinkedList* pList, int data) {
    int n = 0;
    Node* pNode = pList->headNode.nextNode;
    
    while(pNode != NULL) {
        if (pNode->data == data) {
            return n;
        }
        pNode = pNode->nextNode;
        n++;
    }
    return FALSE;
}

void makeEmpty(LinkedList* pList) {
    Node* pDummyNode = NULL, *pTmpNode = NULL;

    if (pList == NULL)
        printf("makeEmpty() error: 잘못된 리스트\n");
    else {
        pTmpNode = pList->headNode.nextNode;
        //그럼 headNode에 있는 값은 못지우나?
        while(pTmpNode != NULL) {
            pDummyNode = pTmpNode;
            pTmpNode = pTmpNode->nextNode;
            free(pDummyNode);
        }
        pList->headNode.nextNode = NULL;
    }

}

int main() {
    int pos;
    LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));
    linkedList->curCount = 0;
    linkedList->headNode.nextNode = NULL;
    //nextNode를 초기화?
    //headNode의 값은 없고 주소만 NULL로 해줌

    showNode(linkedList);
    addNode(linkedList, 0, 10);
    addNode(linkedList, 5, 100);
    addNode(linkedList, 1, 20);
    addNode(linkedList, 2, 30);
    addNode(linkedList, 1, 50);

    showNode(linkedList);

    removeNode(linkedList, 1);
    showNode(linkedList);

    pos = findPos(linkedList, 30);
    printf("the location of node with data '30': %d\n", pos);

    makeEmpty(linkedList);
    showNode(linkedList);

    return 0;
}