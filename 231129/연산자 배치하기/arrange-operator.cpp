#include <iostream>
#include <limits>

#define DEBUG 0
#define NUM_MAX 11
using namespace std;

int arr[NUM_MAX];
int op[NUM_MAX-1]; // 1 : 덧셈, 0 : 곱셈, -1 : 뺄셈
int n;
int add, sub, mul;
int MAX = numeric_limits<int>::min();
int MIN = numeric_limits<int>::max();


void caculate(){
    int temp = arr[0];
    if (DEBUG)
    {
        cout << arr[0] << " ";
    }
    
    for (int i = 0; i < n-1; i++)
    {
        switch (op[i])
        {
        case 1:
            temp += arr[i+1];
            if (DEBUG)
            {
                cout << "+" << " ";
            }
            
            break;
        case 0:
            temp *= arr[i+1];
            if (DEBUG)
            {
                cout << "*" << " ";
            }
            break;
        case -1:
            temp -= arr[i+1];
            if (DEBUG)
            {
                cout << "-" << " ";
            }
            break;

        default:
            if (DEBUG)
            {
                printf("default at op[%d] : %d\n",i,op[i]);
            }
            
            break;
        }
        if (DEBUG)
        {
            cout << arr[i+1] << " ";
        }
    }
    if (DEBUG)
    {
        cout << endl;
    }
    MAX = temp > MAX ? temp : MAX;
    MIN = temp < MIN ? temp : MIN;
    if (DEBUG)
    {
        printf("temp : %d, MAX : %d, MIN : %d\n", temp, MAX, MIN);
    }
}

void simulate(int index, int add_num, int sub_num, int mul_num){
    if (DEBUG)
    {
        printf("index : %d, add_num : %d, sub_num : %d, mul_num : %d\n",
        index, add_num,sub_num,mul_num);
    }
    
    if (add_num > add 
    || sub_num > sub
    || mul_num > mul
    || index == n)
    {
        return;
    }
    
    if (add_num == add 
    && sub_num == sub
    && mul_num == mul)
    {
        caculate();
        return;
    }

    op[index] = 1;
    simulate(index+1, add_num+1, sub_num, mul_num);
    
    op[index] = -1;
    simulate(index+1, add_num, sub_num+1, mul_num);

    op[index] = 0;
    simulate(index+1, add_num, sub_num, mul_num+1);
}

int main() {
    cin >> n;    
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cin >> add >> sub >> mul;

    simulate(0,0,0,0);
    
    cout << MIN  << " " << MAX << endl;
    return 0;
}