// n*n 격자 무늬의 배지에 바이러스를 배양하는 실험 진행
// 초기 각 칸마다 5만큼의 양분 존재, m개의 바이러스로 실행
// 1 사이클 마다 다음의 규칙 존재
// 1) 각각의 바이러스는 속한 1*1 크기의 칸에서 양분 섭취(나이만큼! 섭취)
// 여러개 바이러스 있으면 어린것부터 섭취, 섭취한 바이러스 나이 1! 증가
// 양분이 부족해 나이만큼 섭취 불가시 죽음
// 2) 섭취 끝낸 후(1과정후) 바이러스가 죽은 양분으로 변화 ,
//  죽은 바이러스 나이/2(버림) 가 양분
// 3) 번식 진행, 5의 배수 나이를 가진 바이러스만
// 인접 8개 칸에 나이 1인 바이러스 생성(배지 밖에는 생성 X)
// 4) 1,2,3 과정이 끝난뒤 주어진 양분의 양에 따라 칸에 양분 추가(칸마다 주어짐)

// k 사이클 후 살아남은 바이러스의 수

// 입력*
// 1) 배지 크기 n(1~10), 바이러스 개수 m(1~n^2), 총 사이클의수 k(1~1,000)
// 2~n+1) 마지막에 추가되는 양분의 양 ( 1~100)
// n+2~ n+2 + m-1 ) 바이러스 정보 r ,c (1~n) (바이러스 위치) , 정수(나이 1~10)
// * 입력으로 주어지는 바이러스의 위치는 모두 다름


// *출력
// 총 사이클 후에 남아있는 바이러스

// *알고리즘
// 바이러스가 여러개 있는 경우 선택하는 법

#include <iostream>
#include <vector>
#define DEBUG
#define NUM_MAX 10

using namespace std;

int n, m, k;
int Arr[NUM_MAX][NUM_MAX];
int Food[NUM_MAX][NUM_MAX];


class Virus{
    public:
    int x;
    int y;
    int age;
    Virus(int x, int y, int age) : x(x), y(y), age(age){
    }
};

vector<Virus> virusVector;
int main(){
    cin >> n >> m >> k;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> Food[i][j];
        }        
    }

    for (int i = 0; i < m; i++)
    {
        int r, c, age;
        cin >> r >> c >> age;
        Virus virus(r,c,age);
        virusVector.push_back(virus);
    }
        
    while (k--)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                
            }
            
        }
        
    }
    
}