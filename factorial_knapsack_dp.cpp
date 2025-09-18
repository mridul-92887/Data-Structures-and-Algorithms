#include <bits/stdc++.h>
using namespace std;

struct Item {
    int value;
    int weight;
};

bool cmp(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

double fractionalKnapsack(vector<Item>& items, int W) {
    sort(items.begin(), items.end(), cmp);
    double totalValue = 0;

    for (int i = 0; i < items.size(); i++) {
        if (W >= items[i].weight) {
            W -= items[i].weight;
            totalValue += items[i].value;
        } else {
            totalValue += items[i].value * ((double)W / items[i].weight);
            break;
        }
    }

    return totalValue;
}

int main() {
    vector<Item> items = {{60, 10}, {100, 20}, {120, 30}};
    int W = 50;
    double maxVal = fractionalKnapsack(items, W);
    cout << "Maximum value in Fractional Knapsack = " << maxVal << endl;
    return 0;
}
