#include<iostream>
#include<vector>
using namespace std;
int n, m;
vector<int> visited;
vector<int> circle;

int Find(const vector<int>& a, int x) {
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == x) {
            return i;
        }
    }
    return -1;
}

bool isEnd = false;
void dfsFindCircle(int x, int** a) {
    vector<int> temarr = circle;
    circle.push_back(x + 1);
    if (temarr.size() != 0 && Find(temarr, circle.back()) != -1) {
        isEnd = true;
        return;
    }

    bool findnext = false;
    for (int i = 0; i < n; i++) {
        if (a[x][i] == 1) {
            findnext = true;
            dfsFindCircle(i, a);
        }
        if (isEnd)
            break;
    }
    if (!findnext) {
        circle.pop_back();
        for (int i = 0; i < n; i++) {
            a[i][x] = 0;
        }
    }
}

int main() {
    cin >> n >> m;
    int G[50][50] = { 0 };//邻接矩阵
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        G[x - 1][y - 1] = 1;
    }
    bool isDAG = true;
    int count = n;
    while (count) {
        //找出无前驱的顶点
        int ver;
        bool isFind = false;
        for (int i = 0; i < n; i++) {
            //已访问过
            if (Find(visited, i + 1) != -1) {
                continue;
            }
            isFind = true;
            for (int j = 0; j < n; j++) {
                if (G[j][i] != 0) {
                    isFind = false;
                    break;
                }
            }
            if (isFind) {
                ver = i;
                break;
            }
        }
        if (isFind) {
            visited.push_back(ver + 1);
            count--;
            //调整矩阵
            for (int k = 0; k < n; k++) {
                G[ver][k] = 0;
            }
        }

        //有剩余节点，为环
        if (!isFind && count) {
            isDAG = false;
            break;
        }
    }

    if (isDAG) {
        cout << "YES" << endl;
        for (int i = 0; i < n; i++) {
            cout << visited[i];
            if (i != n - 1)
                cout << ',';
        }
    }

    //环
    else {
        cout << "NO" << endl;
        int** t = new int* [n];
        for (int i = 0; i < n; i++) {
            t[i] = new int[n];
            for (int j = 0; j < n; j++) {
                t[i][j] = G[i][j];
            }
        }

        //重新确定起点
        int cirstart = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (t[i][j] != 0) {
                    cirstart = i;
                    break;
                }
            }
            if (cirstart != -1) {
                break;
            }
        }
        dfsFindCircle(cirstart, t);
        cirstart = circle.back();
        for (int i = Find(circle, cirstart); i < circle.size(); i++) {
            cout << circle[i];
            if (i != circle.size() - 1) {
                cout << ',';
            }
        }
    }
    return 0;
}