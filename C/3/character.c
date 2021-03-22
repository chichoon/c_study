#include <stdio.h>
int main(void){
    printf("--------------\n");
    char a = 'a';
    printf("value of a = %d, character = %c\n", a, a); //value of a = 97, character = a
    printf("--------------\n");
    int d;
    printf("Input any number : ");
    scanf("%d", &d);
    printf("%d + 1 = %d", d, d + 1); //입력한 숫자, 입력한 숫자 + 1
    return 0;
}