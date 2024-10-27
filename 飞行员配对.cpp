#include<iostream>
#include<queue>
#include<cmath>

using namespace std;
int G[100][100] = { 0 };
int before[100];//before[i] 第i个的前一个节点
int dis[100];//dis[i] s到i的最大流量
int num = 0;
const int MAX = 1e9;

int bfs(int s, int t) {
	for (int i = s; i <= t; i++) {
		before[i] = -1;
	}
	queue<int> visit;
	visit.push(s);
	dis[s] = 2;
	while (!visit.empty()) {
		int cur = visit.front();
		visit.pop();
		if (cur == t) {
			break;
		}
		for (int i = s; i <= t; i++) {
			if (before[i] == -1 && G[cur][i] == 1) {
				visit.push(i);
				dis[i] = min(dis[cur], G[cur][i]);
				before[i] = cur;
			}
		}
	}
	if (before[t] == -1) {
		return -1;
	}
	return dis[t];
}

void search(int s, int t) {
	int tem;
	while (1) {
		tem = bfs(s, t);
		if (tem == -1) {
			break;
		}
		int cur = t;
		while (cur != s) {
			G[cur][before[cur]] += tem;
			G[before[cur]][cur] -= tem;
			cur = before[cur];
		}
		num += tem;
	}
	return;
}
int main() {
	int m, n;
	cin >> m >> n;

	int s = 0, t = n + 1;
	for (int i = 1; i <= m; i++) {
		G[s][i] = 1;
	}
	for (int i = m + 1; i <= n; i++) {
		G[i][t] = 1;
	}

	while (1) {
		int u, v;
		cin >> u >> v;
		if (u == -1 && v == -1) {
			break;
		}
		G[u][v] = 1;
	}

	search(s, t);
	cout << num << endl;
	for (int i = 1; i <= m; i++) {
		bool flag = 0;
		for (int j = m + 1; j <= n; j++) {
			if (G[j][i] == 1) {
				cout << i << ' ' << j;
				flag = 1;
				break;
			}
		}
		if(flag == 1)
			cout << endl;
	}
	return 0;
}