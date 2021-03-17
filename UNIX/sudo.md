# 패키지 매니저

## sudo apt-cache

- 패키지를 탐색할 때 사용하는 명령어

### sudo apt-cache search [패키지명]

- 패키지명을 apt 패키지 목록에서 검색, 간단한 설명과 함께 출력

## sudo apt-get

- 패키지를 설치할 때 사용하는 명령어

### sudo apt-get update

- 설치된 패키지의 인덱스 정보를 업데이트

### sudo apt-get upgrade

- 인덱스 정보를 바탕으로 설치된 패키지를 최신 버전으로 업그레이드

### sudo apt-get install [패키지명]

- 새로운 패키지 설치

### sudo apt-get remove [패키지명]

- 패키지 삭제

### sudo apt-get source [패키지명]

- 패키지의 소스코드 다운로드

### sudo apt-get build-dep [패키지명]

- 다운받은 소스코드를 의존성 있게 빌드
