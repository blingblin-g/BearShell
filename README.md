# MiniShell
42seoul team project named "Survivor"


# ground rule

## variable naming
- bool 타입은 is를 붙입니다.
- index로 사용하는 변수는 i, x, y로 사용합니다.
- 너무 축약하지 않기 ex) len(o) l(x), double_q(o), dq(x)

## function naming
- snake case
- 동사와 목적어로 명명하기 ex) search_space, process_dollar

## file naming
- 명사 형태로 명명하기
- 만약 동사가 필요하면 ing를 붙여서 동명사로 쓴다. ex) searching_space.c, processing_dollar.c
- 다른 함수에서 사용될 여지가 있는 함수는 *_utils.c 파일로 분리한다.

## how to comment
- 주석은 /* */를 사용한다.
- 함수의 선언부 위에 작성한다.
- 함수의 간단한 기능, 설명을 적는다.
- 사연이 있는 변수는 그 사연을 적어준다.
- 복잡한 로직은 자세한 설명을 적는다.

## commit message
- commit message head는 다음과 같은 용어를 사용해야한다.
   - [Add]: 새로운 기능이나 파일을 추가할 때
   - [Fix]: 버그 수정
   - [Update]: 기존의 함수를 개선
   
## branch strategy
- 기능별로 분류하여 사용한다.
- 기능이 마무리된 브랜치는 main 브랜치에 PR을 보낸다.
- 리뷰가 끝난 PR만 Merge 한다.

## 기획서 및 참고 자료
- https://hackmd.io/UPWWqCmJTnewt7Uw5wFsWA
- https://hackmd.io/aPSRZ-sjQg2p7YGiBTk5UQ#pipe
- https://mug896.github.io/bash-shell/index.html
