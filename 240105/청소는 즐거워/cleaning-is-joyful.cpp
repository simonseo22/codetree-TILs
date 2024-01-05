// *문제
// n*n행렬 n은 항상 홀수 
// 정가운데 부터 시작하여 나선형으로 바닥청소 시작(정가운데는 먼지 없음)
// 왼 -> 아래 -> 오른쪽 -> 위 순서로 청소 시작
// n이 홀수이기때문에 항상 왼쪽 위에서 끝
//빗자루 이동할 때마다 이동한 위치의 격자(curr)에 있는 먼지가 함께이동
// 아래 비율에 따라 이동, 이동한 먼지는 기존 먼지의 양에 더해짐
// 이동한 위치(curr)에 있는 먼지는 모두 없어짐
// a%에 해당하는 먼지의 양은 (curr에 원래 있던 먼지 - sum*(다른 격자로 이동한 먼지의 양) )
// 비율곱시 소숫점 아래는 버림

// *입력
// 1) n (3~499)
// 2~n+1) 먼지의 양 (1~1,000)
// 정가운데는 항상 0으로 가정

// *출력
// 바깥으로 나간 먼지의 양

#include <iostream>
#include <tuple>

#define N_MAX 499
#define DIR_NUM 4
#define DEBUG 1

using namespace std;

int n;
int dusts[N_MAX][N_MAX];
int dx[] = { 0, 1, 0, -1};
int dy[] = {-1, 0, 1,  0};

int sumOfOutDust = 0;

bool inRange(int x, int y){
    return 0<= x && x < n && 0<= y && y <n;
}

void cleaning(int x, int y, int dir){

    if(DEBUG){
        printf("cleaning! (%d, %d) : dir : %d\n",x,y,dir);
    }
    int currDust = dusts[x][y];
    int SumofMovedDust = 0;

    // 대각선 4방향
    int CleaningDx[] = {1, -1, 1, -1};
    int CleaningDy[] = {1, 1, -1, -1};
    float CleaningVDiagonal[] = {0.01, 0.01, 0.1, 0.1};
    for (int i = 0; i < 4; i++)
    {
        int nx = x + CleaningDx[i];
        int ny = y + CleaningDy[i];
        float movingDust = currDust * CleaningVDiagonal[i];
        if (inRange(nx,ny))
        {
            dusts[nx][ny] += movingDust;            
        }else{
            sumOfOutDust += movingDust;
        }        
        SumofMovedDust += movingDust;
    }
    
    // dir + 1
    float CleaningV[] = {0.07, 0.02};
    for (int i = 0; i < 2; i++)
    {
        int nx = x + dx[(dir+1)%4] + i;
        int ny = y + dy[(dir+1)%4] + i;
        float movingDust = currDust * CleaningV[i];
        if (inRange(nx,ny))
        {
            dusts[nx][ny] += movingDust;
            
        }else{
            sumOfOutDust += movingDust;
        }     
        SumofMovedDust += movingDust;  
    }    

    // dir + 3 
    for (int i = 0; i < 2; i++)
    {
        int nx = x + dx[(dir+3)%4] + i;
        int ny = y + dy[(dir+3)%4] + i;
        float movingDust = currDust * CleaningV[i];
        if (inRange(nx,ny))
        {
            dusts[nx][ny] += movingDust;
            
        }else{
            sumOfOutDust += movingDust;
        }     
        SumofMovedDust += movingDust;  
    }

    // dir방향으로 2번
    int nx = x + dx[dir] + 1;
    int ny = y + dy[dir] + 1;
    float movingDust = currDust * 0.05;
    if (inRange(nx, ny))
    {
        dusts[nx][ny] += movingDust;
    }
    else
    {
        sumOfOutDust += movingDust;
    }
    SumofMovedDust += movingDust;

    nx = x + dx[dir];
    ny = y + dy[dir];
    movingDust = currDust - SumofMovedDust;
    if (inRange(nx, ny))
    {
        dusts[nx][ny] += movingDust;
    }
    else
    {
        sumOfOutDust += movingDust;
    }
}

void simulate(int x, int y, int dir, int count){

    if(DEBUG){
        printf("simulate! (%d, %d) : dir : %d, count : %d\n",x,y,dir,count);
    }

    int nx, ny; 
    
    for (int i = 0; i < count; i++)
    {
        nx = x + dx[dir]; 
        ny = y + dy[dir];
        cleaning(nx,ny,dir);
        x = nx;
        y = ny;
        if (x == 0 && y == 0)
        {
            return;
        }
    }
       

    int new_dir = (dir+1)%DIR_NUM;
    if (new_dir % 2 == 0)
    {
        count++;
    }      
    simulate(nx,ny,new_dir, count);
}


int main(){
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> dusts[i][j];
        }        
    }    

    // 정가운데 부터 시작하여 나선형으로 바닥청소 시작(정가운데는 먼지 없음)
    simulate(n/2, n/2,0, 1);    

    cout << sumOfOutDust;
}