// *
// 길이 n 무빙워크 사람을 한쪽 끝에서 반대쪽 끝으로 옮겨주는 기계-> 총 2n개의 판
// 시계방향 회전
// 2n번째 칸은 1번칸으로 
// 사람은 1번칸에서 올라서서 n번 칸에서 내림 ( n+1에서 2n까지는 존재X)
// 사람이 올라가거나 내리면 그 칸의 안정성은 1만큼 감소
// 안정성 0인 칸은 올라갈수 없음
// 안정성 테스트
// 1) 무빙워크 1칸 회전
// 2) 가장 먼저! 무빙워크에 올라간 사람부터 회전하는 방향으로 1칸 이동
// *앞선칸에 사람이 이미 있거나 앞선 칸의 안정성이 0인 경우 이동X, n칸에 해당되면 내림
// 3) 1번 칸에 사람이 없고 안정성이 0이 아니면 사람을 1명더 올림
// 4) 안정성이 0인 칸이 k개 이상이면 과정 종료 그렇지 않으면 위 과정 반복
// 1~3)과정 중 n번 칸에 사람이 위치하면 즉시 내림
// 안정성은 시간이 지나도 상승하지 않음

// *입력
// 1) 길이 n(1~100), 안정성이 0인판의개수 k(1~2n)
// 2) 무빙워크 각 칸의 안정성 (2n개)  (1~1,000)


// *출력
// 종료까지 실험횟수

#include <iostream>
#define MAX_N 100
#define DEBUG 1

using namespace std;
int n, k;
int ex_num = 0;
int movingwork[MAX_N*2];
int person[MAX_N];

void Rotate(){
    
}

void simulate(){
    Rotate();
}
int main() {
    cin >> n;
    for (int i = 0; i < MAX_N*2; i++)
    {
        cin >> movingwork[i];
    }

    int brokenMovingWorkNum = 0;
    while (brokenMovingWorkNum < k)
    {
        simulate();
        ex_num++
    }
    cout << ex_num;
    
    
    //무빙워크
    // 내구도
    // 회전 (값의 이동) 

    // 사람
    // 회전할 필요는 없다. 0~n-1까지만
    // 사람의 이동
    // 사람의 위치에 무빙워크 내구도 감소

    return 0;
}