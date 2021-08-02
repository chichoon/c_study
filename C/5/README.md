# C언어 #5 for, while문

### [예제 코드](forwhile.c)

## 반복문

- 노가다는 하고싶지 않다!
- 똑같은 내용을 반복해야만 할 때 사용하는 구문들

## for문

- 제어 변수의 값을 반복 시마다 조정해주며, 제어 변수의 값이 조건을 만족하지 않을 경우 반복을 중지한다
- 이것을 이용하여 반복 횟수를 지정할 수 있음

  > for ([초기식]; [조건식]; [증감식]){ 반복할 내용 }

- **초기식** : 제어 변수의 초기값이 지정되는 부분
  > int i = 0;
  >
  > > i는 0부터 시작
- **조건식** : 제어 변수의 조건이 지정되는 부분
  > i < 10;
  >
  > > i는 10 미만이어야 for문이 작동한다
- **증감식** : 1회 실행 시 제어 변수의 변화량
  > i++;
  >
  > > 반복문이 실행될 때마다 i는 1씩 증가
- 조건식을 적지 않으면 (비우면) 무한반복한다..

## while문

- for문과 비슷하지만, 조건식만 적는다는 점에서 조금 다르다
  > while ([조건문]) { 반복할 내용 }
- 조건이 참이면 반복하고, 처음으로 거짓이 나올때 반복을 중단한다
  - 조건문은 if/else를 사용할 때와 같이 적어주면 됨
- 1은 항상 참이라는 의미를 가지므로, while (1) 은 무한 루프를 뜻한다

## do while 문

- while과 비슷하지만, while문은 맨 처음에 명령을 시작할 때부터 조건식이 참인지 아닌지 검사한다
- do while문은 맨 처음 한 번 명령을 실행한 후, 조건식을 검사한다
  - 따라서 반복할 내용이 한 번은 무조건 수행되고, 그 뒤는 조건식에 따라서 결정됨

## break

- 반복문에서 **탈출**하기 위한 수단
- for (;;) 또는 while (1) 등은 무한루프이기 때문에 빠져나올 수 없다
  - 리소스 잡아먹는 건 덤이다
- 이때 if/else문, break를 이용해서 조건을 만족할 경우 반복문을 탈출할 수 있다
- break가 성립되면 아래에 있는 코드는 무시하고 탈출한다
  > while (1){  
  > if (a == 5){  
  >  break  
  > }  
  > }
  >
  > > a가 5일 때 while 무한루프 탈출

## continue

- 반복문의 내용을 무시하고 반복문의 조건 점검부로 워프한다
- continue가 성립되면 아래에 있는 코드는 무시하고 다시 조건을 체크한다
  > for (i = 0; i < 100; i++) {  
  >  if (i % 5 == 0) continue;
  >
  > printf("%d ", i);  
  > }
  >
  > > i가 5의 배수일 때마다 printf를 실행하지 않음