# graduate
졸업프로젝트

# 형상관리
## 이슈사항
* 작업단위로 이슈 등록
* 나누어진 작업 단위에서 또 할 작업이 나누어 진다면 체크박스를 이용하여 작업을 세분화 한다.
* 누가 할 작업인지 assignee를 등록한다.
* label을 통해 해당 이슈가 어떠한 작업인지 구별한다.
    * assign과 label은 복수의 선택도 가능하다.
## 브랜치
master : 프로젝트 완성되면 병합<br>
└ develop : 프로젝트 도중 issue 단위의 구현이 완료되었을 때 병합<br>
...├ feature/#{issue_number} : 각 이슈마다 develop 하위에 브랜치를 생성하여 작업한다. <br>
... : <br>
...└ feature/#{issue_number}<br>
