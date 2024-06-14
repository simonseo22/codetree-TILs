#if 1
// 모든 계란틀에 대해 분리
// 총합 / 칸수
// 계란의 이동이 필요없을때 까지 반복

#include <iostream>
#include <math.h>
#include <vector>
#include <queue>
#include <vector>

#define DEBUG 0
#define N_MAX 50

using namespace std;

int n,l,r;
int arr[N_MAX][N_MAX];
bool visited[N_MAX][N_MAX];
vector<pair<int, int>> checkFrames;

int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

bool AllRight() {
	// 세로 검사	
	for (int i = 0; i < n-1; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int differ = abs(arr[i][j] - arr[i + 1][j]);
				if (l <= differ && differ <=r) {
					return false;
			}
		}
	}

	// 가로검사
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n-1; j++)
		{
			int differ = abs(arr[i][j] - arr[i][j+1]);
			if (l <= differ && differ <= r) {
				return false;
			}
		}
	}
	return true;
}
bool CanGo(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n && visited[x][y] == false;
}

void BFS(int x, int y) {
	queue<pair<int, int>> bfs_q;
	bfs_q.push(make_pair(x, y));
	visited[x][y] = true;
	checkFrames.push_back(make_pair(x, y));
	int sum = arr[x][y];
	while (!bfs_q.empty())
	{
		int cx, cy;
		pair<int, int>curr_pos = bfs_q.front();
		cx = curr_pos.first;
		cy = curr_pos.second;
		bfs_q.pop();
		for (int i = 0; i < 4; i++)
		{
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			int differ = abs(arr[cx][cy] - arr[nx][ny]);
			if (CanGo(nx,ny) && l <= differ && differ <=r)
			{
				visited[nx][ny] = true;
				bfs_q.push(make_pair(nx, ny));
				checkFrames.push_back(make_pair(nx, ny));
				sum += arr[nx][ny];
			}
		}
	}

	int average = sum / checkFrames.size();
#if DEBUG
	printf("average : %d\n", average);
	for (int i = 0; i < checkFrames.size(); i++)
	{
		int cx, cy;
		cx = checkFrames[i].first;
		cy = checkFrames[i].second;
		printf("changed (%d,%d)\n", cx, cy);
	}
#endif // DEBUG
	for (int i = 0; i < checkFrames.size(); i++)
	{
		int cx, cy;
		cx = checkFrames[i].first;
		cy = checkFrames[i].second;
		arr[cx][cy] = average;
	}
	checkFrames.clear();

#if DEBUG
	printf("BFS(%d, %d)\n", x,y);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	printf("------------------------------------------\n");
#endif // DEBUG
}

void CheckBound() {

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			visited[i][j] = false;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (!visited[i][j])
			{
				BFS(i, j);
			}
		}
	}


}

int main() {
	cin >> n >> l >> r;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> arr[i][j];
		}
	}
#if DEBUG
	printf("------------------------------------------\n");
#endif
	int Movecount = 0;
	while (!AllRight())
	{
		Movecount++;
		CheckBound();
#if DEBUG
		printf("Movecount : %d\n", Movecount);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
#endif // DEBUG
	}
	cout << Movecount;
}
#endif // 1