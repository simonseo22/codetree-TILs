#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

#define DIR_NUM 4
#define MAX_N 50



vector<pair<int, int> > hospitals;
vector<pair<int, int> > selected_hos;
int n, m;
int a[MAX_N][MAX_N];

// bfs 필요 성분
queue<pair<int,int>> q;
bool visited[MAX_N][MAX_N];
int step[MAX_N][MAX_N];

int ans = INT_MAX;

void Initialize(){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = step[i][j] = 0;
        }        
    }    
}

void Push(int x, int y, int new_step){
    q.push(make_pair(x,y));
    visited[x][y] = true;
    step[x][y] = new_step;
}

bool InRange(int x, int y){
    return 0<= x && x < n && 0 <= y && y < n;
}

bool CanGo(int x, int y){
    return InRange(x,y) && a[x][y] != 1 && !visited[x][y]; 
}

int FindMaxDist(){
    while (!q.empty())  
    {
        pair<int, int> curr_pos = q.front();
        int x = curr_pos.first, y = curr_pos.second;
        q.pop();
        int dx[4] = {1,-1,0,0};
        int dy[4] = {0,0,1,-1};
        for (int dir = 0; dir < DIR_NUM; dir++)
        {
            int nx = x +dx[dir];
            int ny = y + dy[dir];

            if (CanGo(nx,ny))
            {
                Push(nx,ny,step[x][y]+1);
            }            
        }        
    }

    int max_dist = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] == 0) // 바이러스가 있는 지역의 dist만 확인
            {
                if (visited[i][j])
                {
                    max_dist = max(max_dist, step[i][j]);
                } else{
                    max_dist = INT_MAX;
                }                
            }            
        }        
    }
    
    return max_dist;
}

int ElaspedTimetoKillAllVirus(){
    Initialize();

    for (int i = 0; i < (int)selected_hos.size(); i++) // 각 병원에서 처음 BFS한 결과를 실행
    { // 각 병원에서 동시에 진행되어야함
        Push(selected_hos[i].first, selected_hos[i].second, 0);
    }

    int max_elesed_time = FindMaxDist();
    return max_elesed_time;
}

void FindTime(int curr_idx, int cnt){
    if (cnt == m)
    {
        ans = min(ans, ElaspedTimetoKillAllVirus());
        return;
    }

    if (curr_idx == (int)hospitals.size()) // 
    {
        return;
    }

    FindTime(curr_idx+1, cnt);

    selected_hos.push_back(hospitals[curr_idx]);    
    FindTime(curr_idx+1,cnt+1); // cnt에서 curridx가 선택된 모든경우를 수행
    selected_hos.pop_back();    
}

int main(){
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
            if (a[i][j] == 2)
            {
                hospitals.push_back(make_pair(i,j));
            }            
        }        
    }
    FindTime(0,0);
    
    if (ans == INT_MAX)
    {
        ans = -1;
    }

    cout << ans;
    return 0;
}