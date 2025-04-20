#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1


typedef struct node *nodePointer;
//struct node* 의 별칭 -> nodePointer
typedef struct node {
    int data;
    nodePointer link;
}node;

int main() {
    //out배열: 각 숫자(index)가 탐색되었는지를 저장하는 배열
    int out[MAX_SIZE];
    //seq배열: 각 묶음들을 저장하는 배열
    nodePointer seq[MAX_SIZE];

    nodePointer x, y, top;
    //index 세기, 값 입력받기 용도
    int i, j, n;

    //초기화
    printf("Enter the size (<= %d) ", MAX_SIZE);
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        out[i] = TRUE;
        seq[i] = NULL;
    }

    //정보 입력받기
    printf("Enter a pair of numbers (-1 -1 to quit): ");
    scanf("%d%d", &i, &j);
    while(i >= 0) 
    {
        //새 노드를 만들어 j를 넣고 i번 노드에 추가
        x = (nodePointer)malloc(sizeof(node));
        x->data = j;
        x->link = seq[i];
        seq[i] = x;

        //새 노드를 만들어 i를 넣고 j번 노드에 추가
        x = (nodePointer)malloc(sizeof(node));
        x->data = i;
        x->link = seq[j];
        seq[j] = x;

        printf("Enter a pair of numbers (-1 -1 to quit): ");
        scanf("%d%d", &i, &j);
    }

    //모든 노드를 돌면서 연결고리 확인
    for (i = 0; i < n; i++)
        if (out[i]) {
            printf("\nNew Class: %5d", i);

            //클래스 i 탐색
            out[i] = FALSE;
            x = seq[i];
            //top: 방문 노드를 쌓는 스택
            top = NULL;
            for(;;) { //for(;;) -> 무한루프
            //while문 두개라고 생각
                //x랑 연결된 모든놈들을 다 출력할 것임 이 while에서
                //그리고 출력된 애들은 볼필요 없으니까 FALSE 처리리
                while(x) { //x가 null이 아니면 반복
                    j = x->data;
                    //아직 탐색되지 않았다면 위치를 저장하고 새로운 리스트로 이동
                    if (out[j]) {
                        printf("%5d", j);
                        out[j] = FALSE;
                        //write the code
                        y = x->link;
                        x->link = top;
                        top = x;
                        x = y;
                    }
                    //이미 탐색되었다면 통과
                    else 
                        //write the code
                        x = x->link;
                }
                //top이 FALSE이면(null이면) 전부 탐색한 것
                if (!top)
                    break;
                //위치를 저장해뒀던 top으로 이동
                x = seq[top->data];
                top = top->link;
            }
        }
    printf("\n");
    return 0;
}

//VS Code 내부에서 실행 X
//터미널 실행 by ./equivClass