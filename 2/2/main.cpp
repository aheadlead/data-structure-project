// main.c
// 
// 设有一个双向循环链表，每个结点中除有pre，
// data和next三个域外，还增设了一个访问频度域freq。
// 在链表被起作用前，频度域freq的值均初始化为零，
// 而当对链表进行一次LOCATE(L,x)的操作之后，
// 被访问的结点（即元素值等于x的节点）中的频度域freq的值便增1，
// 同时调整链表中结点之间的次序，
// 使其按访问频度非递增的顺序排列，
// 以便始终保持被频繁访问的结点总是靠近表头结点。
// 试编程实现之（习题集P19  2.38）。
//
// A very boring work.
// 
// Compiler: Apple LLVM version 6.0 (clang-600.0.54) (based on LLVM 3.5svn)
// Compiler are from Xcode 6.1 .
//
// Copyleft @ aheadlead

#include <iostream>
#include <list>

using namespace std;

struct Node
{
    int data;
    int freq;
    bool operator == (Node &t)
    {
        return data == t.data;
    }
};

// In essence, STL container list is a double linked loop list. (aka. 双向循环链表)
list<Node> q;

void LOCATE(list<Node> &L, int x)
{
    for (list<Node>::iterator p=L.begin(); p!=L.end(); ++p)
        if (x == p->data)
        {
            p->freq = p->freq + 1;
            Node t = *p;
            L.erase(p);
            if (t.freq >= L.begin()->freq)
            {
                L.push_front(t);
                return;
            }
            for (list<Node>::iterator q=L.begin(); q!=L.end(); ++q)
            {
                list<Node>::iterator nq = q;
                nq++;
                if (q->freq >= t.freq)
                    if (t.freq > nq->freq && nq != L.end())
                    {
                        L.insert(nq, t);    
                        return;
                    }
            }
            L.push_back(t);
            return;
        }
}

// Print the content of double linked list q
void show()
{
    for (list<Node>::iterator p=q.begin();
            p!=q.end();
            ++p)
    {
        cout << p->data << '\t' << p->freq << endl;
    }
    cout << endl;
}

int main()
{
    // Construct a double linked list with number 0 to 9
    for (int i=0; i<10; ++i)
    {
        Node t = {i, 0};
        q.push_back(t);    
    }

    show();
    // In this section, program accepts a number cnm from keyboard
    // and do method LOCATE(q, cnm)
    int cnm;
    while (1)
    {
        cin >> cnm;
        LOCATE(q, cnm);
        show();
    }

    return 0;
}
