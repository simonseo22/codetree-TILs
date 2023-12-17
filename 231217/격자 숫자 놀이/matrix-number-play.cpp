#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#define MAN_N 100
#define MAX_NUM 100

using namespace std;

int n =3, m = 3;
int r, c, k;

int grid[MAN_N+1][MAN_N+1];

int RowPlay(int row){
    vector<pair<int,int>> pairs; // 빈도, 숫자 형태로 정렬
    // 값과 빈도수 체크
    for(int num = 1; num <= MAX_NUM; num++){
        int frequency = 0;
        for(int col = 1; col<= m; col++){
            if (grid[row][col] == num)
            {
                frequency++;
            }
            if (frequency)
            {
                pairs.push_back(make_pair(frequency,num));
            }
        }
    }

    // 해당 row의 값을 새롭게 할당
    for(int col = 1; col <=m; col++){
        grid[row][col] = 0;
    }
    sort(pairs.begin(), pairs.end()); // 오름차순으로 빈도수 우선 그 다음 값

    for (int i = 0; i < (int)pairs.size(); i++)
    {
        int frequency, num;
        tie(frequency, num) = pairs[i];
        grid[row][i*2+1] = num; // 새로운 grid생성
        grid[row][i*2+2] = frequency;
    }
    return (int)pairs.size() * 2;    
}

int Colplay(int col){
    vector<pair<int,int>> pairs; // 빈도, 숫자 형태로 정렬
    // 값과 빈도수 체크
    for(int num = 1; num <= MAX_NUM; num++){
        int frequency = 0;
        for(int row = 1; row<= n; row++){
            if (grid[row][col] == num)
            {
                frequency++;
            }
            if (frequency)
            {
                pairs.push_back(make_pair(frequency,num));
            }
        }
    }

    // 해당 row의 값을 새롭게 할당
    for(int row = 1; row <=n; row++){
        grid[row][col] = 0;
    }
    sort(pairs.begin(), pairs.end()); // 오름차순으로 

    for (int i = 0; i < (int)pairs.size(); i++)
    {
        int frequency, num;
        tie(frequency, num) = pairs[i];
        grid[i*2+1][col] = num;
        grid[i*2+2][col] = frequency;
    }
    return (int)pairs.size() * 2;    
}

void Simulate(){
    if (n>=m)
    {
        int max_col = 0;
        for (int row = 1; row <= n; row++) {
            max_col = max(max_col, RowPlay(row));            
        }
        m= max_col;        
    }else{
        int max_row = 0;
        for (int col =1; col <=m; col++){
            max_row = max(max_row, Colplay(col));
        }
        n = max_row;
    }
}

int main(){
    cin >> r >> c >> k;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> grid[i][j];
        }        
    }
    int ans = -1;

    for (int t = 0; t <= 100; t++)
    {
        if (grid[r][c] == k)
        {
            ans = t; // 0초만에 찾을수 있으니까
            break;
        }
        Simulate();
    }
    cout << ans;   // 찾지 못했을때 기본값 -1 출력 
}