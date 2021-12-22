#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
template <class T>
class Stacks
{
private:
    T *arr;
    int capacity, top;

public:
    Stacks(int cap = 10)
    {
        capacity = cap;
        arr = new T[capacity];
        top = 0;
    }
    ~Stacks()
    {
        delete[] arr;
    }
    int Size()
    {
        return top;
    }
    bool IsEmpty()
    {
        if (top != 0)
            return false;
        else
            return true;
    }
    T Top()
    {
        if (IsEmpty())
            return -1;
        else
            return arr[top - 1];
    }
    void Push(const T item)
    {
        if (top == capacity)
        {
            capacity *= 2;
            T *carry = new T[capacity];
            for (int x = 0; x < top; x++)
                carry[x] = arr[x];
            delete[] arr;
            arr = new T[capacity];
            for (int x = 0; x < top; x++)
                arr[x] = carry[x];
        }
        arr[top++] = item;
    }
    T Pop()
    {
        if (IsEmpty())
            cout << "stacks is empty" << endl;
        else
        {
            T carry = arr[top - 1];
            arr[top--] = '\0';
            return carry;
        }
    }
    void Show()
    {
        cout << "[";
        for (int x = 0; x < top; x++)
        {
            cout << arr[x];
            if (x != top - 1)
                cout << ",";
        }
        cout << "]" << endl;
    }
    string get()
    {
        if (IsEmpty())
            return "empty";
        else
        {
            string re = "";
            for (int x = 0; x < top; x++)
                re += arr[x];
            return re;
        }
    }
};
int icp(char in)
{ //out stock
    switch (in)
    {
    case '+':
        return 12;
    case '-':
        return 12;
    case '*':
        return 13;
    case '/':
        return 13;
    case '%':
        return 13;
    case '(':
        return 20;
    }
}
int isp(char in)
{ //in stock
    switch (in)
    {
    case '+':
        return 12;
    case '-':
        return 12;
    case '*':
        return 13;
    case '/':
        return 13;
    case '%':
        return 13;
    case '(':
        return 0;
    }
}
int main()
{
    string in, out = "";
    Stacks<char> stack;
    cout << "input:";
    cin >> in;
    for (int x = 0; x < in.length(); x++)
    {
        if (in[x] == ')')
        {
            while (true)
            {
                char carry = stack.Pop();
                if (carry == '(')
                    break;
                else
                    out += carry;
            }
        }
        else if (in[x] == '+' || in[x] == '-' || in[x] == '*' || in[x] == '/' || in[x] == '%' || in[x] == '(')
        {
            while (true)
            {
                if (icp(in[x]) <= isp(stack.Top()))
                    out += stack.Pop();
                else
                {
                    stack.Push(in[x]);
                    break;
                }
            }
        }
        else
            out += in[x];
    }
    if (!stack.IsEmpty())
    {
        int carry = stack.Size();
        for (int y = 0; y < carry; y++)
        {
            out += stack.Pop();
        }
    }
    cout << "output:" << out << endl;
    return 0;
}