// *
// 배터리 모두 소모시 움직일수 없음
// n*n격자 도로, 배터리양, 벽의위치 , m명의 승객의 위치
// 주어진 배터리 용량으로  승객을 모두 태울수 있는지 test
// 출발지 -> 승객 -> 목적지 항상 최단거리 이동
// 한칸 이동시 배터리 1 소요
// 승객을 목적지에 태워주면 승객을 태워 이동하며 소모된 배터리의2배만큼 충전후 다시 이동
// 이동 중 배터리가 모두 소모되면 그 즉시 종료 
// 승객을 목적지로 이동 후 배터리가 모두 소모되면 소모된 배터리의 2배만큼 다시 충전후 운행재개 가능
// 마지막 승객을 태운후 운행을 종료하는 순간에도 충전은 이뤄짐 !!!
// 여러명의 승객 -> 최단 거리가 가장 짧은 승객을 먼저 태움(여러명이면 가장 위, 왼쪽 승객을 먼저)

// 도로의 상태가 주어질때 모든 승객을 성공적으로 데려다 줄수 있는지 여부
// 데려다 줄수 있다면 최종적으로 남은 배터리의 양 출력

//*
// 1) 격자크기 n(2~20), 승객수 m(1~n^2), 초기 배터리 충전량 c(1~500,000)
// 2~n+1) 도로정도 0 : 도로, 1 : 벽
// n+2) 자율주행 전기차 초기 위치 정보 x, y
// n+3~n+3+m-1) m개 승객에 출발지 위치 정보 x_s, y_s 도착지 위치정보 x_e, y_e
// (출발지, 도착지는 1이상 n이하의 자연수)

//모든 승객의 출발지와 목적지는 빈칸으로 가정해도 좋습니다. -> 벽일 일은 어 ㅄ다.
// 각 승객의 출발지와 목적지는 모두 다르다고 가정해도 좋습니다. -> 출-목이 겹치지 않는다.
// 단 한 승객의 출발지와 다른 승객의 목적지는 같을 수 있습니다. -> 목적지에 내려준후 바로 픽업 가능
// 서로 다른 승객의 출발지가 동일한 경우는 없다고 가정해도 좋습니다. -> 한곳에서 여러명을 픽업하는 경우는 없음

#include <iostream>
#include <tuple>
#include <queue>
#include <climits>
#define DEBUG 0
#define MAX_N 20
#define MAX_M 400

using namespace std;
int n,m,c;
int Road[MAX_N][MAX_N];
int Dist[MAX_N][MAX_N]; // 거리 정보 저장, 방문하지 않은곳은 -1(또한 벽인부분도 1로)로 ( x_c,y_c를 0으로 지정), BFS의 visited로 사용
int Passenger[MAX_M][4];
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
int x_c, y_c;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y){
    // 범위를 벗어나거나
    if (!InRange(x,y))
    {
        return false;
    }
    
    // 벽이거나
    return Road[x][y] == 0 && Dist[x][y] == -1; // 빈공간이면서 또한 거리가 아직 책정되지 않은경우
}

void calDist(){
    // 거리 초기화
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Dist[i][j] = -1;
        }    
    }
    
    // BST진행
    queue<pair<int,int>> q;
    q.push(make_pair(x_c,y_c));
    Dist[x_c][y_c] = 0;
    while (!q.empty())   
    {
        int curr_x, curr_y;
        tie(curr_x,curr_y) = q.front();
        q.pop();
        for (int dir = 0; dir < 4; dir++)
        {
            int nx = curr_x + dx[dir];
            int ny = curr_y + dy[dir];
            if (CanGo(nx,ny))
            {
                Dist[nx][ny] = Dist[curr_x][curr_y] + 1;
                q.push(make_pair(nx,ny));
            }            
        }        
    }    

    if (DEBUG)
    {
        printf("Dist!\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << Dist[i][j] << " ";
            }
            cout << endl;
        }
    }    
}

int ChoseMinDistPassenger(){
    tuple<int, int, int> minPassenger(INT_MAX, INT_MAX, INT_MAX);
    int minPassengerIndex = -1;
    for (int i = 0; i < m; i++)
    {
        if (Passenger[i][0] == -1)
        {
            continue;
        }
        int x_s = Passenger[i][0];
        int y_s = Passenger[i][1];
        tuple<int, int, int> newPassenger = make_tuple(Dist[x_s][y_s],x_s,y_s);
        if (minPassenger > newPassenger)
        {
           minPassenger = newPassenger;
           minPassengerIndex = i;
        }
    }    

    if (DEBUG)
    {
        printf("minPassenger :%d (%d,%d)\n",minPassengerIndex, get<1>(minPassenger), get<2>(minPassenger));
    }
    
    return minPassengerIndex;
}

