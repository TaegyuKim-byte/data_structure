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
                   //가 아니라 시작노드를 가리키는 포인터를 가지고있기 위한 용도로만 쓰이는 놈. 
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
    //n번 이동하면 pTmpNode는 [n-1]에 있음
        pTmpNode = pTmpNode->nextNode;

    pNewNode->nextNode = pTmpNode->nextNode;
    pTmpNode->nextNode = pNewNode;

    pList->curCount++;
    //연산자 우선순위 암기

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
/*
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE -1

typedef struct Node {
    int data;
    struct Node* nextNode;
}Node;

typedef struct LinkedList {
    int curCount;
    Node headNode;
}LinkedList;

int addNode(LinkedList* plist, int pos, int data);
int removeNode(LinkedList* plist, int pos);
int showLinkedList(LinkedList* plist);
int isEmpty(LinkedList* plist);
int findPos(LinkedList* plist, int data);
void makeEmpty(LinkedList* plist);

int addNode(LinkedList* plist, int pos, int data) {
    //위치 검사
    if (pos > plist->curCount || pos < 0) {
        printf("Error! wrong position\n");
        return FALSE;
    }
    
    //새로운 노드 생성
    Node* pNewNode = (Node*)malloc(sizeof(Node));
    pNewNode->data = data;
    pNewNode->nextNode = NULL;
    
    //직전 노드까지 이동
    Node* pTmpNode = &(plist->headNode);
    for (int i = 0; i < pos; i++) {
        pTmpNode = pTmpNode->nextNode;
    }
    
    //link 변경
    pNewNode->nextNode = pTmpNode->nextNode;
    pTmpNode->nextNode = pNewNode;
    
    (plist->curCount)++;
    return TRUE;
}

int removeNode(LinkedList* plist, int pos) {
    //pos 검사
    if (pos >= plist->curCount || pos < 0) {
        printf("Error! wrong position");
        return FALSE;
    }
    
    //직전 노드까지 이동
    Node* pTmpNode = &(plist->headNode);
    Node* pDelNode = NULL;
    for (int i = 0; i < pos; i++) {
        pTmpNode = pTmpNode->nextNode;
    }
    pDelNode = pTmpNode->nextNode;
    
    //link 변경
    pTmpNode->nextNode = pDelNode->nextNode;
    
    //free!
    free(pDelNode);
    
    (plist->curCount)--;
    return TRUE;
}

int isEmpty(LinkedList* plist) {
    return plist->headNode.nextNode == NULL;   
}

int findPos(LinkedList* plist, int data) {
    Node* pTmpNode = plist->headNode.nextNode;
    int n = 0;
    while (pTmpNode != NULL) {
        if (pTmpNode->data == data) 
            return n;
        pTmpNode = pTmpNode->nextNode;
        n++;
    }
    
    return FALSE;
}

void makeEmpty(LinkedList* plist) {
    Node* pTmpNode = plist->headNode.nextNode;
    Node* pDelNode = NULL;
    
    while (pTmpNode != NULL) {
        pDelNode = pTmpNode;
        pTmpNode = pDelNode->nextNode;
        free(pDelNode);
    }
    
    plist->headNode.nextNode = NULL;
    plist->curCount = 0;
}

int showNode(LinkedList* plist) {
    printf("현재 노드 개수: %d\n", plist->curCount);
    
    Node* pTmpNode = plist->headNode.nextNode;
    
    for (int i = 0; i < plist->curCount; i++) {
        printf("[%d]\n", pTmpNode->data);
        pTmpNode = pTmpNode->nextNode;
    }
    printf("----------------\n");
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
*/