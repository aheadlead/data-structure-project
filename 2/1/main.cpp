// main.c
// 
// 分别用顺序结构和单链表结构编程实现下列功能：
// 假设以两个元素依值递增有序排列的线性表A和B 分别表示两个集合，
// 现要求在A的空间上构成一个新线性表C，其元素为A和B元素的交集，
// 且表C中的元素也是依值递增有序排列（习题集P18  2.25  2.26）；
// 
// Compiler: Apple LLVM version 6.0 (clang-600.0.54) (based on LLVM 3.5svn)
// Compiler are from Xcode 6.1 .
//
// Copyleft @ aheadlead

#include <iostream>
// STL container vector is a instance of sequantial list.
#include <vector>
// STL container list is a instance of linked list.
#include <list>

using namespace std;

// Program will store data_a and data_b to two different container (Sq and L) separately,
// then merge it together separately.
// All number needs be ordered ascendingly.
int data_a[] = {1, 3, 5, 7, 9, 11, 13};
int data_b[] = {0, 2, 4, 6, 8, 10, 12};

void merge_Sq()
{
    vector<int> a, b, s;
    // Store data_a into sequential list a.
    for (size_t i=0; i<sizeof(data_a)/sizeof(int); ++i)
        a.push_back(data_a[i]);
    // Store data_b into sequential list b.
    for (size_t i=0; i<sizeof(data_b)/sizeof(int); ++i)
        b.push_back(data_b[i]);

    // Merge
    vector<int>::iterator 
        pa=a.begin(), 
        pb=b.begin();
    for (; pa!=a.end() && pb!=b.end(); )
    {
        if (*pa < *pb)
        {
            s.push_back(*pa);
            pa++;
        }
        else
        {
            s.push_back(*pb);
            pb++;
        }
    } 
    for (; pa != a.end(); pa++)
        s.push_back(*pa); 
    for (; pb != b.end(); pb++)
        s.push_back(*pb);
    
    for (vector<int>::iterator ps=s.begin(); ps!=s.end(); ++ps)
        cout << *ps << '\t';
    cout << endl;
}

// STL container list is a double linked list (called deque in STL) in essence.
// The interface of list is same to vector.
void merge_L()
{
    list<int> a, b, s;
    // Store data_a into linked list a.
    for (size_t i=0; i<sizeof(data_a)/sizeof(int); ++i)
        a.push_back(data_a[i]);
    // Store data_b into linked list b.
    for (size_t i=0; i<sizeof(data_b)/sizeof(int); ++i)
        b.push_back(data_b[i]);

    // Merge
    list<int>::iterator 
        pa=a.begin(), 
        pb=b.begin();
    for (; pa!=a.end() && pb!=b.end(); )
    {
        if (*pa < *pb)
        {
            s.push_back(*pa);
            pa++;
        }
        else
        {
            s.push_back(*pb);
            pb++;
        }
    } 
    for (; pa != a.end(); pa++)
        s.push_back(*pa); 
    for (; pb != b.end(); pb++)
        s.push_back(*pb);
    
    for (list<int>::iterator ps=s.begin(); ps!=s.end(); ++ps)
        cout << *ps << '\t';
    cout << endl;
}

int main()
{
    merge_Sq();
    merge_L();

    return 0;
}
