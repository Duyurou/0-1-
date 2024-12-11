#include <bits/stdc++.h>
#include<time.h>
#define count 100000
using namespace std;
class Object
{
public:
    int ID;
    int weight;
    int price;
    float d;
};
class HeapNode
{
public:
    HeapNode *parent;
    int lchild;
    int uprofit;
    int profit;
    int weight;
    int lev;
};
struct cmp
{
    bool operator()(HeapNode *&a, HeapNode *&b) const
    {
        return a->uprofit < b->uprofit;
    }
};
bool compare(const Object &a, const Object &b)
{
    return a.d >= b.d;
}
int n;
int c;
int cw;
int cp;
int bestp;
Object Q[count];
int bestx[count];

int Bound(int i)
{
    int cleft = c - cw;
    int b = cp;
    while(cleft >= Q[i].weight && i <= n)
    {
        cleft -= Q[i].weight;
        b += Q[i].price;
        i++;
    }
    if(i <= n)
    {
        b += cleft * Q[i].d;
    }
    return b;
}
void AddliveNode(priority_queue<HeapNode *, vector<HeapNode *>, cmp> &q, HeapNode *E, int up, int cw, int cp, int lev, int ch)
{
    HeapNode *p = new HeapNode;
    p->parent = E;
    p->lchild = ch;
    p->weight = cw;
    p->uprofit = up;
    p->profit = cp;
    p->lev = lev ;
    q.push(p);
}
void MaxKnapsack()
{
    priority_queue<HeapNode *, vector<HeapNode *>, cmp > q; 
    HeapNode *E = NULL;
    cw = cp = bestp = 0;
    int i = 1;
    int up = Bound(1); 
    while(i != n + 1)
    {
        int wt = cw + Q[i].weight;
        if(wt <= c)//当前重量小于背包 
        {
            if(bestp < cp + Q[i].price)
                bestp = cp + Q[i].price;
            AddliveNode(q, E, up, cw + Q[i].weight, cp + Q[i].price, i + 1 , 1);
        }
        up = Bound(i + 1); 
        if(up >= bestp) 
        {
            AddliveNode(q, E, up, cw, cp, i + 1, 0);
        }
        E = q.top();
        q.pop();
        cw = E->weight;
        cp = E->profit;
        up = E->uprofit;
        i = E->lev;
    }
    for(int j = n; j > 0; --j)
    {
        bestx[Q[E->lev - 1].ID] = E->lchild;
        E = E->parent;
    }
}

int main()
{
    cout << "请输入背包容量与物品数：";
    cin>>c>>n;
    cout << "请输入各个物品价值：";
    for (int i = 1;i <= n;i++) {
	cin >> Q[i].price;
	Q[i].ID = i;
	}
	cout << "请输入各个物品重量：";
    for(int i = 1; i <= n; ++i)
    {
    cin>>Q[i].weight;
    Q[i].d = 1.0 * Q[i].price / Q[i].weight;
    }
 double startTime1 = clock();
    sort(Q + 1, Q + n + 1, compare);
    MaxKnapsack();
    printf("最优装入量为: %d\n", bestp);
    printf("装入的物品为:");
    for(int i = 1; i <= n; ++i)
        if(bestx[i] == 1)
          	cout<<i<<" ";
          	double endTime1 = clock();
std::cout << "\n" << "The run time is : " << (double)(endTime1 - startTime1) / CLOCKS_PER_SEC << "s" << std::endl;

}

