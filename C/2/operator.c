#include <stdio.h>

int main(void){
    printf("3 + 4 : %d\n", 3 + 4); //7
    printf("16 - 8 : %d\n", 16 - 8); //8
    printf("4 * 8 : %d\n", 4 * 8); //32
    printf("27 / 4 : %d\n", 27 / 4);  //정수끼리의 나눗셈 : 6
    printf("27.0 / 4.0 : %f\n", 27.0 / 4.0); //실수끼리의 나눗셈 : 6.750000
    printf("34 %% 8 : %d\n", 34 % 8); //2

    printf("--------------\n");

    int a, b;
    a = b = 8;
    printf("a = %d, b = %d\n", a, b); //a = 8, b = 8

    printf("--------------\n");

    printf("a is now %d\n", a);
    a += 2;
    printf("a += 2 -> a is now %d\n", a); //8 + 2 = 10
    a -= 2;
    printf("a -= 2 -> a is now %d\n", a); //10 - 2 = 8
    a *= 2;
    printf("a *= 2 -> a is now %d\n", a); //8 * 2 = 16
    a /= 2;
    printf("a /= 2 -> a is now %d\n", a); // 16 / 2 = 8

    printf("--------------\n");

    printf("a is now %d\n", a); //a는 8
    printf("a++ => a is now %d\n", a++); //출력 후 계산 -> a는 8
    printf("a is now %d\n", a); //연산이 되었으므로 a는 9
    printf("++a => a is now %d\n", ++a); //계산 후 출력 -> a는 10
    printf("a-- => a is now %d\n", a--); //출력 후 계산 -> a는 10
    printf("a is now %d\n", a); //연산이 되었으므로 a는 9
    printf("--a => a is now %d\n", --a); //계산 후 출력 -> a는 8
    
    printf("--------------\n");

    int c = 0x73; //0111 0011
    int d = 0xC6; //1100 0110
    printf("c & d : %x\n", c & d); //0x42 = 0100 0010
    printf("c | d : %x\n", c | d); //0xf7 = 1111 0111
    printf("c ^ d : %x\n", c ^ d); //0xb5 = 1011 0101
    printf("~c : %x\n", ~c); //0xffffff8c (int = 4바이트이기 때문에)
    printf("c << 2 : %x\n", c << 2); //0x1cc = 0001 1100 1100
    printf("c >> 3 : %x\n", c >> 3); //0xe = 1110
    return 0;
}