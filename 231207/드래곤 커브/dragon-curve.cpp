#include <iostream>
#define NUM_MAX 100
#define DEBUG 1
using namespace std;
int arr[NUM_MAX][NUM_MAX];
int dx[] = {0,-1,0,1};
int dy[] = {1,0,-1,0};
bool CanRectangle(int i, int j){
    // 입력된 좌표가 정사각혀의 
    if (i == 0 || i == NUM_MAX-1 || j == 0 || j == NUM_MAX)
    {
        return false;
    } else{ // 4점이 모든 드래곤 커브인경우 
        if (arr[i+1][j] == 1 && arr[i][j+1] && arr[i+1][j+1])
        {
            return true;
        }        
    }    
}

int CalRectangle(){
    int sum = 0;
    for (int i = 0; i < NUM_MAX; i++)
    {
        for (int i = 0; i < NUM_MAX; i++)
        {     
            if (CanRectangle)
            {
                sum++
            }                   
        }        
    }    
    return sum;
}
void MakeDragonLine(int x, int y, int d, int g){
    if (DEBUG)
    {
        printf("MAKE LINE!! x : %d, y : %d, d : %d, g: %d\n",x,y,d,g);
    }
    
}

int main(){
    int n;
    cin >> n;
    while (n--)
    {
        int x, y, d, g;
        cin >> x >> y >> d >> g;
        MakeDragonLine(x,y,d,g);
    }

    cout << CalRectangle();
    return 0;
}#include <iostream>
#define NUM_MAX 100
#define DEBUG 1
using namespace std;
int arr[NUM_MAX][NUM_MAX];
int dx[] = {0,-1,0,1};
int dy[] = {1,0,-1,0};
bool CanRectangle(int i, int j){
    // 입력된 좌표가 정사각혀의 
    if (i == 0 || i == NUM_MAX-1 || j == 0 || j == NUM_MAX)
    {
        return false;
    } else{ // 4점이 모든 드래곤 커브인경우 
        if (arr[i+1][j] == 1 && arr[i][j+1] && arr[i+1][j+1])
        {
            return true;
        }        
    }    
}

int CalRectangle(){
    int sum = 0;
    for (int i = 0; i < NUM_MAX; i++)
    {
        for (int i = 0; i < NUM_MAX; i++)
        {     
            if (CanRectangle)
            {
                sum++
            }                   
        }        
    }    
    return sum;
}
void MakeDragonLine(int x, int y, int d, int g){
    if (DEBUG)
    {
        printf("MAKE LINE!! x : %d, y : %d, d : %d, g: %d\n",x,y,d,g);
    }
    
}

int main(){
    int n;
    cin >> n;
    while (n--)
    {
        int x, y, d, g;
        cin >> x >> y >> d >> g;
        MakeDragonLine(x,y,d,g);
    }

    cout << CalRectangle();
    return 0;
}