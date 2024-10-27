#include <iostream>
#include <vector>

using namespace std;

// 查找元素在数组中的索引
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
    vector<int> lose;
    while (count_stu) {
        // 找到一个未匹配学生索引
        int stu_free;
        for (int i = 0; i < n; i++) {
            if (admit[i] == 0) {
                stu_free = i;
                break;
            }
        }

        for (int i = 0; i < stu_pref[stu_free].size(); i++) {
            // 找到一个未匹配学校索引，且名额未满
            int sch = stu_pref[stu_free][i] - 1; //索引值
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
                    // 比较两学生索引
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
                    // 最后一个也未匹配中，记录落榜
                    admit[stu_free] = -1;
                    count_stu--;
                    lose.push_back(stu_free + 1);
                }
            }
        }
    }

    // 二次匹配
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
