# Shell

### 목차

## Kernel

- 프로그램을 동작시키는 것은 특정 명령으로 하드웨어를 작동시키는 방식
- 이때 하드웨어를 직접 제어하는 코어 부분이 **커널** 임

## Shell

- 사용자가 직접 명령을 입력하는 부분
- **쉘**은 사용자의 명령을 해석해서 커널에게 전달해주는 역할을 함
  - (커널을 사용자가 직접 제어하는 것은 까다롭다)
- 그럼 그 커널은 쉘에게 받은 명령을 기반으로 하드웨어를 동작시켜 원하는 결과를 출력
- 어플리케이션 (프로그램) 또한 이러한 쉘을 사용자가 쉽게 다룰 수 있도록 설계된 것

## Shell Script

- 버전관리 시스템