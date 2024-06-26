#include <iostream>
#include <vector>
#include <tuple>
#define DEBUG 0
#define N_MAX 8

using namespace std;

int n, m;
int arr[N_MAX][N_MAX];
int minA = N_MAX * N_MAX;

vector<tuple<int, int, int>> Tokens;
int TokenD[N_MAX];
int TokenMove[6][4][4] = {
    {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
    {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
    {{0,1,0,1},{1,0,1,0},{0,1,0,1},{1,0,1,0}},
    {{1,1,0,0},{0,1,1,0},{0,0,1,1},{1,0,0,1}},
    {{1,1,0,1},{1,1,1,0},{0,1,1,1},{1,0,1,1}},
    {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}
};
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

bool CanGo(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m && 0 <= arr[x][y] && arr[x][y] < 6;
}

void TokenGo(int T_i) {
    int x, y, type;
    tie(x, y, type) = Tokens[T_i];
    int Td = TokenD[T_i];

    for (int d_i = 0; d_i < 4; d_i++) {
        if (TokenMove[type][Td][d_i] == 0) continue;

        int nx = x, ny = y;
        while (true) {
            nx += dx[d_i];
            ny += dy[d_i];
            if (CanGo(nx, ny)) {
                arr[nx][ny] = type;
            } else {
                break;
            }
        }
    }
}

void Calculate() {
    int temp[N_MAX][N_MAX];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            temp[i][j] = arr[i][j];

    for (int T_i = 0; T_i < Tokens.size(); T_i++)
        TokenGo(T_i);

    int leftA = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (arr[i][j] == 0)
                leftA++;

    if (leftA < minA)
        minA = leftA;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            arr[i][j] = temp[i][j];
}

void simulate(int count) {
    if (count == Tokens.size()) {
        Calculate();
        return;
    }

    for (int di = 0; di < 4; di++) {
        TokenD[count] = di;
        simulate(count + 1);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            int tmp;
            cin >> tmp;
            if (1 <= tmp && tmp <= 5)
                Tokens.push_back(make_tuple(i, j, tmp));
            arr[i][j] = tmp;
        }

    simulate(0);
    cout << minA;
    return 0;
}