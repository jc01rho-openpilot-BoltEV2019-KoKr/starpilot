# StarPilot Repository Guide

## Branch Commit And Push Workflow

일반 수정은 `paddle5`에서 검증·커밋한 뒤 `paddle5_215-55-17`에 merge하여 두 브랜치에 동일하게 전파한다.

1. `paddle5`에서 작업 트리가 요청 범위의 변경만 포함하는지 확인한다.
2. 관련 테스트와 build 검증을 통과한 뒤 원자 단위로 커밋한다.
3. `git push origin paddle5`로 `paddle5`를 먼저 push한다.
4. `paddle5_215-55-17`로 전환하여 `git merge paddle5 --no-edit`를 실행한다.
5. 충돌이 발생하면 215 전용 커스터마이징을 보존한다. 단, 파일 전체를 무조건 `--ours`로 덮지 말고 충돌 영역이 실제 215 전용 변경인지 확인한다.
6. merge 후 영향받는 테스트와 build 검증을 다시 실행한다. `*.capnp` 변경이 포함되면 schema load, ordinal, union init, round-trip, consumer 검증을 재실행한다.
7. `git push origin paddle5_215-55-17`로 215 브랜치를 push한다.
8. 두 브랜치의 로컬·원격 SHA가 일치하는지 확인한 뒤 `paddle5`로 복귀한다.
9. 최종 작업 트리는 clean이어야 한다.

Upstream 동기화는 `.opencode/skills/starpilot-sync.md` 규칙을 따른다. `upstream/Dom`을 사용할 때도 `paddle5`에 먼저 병합·검증하고, 이후 위 순서로 `paddle5_215-55-17`에 전파한다.

기존 stash와 다른 worktree의 변경은 명시적 요청 없이 수정하거나 삭제하지 않는다. 강제 push, commit amend, destructive reset은 사용하지 않는다.
