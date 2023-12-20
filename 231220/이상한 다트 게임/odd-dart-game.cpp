#include <iostream>
#define DEBUG 0
#define NUM_MAX 50

using namespace std;
int n, m, q;
int Dart[NUM_MAX][NUM_MAX];
int Next_Dart[NUM_MAX][NUM_MAX];
int temp[NUM_MAX];
int dx[] = {1,0};
int dy[] = {0,1};
int x,d,k;

void normalize(){

    int leftNum = 0;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (Dart[i][j] > 0) // 원판에 수는 1~1,000
            {
                sum += Dart[i][j];
                leftNum++;
            }            
        }        
    }  

    int avg = sum / leftNum;

    if (DEBUG)
    {
        printf("sum %d, leftNum : %d, avg : %d\n", sum, leftNum, avg);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (Dart[i][j] > avg)
            {
                Dart[i][j] -= 1;
            } else if (Dart[i][j] < avg && Dart[i][j] != 0) 
            {
                 Dart[i][j] += 1;
            }// 같은수는 변형 X                    
        }
        
    }

    if (DEBUG)
    {
        printf("after normalize\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                printf("%d ",Dart[i][j]);
            }
            printf("\n");            
        }        
    }       

}

bool erase(){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            Next_Dart[i][j] = -1; // 지점마다 주변 2개를 비교하므로 비교를 해서 변화가 있음을 알리기 위해
        }        
    }

    bool isErase = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            bool isThisErase = false;
            for (int dir = 0; dir < 2; dir++)
            {
                int nx = i + dx[dir];
                int ny = (j + dy[dir]) % m;
                if (Dart[nx][ny] == Dart[i][j] && Dart[i][j] != 0)
                {
                    isThisErase = true;
                    Next_Dart[nx][ny] = 0;
                    Next_Dart[i][j] = 0;
                    if (!isErase)
                    {
                        if (DEBUG)
                        {
                            printf("isErase!! at (%d, %d)\n",i,j);
                        }
                        
                        isErase = true;
                    }
                }
            }
            if (!isThisErase && Next_Dart[i][j] == -1)
            {
                Next_Dart[i][j] = Dart[i][j];   
            }
        }
    }   

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            Dart[i][j] = Next_Dart[i][j];
        }
        
    }

    if (DEBUG)
    {
        printf("after erase\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                printf("%d ",Dart[i][j]);
            }
            printf("\n");            
        }        

        cout << "isErase : " << isErase << endl;
    }   

    return isErase;
}


void simulate(){
    
    // tmep 초기화
    for (int i = 0; i < m; i++)
    {
        temp[i] = 0; 
    }
  
    // 회전진행 
    int multiple_of_x = x-1; // 반지름이므로 n
    int dir;
    if (d ==  0)
    {
        dir = 1;
    }else{
        dir = -1;
    }

    if (DEBUG)
    {
        //printf("x : %d, d : %d-> dir : %d, k : %d\n",x,d,dir,k);
    }
    
    while (multiple_of_x < n)
    {
        for (int i = 0; i < m; i++)
        {
            int ny = i + dir*k; 
            if (ny < 0)
            {
                ny = m+ny;
            }if (ny >= m)
            {
                ny = ny%m; 
            }

            temp[ny] = Dart[multiple_of_x][i];
        }        
        for (int i = 0; i < m; i++)
        {
            Dart[multiple_of_x][i] = temp[i];
        }
        
        multiple_of_x += x;     
    }

    if (DEBUG)
    {
        printf("after Rotate\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                printf("%d ",Dart[i][j]);
            }
            printf("\n");            
        }        
    }   

    if (!erase())
    {
        normalize();
    } 


       
}
int main() {
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> Dart[i][j];
        }        
    }

    while (q--) // 중간에 숫자가 모두 없어지면 0
    {
        cin >> x >> d >> k;
        
        // 문제는 순서로 주어지므로 배열의 인자로 사용하기 위해 보정 -> 배수를 사용하기에 이러면 안돼 
        // d : 0(시계), 1(반시계)
        simulate();        
    }    

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            sum +=Dart[i][j];
        }        
    }

    cout << sum;
    
    
    return 0;
}