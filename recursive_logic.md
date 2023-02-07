재귀함수


1. 자신의 타입 확인
    1. Logical node
        1. Cmd 노드에 들어가서 재귀 실행 => cmd실행결과가 child_status 에 저장
        2. Logical type 확인
            1. Pipe
                1. Next node 들어가서 재귀 실행
            2. And
                1. child_status 확인 true면 next node 들어가서 재귀 실행
            3. Or
                1. child_status 확인 false면 next node 들어가서 재귀 실행
            4. Temp
                1. 부모노드가 있으면 parent_node->status_code = status_code (현재 상태코드 부모노드로 복붙)
                2. Next_node 들어가서 재귀 실행
            5. Null
                1. 종료
        3. Secondary logical node 들어가서 실행
    2. cmd
        1. Redirect 노드 확인하고 있으면 들어가서 재귀 실행
        2. Command와 arguments를 가지고 command 수행
        3. status를 parent_node->child_status 에 저장
    3. Redirect
        1. Redirect_type, File 가지고 redirect 명령 수행
        2. 다음 redirect 노드가 있는지 확인하고 있으면 들어가서 재귀 실행
        3. 없으면 종료

