#if 1

#include <iostream>
#include <vector>
#include <tuple>
#define DEBUG 0
#define N_MAX 8
#define CANGO 1

using namespace std;
int n, m;
int arr[N_MAX][N_MAX];
int temp[N_MAX][N_MAX];

vector<tuple<int,int,int>>Tokens; // x,y
int TokenD[N_MAX];
int TokenMove[6][4][4] = {
	{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
	{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
	{{0,1,0,1},{1,0,1,0},{0,1,0,1},{1,0,1,0}},
	{{1,1,0,0},{0,1,1,0},{0,0,1,1},{1,0,0,1}},
	{{1,1,0,1},{1,1,1,0},{0,1,1,1},{1,0,1,1}},
	{{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}}
};
int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };
int minA = N_MAX*N_MAX;

bool CanGo(int x, int y) {
	// 갈수있는경우 범위안, 0~5
	return 0 <= x && x < n && 0 <= y && y < m &&  0 <= arr[x][y] && arr[x][y] < 6;
}

void TokenGo(int T_i) {
	//type = arr[x][y]; //  다른 말 이동에 영향을줌, 따로 저장
	for (int d_i = 0; d_i < 4; d_i++) // 4방향중 갈수있는 방향 진행
	{
		int x, y, Td, type; // x,y가 변하면 안된다. -> 새로운 방향일때 x,y는 초기위치여야한다.
		tie(x, y, type) = Tokens[T_i];
		Td = TokenD[T_i];
		if (TokenMove[type][Td][d_i] == 0)
		{
			continue;
		}

		while (1)
		{		
			int nx = x + dx[d_i] * TokenMove[type][Td][d_i];
			int ny = y + dy[d_i] * TokenMove[type][Td][d_i];
			if (CanGo(nx, ny))
			{
				arr[nx][ny] = type; // 지sk감을 표시,
				x = nx;
				y = ny;
			}
			else
			{
				break;
			}
		}
	}
	// 종류에 따른 이동 
}

void Calculate() {
	// 방향에 따라 이동
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			temp[i][j] = arr[i][j];
		}
	}

	for (int T_i = 0; T_i < Tokens.size(); T_i++)
	{
		TokenGo(T_i);
	}

	//토근이 모두 지나감
	int leftA = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (arr[i][j] == 0)
			{
				leftA++;
			}
		}
	}
	if (leftA < minA)
	{
		minA = leftA;
	}

#if DEBUG
	printf("AFTERMOVE\n");
	for (int t_i = 0; t_i < Tokens.size(); t_i++)
	{		
		int x, y, type;
		tie(x, y, type) = Tokens[t_i];
		printf("%d-token-(%d,%d), dir : %d\n", type, x, y, TokenD[t_i]);		
	}
	cout << endl;

	printf("aar\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	printf("leftA : %d\n", leftA);
	printf("minA : %d\n", minA);

	printf("=========================================\n");
#endif // DEBUG
	// 초기화
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			arr[i][j] = temp[i][j];
		}
	}
}

void simulate(int count) {
	if (count == Tokens.size())
	{
		Calculate();
		return; // return이 없으면 바로 다음이 실행되고 count는 끝없이 높아짐
	}

	for (int T_i = count; T_i < Tokens.size(); T_i++)
	{
		for (int di = 0; di < 4; di++)
		{
			TokenD[T_i] = di;
			simulate(count + 1);
		}
	}
	return;
}

int main() {
	// 5종류의 말
	// 4방향 중 선택
	// 갈수 없는 격자 크기 최소화 ( 방향을 정한다음)
	// 규칙
	// 1. 본인 말은 뛰어넘어 이동 가능
	// 2. 상대 말은 뛰어넘어 이동 불가
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			int tmp;
			cin >> tmp;
			if (1<=tmp && tmp <=5)
			{
				Tokens.push_back(make_tuple(i, j, tmp));
			}
			arr[i][j] = tmp;
			
				
		}
	}

#if DEBUG

	printf("init\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	printf("=========================================\n");
#endif // DEBUG

	simulate(0);
	cout << minA;
}

#endif // 1