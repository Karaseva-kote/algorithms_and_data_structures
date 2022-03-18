#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
int n, heap[N], size_heap = 0;

void inserttoheap (int x) {
    heap[size_heap] = x;
    int i = size_heap, p = (size_heap - 1)/2;
    size_heap++;
    while(i > 0 && heap[p] < heap[i]){
        swap(heap[p], heap[i]);
        i = p;
        p = (i-1)/2;
    }
}

void extract (){
    cout << heap[0] << endl;
    size_heap--;
    swap(heap[0], heap[size_heap]);
    int i = 0, l = 1, r = 2;
    while ((l < size_heap && heap[l] > heap[i]) || (r < size_heap && heap[r] > heap[i])) {
        if (r < size_heap){
            if (heap[l] > heap[r]){
                swap(heap[l], heap[i]);
                i = l;
            } else {
                swap(heap[r], heap[i]);
                i = r;
            }
        } else {
            swap(heap[l], heap[i]);
            i = l;
        }
        l = i*2 + 1;
        r = i*2 + 2;
    }
}

int main()
{
    cin >>  n;
    for (int i = 0; i < n; i++){
        bool command;
        cin >> command;
        if (command) {
            extract();
        } else {
            int x;
            cin >> x;
            inserttoheap(x);
        }
    }
    return 0;
}
