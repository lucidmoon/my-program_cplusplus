// Stack implementation using vector
// Praktikum 2 - Struktur Data
// created: 22 oct 2026
#include <iostream>
#include <vector>
using namespace std;

class Stack
{
    vector<int> items;
public:
    void push(int data)
    {
        items.push_back(data);
        cout << "Data masuk: " << data << endl;
    }
    int pop()
    {
        if (isEmpty())
        {
            cout << "Stack kosong, tidak bisa pop!" << endl;
            return -1; // Return -1 to indicate stack is empty  
        }
        int data = items.back();
        items.pop_back();
        cout << "Data keluar: " << data << endl;
        return data;
    }
    int top()
    {
        if (isEmpty())
        {
            cout << "Stack kosong, tidak ada top!" << endl;
            return -1; // Return -1 to indicate stack is empty
        }
        return items.back();
    }

    bool isEmpty()
    {
        return items.empty();
    }

    int size()
    {
        //return items.size();
        return static_cast<int>(items.size());
    }

    void clear()
    {
        items.clear();
        cout << "Stack dikosongkan." << endl;
    }

    void tampilkan()
    {
        cout << "Isi Stack (bawah -> atas): [";

        for (size_t i = 0; i < items.size(); i++)
        {
            cout << items[i];

            if(i + 1 < items.size())
            {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
};

int main(){
    Stack s;

    s.push(300);
    s.push(500);
    s.push(100);
    s.push(200);
    s.push(400);

    s.tampilkan();

    cout << "Top: " << s.top() << endl;
    cout << "Jumlah elemen: " << s.size() << endl;

    cout << "Apakah kosong? " << (s.isEmpty() ? "true" : "false") << endl;

    return 0;
}