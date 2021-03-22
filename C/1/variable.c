#include <stdio.h>
int main(void){
    printf("--------------\n");
    printf("char size: %d\n", sizeof(char)); //1바이트
    printf("short size: %d\n", sizeof(short)); //2바이트
    printf("int size: %d\n", sizeof(int)); //4바이트
    printf("long size: %d\n", sizeof(long)); //4바이트
    printf("float size: %d\n", sizeof(float)); //4바이트
    printf("double size: %d\n", sizeof(double)); //8바이트
    printf("--------------\n");
    printf("Decimal : %d\n", 252); //252
    printf("Octal : %o\n", 252); //374 = 64*3 + 8*7 + 4
    printf("Hexadecimal : %x\n", 252); //fc = 15*16 + 12
    printf("--------------\n");
    printf("%5d\n", 357); //공백 발생
    printf("%.2f\n", 2.2367); //소수점 2자리 아래에서 컷
    printf("%8.5f", 3.451); //공백 1개, 소수점 아래 0 2개 추가
}