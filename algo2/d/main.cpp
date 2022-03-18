#include <bits/stdc++.h>

using namespace std;

int n;

struct Node {
    int num;
    Node *next;
    Node(int v){
        num = v;
        next = NULL;
    }
};

struct Queue{
    int Size;
    Node *first;
    Node *center;
    Node *last;
    Queue(){
        Size = 0;
        first = NULL;
        last = NULL;
        center = NULL;
    }
};

int Top(Queue *Q){
    return Q->first->num;
}

void AddEnd(Queue *Q, int val){
    if (Q->Size == 0){
        Node *b = new Node(val);
        Q->last = b;
        Q->first = b;
        Q->center = b;
        Q->Size++;
    } else {
        Node *b = new Node(val);
        Q->last->next = b;
        Q->last = Q->last->next;
        Q->Size++;
        if (Q->Size % 2 == 1){
            Q->center = Q->center->next;
        }
    }
}

void AddCenter(Queue *Q, int val){
    if (Q->Size == 0){
        Q->center = new Node(val);
        Q->first = Q->center;
        Q->last = Q->center;
        Q->Size++;
        return;
    }
    if (Q->Size == 1){
        Node *b = new Node(val);
        b->next = Q->center->next;
        Q->center->next = b;
        Q->last = Q->last->next;
        Q->Size++;
        return;
    }
    Node *b = new Node(val);
    b->next = Q->center->next;
    Q->center->next = b;
    Q->Size++;
    if (Q->Size % 2 == 1){
        Q->center = Q->center->next;
    }
}

void DeleteFirst(Queue *Q){
    if (Q->Size == 1){
        Q->center = NULL;
        Q->first = NULL;
        Q->last = NULL;
        Q->Size = 0;
    } else {
        Q->first = Q->first->next;
        Q->Size--;
        if (Q->Size % 2 == 1){
            Q->center = Q->center->next;
        }
    }
}

/*void print (Node *b){
    if (b == NULL){
        return;
    }
    cout << b->num << " ";
    b = b->next;
    print(b);
}*/

int main()
{
    cin >> n;
    Queue *q = new Queue();
    for (int i = 0; i < n; i++){
        char b;
        cin >> b;
        if (b == '+'){
            int ind;
            cin >> ind;
            AddEnd(q, ind);
        }
        if (b == '*'){
            int ind;
            cin >> ind;
            AddCenter(q, ind);
        }
        if (b == '-'){
            cout << Top(q) << endl;
            DeleteFirst(q);
        }
        /*print(q->first);
        cout << "   size = " << q->Size << endl << q->last->num << endl;*/
    }
    return 0;
}
