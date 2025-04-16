#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1

typedef struct node *nodePointer;
//struct node* 의 별칭 -> nodePointer
typedef struct node
{
    int data;
    nodePointer link;
};

int main() {
    int out[MAX_SIZE];
    nodePointer seq[MAX_SIZE];
    nodePointer x, y, top;
    int i, j, n;

    printf("Enter the size (<= %d) ", MAX_SIZE);
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        out[i] = TRUE;
        seq[i] = NULL;
    }

    printf("Enter a pair of numbers (-1 -1 to quit): ");
    scanf("%d%d", &i, &j);
    while(i >= 0) 
    {
        //새 노드를 만들어 j를 넣고 i번 노드에 추가
        x = (nodePointer)malloc(sizeof(node));

        printf("Enter a pair of numbers (-1 -1 to quit): ");
        scanf("%d%d", &i, &j);
    }

    for (i = 0; i < n; i++)
        if (out[i]) {
            printf("\nNew Class: %5d", i);

            //클래스 i 탐색
            out[i] = FALSE;
            x = seq[i];
            top = NULL;
            for(;;) {
            //while문 두개라고 생각
                while(x) {
                    j = x->data;

                }
            }
        }
    return 0;
}