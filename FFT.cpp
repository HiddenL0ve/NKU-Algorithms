#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
using namespace std;
const double pi = acos(-1);

void FFT(vector<complex<double>>& p, int len) {
    if (len == 1) {
        return;
    }
    vector<complex<double>> p_odd, p_even;
    for (int i = 0; i < len; i++) {
        if (i % 2 == 0)
            p_even.push_back(p[i]);
        else
            p_odd.push_back(p[i]);
    }
    FFT(p_odd, len / 2);
    FFT(p_even, len / 2);
    for (int i = 0; i < len / 2; i++) {
        complex<double> w = polar(1.0, 2 * pi * i / len);
        p[i] = p_even[i] + w * p_odd[i];
        p[len / 2 + i] = p_even[i] - w * p_odd[i];
    }
}

void IFFT(vector<complex<double>>& p, int len) {
    if (len == 1) {
        return;
    }
    vector<complex<double>> p_odd, p_even;
    for (int i = 0; i < len; i++) {
        if (i % 2 == 0)
            p_even.push_back(p[i]);
        else
            p_odd.push_back(p[i]);
    }
    IFFT(p_odd, len / 2);
    IFFT(p_even, len / 2);
    for (int i = 0; i < len / 2; i++) {
        complex<double> w = polar(1.0, -2 * pi * i / len);
        complex<double> t1 = p_even[i] + w * p_odd[i];
        complex<double> t2 = p_even[i] - w * p_odd[i];
        p[i] = t1 / 2.0;
        p[len / 2 + i] = t2 / 2.0;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> N(n + 1), M(m + 1);
    vector<complex<double>> t1, t2;
    for (int i = 0; i < n + 1; i++) {
        cin >> N[i];
        t1.push_back(complex<double>(N[i], 0.0));
    }
    for (int i = 0; i < m + 1; i++) {
        cin >> M[i];
        t2.push_back(complex<double>(M[i], 0.0));
    }
    int len = 1;
    while (len <= n + m)
        len *= 2;
    t1.resize(len);
    t2.resize(len);
    FFT(t1, len);
    FFT(t2, len);
    vector<complex<double>> t3(len);
    for (int i = 0; i < len; i++) {
        t3[i] = t1[i] * t2[i];
    }
    IFFT(t3, len);
    for (int i = 0; i < n + m + 1; i++) {
        cout << int(t3[i].real() + 0.5) << " ";
    }
    return 0;
}