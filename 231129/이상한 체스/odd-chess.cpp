// *문제
// 5종류의 체스말 존재 
// *1 : 한방향, *2 : 좌우, *3 : 90도 차이가 나는 2방향, *4 : 위, 양옆, *5 : 4방향 전부
// 1은 바라보는 방향에 따라 이동할수 있는 격자가 달라짐
// 나머지 말들은 독립적으로 바라보는 방향을 지정할수있음
// *말이동규칙
// *1)본인의 말은 뛰어넘어 지나갈수 있음
// *2)상대편 말은 뛰어넘어 지나갈수 없음
// *3)갈수없는 격자 크기 계산시 상대편 말 위치 계산 X

// *입력
// 1)체크판의 크기 n,m (1~8)
// 2~n+1) 체스판에 있는 자신의 말(1~5)과 상대의 말(6)
// *자신의 말의 개수는 최대 8개
// *출력
// 비어있음에도 자신의 말을 이용해 갈수없는 체스판의 영역 넓이의 총합의 최솟값

//*유의사항
// 1번말의 방향은 내가 정하는것이며 그 방향으로 계속 이동
// 8개마다 방향을 돌리며 진행
#include <iostream>
#include <vector>

#define DEBUG 1
#define NUM_MAX 8
using namespace std;
int n,m;
int arr[NUM_MAX][NUM_MAX];

// dir 0 1 2 3 상 하 좌 우

class Chess{
public:
    int type;
    int x;
    int y;
    Chess(int type, int x, int y):type(type), x(x), y(y){}
};

vector<Chess> My;

void Calculate(){

}

void move(Chess chess, int dir){
    switch (chess.type)
    {
    case 1:      
        switch (dir)
        {
        case 0:   
            for (int i = chess.x; i > -1 ; i--)
            {
                if (arr[i][chess.y] == 6)
                {
                    break;
                }else{
                    arr[i][chess.y] = -1;
                }                
            }                    
            break;
        case 1:   

            break;
        case 2:           
            break;
        case 3:           
            break;            
        default:
            break;
        }  
        break;
    case 2:
        /* code */
        break;
    case 3:
        /* code */
        break;
    case 4:
        /* code */
        break;
    case 5:
        /* code */
        break;

    default:
        break;
    }
}

void simulate(int index, int dir){
    if (DEBUG)
    {
        printf("index : %d, dir : %d",index, dir);
    }
    
    if (index == My.size())
    {
        Calculate();
        return;
    }
    int temp[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            temp[i][j] = arr[i][j];
        }        
    }

    for (int i = 0; i < 4; i++)
    {
        move(My[index], i);
        simulate(index, i);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                arr[i][j] = temp[i][j];
            }
        }

        if (My[index].type == 5)
        {
            break;
        }        
    }  
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> arr[i][j];
            if (arr[i][j] != 0 && arr[i][j] != 6)
            {
                My.push_back(Chess(arr[i][j],i,j));
            }       
        }        
    }
    
    if (0)
    {
        for (int i = 0; i < My.size(); i++)
        {
            printf("tyep : %d, x : %d, y: %d\n",My[i].type, My[i].x, My[i].y);
        }       
    }
    
    for (int i = 0; i < 4; i++)
    {
        simulate(0,i);
    }  
    return 0;
}