void moveToDestination(int minPassengerIndex){ 

    // 거리 초기화
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Dist[i][j] = -1;
        }    
    }

    // 가능 거리 또한 BFS를 이용해 탐색
    int x_s = Passenger[minPassengerIndex][0];
    int y_s = Passenger[minPassengerIndex][1];
    int x_e = Passenger[minPassengerIndex][2];
    int y_e = Passenger[minPassengerIndex][3];

    queue<pair<int,int>> q;
    q.push(make_pair(x_s, y_s));
    Dist[x_s][y_s] = 0;
    int BatteryConsumption = 0;
    while (!q.empty())   
    {
        int curr_x, curr_y;
        tie(curr_x,curr_y) = q.front();
        q.pop();
        for (int dir = 0; dir < 4; dir++)
        {
            int nx = curr_x + dx[dir];
            int ny = curr_y + dy[dir];
            if (CanGo(nx,ny))
            {
                Dist[nx][ny] = Dist[curr_x][curr_y] + 1;
                if (nx == x_e && ny == y_e)
                {
                    BatteryConsumption = Dist[nx][ny];
                    // 멈춘 위치가 아니고
                    c = c - BatteryConsumption;
                    if (c < 0) // 정확히 0이어도 목적지에 도착하면 채워짐
                    {
                        return;
                    }
                    x_c = nx; // 차량 위치 이동
                    y_c = ny;
                    c = c + BatteryConsumption * 2;

                    for (int i = 0; i < 4; i++)
                    {
                        Passenger[minPassengerIndex][i] = -1;
                    }

                    if (DEBUG)
                    {
                        printf("car move to Destination(%d,%d) left battery : %d\n",x_s,y_s,c);
                    }

                    return;
                }
                q.push(make_pair(nx,ny));
            }            
        }        
    } 

    
    
}

void moveToPassenger(int minPassengerIndex){ 
    int x_s = Passenger[minPassengerIndex][0];
    int y_s = Passenger[minPassengerIndex][1];

    c = c - Dist[x_s][y_s];
    x_c = x_s;
    y_c = y_s;
    if(DEBUG){
        printf("car move to Passenger, left battery : %d\n",c);
    }
}


void simulate(){
    // 거리 계산
    calDist();
    // 이동 지점 선택
    int ChosenPassengerIndex;
    ChosenPassengerIndex = ChoseMinDistPassenger();
    // 이동 (벽을 피하기 위해  BFS진행 ? 목적지 도착지는 이동해도 괜찮은가?)
    moveToPassenger(ChosenPassengerIndex); // 자동차 -> 승객이동, 배터리 소모
    if (c <=0) // 출발해야 하는데 배터리가 0인 경우
    {
        return;
    }    
    moveToDestination(ChosenPassengerIndex); // 승객 -> 목적지 이동, 배터리 소모, 충전, 승객 제거
}

bool End(){
    if (c <= 0) // 배터리가 0이어도 
    {
        return true;
    }    
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (Passenger[i][j] != -1) 
            {
                return false;
            }            
        }        
    }
    return true; 
}

int main() {
    cin >> n >> m >> c;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)     
        {
            cin >> Road[i][j];
        }        
    }
    cin >> x_c >> y_c;
    x_c--;
    y_c--; // 순서를 좌표로 보정

    // 초기화
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Passenger[i][j] = -1;
        }        
    }
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> Passenger[i][j];            
            Passenger[i][j]--; // x_s, y_s, x_e, y_e를 각각 입력
        } 
    }

    if (DEBUG)
    {
        printf("input print!\n");
        printf("n : %d, m : %d, c: %d\n",n,m,c);
        printf("x_c : %d, y_c : %d\n",x_c,y_c);
        printf("the Road!\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << Road[i][j] << " ";
            }
            cout << endl;
        }

        printf("the Passenger!\n");
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cout << Passenger[i][j] << " "; // x_s, y_s, x_e, y_e를 각각 입력
            }
            cout << endl;
        }
    }


    

    while(!End()){
        simulate();
    }

    cout << c;

    return 0;
}