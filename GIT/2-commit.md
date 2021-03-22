# 초기 설정

- git 저장소 생성 or Clone, 커밋 이메일 등록 등

## git status

- 현재 repository의 working tree와 index의 상태를 보여주는 명령어
- ![status](2-status.png)
- **Your branch is up to date with [브랜치명]**
  - 현재 내가 작업중인 Branch 이름
- **Changes not staged for commit**
  - 파일들이 수정되었지만 Index로의 Staging이 이루어지지 않았기 때문에 stage 대기중인 파일들
- **Untracked files**
  - 이전 커밋 이후에 생성된 파일로, 한번도 Index에 올라가본 적 없는 (변화가 추적되지 않은) 새 파일

## git add [파일명1] [파일명2]

- 파일을 commit하기 전에 index에 등록
- 여러 파일을 띄어쓰기로 지정하여 올릴 수 있음
  > git add test.png test.html
- 파라미터에 파일명 대신 . 만 쓰면 해당 폴더 내 모든 파일을 등록함
  > git add .
