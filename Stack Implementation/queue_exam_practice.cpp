// output -> Momor antrian-i: nama
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Queue {
    vector<string> items;
public:
    bool isEmpty(){
        return items.empty();
    }

    void enqueue(string data){
        items.push_back(data);
        //cout << data << " masuk ke antrean.\n";
    }

    void dequeue(){
        if (isEmpty()){
            cout << "Queue kosong!\n";
            return;
        }
        cout << items.front() << " keluar dari antrean.\n";
        items.erase(items.begin());
    }

    void peek(){
        if (isEmpty()){
            cout << "Queue kosong!\n";
            return;
        }
        cout << "Data paling depan: " << items.front() << endl;
    }

    int size(){
        return items.size();
    }

    void clear(){
        items.clear();
        cout << "Antrean dikosongkan.\n";
    }

    void tampilkan(){
        for (int i = 0; i < items.size(); i++){
            cout << "Antrean ke-" << i+1 << " :" << items[i] << endl;
        }
        //cout << "Selesai!\n";
    }
};



int main(){
    Queue q;

    q.enqueue("rizal");
    q.enqueue("razib");
    q.enqueue("akmal");

    q.tampilkan();
    q.dequeue();
    q.tampilkan();
    q.size();

    return 0;
}
