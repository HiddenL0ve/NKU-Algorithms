#include <iostream>
#include <vector>

using namespace std;

// ����Ԫ���������е�����
int search(const vector<int>& a, int x) {
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
    int replaced_index = -1; // ��¼���滻ѧ��������

    // ƥ�����
    for (int i = 0; i < n; i++) {
        int stu_free = (replaced_index == -1) ? i : replaced_index; // ѡ��δƥ���ѧ������
        replaced_index = -1; // ���ñ��滻ѧ������

        for (int j = 0; j < stu_pref[stu_free].size(); j++) {
            int sch = stu_pref[stu_free][j] - 1; //ѧУ����
            if (count_sch[sch] > 0) {
                admit[stu_free] = sch + 1;
                count_stu--;

                member[sch].push_back(stu_free + 1);
                count_sch[sch]--;

                break;
            }
            else {
                int stu_admitted = admit[stu_free] - 1; // ��ȡ��ǰѧ����ƥ��ѧУ����
                int sch_index = search(sch_pref[sch], stu_free + 1); // ��ȡ��ǰѧ���ڵ�ǰѧУ��־Ը˳��

                if (search(sch_pref[sch], stu_free + 1) < search(sch_pref[sch], stu_admitted + 1)) {
                    admit[stu_free] = sch + 1;
                    admit[stu_admitted] = 0;

                    member[sch][search(member[sch], stu_admitted + 1)] = stu_free + 1;
                    replaced_index = stu_admitted; // ��¼���滻ѧ������
                    break;
                }
            }
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
