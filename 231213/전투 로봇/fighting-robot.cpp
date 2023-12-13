// n*n 격자 M개 몬스터(1칸에 1개) 1개 로봇
// 몬스터, 로봇 자연수 레벨, (로봇의 레벨 2)
// 로봇 1초 상, 하, 좌, 우 인접 1칸 이동
// 자신보다 레벨 큰 몬스터칸 이동X, 나머지 가능
// 자신보다 레벨 작은 목스터 없애기 가능
// 자신과 같은 레벨은 없애지는 못하지만 이동은 가능
// 전투로봇의 이동규칙
// 1) 없앨수 있는 몬스터가 있으면 없애러 이동
// 2) 없앨수 있는 몬스터가 1개 이상 거리가 가장 가까운 곳으로
// 2-1) 거리는 해당 칸으로 이동시 지나는 칸의 개수의 최솟값
// 2-2) 거리가 동일한 경우 가장위, 그 다음 가장 왼쪽 몬스터부터
// 3) 없앨수 있는 몬스터가 없다면 일을 끝
// 전투로봇 1칸 이동 1초, 몬스터 없애는 시간은 없음
// 로봇의 레벨과 같은 수의 몬스터를 없앨때마다 레벨 상승(시간 소모X)

// 공간에 몬스터와 전투로봇 정보가 있을때 일을 끝내기 전까지 걸린시간

// *입력
// 1)격자판의 크기 n (2~20)
// 2~n+1)  공간에 대한 정보 0 : 빈곳, 1~6 몬스터 레벨, 9 전투로봇

// *출력
// 일을 끝내기까지 걸린시간

// *알고리즘
// 알고리즘 구현시 내용이 빠지면 안되므로 
// 정리한 내용들이 구현된 곳에 주석으로 표시




// n*n 격자 M개 몬스터(1칸에 1개) 1개 로봇

// 로봇 1초 상, 하, 좌, 우 인접 1칸 이동

// 자신보다 레벨 작은 목스터 없애기 가능
// 자신과 같은 레벨은 없애지는 못하지만 이동은 가능
// 전투로봇의 이동규칙

// 2-1) 거리는 해당 칸으로 이동시 지라는 칸의 개수의 최솟값
// 2-2) 거리가 동일한 경우 가장위, 가장 왼쪽 몬스터부터
// 3) 없앨수 있는 몬스터가 없다면 일을 끝
// 전투로봇 1칸 이동 1초, 몬스터 없애는 시간은 없음
// 로봇의 레벨과 같은 수의 몬스터를 없앨때마다 레벨 상승(시간 소모X)

// 공간에 몬스터와 전투로봇 정보가 있을때 일을 끝내기 전까지 걸린시간

#include <iostream>
#include <queue>
#include <vector>
#define NUM_MAX 20
#define DEBUG 1
using namespace std;

int n;
int r_x; // 로봇위치
int r_y;
int m_x; // 제일 가까운 몬스터의 위치
int m_y;
int arr[NUM_MAX][NUM_MAX];
int robotLevel = 2;  // 몬스터, 로봇 자연수 레벨, (로봇의 레벨 2)
int robotKill = 0; // 로봇이 처리한 것들
int dx[] = {-1,0,1,0};
int dy[] = {0,-1,0,1}; 
int time = 0;

struct Point {
    int x, y;

    Point(int _x, int _y) : x(_x), y(_y) {}
};

vector<Point> Monsters;

bool canGo(){

    queue<Point> q;

    q.push(Point(r_x, r_y));
    int d = 0;
    int distance[n][n]; // 0으로 초기화
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            distance[i][j] = -1; 
        }
        
    }
    
    distance[r_x][r_y] = 0;

    while (!q.empty()) {
        Point current = q.front();
        if (DEBUG)
        {
            printf("front (%d, %d)\n",current.x,current.y);
        }
        int d = distance[current.x][current.y];
        for (int i = 0; i < 4; ++i) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && n < n && distance[nx][ny] == -1
            && (arr[nx][ny] <= robotLevel)) { // 자신보다 레벨 큰 몬스터칸 이동X, 나머지 가능
                q.push(Point(nx, ny));
                distance[nx][ny] = d+1;
            }
        }
        q.pop();
    }    
}

void go(){
    
    // 1) 없앨수 있는 몬스터가 있으면 없애러 이동
    // 2) 없앨수 있는 몬스터가 1개 이상 거리가 가장 가까운 곳으로
}
void simulate(){
    if (!canGo())
    {
        return;
    } else{
        go();
        simulate();
    }       
}
int main(){
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
            if (arr[i][j] == 9) //9 전투로봇
            {
                r_x = i;
                r_y = j;
            } else if (0 < arr[i][j] && arr[i][j] <= 6)
            {
                Monsters.push_back(Point(i,j));
            }                    
        }        
    }
    cout << time;
    simulate();
    
}