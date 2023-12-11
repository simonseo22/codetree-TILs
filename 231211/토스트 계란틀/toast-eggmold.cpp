#include <iostream>
#define NUM_MAX 50
#define DEBUG 1

using namespace std;

int arr[NUM_MAX][NUM_MAX];
int check[NUM_MAX][NUM_MAX][4];
int N;
int L;
int R;
int dx[] = {-1,0,1,0}; // 상 우 하 좌
int dy[] = {0,1,0,-1};


bool canFind(){
    bool isDistribute = false;
    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
        {
            for (int d = 0; d < 4; d++)
            {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (nx < 0 && nx > N-1
                && ny <0 && ny > N-1)
                {
                    continue;
                }
                
                if (L <= abs(arr[x][y] - arr[nx][ny])
                && abs(arr[x][y] - arr[nx][ny]) <= R)
                {                    
                    check[x][y][d] = 1; 
                    if (!isDistribute)
                    {
                        isDistribute = true;
                    }
                }
            }
        }
    }
    return isDistribute;
}

void distributeEggs(){
    if (DEBUG)
    {
        printf("Distribute EGG!\n");
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cout << arr[i][j] << " ";
            }   
            cout << endl;           
        }
        cout << endl;        

        printf("Check EGG!\n");
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    cout << check[i][j][k] << ",";
                }
                cout << " ";                
            }            
            cout << endl;  
        }
        cout << endl;        
    } 

    return;
}

void initCheck(){
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                check[i][j][k] = -1;
            }
        }        
    }    
}

int simulate(int cnt){
    if (DEBUG)
    {
        printf("cnt : %d\n",cnt);
    }
    
    if (DEBUG)
    {
        if (cnt > 1)
        {
            return cnt;
        }
    }
    
    if (cnt > 2000)
    {        
        return cnt;
    }
    
    initCheck();
    if(canFind()){
        distributeEggs();
        simulate(cnt+1);
    } else{
        return cnt;
    }    
}

int main(){
    cin >> N >> L >> R;
#if DEBUG
    printf("N : %d, L : %d, R : %d\n",N,L,R);
#endif
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> arr[i][j];
        }        
    }
    
    cout <<  simulate(0);
}