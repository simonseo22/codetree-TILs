#if 1
// 위로 1~n -> 사람 타고 내림
// 아래로 2n~n+1
// 시계방향 회전, 순환
// 1. 무빙워크 회전
// 2. 가장 먼저 올라간 사람부터 앞에사람 or 안전도 0이면 이동X (이동이 가능하면 끝까지 이동)
// 3. 1번칸 사람X 안전도0이 아니면 사람더
// 4.안전성 0 k이상이면 종료

#include <iostream>
#include <vector>
#include <queue>

#define DEBUG 0
#define N_MAX 100 

using namespace std;

int uarr[N_MAX];
int darr[N_MAX];
int Marr[N_MAX]; // 올라간 순서는 뒤에서부터 이동하면 되지 않나?
int n, k;
int tryCount = 0;
bool IsEnd() {
	int brokenNum = 0;
	for (int i = 0; i < n; i++)
	{
		if (uarr[i] == 0)
		{
			brokenNum++;
		}

		if (darr[i] == 0)
		{
			brokenNum++;
		}
	}
	if (brokenNum >= k)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void Rotate() {
	// 사람이동 추가
	Marr[n - 1] = 0;
	for (int i = n - 1; i >= 1; i--)
	{
		Marr[i] = Marr[i - 1];
	}
	Marr[0] = 0;


	int uLast = uarr[n - 1];
	for (int i = n - 1; i >= 1; i--)
	{
		uarr[i] = uarr[i - 1];
	}

	int dLast = darr[n - 1];
	for (int i = n - 1; i >= 1; i--)
	{
		darr[i] = darr[i - 1];
	}
	uarr[0] = dLast;
	darr[0] = uLast;
#if DEBUG
	printf("Rotate :%d\n", tryCount);
	printf("Marr\n");
	for (int i = 0; i < n; i++)
	{
		cout << Marr[i] << " ";
	}
	cout << endl;

	printf("uarr\n");
	for (int i = 0; i < n; i++)
	{
		cout << uarr[i] << " ";
	}
	cout << endl;

	printf("darr\n");
	for (int i = n - 1; i >= 0; i--)
	{
		cout << darr[i] << " ";
	}
	cout << endl;

	printf("----------------------------------------\n");
#endif // DEBUG
}

void ManMove() {
	for (int i = n - 1; i >= 0; i--) // 앞쪽에 있는 사람이 먼저온 사람
	{
		if (Marr[i] == 1)
		{
			if (i == n - 1)
			{
				Marr[i] = 0;
			}
			else if (i < n - 1 && uarr[i + 1] > 0 && Marr[i + 1] == 0) // 끝이 아니고, 무빙워크 내구도가 있고, 앞에 사람없고
			{
				// 사람이동
				Marr[i] = 0;
				Marr[i + 1] = 1;

				// 이동위치 내구도 -1
				uarr[i + 1] -= 1;
			}
			else if (uarr[i + 1] == 0 || Marr[i + 1] == 1) // 사람이 있거나 내구도가 0인경우 이동 멈춤(찾지못함) -> 모든 경우를 정리해야한다. 안그러면 구현중 까먹음
			{
				//break;
			}
		}
	}

#if DEBUG
	printf("ManMove :%d\n", tryCount);
	printf("Marr\n");
	for (int i = 0; i < n; i++)
	{
		cout << Marr[i] << " ";
	}
	cout << endl;

	printf("uarr\n");
	for (int i = 0; i < n; i++)
	{
		cout << uarr[i] << " ";
	}
	cout << endl;

	printf("darr\n");
	for (int i = n - 1; i >= 0; i--)
	{
		cout << darr[i] << " ";
	}
	cout << endl;

	printf("----------------------------------------\n");
#endif // DEBUG
}

int main() {
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> uarr[i];
	}
	for (int i = 0; i < n; i++)
	{
		cin >> darr[i];
	}

#if DEBUG
	printf("first!!! :%d\n", tryCount);
	printf("Marr\n");
	for (int i = 0; i < n; i++)
	{
		cout << Marr[i] << " ";
	}
	cout << endl;

	printf("uarr\n");
	for (int i = 0; i < n; i++)
	{
		cout << uarr[i] << " ";
	}
	cout << endl;

	printf("darr\n");
	for (int i = n - 1; i >= 0; i--)
	{
		cout << darr[i] << " ";
	}
	cout << endl;

	printf("----------------------------------------\n");
#endif // DEBUG

	while (!IsEnd())
	{
		tryCount++;
		Rotate();
		ManMove();
		if (uarr[0] > 0)
		{
			uarr[0] -= 1;
			Marr[0] = 1;
		}
#if DEBUG
		printf("PutMan :%d\n", tryCount);
		printf("Marr\n");
		for (int i = 0; i < n; i++)
		{
			cout << Marr[i] << " ";
		}
		cout << endl;

		printf("uarr\n");
		for (int i = 0; i < n; i++)
		{
			cout << uarr[i] << " ";
		}
		cout << endl;

		printf("darr\n");
		for (int i = n - 1; i >= 0; i--)
		{
			cout << darr[i] << " ";
		}
		cout << endl;

		printf("----------------------------------------\n");
#endif // DEBUG
	}
	cout << tryCount << endl;
}

#endif // 1