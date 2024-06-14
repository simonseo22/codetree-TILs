#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

#define MAX_N 50
#define MAX_HOSPITAL 13 // 

int n, m;
int min_distance = INT_MAX;
vector<pair<int, int> > people;
vector<pair<int, int> > hospitals;
bool visited[MAX_HOSPITAL]; // 병원의 선택여부를 기록

bool checked[MAX_N][MAX_N]; // bfs시 방문 여부를 체크하기 위한 배열입니다.
int step[MAX_N][MAX_N]; // bfs시 병원까지의 거리를 기록

bool CanGo(int x, int y) { // bfs시 나아가려는 위치가 격자 내에 아직 방문하지 않은 지점인지를 판단합니다.
	return 0 <= x && x < n && 0 <= y && y < n && checked[x][y] == false;
}

int GetCurrMinDistance() { // 각 사람이 병원까지의 최소거리를 구할때 병원위치에서 BFS를 한번에 진행해 거리를 구한다.
	int curr_min_distance = 0;

	queue<pair<int, int>> q;
	memset(checked, false, sizeof(bool) * n * n);
	memset(step, 0, sizeof(int) * n * n);

	for (int i = 0; i < (int)hospitals.size(); i++)
	{
		if (visited[i])
		{
			int x = hospitals[i].first, y = hospitals[i].second;
			checked[x][y] = true;
			step[x][y] = 0;
			q.push(make_pair(x, y));
		}
	}

	int dx[4] = { 1, -1, 0, 0 };
	int dy[4] = { 0, 0, 1, -1 };

	while (!q.empty())
	{
		pair<int, int> curr_pos = q.front();
		int x = curr_pos.first, y = curr_pos.second;
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int nx = x + dx[i], ny = y + dy[i];
			if (CanGo(nx,ny))
			{
				checked[nx][ny] = true;
				step[nx][ny] = step[x][y] + 1;
				q.push(make_pair(nx, ny));
			}
		}
;	}

	for (int i = 0; i < people.size(); i++)
	{
		int x = people[i].first, y = people[i].second;
		curr_min_distance += step[x][y];
	}
	return curr_min_distance;
}

void SearchMinDistance(int cnt, int last_idx) {
	if (cnt == m)
	{
		min_distance = min(min_distance, GetCurrMinDistance());
		return;
	}

	for (int i = last_idx+1; i < hospitals.size(); i++){ // 개수 탐색
		visited[i] = true;
		SearchMinDistance(cnt + 1, i);
		visited[i] = false;
	}
}

int main() {
	cin >> n >> m;

	int buffer;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> buffer;
			if (buffer == 1){
				people.push_back(make_pair(i, j)); // m~13, m개의 병원을 골라야함
			}
			else if (buffer == 2) {
				hospitals.push_back(make_pair(i, j));
			}
		}
	}
	SearchMinDistance(0, -1);
	cout << min_distance;

	return 0;
}