#include "stack.h"
#include <iostream>

using namespace std;

void square(int e)
{
    cout << e*e << ' ';
    return;
}

int main()
{
    ADT_Stack s;
    int e;

    InitStack(&s);

    cout << "StackEmpty(&s) returns " << (StackEmpty(&s) ? "true" : "false") << endl;

    cout << "StackLength(&s) returns " << StackLength(&s) << endl;

    cout << "Push 1-5 five numbers into stack s" << endl;
    for (int i=1; i<=5; ++i)
        Push(&s, i);

    GetTop(&s, &e);
    cout << "The top element is " << e << endl;

    cout << "Pop three elements from stack s : ";
    for (int i=0; i<3; ++i)
    {
        Pop(&s, &e);
        cout << e << ' ';
    }
    cout << endl;

    cout << "Push 6-10 five numbers into stack s" << endl;
    for (int i=6; i<=10; ++i)
        Push(&s, i);

    cout << "Traverse stack s by function square()" << endl;
    StackTraverse(&s, &square);
    cout << endl;
    
    return 0;
}
