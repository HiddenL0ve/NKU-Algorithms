#include <iostream>
#include <vector>

using namespace std;

// 查找元素在数组中的索引
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

    vector<vector<int>> stu_pref(n); // 学生志愿情况
    vector<vector<int>> sch_pref(m); // 学校优先选择情况

    int count_stu = n;
    vector<int> count_sch(m, 0);

    // 输入学生志愿情况
    for (int i = 0; i < n; i++) {
        cout << "学生" << i + 1 << "志愿：" << endl;
        while (1) {
            int t;
            cin >> t;
            if (t == -1) {
                break;
            }
            stu_pref[i].push_back(t);
        }
    }

    // 输入学校优先选择情况
    for (int i = 0; i < m; i++) {
        cout << "学校" << i + 1 << "对所有学生意愿：";
        for (int j = 0; j < n; j++) {
            int t;
            cin >> t;
            sch_pref[i].push_back(t);
        }
        // 名额
        cout << "学校" << i + 1 << "的招生名额有：";
        int num;
        cin >> num;
        count_sch[i] = num;
    }

    vector<int> admit(n, 0); // 记录学生匹配情况
    vector<vector<int>> member(m); // 记录学校当前录取的学生
    int replaced_index = -1; // 记录被替换学生的索引

    // 匹配过程
    for (int i = 0; i < n; i++) {
        int stu_free = (replaced_index == -1) ? i : replaced_index; // 选择未匹配的学生索引
        replaced_index = -1; // 重置被替换学生索引

        for (int j = 0; j < stu_pref[stu_free].size(); j++) {
            int sch = stu_pref[stu_free][j] - 1; //学校索引
            if (count_sch[sch] > 0) {
                admit[stu_free] = sch + 1;
                count_stu--;

                member[sch].push_back(stu_free + 1);
                count_sch[sch]--;

                break;
            }
            else {
                int stu_admitted = admit[stu_free] - 1; // 获取当前学生已匹配学校索引
                int sch_index = search(sch_pref[sch], stu_free + 1); // 获取当前学生在当前学校的志愿顺序

                if (search(sch_pref[sch], stu_free + 1) < search(sch_pref[sch], stu_admitted + 1)) {
                    admit[stu_free] = sch + 1;
                    admit[stu_admitted] = 0;

                    member[sch][search(member[sch], stu_admitted + 1)] = stu_free + 1;
                    replaced_index = stu_admitted; // 记录被替换学生索引
                    break;
                }
            }
        }
    }

    // 最终录取情况
    for (int i = 0; i < m; i++) {
        cout << "学校" << i + 1 << "录取结果为：" << endl;
        for (int j = 0; j < member[i].size(); j++) {
            cout << member[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}
