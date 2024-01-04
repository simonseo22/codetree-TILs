// *문제
// n*n격자판, m개의 원자
// m개의 원자는 각각 질량, 방향, 속력, 초기위치
// 방향은 상하좌우, 대각선,
// 초기위치는 몇번째 행렬 -> 1~n자연수
// 격자의 끝과 끝은 연결 n번열에서 오른쪽 이동하면 1번열
// 실험과정
// 1) 모든 원자는 1초가 지날때 마다 자신의 방향으로 자신의 속력만큼 이동
// 2) 이동이 끝난후 하나의 칸에 2개의 이상 원자가 있는 경우 다음의 합성 진행
// a.칸은 칸에 있는 원자들은 각각의 질향과 속력을 모두 합한 하나의 원자로
// b. 이후 합쳐진 원자는 4개의 원자로 나눠짐
// c. 나누어진 원자들은 모두 해당 칸에 위치하고 질량, 속력, 방향은 다음 기준을 따라 결정
// - 질량은 합쳐진 원자의 질량에 5를 나눔
// - 속력은 합쳐진 원자의 속력에 합쳐진 원자의 개수
// - 합쳐진 원자의 방향이 모두 상하좌우중 1개, 모두 대각선중 1개  : 상하좌우
// - 그렇지 않으면 (상하좌우랑 대각선이 섞여 있으면) : 대각선
// - 질량이 0인 원자는 소멸
// 3) 이동과정중 만나는 경우는 합성으로 고려X
// k초가 될때 남아있는 원자의 질량 합

// *입력
// 1) n(4~50), m(0~n^2) ,k(1~1000)
// 2~m+1) 원자의 정보 x,y(1~n) 질량 m(1~1,000) 속력 s(1~1,000) 방향 d(0~7)
// 방향은 0~7 0이 위이고 시계방향
// 초기에 주어지는 원자의 위치는 겹치지 않는다고 가정

//*출력
// k초이후 남아있는 원자들의 질량합

#include <iostream>
#include <vector>
#include <tuple>

#define N_MAX 50
#define M_MAX 2500
#define DEBUG 0

using namespace std;
int n, m, k;


vector<tuple<int,int,int>> Atoms[N_MAX][N_MAX];
vector<tuple<int,int,int>> NextAtoms[N_MAX][N_MAX]; // 벡터는 값이 무한정으로 늘어날수있다. 그러므로 배열이 좋아보인다.
// 입력이 m개가 되더라도 증식 가능성이 있으므로 벡터를 사용


int dx[] = {-1,-1, 0, 1, 1, 1, 0,-1}; 
int dy[] = { 0, 1, 1, 1, 0,-1,-1,-1};

void FusionAtoms(){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Atoms[i][j].clear();
        }        
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (NextAtoms[i][j].size() > 1)
            {                
                // 상하좌우 0,2,4,6
                // 대각산 1,3,5,7
                int newM = 0;
                int newS = 0;
                bool isDiagonal = false;
                int initDir;
                for (int k = 0; k < NextAtoms[i][j].size(); k++)
                {
                    int m,s,d;
                    tie(m,s,d) = NextAtoms[i][j][k];
                    newM += m;
                    newS += s;
                    if (k == 0)
                    {
                        initDir = d%2;
                    }else{ 
                        if (!isDiagonal) // 아직 변하지 않음
                        {
                            if (initDir != (d%2)) 
                            {
                                isDiagonal = true; // 섞여있으므로 대각선
                            }
                            
                        }                        
                    }    
                }

                // a.칸은 칸에 있는 원자들은 각각의 질향과 속력을 모두 합한 하나의 원자로
                // b. 이후 합쳐진 원자는 4개의 원자로 나눠짐
                // c. 나누어진 원자들은 모두 해당 칸에 위치하고 질량, 속력, 방향은 다음 기준을 따라 결정
                // - 질량은 합쳐진 원자의 질량에 5를 나눔
                // - 속력은 합쳐진 원자의 속력에 합쳐진 원자의 개수 (평균)
                // - 합쳐진 원자의 방향이 모두 상하좌우중 1개, 모두 대각선중 1개  : 상하좌우
                // - 그렇지 않으면 (상하좌우랑 대각선이 섞여 있으면) : 대각선
                // - 질량이 0인 원자는 소멸
                newM = newM/5;
                if(newM != 0){
                    newS = newS / NextAtoms[i][j].size();
                    for (int k = 0; k < 4; k++)
                    {
                        int newDir; 
                        if (isDiagonal)
                        {
                            newDir = k*2 + 1;
                        }else{
                            newDir = k*2;
                        }
                        Atoms[i][j].push_back(make_tuple(newM,newS,newDir));                        
                    }                                            
                }  
            }
            if (NextAtoms[i][j].size() == 1)
            {
                int newM,newS,newDir;
                tie(newM,newS,newDir) = NextAtoms[i][j][0];
                Atoms[i][j].push_back(make_tuple(newM,newS,newDir));
            }
                   
        }        
    }
    
    if (DEBUG)
    {
        printf("after Fusion\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < Atoms[i][j].size(); k++)
                {
                    int m,s,d;
                    tie(m,s,d) = Atoms[i][j][k];
                    printf("(%d,%d) : (%d,%d,%d)\n",i,j,m,s,d);
                }        
            }
        }
    }    
}


void MoveAtoms(){

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            NextAtoms[i][j].clear();
        }
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < Atoms[i][j].size(); k++)
            {
                int m, s, d;
                tie(m, s, d) = Atoms[i][j][k];
                // 새로운 방향 계산
                int nx = (i + s*dx[d]);
                if (nx >= 0)
                {
                    nx = nx%n;
                }else{
                    nx = nx + n;
                }

                int ny = (j + s*dy[d])%n;
                if (ny >= 0)
                {
                    ny = ny%n;
                }else{
                    ny = ny + n;
                }


                NextAtoms[nx][ny].push_back(make_tuple(m,s,d));
            }
        }
    }

    if (DEBUG)
    {
        printf("after Move\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < NextAtoms[i][j].size(); k++)
                {
                    int m,s,d;
                    tie(m,s,d) = NextAtoms[i][j][k];
                    printf("(%d,%d) : (%d,%d,%d)\n",i,j,m,s,d);
                }        
            }
        }
    }    
}

void simulate(){
    // 1) 모든 원자는 1초가 지날때 마다 자신의 방향으로 자신의 속력만큼 이동
    MoveAtoms();
// 2) 이동이 끝난후 하나의 칸에 2개의 이상 원자가 있는 경우 다음의 합성 진행
    FusionAtoms();

}

int main(){
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++)
    {        
        int x,y,m,s,d;
        cin >> x >> y >> m >> s >>d;
        s = s % n; // 크기 0~n으로 보정
        Atoms[x-1][y-1].push_back(make_tuple(m,s,d));
    }

    if (DEBUG)
    {
        printf("initial!\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < Atoms[i][j].size(); k++)
                {
                    int m,s,d;
                    tie(m,s,d) = Atoms[i][j][k];
                    printf("(%d,%d) : (%d,%d,%d)\n",i,j,m,s,d);
                }        
            }
        }
    }
    
    while (k--)
    {
        simulate();
    }

    int leftAtoms = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < Atoms[i][j].size(); k++)
            {
                int m,s,d;
                tie(m,s,d) = Atoms[i][j][k];
                leftAtoms += m;
            }            
        }        
    }
    
    cout << leftAtoms;
}