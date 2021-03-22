#include <stdio.h>

int main(void){
    printf("--------------\n");
    int b = 0;
    printf("Input your tree size : ");
    scanf("%d", &b);
    for (int i = 0; i < b; i++){ //i는 1씩 계속 증가
        int j = 0; //j는 0부터 시작해서 1씩 증가
        while (j < b + i + 1){ //j가 b + i + 1 보다 작을 때
            if (j < b - i){
            //만약 b = 3, i = 3이면 공백 개수 = 0
            //만약 b = 3, i = 2이면 공백 개수 = 1
                printf(" ");
            } else {
                printf("*");
            }
            j++; //j 1씩 늘려가며 반복
        }
        printf("\n");
    }
}