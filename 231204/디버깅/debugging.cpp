// 최소한의 유실선으로 버그를 없애는 프로그램

// *입력
// 1)고객의수 n(2~10, 가로), 유실선 m(0~(n-1)*h, 이으는방법),
// 취약지점 h(1~30, 세로)  공백을 사이에 두고
// 고객번호는 1부터 시작, 취약지점도 1부터 시작
// 2~m+1) 유실선의 정보, 취약지점과 메모리 유실이 일어난 지점이
// 정수로 공백을 사이에 두고 주어짐
// a(1~h),b(1~n-1) -> a번째 취약지점(세로)에서 b~b+1고객으로 유실선
// 유실선이 이어지면 안됨 a,b와 a,b+1은 불가능
// *출력
// 메모리 유실선의 개수 최솟값
// 3보다 크거나 버그를 고치는 것이 불가능하면 -1

// 모든 경로를 해보고 시뮬레이션
// ( 300 + 300C2 + 300C3 ) * 300 < 1억

// 4 3 5
// 1 1
// 3 2
// 5 1

#include <iostream>
#include <vector>
#define N_MAX 10
#define H_MAX 30 // 0~30 31개 만들어지며 이중 1~30 개만 사용
#define DEBUG 0
using namespace std;

int n;
int m;
int h;
int arr[H_MAX + 1][N_MAX + 1];
int MinSol = 0;

vector<pair<int, int>> Lines;

bool Go(int n_i)
{
    int temp = n_i;
    for (int i = 1; i < h + 1; i++)
    {
        if (arr[i][temp] == 1)
        {
            temp++;
        }
        else if (arr[i][temp - 1] == 1)
        {
            temp--;
        }
    }
    if (DEBUG)
    {
        printf("start : %d -> end : %d \n", n_i, temp);
    }
    return temp == n_i ? true : false;
}

void simulate(int num, int sol)
{
    if (MinSol != 0 || sol > 3)
    {
        if (DEBUG)
        {
            printf("Minsol : %d, sol : %d\n",MinSol, sol); 
        }
        return;
    }

    if (num == sol && MinSol == 0)
    {
        if (DEBUG)
        {
            cout << "canGo?!" << endl;
            for (int i = 1; i < h + 1; i++)
            {
                for (int j = 1; j < n + 1; j++)
                {
                    cout << arr[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        
        for (int n_i = 1; n_i < n + 1; n_i++)
        {
            if (!Go(n_i))
            {
                if (DEBUG)
                {
                    cout << "false !" << endl;
                }
                if (sol != 0)
                {
                    return;
                }
                else
                {
                    simulate(0, sol + 1);
                }
            }
        }
        if (MinSol == 0)
        {
            MinSol = sol;
        }
        
         // 모두 go인경우
        if (DEBUG)
        {
            cout << "MinSol : " << MinSol << endl;
        }
        return;
    }

    for (int i = 1; i < h + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            if (arr[i][j] != 1 && arr[i][j - 1] == 0)
            {
                arr[i][j] = 1;
                simulate(num + 1, sol);
                arr[i][j] = 0;
            }
        }
    }

    if (sol <= 3)
    {
        simulate(0, sol + 1);
    }
}

int main()
{
    cin >> n >> m >> h; // arr[h][n]
    while (m--)
    {
        int i, j; // 위치를 기록할 필요는 없는 그 위치에 있냐만이 중요 W
        cin >> i >> j;
        arr[i][j] = 1;
    }

    if (DEBUG)
    {
        cout << "start! " << endl;
        for (int i = 1; i < h + 1; i++)
        {
            for (int j = 1; j < n + 1; j++)
            {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    simulate(0, 0);

    cout << MinSol << endl;
    return 0;
}