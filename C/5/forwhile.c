#include <stdio.h>
int main(void){
    printf("--------------\n");
    int num;
    printf("Input any number : ");
    scanf("%d", &num);
    if (num < 9) { //입력한 숫자가 9보다 작을 경우
        printf("%d is less than 9", num); 
    } else if (num >= 9 && num < 18) { //입력한 숫자가 9 이상 18 미만일 경우
        printf("%d is bigger or same with 9", num);
    } else { //그 외: 입력한 숫자가 18 이상일 때
        printf("%d is bigger or same with 18", num);
    }
    return 0;
}