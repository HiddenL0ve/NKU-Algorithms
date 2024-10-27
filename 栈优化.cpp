#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<stack<int>> boys(n); // �洢������ƫ��ջ
    vector<vector<int>> girls(m); // �洢Ů����ƫ���б�
    vector<int> match(m, -1); // �洢ƥ���������ʼ��Ϊ-1����ʾδƥ��
    int yes = 0; // ��ƥ�����������

    // ����������ϲ��ջ
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int t;
            cin >> t;
            boys[i].push(t - 1); // ϲ�ô�0��ʼ��������Ҫ��1
        }
    }

    // ����Ů����ϲ���б�
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int t;
            cin >> t;
            girls[i].push_back(t - 1); // ϲ�ô�0��ʼ��������Ҫ��1
        }
    }

    // ƥ�����
    while (yes < n) {
        int i = yes + 1; // ȡ��һ������
        stack<int>& stack_boys = boys[i - 1]; // ȡ����i��ϲ��ջ
        int k = stack_boys.top(); // ȡ��ջ��Ů��
        stack_boys.pop(); // �Ƴ�ջ��Ů��

        int i0 = match[k]; // ��ǰƥ�����
        if (i0 == -1) {
            // ����ǰŮ��δƥ�䣬ֱ��ƥ��
            yes++;
            match[k] = i - 1;
        }
        else {
            // ����ǰŮ����ƥ�䣬�Ƚ�����i��i0�ĺø�
            vector<int>& girl_pref = girls[k];
            int pref_i = distance(girl_pref.begin(), find(girl_pref.begin(), girl_pref.end(), i - 1)); // ����i�ڵ�ǰŮ����ϲ���б��е�λ��
            int pref_i0 = distance(girl_pref.begin(), find(girl_pref.begin(), girl_pref.end(), i0)); // ����i0�ڵ�ǰŮ����ϲ���б��е�λ��
            if (pref_i < pref_i0) {
                // �������i�ĺø���������i0��������ƥ��
                match[k] = i - 1;
                boys[i0].push(i0); // ����i0������ջ
            }
        }
    }

    // ���ƥ�����
    for (int i = 0; i < m; i++) {
        cout << "Ů��" << i + 1 << "������" << match[i] + 1 << "ƥ��" << endl;
    }

    return 0;
}
