#include <stdio.h>

int main(void){
    printf("--------------\n");
    int b = 0;
    printf("Input your reverse-tree size : ");
    scanf("%d", &b);

    for (int i = b; i > 0; i--){ //i는 전체 층 수 부터 시작해서 감소
        int j = b + i - 1; //j는 층수 + i - 1부터 시작
        //만약 b = 3, i = 3이면 j = 5
        //만약 b = 3, i = 2이면 j = 4
        while (j > 0){
            if (j > 2 * i - 1){ //j가 2i - 1보다 클 때
                printf(" "); //공백 (트리의 왼쪽 옆)
            } else {
                printf("*"); //트리의 부품
            }
            j--; //j를 감소시켜가면서 반복
        }
        printf("\n"); //줄옮김
    }

}