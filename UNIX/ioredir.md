# IO Redirection

## Standard Output redirection

- 명령어 입력 후 결과물을 파일로 저장하고 싶을 때 (예를 들면 폴더목록 등) 사용
- \> 앞에 1이 default로 붙어있는 상태 (1>와 같은 의미)
- **[명령어] [옵션] > [파일명]**
- 예시: ls -l **>** result.txt
  - ls -l 1> result.txt와 같은 의미임
  - 커맨드창에 결과물이 출력되지 않는 대신 파일에 저장된다 (파일로 리다이렉션 되었다)
- 값을 덮어쓰지 않고 원본 파일에 append할 땐 **>>** 사용

## Standard Error redirection

- 2> 를 사용
- 1은 Standard Output을 의미, 2는 Error를 의미하기 때문
- 예시: rm -rf [존재하지않는파일.txt] 2> error.txt
- 위의 Standard Output redirection과 혼용 가능하다
  - 예시: rm -rf input.txt 1> result.txt 2> error.txt

## Standard Input redirection

- <를 사용
- 원래는 argument (인자) 로 불러오는 대신 Standard Input으로 불러와줌
- 당연하게도 위의 두 개와 이어서 쓸 수 있음
- 여러 개의 값을 묶어서 사용할 때
  - [커맨드] << [마지막문자열]
  - 그리고 뒤에 [문자열1] [문자열2] [마지막문자열] 을 적는다
  - [마지막문자열] 을 입력값의 끝으로 보고 연속으로 입력받는것을 종료함

## /dev/null

- 쓰레기통
- [커맨드명] > /dev/null 하면 결과값이 쓰레기통으로 직행한다
