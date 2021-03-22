#include <stdio.h>
int main(void){
    printf("--------------\n");
    for (int i = 0; i < 50; i++){ //i는 0부터 50 미만까지 총 50회 반복
    //i = 49까지만 작동하고 i = 50일 땐 조건 불만족으로 탈출
        printf("Now i is : %d\n", i); //i의 값이 50번 출력
    }
    printf("--------------\n");
    int a = 0;
    while (1){
        printf("You can escape when put 5 : ");
        scanf("%d", &a);
        if (a == 5){ //입력받은 값이 5이면 종료
            break;
        }
        else {printf("your input : %d\n", a);}
        //입력받은 값이 5가 아니면 값 출력 후 반복
    }
}