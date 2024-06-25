// 일종의 순열문제
// 하지만 2차원 으로 구현하기 때문에 2차원의 값을 1차원으로 해야함
// 다음 행으로 진행시 1개의 열을 뛰고 진행

#if 1
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

#define DEBUG 0
#define A_MAX 8

using namespace std;

int n, m;
int arr[A_MAX][A_MAX];
int temp[A_MAX][A_MAX];
int maxLand = 0;


int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,1,-1 };

bool inRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < m;
}

void Firing(int x, int y) {
#if DEBUG
	printf("start fire (%d,%d)\n", x, y);
#endif // DEBUG

	queue<pair<int, int>> q;
	q.push(make_pair(x, y));

	while (!q.empty())
	{
		int cx, cy;
		tie(cx, cy) = q.front();
		q.pop();
		for (int d_i = 0; d_i < 4; d_i++)
		{
			int nx = cx + dx[d_i];
			int ny = cy + dy[d_i];
			if (inRange(nx, ny) && arr[nx][ny] == 0)
			{
#if DEBUG
				printf("nx, ny = (%d,%d)\n", nx, ny);
#endif // DEBUG
				arr[nx][ny] = 2;
				q.push(make_pair(nx, ny));
			}
		}
	}
}

void countLeftLand() {
#if DEBUG
	printf("arr!!\n");
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < m; y++) {
			cout << arr[x][y] << " ";
		}
		cout << endl;
	}
#endif // DEBUG

	// 불은 상화좌우 인접한 영역의 퍼짐 -> BFS
	// 방화벽있는 영역은 퍼지지 않음
	
	// 원래 상태 저장
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < m; y++)
		{
			temp[x][y] = arr[x][y];
		}
	}
	
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < m; y++)
		{
			if (arr[x][y] == 2) {
				Firing(x, y);
			}
		}
	}

#if DEBUG
	printf("after Firing!!!\n");
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < m; y++) {
			cout << arr[x][y] << " ";
		}
		cout << endl;
	}

#endif // DEBUG

	int leftLand = 0;
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < m; y++)
		{
			if (arr[x][y] == 0)
			{
				leftLand++;
			}
		}
	}

	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < m; y++)
		{
			arr[x][y] = temp[x][y];
		}
	}

#if DEBUG
	printf("leftLand : %d, maxLand : %d\n",leftLand,maxLand);
#endif // DEBUG

	if (leftLand > maxLand)
	{
		maxLand = leftLand;
	}
}

void simulate(int count, int start1, int start2, int start3) {
	if (count == 3)
	{
		countLeftLand();
#if DEBUG
		printf("===============================================\n");
#endif // DEBUG
		return;
	}


	// for탐색을 start_x, start_y로 진행시 3번째는 2번째 선택된 좌표값 이상에 값에서만 탐색
	int start_x, start_y;
	switch (count)
	{
		case 0:
			start_x = start1 / m;
			start_y = start1 % m;
			break;
		case 1:
			start_x = start2 / m;
			start_y = start2 % m;
			break;
		case 2:
			start_x = start3 / m;
			start_y = start3 % m;
			break;
	}

	for (int x = start_x; x < n; x++)
	{
		for (int y = start_y; y < m; y++)
		{
			// 방화벽은 불(2), 방화벽(1)외 영역(0)에만 둘수있음)
			if (arr[x][y] == 0)
			{
				arr[x][y] = 1;
				if (count == 0)
				{
					simulate(count + 1, x * m + y,start2,start3); // count에서 x,y가 방화벽인 모든 경우를 게산
				}
				if (count == 1)
				{
					simulate(count + 1, start1, x * m + y, start3);
				}
				if (count == 2)
				{
					simulate(count + 1, start1, start2, x * m + y);
				}				
				arr[x][y] = 0;
			}
		}
	}
}

int main() {
	cin >> n >> m;

	// 방화벽 3개 추가 설치하여 불이 퍼지지 않는 영역이 최대
	
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < m; y++)
		{
			cin >> arr[x][y];
		}
	}
#if DEBUG
	printf("initial!!\n");
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < m; y++) {
			cout << arr[x][y] << " ";
		}
		cout << endl;
	}
#endif // DEBUG

	simulate(0,0,0,0);
	cout << maxLand << endl;
}



#endif // 1