#include <stdio.h>
#include <stdlib.h>

int fibo(int n, int* fs)
{
    //6-11줄 -> fs[n]의 값이 설정되어 있을 때: 그대로 return
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else if (fs[n] > 0)
        return fs[n];
    
    //14-15 -> fs[n]값이 설정되어있지 않을 때: 값을 설정해주고 return
    fs[n] = fibo(n - 1, fs) + fibo(n - 2, fs); 
    //요렇게 정수형 포인터 배열을 가지고 값을 할당하면 주소만 반복해서 갖고오면 되기 때문에 계산 중복 X 
    return fs[n];
}

int main() 
{
    int n = 0;

    printf("구하고 싶은 항의 번호를 입력하시오: ");
    scanf("%d", &n);

    int* fs = (int*)malloc(sizeof(int) * (n+1));
    for(int i = 0; i <= n; i++) fs[i] = -1;
    
    printf("F(%d) = %d\n", n, fibo(n, fs));

    free(fs);

    return 0;
}