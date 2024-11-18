// *문제
// *N지역사람, S지역 사람
// 4개의 팔각의자
// K번 회전 (시계 or 반시계 45도 회전)
// 회전규칙
// 1) 회전시킬 의자 번호, 방향 주어짐
// 2) n의자 회전시 주변의자 (n-1, n+1) 또한 회전
// 3) 회전시 제일 가깝게 마주친 2명의 지역이 다르면 반대 방향 회전
// 3-1) 같으면 회전하지 않음
// 4) 한번 회전이 일어난 후 모든 회전이 일어날때까지 기다림
// 5) 한번 회전한 의자는 다시 회전 하지 않음

// *입력
// 1~4) n번째 의자에 않아있는 사람들의 지역
// * 12시방향부터 시계방향순서대로 공백없이 0: 북쪽, 1 : 남쪽
// 5) 회전수 k (1~100)
// 6~k+5) 회전시킬 팔각의자 번호 n, 방향 d( 1: 시계방향, -1 : 반시계 방향)

// *출력
// 각의자 12시방향 의자에 남쪽지방 착석 여부 출력
// 각 테이블 여 s1, s2, s3, s4라고 할 때
// 1*s1 + 2*s2 + 4*s3 + 8*s4를 출력

// *알고리즘
// 회전방향은 동시에 결정!

#include <iostream>
#include <cmath>

#define MAX_N 4
#define MAX_M 8
#define ROTATE_CW 1
#define ROTATE_CCW -1
#define NOT_ROTATE 0

using namespace std;
int n = 4, m = 8, k;
char a[MAX_N+1][MAX_M+1];
int roate_dir[MAX_N + 1];

void shift(int curr_num, int curr_dir){
    if(curr_dir == ROTATE_CW){
        int temp = a[curr_num][m];
        for(int i=m; i>=2; i--){
            a[curr_num][i] = a[curr_num][i-1];
        }
        a[curr_num][1] = temp;
    }else{
        int temp = a[curr_num][1];
        for(int i=1; i<= m-1; i++){
            a[curr_num][i] = a[curr_num][i + 1];
        }
         a[curr_num][m] = temp;
    }
}

int FLip(int curr_dir){
    return (curr_dir == ROTATE_CW) ? ROTATE_CCW : ROTATE_CW;
}

void Simulate(int start_num, int start_dir){
    for(int i=1; i<=n; i++){
        roate_dir[i] = NOT_ROTATE;
    }
    roate_dir[start_num] = start_dir;

    // 좌측 회전방향 설정
    for(int i=start_num-1; i>=1; i--){
        if(a[i][3] != a[i+1][7]){
            roate_dir[i] = FLip(roate_dir[i+1]);
        }
        else{
            break;
        }
    }

    //우측방향 설정
    for(int i=start_num+1; i<=n; i++){
        if(a[i][7] != a[i-1][3]){
            roate_dir[i] = FLip(roate_dir[i-1]);
        }
        else{
            break;
        }
    }

    //회전이 결정된 방향으로 회전
    for(int i=1; i<=n; i++){
        if(roate_dir[i] != NOT_ROTATE){
            shift(i, roate_dir[i]);
        }
    }
}

int main(){
  for(int i=1; i<=n; i++){
    for(int j=1; j<=m; j++){
        cin >> a[i][j];
    }
  }
  cin >> k;

  while(k--){
    int start_num, start_dir;
    cin >> start_num >> start_dir;

    Simulate(start_num, start_dir);
  }

  int ans = 0;
  for(int i=1; i<=n; i++){
    if(a[i][1] == '1'){
        ans += pow(2,i-1);
    }
  }
  cout << ans;
  return 0;
}