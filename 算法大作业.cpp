#include <iostream>
#include <vector>

using namespace std;

// ����Ԫ���������е�����
int search(vector<int> a, int x) {
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == x) {
            return i;
        }
    }
    return -1;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> stu_pref(n); // ѧ��־Ը���
    vector<vector<int>> sch_pref(m); // ѧУ����ѡ�����

    int count_stu = n;
    vector<int> count_sch(m, 0);

    // ����ѧ��־Ը���
    for (int i = 0; i < n; i++) {
        cout << "ѧ��" << i + 1 << "־Ը��" << endl;
        while (1) {
            int t;
            cin >> t;
            if (t == -1) {
                break;
            }
            stu_pref[i].push_back(t);
        }
    }

    // ����ѧУ����ѡ�����
    for (int i = 0; i < m; i++) {
        cout << "ѧУ" << i + 1 << "������ѧ����Ը��";
        for (int j = 0; j < n; j++) {
            int t;
            cin >> t;
            sch_pref[i].push_back(t);
        }
        // ����
        cout << "ѧУ" << i + 1 << "�����������У�";
        int num;
        cin >> num;
        count_sch[i] = num;
    }

    vector<int> admit(n, 0); // ��¼ѧ��ƥ�����
    vector<vector<int>> member(m); // ��¼ѧУ��ǰ¼ȡ��ѧ��
    vector<int> lose;
    while (count_stu) {
        // �ҵ�һ��δƥ��ѧ������
        int stu_free;
        for (int i = 0; i < n; i++) {
            if (admit[i] == 0) {
                stu_free = i;
                break;
            }
        }

        for (int i = 0; i < stu_pref[stu_free].size(); i++) {
            // �ҵ�һ��δƥ��ѧУ������������δ��
            int sch = stu_pref[stu_free][i] - 1; //����ֵ
            if (count_sch[sch] > 0) {
                admit[stu_free] = sch + 1;
                count_stu--;

                member[sch].push_back(stu_free + 1);
                count_sch[sch]--;

                break;
            }
            else {
                bool ischange = false;
                for (int j = 0; j < member[sch].size(); j++) {
                    int stu_admitted = member[sch][j] - 1;
                    // �Ƚ���ѧ������
                    if (search(sch_pref[sch], stu_free + 1) < search(sch_pref[sch], stu_admitted + 1)) {
                        admit[stu_free] = sch + 1;
                        admit[stu_admitted] = 0;

                        member[sch][j] = stu_free + 1;
                        ischange = true;
                        break;
                    }
                }
                if (ischange) {
                    break;
                }
                else if (i == stu_pref[stu_free].size() - 1) {
                    // ���һ��Ҳδƥ���У���¼���
                    admit[stu_free] = -1;
                    count_stu--;
                    lose.push_back(stu_free + 1);
                }
            }
        }
    }

    // ����ƥ��
    while (!lose.empty()) {
        int min_index = n;
        int sch;
        bool notfull = false;
        for (int i = 0; i < m; i++) {
            if (count_sch[i] > 0) {
                notfull = true;
                int index = search(sch_pref[i], lose.back());
                if (index < min_index) {
                    min_index = index;
                    sch = i;
                }
            }
        }
        if (notfull) {
            member[sch].push_back(lose.back());
            count_sch[sch]--;
            lose.pop_back();
        }
        else {
            break;
        }
    }

    // ����¼ȡ���
    for (int i = 0; i < m; i++) {
        cout << "ѧУ" << i + 1 << "¼ȡ���Ϊ��" << endl;
        for (int j = 0; j < member[i].size(); j++) {
            cout << member[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}
