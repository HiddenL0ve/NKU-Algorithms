#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<stack<int>> boys(n); // 存储男生的偏好栈
    vector<vector<int>> girls(m); // 存储女生的偏好列表
    vector<int> match(m, -1); // 存储匹配情况，初始化为-1，表示未匹配
    int yes = 0; // 已匹配的男生数量

    // 输入男生的喜好栈
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int t;
            cin >> t;
            boys[i].push(t - 1); // 喜好从0开始计数，需要减1
        }
    }

    // 输入女生的喜好列表
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int t;
            cin >> t;
            girls[i].push_back(t - 1); // 喜好从0开始计数，需要减1
        }
    }

    // 匹配过程
    while (yes < n) {
        int i = yes + 1; // 取下一个男生
        stack<int>& stack_boys = boys[i - 1]; // 取男生i的喜好栈
        int k = stack_boys.top(); // 取出栈顶女生
        stack_boys.pop(); // 移除栈顶女生

        int i0 = match[k]; // 当前匹配对象
        if (i0 == -1) {
            // 若当前女生未匹配，直接匹配
            yes++;
            match[k] = i - 1;
        }
        else {
            // 若当前女生已匹配，比较男生i与i0的好感
            vector<int>& girl_pref = girls[k];
            int pref_i = distance(girl_pref.begin(), find(girl_pref.begin(), girl_pref.end(), i - 1)); // 男生i在当前女生的喜好列表中的位置
            int pref_i0 = distance(girl_pref.begin(), find(girl_pref.begin(), girl_pref.end(), i0)); // 男生i0在当前女生的喜好列表中的位置
            if (pref_i < pref_i0) {
                // 如果男生i的好感优于男生i0，则重新匹配
                match[k] = i - 1;
                boys[i0].push(i0); // 男生i0重新入栈
            }
        }
    }

    // 输出匹配情况
    for (int i = 0; i < m; i++) {
        cout << "女生" << i + 1 << "被男生" << match[i] + 1 << "匹配" << endl;
    }

    return 0;
}
