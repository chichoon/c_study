# Shell

### 목차

1. [Kernel](#Kernel)
2. [Shell](#Shell)
3. [Bash & zsh](#Bash-&-zsh)
4. [Shell Script](#Shell-Script)
5. [Shell Script 작성하기](#Shell-Script-작성하기)

## Kernel

- 프로그램을 동작시키는 것은 특정 명령으로 하드웨어를 작동시키는 방식
- 이때 하드웨어를 직접 제어하는 코어 부분이 **커널** 임

## Shell

- 사용자가 직접 명령을 입력하는 부분
- **쉘**은 사용자의 명령을 해석해서 커널에게 전달해주는 역할을 함
  - (커널을 사용자가 직접 제어하는 것은 까다롭다)
- 그럼 그 커널은 쉘에게 받은 명령을 기반으로 하드웨어를 동작시켜 원하는 결과를 출력
- 어플리케이션 (프로그램) 또한 이러한 쉘을 사용자가 쉽게 다룰 수 있도록 설계된 것

## Bash & zsh

- **bash**는 기본적으로 ubuntu에 설치되어 있는 상태
- **zsh**는 추가적으로 설치를 해야함
- 두 프로그램은 부모가 같아 상당히 유사한 특성을 띄지만 zsh 쪽이 추가적인 기능이 많아 편의성이 높다
- 쉘은 이처럼 다양한 종류가 있기 때문에 사용자가 원하는 쉘을 선택해서 사용해도 커널을 자유롭게 제어할 수 있다

## Shell Script

- 쉘을 이용하여 명령을 실행시킬 수 있는데, 이 명령이 한 줄이 아니라 여러 줄로 이루어져 있을 경우에 명령을 순서대로 실행시키기 위한 각본을 **shell script** 라 한다
- 쉘 스크립트를 사용하면 여러 줄의 복잡한 명령을 언제나 재사용이 가능하기 때문에 편리하다

## Shell Script 작성하기

- 파일의 맨 앞은 **! /bin/bash** 라고 작성

  - 해당 코드가 무슨 shell 프로그램을 이용하여 실행되는지 명시하는 것
  - /bin/bash는 bash를 이용해 shell을 실행시킬 것이란 의미

- 확장자는 일반적으로 **.sh**

- [Shell Script 문법](shell_command.md)
- 쉘 스크립트를 작성했을 땐 **권한을 꼭 변경**해서 실행가능하게 만들어줘야 함 (안그러면 읽기/쓰기만 가능)
  - chmod +x [파일명] 은 **모든 유저에 대하여 x 권한** (실행 권한) 을 파일에 추가함
    > chmod +x test.sh
