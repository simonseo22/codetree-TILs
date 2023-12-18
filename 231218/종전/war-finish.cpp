#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#define NUM_MAX 20
#define DEBUG 0

using namespace std;
int n;
int land[NUM_MAX][NUM_MAX];
int Tribe[NUM_MAX][NUM_MAX];
int dx[] = {-1,-1,1,1};
int dy[] = {1,-1,-1,1};

vector<pair<int,int>> ChosenPoint;
vector<int> TribeLand;
int minDiff = INT_MAX;

// 
queue<pair<int,int>> q;

bool inRange(int x, int y){
    return 0<=x && x <n && 0<=y && y<n;
}

bool isRectangle(int nx, int ny){
    int x_0 = ChosenPoint[0].first;
    int y_0 = ChosenPoint[0].second;
    int x_2 = ChosenPoint[2].first;
    int y_2 = ChosenPoint[2].second;
    return (abs(x_0 - nx) == abs(y_0 - ny)) && (abs(x_2 - nx) == abs(y_2 - ny));
}

void initializeLand(){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Tribe[i][j] =0;
        }        
    }    
}

void makeLandLine(){
    int x[4];
    int y[4];
    for (int i = 0; i < ChosenPoint.size(); i++)
    {
        x[i] = ChosenPoint[i].first;
        y[i] = ChosenPoint[i].second;
        Tribe[x[i]][y[i]] = 1;
    }

    // 경계 1
    for (int i = 0; i < 4; i++)
    {
        int nx = x[i];
        int ny = y[i];
        while (1)
        {
            nx += dx[i];
            ny += dy[i];
            Tribe[nx][ny] = 1;
            if (nx == x[(i+1)%4] && ny == y[(i+1)%4])
            {
                break;;
            }                
        }        
    }

    // 경계2
    for (int i = 0; i < x[2]; i++)
    {
        Tribe[i][y[2]] = 2;
    }

    // 경계3
    for (int i = y[1]+1; i < n; i++)
    {
        Tribe[x[1]][i] =3;
    }
    
    // 경계4
    for (int i =0; i<y[3]; i++){
        Tribe[x[3]][i] = 4;
    }

    // 경계 5
    for (int i = x[0]+1; i < n; i++)
    {
        Tribe[i][y[0]] = 5;
    }

    if (DEBUG)
    {
        printf("TrieLine!\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%d ",Tribe[i][j]);
            }
            printf("\n");            
        }        
    }    
}

bool CanGo(int x, int y){
    return inRange(x,y) && Tribe[x][y] == 0; 
}

void BFS(){
    // 처음값 
    int x[4];
    int y[4];
    for (int i = 0; i < ChosenPoint.size(); i++)
    {
        x[i] = ChosenPoint[i].first;
        y[i] = ChosenPoint[i].second;
        Tribe[x[i]][y[i]] = 1;
    }
    Tribe[x[0]][y[0]+1];
    q.push(make_pair(x[0],y[0]+1));



    Tribe[0][0] = 2;
    q.push(make_pair(0,0));

    Tribe[0][n-1] = 3;
    q.push(make_pair(0,n-1));

    Tribe[n-1][0] = 4;
    q.push(make_pair(n-1,0));    

    Tribe[n-1][n-1] = 5;
    q.push(make_pair(n-1,n-1));

    while (!q.empty())
    {
        pair<int, int> curr_pos = q.front();
        int x = curr_pos.first, y = curr_pos.second;
        int curr_tribe = Tribe[x][y];
        q.pop();
        int dx[4] = {1,-1,0,0};
        int dy[4] = {0,0,1,-1};
        for (int dir = 0; dir < 4; dir++)
        {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (CanGo(nx,ny))
            {
                Tribe[nx][ny] = curr_tribe;
                q.push(make_pair(nx,ny));
            }
            
        }        
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (Tribe[i][j] == 0)
            {
                Tribe[i][j] = 1;
            }            
        }        
    }
        

    if (DEBUG)
    {
        printf("AFTER BFS!\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%d ",Tribe[i][j]);
            }
            printf("\n");            
        }        
    }  
}
void calculate(){
    if (DEBUG)
    {
        printf("chose %d!\n",ChosenPoint.size());
        for (int i = 0; i < ChosenPoint.size(); i++)
        {
            printf("%dst! (%d, %d)\n",i,ChosenPoint[i].first, ChosenPoint[i].second);
        }        
    }    
    initializeLand();
    makeLandLine();
    BFS();    
    int TribeNum[5] = {0,0,0,0,0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int num = Tribe[i][j];
            switch (num)
            {
            case 1:
                TribeNum[0] += land[i][j];
                break;
            case 2:
                TribeNum[1] += land[i][j];
                break;
            case 3:
                TribeNum[2] += land[i][j];
                break;
            case 4:
                TribeNum[3] += land[i][j];
                break;
            case 5:
                TribeNum[4] += land[i][j];
                break;
            default:
                break;
            }
        }        
    }
    int Tribemax = INT_MIN;
    int Tribemin = INT_MAX;
    for (int i = 0; i < 5; i++)
    {
        if (DEBUG)
        {
            printf("tirbe %d sum : %d\n",i+1,TribeNum[i]);
        }
        
        Tribemax = max(Tribemax, TribeNum[i]);
        Tribemin = min(Tribemin, TribeNum[i]);
    }
    minDiff = min(minDiff, Tribemax-Tribemin);
}

void simulate(int cnt, int d){
    if (cnt == 2)
    {
        int x_0 = ChosenPoint[0].first;
        int y_0 = ChosenPoint[0].second;
        int x_2 = ChosenPoint[2].first;
        int y_2 = ChosenPoint[2].second;
        int nx = (x_0+x_2+y_2-y_0)/2;
        int ny = nx-x_0+y_0;
        if (inRange(nx,ny) && isRectangle(nx,ny))
        {   
            ChosenPoint.push_back(make_pair(nx,ny));
            calculate();
            ChosenPoint.pop_back();
        }      
        return;
    }
    
    int chosen_x = ChosenPoint[cnt].first;
    int chosen_y = ChosenPoint[cnt].second;
    while (1)
    {
        int nx = chosen_x + dx[d];
        int ny = chosen_y + dy[d];
        if (inRange(nx,ny))
        {
            ChosenPoint.push_back(make_pair(nx,ny));
            simulate(cnt+1,d+1); 
            ChosenPoint.pop_back();
        }else{
            break;
        }      
        chosen_x = nx;
        chosen_y = ny;
    }
    return;    
}

int main(){
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> land[i][j];
        }        
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ChosenPoint.push_back(make_pair(i,j));
            simulate(0,0);
            ChosenPoint.pop_back();
        }        
    }  
    cout << minDiff;
    return 0;
}