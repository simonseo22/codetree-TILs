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
int leftPassenger;
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
    int passengerCount = 0;
    // BST진행 -> m개만 하면 되는거네?
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

        if (Dist[x_s][y_s] == -1)
        {
            continue;
        }
        
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
            if (CanGo(nx,ny)) // 애초에 갈수가 없다면?
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
                        printf("car move to Destination(%d,%d) left battery : %d\n", x_c, y_c, c);

                        printf("the left Passenger!\n");
                        for (int i = 0; i < m; i++)
                        {
                            for (int j = 0; j < 4; j++)
                            {
                                cout << Passenger[i][j] << " "; // x_s, y_s, x_e, y_e를 각각 입력
                            }
                            cout << endl;
                        }
                    }

                    return;
                }
                q.push(make_pair(nx,ny));
            }            
        }        
    }   
    // 도달할수있는 길이 없는 경우 
    if (Dist[x_e][y_e] == -1)
    {
        c = -1;
        return;
    }    
}

void simulate(){
    // 거리 계산
    calDist();
    // 이동 지점 선택
    int ChosenPassengerIndex;
    ChosenPassengerIndex = ChoseMinDistPassenger();
    if (ChosenPassengerIndex == -1)
    {
        c = -1;
        return;
    }
    
    // 이동 (벽을 피하기 위해  BFS진행 ? 목적지 도착지는 이동해도 괜찮은가?)
    moveToPassenger(ChosenPassengerIndex); // 자동차 -> 승객이동, 배터리 소모
    if (c <=0) // 출발해야 하는데 배터리가 0인 경우
    {
        return;
    }    
    moveToDestination(ChosenPassengerIndex); // 승객 -> 목적지 이동, 배터리 소모, 충전, 승객 제거

    if (DEBUG)
    {
        printf("the left Passenger!\n");
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cout << Passenger[i][j] << " "; // x_s, y_s, x_e, y_e를 각각 입력
            }
            cout << endl;
        }
    }
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
    leftPassenger = m;

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