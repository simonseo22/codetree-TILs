#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#define NUM_MAX 50
#define DEBUG 0
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

// *따로따로 찾는것이 아니라 한번에 넣고 찾아야 한다.

void CalDistance(){
    //BFS를 이용해 제일 가까운 병원 탐색
    // 병원이 빠지는게 좋다 사람을 하나또 만들거야? 비효율적이야
    int DistanceSum = 0;
    queue<pair<int,int>> q;

    for (const auto& Patient : Patients)
    {        
        q.push(make_pair(Patient.first,Patient.second));
    }

    while (!q.empty())
    {
        const auto &Position = q.front();
        int i = Position.first;
        int j = Position.second;


        for (int d = 0; d < 4; d++)
        {
            int di = i + dx[d];
            int dj = j + dy[d];
            if (-1 < di && di < n && -1 < dj && dj < n)
            {
                if (DEBUG)
                {
                    printf("push (%d,%d)\n", di, dj);
                }
                q.push(make_pair(di, dj));
            }
        }
    }
       

    if(DEBUG){
        printf("MinDistance : %d, DistanceSum : %d\n",MinDistance, DistanceSum);
        if (MinDistance > DistanceSum)
        {
            printf("Change!!!!!\n");
        }
        
        if (DistanceSum == 6)
        {
            printf("here~\n");
        }        
    }

    MinDistance = MinDistance > DistanceSum ? DistanceSum : MinDistance;
}

// 병원까지의 거리를 구하는 함수
void SelectHosipital(int index){
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


    for (int i = index; i < Hospitals.size(); i++) // 똑같은 녀석이 들어간다. index로 구분필요
    {            

        UnChosenHospital.push_back(make_pair(Hospitals[i].first,Hospitals[i].second));
        arr[Hospitals[i].first][Hospitals[i].second] = 0;

        SelectHosipital(i + 1);

        arr[Hospitals[i].first][Hospitals[i].second] = 2;
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

    SelectHosipital(0);
    cout << MinDistance;    

}