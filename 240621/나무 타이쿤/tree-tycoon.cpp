#if 1
#include <iostream>

#define DEBUG 0
#define N_MAX 15

using namespace std;
int n, m;
int dx[] = {0,0,-1,-1,-1,0,1,1,1};
int dy[] = {0,1,1,0,-1,-1,-1,0,1};
int arr[N_MAX][N_MAX];
bool MEDIC[N_MAX][N_MAX];
bool NEW_MEDIC[N_MAX][N_MAX];

bool InRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

void MoveMedic(int d, int p) {

	for (int x = 0; x < n; x++) // 배열은 진행하며 영향을 주기 때문에 반드시 새로운 배열을 사용
	{
		for (int y = 0; y < n; y++)
		{
			NEW_MEDIC[x][y] = false;
		}
	}

	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			if (MEDIC[x][y] == true)
			{
				int nx = x + dx[d] * p;
				int ny = y + dy[d] * p;

				while (nx < 0)
				{
					nx += n;
				}

				while (ny < 0)
				{
					ny += n;
				}
				
				nx = nx % n;
				ny = ny % n;
#if DEBUG
				//printf("%d-%d\n", nx, ny);
#endif // DEBUG
				NEW_MEDIC[nx][ny] = true;
			}
		}
	}

	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			MEDIC[x][y] = NEW_MEDIC[x][y];
		}
	}
#if DEBUG
	printf("after MEDIC MOVE\n");
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			cout << MEDIC[x][y] << " ";
		}
		cout << endl;
	}
#endif // DEBUG

}

int checkDiagonal(int x, int y) {

#if DEBUG
	//printf("checkDiagonal(%d,%d)d\n", x, y);
#endif // DEBUG

	int dg_x[] = {-1,1,1,-1};
	int dg_y[] = {1,1,-1,-1};
	int num = 0;
	for (int dir = 0; dir < 4; dir++)
	{
		int nx = x + dg_x[dir];
		int ny = y + dg_y[dir];
		if (InRange(nx,ny) && arr[nx][ny] >= 1)
		{
			num++;
#if DEBUG
			//printf("nx : %d, ny : %d, num : %d\n", nx, ny, num);
#endif // DEBUG

		}
	}
	return num;
}

int main() {
	cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> arr[i][j];
		}
	}

	// 좌하단 4칸
	for (int i = n-2; i < n; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			MEDIC[i][j] = true;
		}
	}




	while (m--)
	{

		int d, p;
		cin >> d >> p;
#if DEBUG
		printf("%d-start aar!!\n", m);
		for (int x = 0; x < n; x++)
		{
			for (int y = 0; y < n; y++)
			{
				cout << arr[x][y] << " ";
			}
			cout << endl;
		}
		printf("start MEDIC!!\n");
		for (int x = 0; x < n; x++)
		{
			for (int y = 0; y < n; y++)
			{
				cout << MEDIC[x][y] << " ";
			}
			cout << endl;
		}
#endif // DEBUG
		// 1. 이동규칙따라 이동

		MoveMedic(d, p);
		
		for (int x = 0; x < n; x++)
		{
			for (int y = 0; y < n; y++)
			{
				if (MEDIC[x][y] == true)
				{
					// 2. 땅에 영양제 투입, 영양제는 사라짐
					arr[x][y] += 1;
				}
			}
		}

#if DEBUG
		printf("after MEDIC +1\n");
		for (int x = 0; x < n; x++)
		{
			for (int y = 0; y < n; y++)
			{
				cout << arr[x][y] << " ";
			}
			cout << endl;
		}
#endif // DEBUG

		for (int x = 0; x < n; x++)
		{
			for (int y = 0; y < n; y++)
			{
				if (MEDIC[x][y] == true)
				{
					// 3. 투입한 땅의 대각선, 인접한 높이 1 이상 개수 만큼 추가성장  (격자 벗어나는 경우 제외)
					int num = checkDiagonal(x, y);
					arr[x][y] += num;
				}
			}
		}


#if DEBUG
		printf("after MEDIC DIAGONAL\n");
		for (int x = 0; x < n; x++)
		{
			for (int y = 0; y < n; y++)
			{
				cout << arr[x][y] << " ";
			}
			cout << endl;
		}
#endif // DEBUG


		// 4. 영양제를 투입한 땅 제외/ 2이상인 나무 높이 -2 / 해당 위치에 영양제 투입

		for (int x = 0; x < n; x++)
		{
			for (int y = 0; y < n; y++) {
				NEW_MEDIC[x][y] = false;
			}
		}


		for (int x = 0; x < n; x++)
		{
			for (int y = 0; y < n; y++)
			{
				if (arr[x][y] >= 2 && !MEDIC[x][y])
				{
					arr[x][y] -= 2;
					NEW_MEDIC[x][y] = true;
				}
			}
		}

		for (int x = 0; x < n; x++)
		{
			for (int y = 0; y < n; y++)
			{
				MEDIC[x][y] = NEW_MEDIC[x][y];
			}
		}

#if DEBUG
		printf("NEW MEDIC\n");
		for (int x = 0; x < n; x++)
		{
			for (int y = 0; y < n; y++)
			{
				cout << MEDIC[x][y] << " ";
			}
			cout << endl;
		}  

		printf("after NEW MEDIC aar\n");
		for (int x = 0; x < n; x++)
		{
			for (int y = 0; y < n; y++)
			{
				cout << arr[x][y] << " ";
			}
			cout << endl;
		}
		printf("====================================================\n");
#endif // DEBUG
	}


	//남은 높이의 총합
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			sum += arr[i][j];
		}
	}

	cout << sum;
	return 0;
}

#endif // 1