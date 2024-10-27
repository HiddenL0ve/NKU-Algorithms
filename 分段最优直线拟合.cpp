#include<iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

const double MAX = 1e9;
double Error(double x[], double y[], int i, int j) {
	double sum_x = 0, sum_y = 0, sum_x2 = 0, sum_xy = 0;
	int n = j - i + 1;

	for (int k = i; k <= j; k++) {
		sum_x += x[k];
		sum_y += y[k];
		sum_x2 += pow(x[k], 2);
		sum_xy += x[k] * y[k];
	}
	// y = ax+b
	double a = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
	double b = (sum_y - a * sum_x) / n;

	double error = 0.0;
	for (int k = i; k <= j; k++) {
		double y_pred = a * x[k] + b;
		error += pow((y[k] - y_pred), 2);
	}

	return error;
}
int main() {
	int n;
	double c;
	cin >> n >> c;
	double x[1000], y[1000];
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}

	vector<double> M(n + 1, MAX);
	M[0] = 0;
	for (int j = 1; j <= n; j++) {
		for (int i = 0; i <= j; i++) {
			double eij = Error(x, y, i, j - 1);
			M[j] = min(M[j], eij + c + M[i]);
		}
	}

	cout << fixed << setprecision(2) << M[n] << endl;
	return 0;
}