#include<iostream>
#include<cmath>
#include<vector>
#include <algorithm>

using namespace std;

class Knap {
	friend int Knapsack(int*, int*, int, int);
private:
	int Bound(int i);
	void Backtrack(int i);
	int c;
	int n;
	int* w;
	int* p;
	int cw;
	int cp;
	int bestp;
};

class Object {
	friend int Knapsack(int*, int*, int, int);
	friend void Sort(Object*, int);
public:
	int operator<=(Object a) const { return (d >= a.d); }
private:
	int ID;
	double d;
};

void Swap(double &i, double &j) {
	double a;
	a = i;
	i = j;
	j = a;
}

void Sort(Object* Q, int n) {
	float max;
	int a, max_a = 0;
	for (int i = 0;i < n;i++) {
		max = Q[i].d;
		for (int j = i;j < n;j++) {
			if (Q[j].d >= max) {
				max = Q[j].d;
				max_a = j;
			}
		}
		Swap(Q[i].d, Q[max_a].d);
		a = Q[i].ID;
		Q[i].ID = Q[max_a].ID;
		Q[max_a].ID = a;
	}

}

int Knapsack(int *p, int *w, int c, int n) {//初始化
	int W = 0;
	int P = 0;
	Object* Q = new Object[n];
	for (int i = 1;i <= n;i++) {
		Q[i - 1].ID = i;
		Q[i - 1].d = 1.0*p[i] / w[i];
		P += p[i];
		W += w[i];
	}
	if (W <= c)
		return P;
	Sort(Q, n);
	
	Knap k;
	k.p = new int [n + 1];
	k.w = new int[n + 1];
	for (int i = 1;i <= n;i++) {
		k.p[i] = p[Q[i - 1].ID];
		k.w[i] = w[Q[i - 1].ID];
	}
	k.cp = 0;
	k.cw = 0;
	k.c = c;
	k.n = n;
	k.bestp = 0;
	k.Backtrack(1);
	delete[] Q;
	delete[] k.w;
	delete[] k.p;
	return k.bestp;
}

void Knap::Backtrack(int i) {
	if (i > n) {
		bestp = cp;
		return;
	}
	if (cw + w[i] <= c) {
		cw += w[i];
		cp += p[i];
		Backtrack(i + 1);
		cp -= p[i];
		cw -= w[i];
	}
	if (Bound(i + 1) > bestp)
		Backtrack(i + 1);

}

int Knap::Bound(int i) {
	int cleft = c - cw;
	float b = cp;
	while (i <= n && w[i] <= cleft) {
		cleft -= w[i];
		b += p[i];
		i++;
	}
	if (i <= n)
		b += cleft * p[i] / w[i];
	return b;
}

int main() {
	cout << "请输入背包容量与物品数：";
	int c, n;
	cin >> c >> n;
	int* w = new int(n + 1);
	int* p = new int(n + 1);
	cout << "请输入各个物品价值：";
	for (int i = 1;i <= n;i++) {
		cin >> p[i];
	}
	cout << "请输入各个物品重量：";
	for (int i = 1;i <= n;i++) {
		cin >> w[i];
	}
	int bestp = Knapsack(p, w, c, n);
	cout << "背包可装的最大价值为：" << bestp;
}

