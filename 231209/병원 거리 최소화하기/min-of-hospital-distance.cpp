// *문제
// n*n크기의 사람과 병원의 위치가 주어짐 병원거리는 가장 가까운 거리
// 거리는 |x2-x1| + |y2-y1|로 각 좌표의 차이의 절대값
// m개의 병원만 남겨둘때 병원거리의 총합이 최소

// *입력
// 1) n과 m이 공백을 사이에 두고 입력 
// 2~n~50, 1~m~13, m~병원의수~13, 사람의수~2*n 
// 2~n+1) 빈칸인 경우 0, 사람인경우 1, 병원인 경우 2를 공백을 사이에 두고 입력
// m개의 병원을 고르는게 불가능한 입력은 주어지지 않음

//*출력
// m개를 남겼을때 각 사람들의 병원거리 총 합 중 최솟값 
// (사람은 제일 가까운 병원에 간다.)
//

// 알고리즘 ( 예제를 풀며 성립)
// 
// 
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#define NUM_MAX 50
#define DEBUG 1
using namespace std;

int n;
int m;
int NumHospitals;
int arr[NUM_MAX][NUM_MAX];
int MinDistance = numeric_limits<int>::max();
int dx[] = {-1,0,1,0};
int dy[] = {0,1,0,-1};

vector<pair<int,int>> Hospitals;
vector<pair<int,int>> UnChosenHospital;
vector<pair<int,int>> Patients;

// m개의 병원만 선택하여

void CalDistance(){
    //BFS를 이용해 제일 가까운 병원 탐색
    // 병원이 빠지는게 좋다 사람을 하나또 만들거야? 비효율적이야
    int DistanceSum = 0;
    for (const auto& Patient : Patients)
    {
        queue<pair<int,int>> q;
        q.push(make_pair(Patient.first,Patient.second));
        if(DEBUG){
            printf("patient(%d,%d) search!\n",Patient.first,Patient.second);
        }
        while (!q.empty())
        {
            const auto& Position = q.front();
            int i = Position.first;
            int j = Position.second;
            q.pop();
            // 4방향중 가능한 방향을 q에 push
            if (arr[i][j] == 2)
            {
                int temp = abs(Patient.first-i) + abs(Patient.second - j);
                if (DEBUG)
                {
                    printf("patient(%d,%d) go Hospital(%d,%d) dist %d\n",Patient.first,Patient.second,i,j,temp);                    
                }
                DistanceSum += temp;
                break;                
            }
            for (int d = 0; d < 4; d++)
            {
                int di = i + dx[d];
                int dj = j + dy[d];
                if (-1 < di && di < n && -1 < dj && dj < n)
                {
                    if (DEBUG)
                    {
                        printf("push (%d,%d)\n",di,dj);
                    }                    
                    q.push(make_pair(di,dj));
                }
                
            }
            

        }        
    }   

    if(DEBUG){
        printf("MinDistance : %d, DistanceSum : %d\n",MinDistance, DistanceSum);
        if (DistanceSum == 6)
        {
            printf("here~\n");
        }        
    }

    MinDistance = MinDistance > DistanceSum ? DistanceSum : MinDistance;
}

// 병원까지의 거리를 구하는 함수
void SelectHosipital(){
    if (UnChosenHospital.size() + m == NumHospitals)
    {
        if (DEBUG)
        {
            printf("UnChosenHospital : %d\n",UnChosenHospital.size());
            for (int i = 0; i < UnChosenHospital.size(); i++)
            {
                printf("%dst (%d, %d)\n", i,UnChosenHospital[i].first,UnChosenHospital[i].second);
            }

            printf("arr!!\n");
            for (int i = 0; i < n; i++)
            {
                cout << endl;
                for (int j = 0; j < n; j++)
                {
                    cout << arr[i][j] << " ";
                }
            }
            cout << endl;
        }
        CalDistance();     
        return; 
    } 


    for (const auto& hospital : Hospitals)
    {        
        UnChosenHospital.push_back(hospital);
        arr[hospital.first][hospital.second] = 0;

        SelectHosipital();

        arr[hospital.first][hospital.second] = 2;
        UnChosenHospital.pop_back();    
    }    
    return; 
}

int main(){

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {            
            cin >> arr[i][j];
            if (arr[i][j] == 2)
            {
                NumHospitals++;
                Hospitals.push_back(make_pair(i,j));
            } else if (arr[i][j] == 1)
            {
                Patients.push_back(make_pair(i,j));
            }
               
        }        
    }

    if (DEBUG)
    {
        printf("input arr\n");
        for (int i = 0; i < n; i++)
        {
            cout << endl;
            for (int j = 0; j < n; j++)
            {
                cout << arr[i][j] << " ";
            }
        }
        cout << endl;
    }

    SelectHosipital();
    cout << MinDistance;    

}