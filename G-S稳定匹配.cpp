/*5
2 1 4 5 3
4 2 1 3 5
2 5 3 4 1
1 4 3 2 5
2 4 1 5 3
5 1 2 4 3
3 2 4 1 5
2 3 4 5 1
1 5 4 3 2
4 2 5 3 1  */
#include<iostream>
using namespace std;
// ����Ԫ���������е�����
int search(int a[], int size, int x) {
    for (int i = 0; i < size; i++) {
        if (a[i] == x) {
            return i;
        }
    }
    return -1;
}
int main() {
    int n;
    cin >> n;
    int m[30][30], w[30][30];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> m[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> w[i][j];
        }
    }
    int assign[30] = { 0 };
    int count = n;
    while (count) {
        // �ҵ�һ��δƥ��������
        int mfree;
        for (int i = 0; i < n; i++) {
            if (assign[i] == 0) {
                mfree = i;
                break;
            }
        }

        for (int i = 0; i < n; i++) {
            // �ҵ�һ��δƥ��Ů����
            if (search(assign, n, m[mfree][i]) == -1) {
                assign[mfree] = m[mfree][i];
                count--;
                break;
            }
            else {
                int w_assigned = m[mfree][i] - 1;
                int m_assigned = search(assign, n, m[mfree][i]);
                // �Ƚ���������
                if (search(w[w_assigned], n, mfree + 1) < search(w[w_assigned], n, m_assigned + 1)) {
                    assign[mfree] = w_assigned + 1;
                    assign[m_assigned] = 0;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << assign[i] << " ";
    }
    return 0;
}
