#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
struct sweets
{
    string Name;
    int cost;
    int kcal;
    int fats;
};
struct MyStack
{
    struct Node
    {
        sweets data;
        Node* prev;
    };
    Node* Top = NULL;
    int Count = 0;
    bool Push(sweets);
    bool Pop(sweets&);
    void Info();
};
bool MyStack::Push(sweets dt)
{
    if (!Top)
    {
        Top = new Node;
        Top->prev = NULL;
        Count = 1;
    }
    else
    {
        Node* temp;
        temp = new Node;
        temp->prev = Top;
        Top = temp;
        Count++;
    }
    Top->data = dt;
    return true;
}
bool MyStack::Pop(sweets& dt)
{
    if (!Top) return false;
    Node* temp = Top->prev;
    dt = Top->data;
    delete Top;
    Top = temp;
    Count--;
    return true;
}
void MyStack::Info()
{
    if (!Top) cout << "Stack is empty" << endl;
    else
    {
        cout << endl << "Info stack's: " << endl;
        cout << "\tStack size = " << Count << endl;
        cout << "\tName = " << Top->data.Name << endl;
        cout << "\tcost = " << Top->data.cost << endl;
        cout << "\tkcal = " << Top->data.kcal << endl;
        cout << "\tfats = " << Top->data.fats << endl << endl;
    }
}
void print(MyStack& S, MyStack& V)
{
    sweets dt;
    while (S.Count)
    {
        S.Pop(dt);
        cout << "\Name = " << dt.Name << endl;
        cout << "\cost = " << dt.cost << endl;
        cout << "\tkcal = " << dt.kcal << endl;
        cout << "\tfats = " << dt.fats << endl << endl;
        V.Push(dt);
    }
    while (V.Count)
    {
        V.Pop(dt);
        S.Push(dt);
    }
}
int main()
{
    MyStack S;
    MyStack V;
    sweets dt;
    ifstream file("sweets.txt");
    string line;
    while (getline(file, line))
    {
        istringstream line_F(line);
        line_F >> dt.Name >> dt.cost >> dt.kcal >> dt.fats;
        S.Push(dt);
    }
    file.close();
    int m = 1;
    while (m)
    {
        S.Info();
        cout << "1) add product to basket" << endl;
        cout << "2) pull item from the basket" << endl;
        cout << "3) clear the basket" << endl;
        cout << "4) show basket contents" << endl;
        cout << "0) exit" << endl;
        cin >> m;
        switch (m)
        {
        case 1:
        {
            system("cls");
            cout << "Enter product specifications:" << endl;
            cout << "Name = "; cin >> dt.Name;
            cout << "cost = "; cin >> dt.cost;
            cout << "kcal = "; cin >> dt.kcal;
            cout << "fats = "; cin >> dt.fats;
            S.Push(dt);
            system("cls");
            break;
        }
        case 2:
        {
            system("cls");
            sweets dt_x;
            bool metka = false;
            cout << "Enter product specifications:" << endl;
            cout << "Name = "; cin >> dt_x.Name;
            cout << "cost = "; cin >> dt_x.cost;
            cout << "kcal = "; cin >> dt_x.kcal;
            cout << "fats = "; cin >> dt_x.fats;
            while (S.Count)
            {
                S.Pop(dt);
                if (dt.Name != dt_x.Name || dt.cost != dt_x.cost || dt.kcal != dt_x.kcal || dt.fats != dt_x.fats)
                {
                    V.Push(dt);
                }
                else
                {
                    metka = true;
                    break;
                }
            }
            if (!metka) cout << "Product not found" << endl;
            while (V.Count)
            {
                V.Pop(dt);
                S.Push(dt);
            }
            system("pause");
            system("cls");
            break;
        }
        case 3:
        {
            system("cls");
            while (S.Count)
            {
                S.Pop(dt);
            }
            break;
        }
        case 4:
        {
            system("cls");
            print(S, V);
            system("pause");
            system("cls");
            break;
        }
        }
    }
}