#if 1
// 규칙 판별
// 일반화
//
// 친구 번호와 친구번호가 담긴 index를 혼동해서 사용하여 오류 발생 -> 명확하게 결정
// 친구개수, 공백개수등이 동일할 경우는 그냥 추가

// n*n칸 놀이기구 탑승
// 모든칸은 비어있음 (r,c) r행 c열
// 각 학생마다 좋아하는 학생 4명씩(자기자신 X, 중복 X)
// 우선순위 높은칸(항상 비어있는 칸으로만 이동)
// 규칙
// 1.격자 내부에서 4방향 좋아하는 친구가 가장 많은 위치
// 2. 1번조건 여러곳 -> 인접칸중 비어있는 칸의 수가 가장 많은 위치( 격자외부는 빈칸X)
// 3. 2번조건 여러곳 -> 행번호가 가장 작은 곳
// 4. 3번조건 여러곳 -> 열번호가 가장 작은곳
// 점수 계산
// 좋아하는 친구수에 따라 점수
#include <iostream>
#include <vector>
#include <tuple>

#define N_MAX 20
#define DEBUG 0

using namespace std;

int n;
int LovingFriends[N_MAX][5]; // [순서][본인, 좋아하는1~4]
int arr[N_MAX][N_MAX];
vector<pair<int, int>> candidates;
int dx[] = { 1,0,-1,0 };
int dy[] = { 0,1,0,-1 };
int score[] = { 0,1,10,100,1000 };

bool inRange(int x, int y) {
	return 0 <= x && x < n && 0 <= y && y < n;
}

bool nearFriend(int friends_i, int x, int y) {
	for (int i = 0; i < n * n; i++) {
		if (LovingFriends[i][0] == friends_i) {
			for (int j = 1; j <= 4; j++) {
				if (LovingFriends[i][j] == arr[x][y]) {
					return true;
				}
			}
		}
	}
	return false;}

// rule1에 의해 index가 갈수있는 자리를 candiates에 추가
void rule1(int index) {
#if DEBUG
	printf("%d rule1\n", LovingFriends[index][0]);
	printf("friend!\n");
	for (int i = 1; i < 5; i++)
	{
		cout << LovingFriends[index][i] << " ";
	}
	cout << endl;
#endif // DEBUG

	int maxFriend = 0;
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			if (arr[x][y] != 0) // 이미 사람 있다면 pass
			{
				continue;
			}
			int numFriend = 0;
			for (int d = 0; d < 4; d++) // 4방향 확인
			{
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (inRange(nx,ny) && nearFriend(LovingFriends[index][0], nx,ny))
				{
					numFriend++;
				}
			}
			if (numFriend > maxFriend)
			{
				maxFriend = numFriend;
				candidates.clear();
				candidates.push_back(make_pair(x, y));
			}
			else if (numFriend == maxFriend)
			{
				candidates.push_back(make_pair(x, y));
			}			
		}
	}
#if DEBUG
	printf("rule1 done\n");
	printf("maxFriend : %d\n", maxFriend);
	for (int i = 0; i < candidates.size(); i++)
	{
		printf("candiate %dst (%d,%d)\n", i, candidates[i].first, candidates[i].second);
	}
#endif // DEBUG

}

void rule2(int index) { // candiates만 확인
	int maxBlank = 0; 
	vector<pair<int, int>> temp; // candiates의 data를 순환중 이를 건드리면 안된다.
	for (int i = 0; i < candidates.size(); i++) // 후보만 출력
	{
		int x = candidates[i].first;
		int y = candidates[i].second;
		int numBlank = 0;
#if DEBUG
		//printf("rule2 (%d, %d)\n", x, y);
#endif // DEBUG
		for (int d = 0; d < 4; d++) // 4방향 확인
		{
			int nx = x + dx[d];
			int ny = y + dy[d];
#if DEBUG
			//printf("inRange(%d, %d) : %d\n",nx,ny, inRange(nx, ny));
			//printf("arr[%d][%d] : %d\n",nx,ny, arr[nx][ny]);
#endif // DEBUG
			if (inRange(nx, ny) && arr[nx][ny] == 0)
			{
				numBlank++;
			}
		}
		if (numBlank > maxBlank) 
		{
			maxBlank = numBlank;
			temp.clear();
			temp.push_back(make_pair(x, y));
		}
		else if(numBlank == maxBlank)
		{
			temp.push_back(make_pair(x, y));
		}		
	}
	candidates = temp;
#if DEBUG
		printf("rule2 done\n");
		printf("maxBlank : %d\n", maxBlank);
		for (int i = 0; i < candidates.size(); i++)
		{
			printf("candiate %dst (%d,%d)\n", i, candidates[i].first, candidates[i].second);
		}
#endif // DEBUG
}

int main() {
	cin >> n;
	std::fill(&arr[0][0], &arr[0][0] + N_MAX * N_MAX, -1); // - 경계 check
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			arr[i][j] = 0;
		}
	}

	for (int i = 0; i < n*n; i++)
	{
		for (int j = 0; j < 5; j++)
		{					
			cin >> LovingFriends[i][j];
		}
	}
#if DEBUG
	printf("check input\n");
	for (int i = 0; i < n*n; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << LovingFriends[i][j] << " ";
		}
		cout << endl;
	}
	printf("===================================================\n");
#endif // DEBUG

	for (int i = 0; i < n * n; i++) // arr[1~n]
	{
		candidates.clear(); // 시작할때 기존 위치 조건들 초기화
		rule1(i);
		if (candidates.size() == 1)
		{
			int x, y;
			tie(x,y) = candidates[0];
			arr[x][y] = LovingFriends[i][0]; // 위치 설정
			candidates.clear();
		}
		else // rule2진행
		{
#if DEBUG
			printf("%d rule1 candiate : %d\n",LovingFriends[i][0],candidates.size());
#endif // DEBUG
			rule2(i);
			if (candidates.size()==1)
			{
				int x, y;
				tie(x, y) = candidates[0];
				arr[x][y] = LovingFriends[i][0]; // 위치 설정
				candidates.clear();
			}
			else
			{
#if DEBUG
			printf("%d rule2 candiate : %d\n", LovingFriends[i][0], candidates.size());
#endif // DEBUG
				pair<int, int>pos = make_pair(N_MAX,N_MAX);
				for (int i = 0; i < candidates.size(); i++)
				{
					pair<int, int>currentPos = candidates[i];
					if (currentPos < pos)
					{
						pos = currentPos;
					}
				}
				arr[pos.first][pos.second] = LovingFriends[i][0];
				candidates.clear();
			}
		}
#if DEBUG
		printf("%d SET\n",LovingFriends[i][0]);
		for (int x = 0; x < n; x++)
		{
			for (int y = 0; y < n; y++)
			{
				cout << arr[x][y] << " ";
			}
			cout << endl;
		}
		printf("===================================================\n");
#endif // DEBUG
	}
#if DEBUG
	printf("ALL SET\n");
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			cout << arr[x][y] << " ";
		}
		cout << endl;
	}
#endif // DEBUG

	// 점수 계산
	int ScroeSum = 0;
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
		{
			int numFriend = 0;
			int friend_i = arr[x][y];
			for (int d = 0; d < 4; d++) // 4방향 확인
			{
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (inRange(nx, ny) && nearFriend(friend_i, nx, ny))
				{
					numFriend++;
				}
			}
#if DEBUG
			printf("friend-%d numFriend : %d, scroe : %d\n", friend_i, numFriend, score[numFriend]);
#endif // DEBUG
			ScroeSum += score[numFriend];
		}
	}
	cout << ScroeSum << endl;
	return 0;
}


#endif // 1