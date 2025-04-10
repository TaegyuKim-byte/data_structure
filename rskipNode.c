#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 3
#define MIN_DATA -9999

typedef struct SkipNode {
    int level;
    int data;
    struct SkipNode* next[MAX_LEVEL];
    //실제 값이 들어있는 배열
}SkipNode;
/*
구조 이해를 위한 자료 

Level 3:  A -----------> D -----------> NULL
Level 2:  A ------> C -> D -----------> NULL
Level 1:  A -> B -> C -> D -----------> NULL
Level 0:  A -> B -> C -> D -> E -> F -> NULL

각 노드의 next 배열:
A: [B, B, C, D]
B: [C, C, NULL, NULL]
C: [D, D, D, NULL]
D: [E, NULL, NULL, NULL]
...
*/
void insertSkipNode(SkipNode** pHeadNode, int data);
void showSkipNode(SkipNode* pHeadNode);
void searchSkipNode(SkipNode* pHeadNode, int data);

void showSkipNode(SkipNode* pHeadNode) {
    SkipNode* pTmpNode = NULL;
    int i, j;

    printf("--------------------------\n");
    for (i = MAX_LEVEL; i > 0; i--) {
        pTmpNode = pHeadNode->next[0];
        //반드시 [0]으로 각 숫자들을 훑어봐야함.
        //level 0에만 모든 숫자가 최소 1개 있기 때문
        printf("level %d:\t", i);
        //매개 노드 초기화
        while (pTmpNode != NULL) {
            if (pTmpNode->level >= i) {
                printf("%d-----", pTmpNode->data);
            } else {    
                printf("------");
            }
            pTmpNode = pTmpNode->next[0];
        }
        printf("NULL\n");
    }
    //for 구문 한바퀴 돌때마다 level 하나 다 보는거임
    //i값을 설정 -> 층수 고정. ->next[i] 하면 됨
    //각 층이 포인터로 연결된 건 아니지만 i층에서 가리키는 값이 있으면 그 값도 i층에 쌓여있는거임.
    //30이 2층에서 40을 가리킨다? 그게 2층에 있는 40을 정확하게 가리키는것 은 아님
    //하지만 30이 2층이였기 때문에 당연히 그 40도 2층으로 보는것.
    //pTmpNode[i]->next[i] 요렇게 i로 층수 통일
    printf("--------------------------\n");
}

void insertSkipNode(SkipNode** pHeadNode, int data) {
/*
함수 인자로 더블포인터를 갖는 경우는 대부분 
'포인터의 주소'를 가져와서
포인터의 값(주소) 자체를 수정할 수 있음
*/
    int level = 1, i, pos = MAX_LEVEL;
    SkipNode* pTmpNode[MAX_LEVEL];
    //SkipNode를 가리키는 포인터로 구성된 배열! (새로운 숫자의 층)
    SkipNode* pNewNode;

    //MAX_LEVEL에서 내려가면서 찾을 temp노드 변수 초기화
    for (i = 0; i < MAX_LEVEL; i++)
        pTmpNode[i] = *pHeadNode; 

    for (i = MAX_LEVEL - 1; i >= 0; i--) {
        while(pTmpNode[i]->next[i] != NULL) {
            if ((pTmpNode[i]->next[i])->data > data)
                break;
            pTmpNode[i] = pTmpNode[i]->next[i];
        } 
    }

    while (rand()%2) {
        level++;
        if (level >= MAX_LEVEL)
            break;
    }

    pNewNode = (SkipNode*)malloc(sizeof(SkipNode));
    pNewNode->data = data;
    pNewNode->level = level;
    for (int i = 0; i < MAX_LEVEL; i++)
        pNewNode->next[i] = NULL;

    for (i = pNewNode->level - 1; i >= 0; i--) {
        pNewNode->next[i] = pTmpNode[i]->next[i];
        pTmpNode[i]->next[i] = pNewNode;
        //왜 pNewNode[i]가 아니지?
        //애초에 pNewNode는 배열이 아님
    }

    printf("Insert [%d] with level [%d]\n", data, level);
}

void searchSkipNode(SkipNode* pHeadNode, int data) {
    int pos = MAX_LEVEL - 1;
    SkipNode* pTmpNode = pHeadNode->next[pos];

    while(pTmpNode == NULL || pTmpNode->data > data)
        pTmpNode = pHeadNode->next[--pos];
    
    printf("Search [%d] : ", data);
    while (pTmpNode->data != data) {
        if (pTmpNode->next[pos] == NULL || pTmpNode->next[pos]->data > data)
            pos -= 1;
        else {
            printf("%d, ", pTmpNode->data);
            pTmpNode = pTmpNode->next[pos];
            if (pTmpNode->data == data) {
                printf("%d\n", pTmpNode->data);
                return;
            }
        }
    }
    printf(",,, there is no %d\n", data);
    printf("------------------------------------\n");
}

int main() {
    //랜덤함수 시드 초기화
    srand(time(NULL));

    SkipNode* SkipList = (SkipNode*)malloc(sizeof(SkipNode));
    SkipList->level = MAX_LEVEL;
    //맨 앞 노드의 레벨: 무조건 MAX_LEVEL
    SkipList->data = MIN_DATA;                                            
    for (int i = 0; i < SkipList->level; i++) 
        SkipList->next[i] = NULL;
    //배열이라서 하나하나 다 초기화 vv  

    insertSkipNode(&SkipList, 3);
    insertSkipNode(&SkipList, 9);
    showSkipNode(SkipList);

    insertSkipNode(&SkipList, 1);
    insertSkipNode(&SkipList, 4);
    showSkipNode(SkipList);

    searchSkipNode(SkipList, 4);

    insertSkipNode(&SkipList, 5);
    insertSkipNode(&SkipList, 7);
    showSkipNode(SkipList);

    insertSkipNode(&SkipList, 6);
    insertSkipNode(&SkipList, 8);
    showSkipNode(SkipList);

    insertSkipNode(&SkipList, 2);
    insertSkipNode(&SkipList, 10);
    showSkipNode(SkipList);

    searchSkipNode(SkipList, 7);
    
    return 0;
}