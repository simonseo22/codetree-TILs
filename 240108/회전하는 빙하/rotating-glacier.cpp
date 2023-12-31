// *문제
// 2^n * 2^n 격자의 빙하를 회전 ( 오른쪽?)
// 빙항에 속한 각각의 얼음은 인접 회전성이라는 성질 소유
// 좌측 상단에 있는 빙하, 특정범위 선택 -> 회전, 상하좌우 인접격자들도 똑같은 크기로 회전
// 레벨 : 빙하 회전 범위
// L레벨 2^L * 2^L만큼 격자 선택 2^(L-1) * 2^(L-1)만큼 잘라 4등분 하여 회전
// 회전이 끝난다음 빙하의 얼음이 녹음
// 1칸을 기준으로 상하좌우 인접한칸의 얼음이 3개 이상인경우 녹지 않음, 그렇지 않으면 1 줄어듬
// 인접칸이 격자를 벗어나거나 해당칸의 값이 0인경우 얼음이 존재X라고 가정, 얼음이 녹는것은 동시에 진행
// 모든 회전이 끝난 다음 남아있는 빙하의 양(격자 총합)과 가장 큰 얼음 군집(상하좌우 연결)의 크기 출력

// *입력
// 1) 회전 가능 레벨 n(격자의 크기가 2^n * 2^n이다. 2~6), 회전 횟수 q(1~1000)
// 2~2^n+1 ) 빙하 각 칸에 있는 얼음의 양 (0~100)
// 2^n+2 ~ ) 회전 레벨 ( 0~ n)
// * 회전은 반드시 순서대로 진행

// *출력
// 1) 빙하의 총양
// 2) 가장 큰 크기를 가지는 얼음 군집의 크기 ( 존재X면 0출력)


#include <iostream>

int main() {
    // 회전
    // 빙하녹음
    // 출력(군집계산 BFS)
    return 0;
}