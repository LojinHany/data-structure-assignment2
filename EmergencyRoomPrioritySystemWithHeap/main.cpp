#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int Max_Patients = 1000;

struct Patient {
    string name;
    int severity;
    int arrival_time;

    Patient(string n, int s, int a) : name(n), severity(s), arrival_time(a) {}

    Patient() : name("None"), severity(-1), arrival_time(-1) {}
};

bool Higher_Priority(const Patient &a, const Patient &b) {
    if (a.severity > b.severity) {
        return true;
    } else if (a.severity < b.severity) {
        return false;
    } else {
        return a.arrival_time < b.arrival_time;
    }
}

class Max_Heap {
private:
    Patient heap[Max_Patients];
    int size;

    void HeapUp(int index) {
        int parent = (index - 1) / 2;
        if (index > 0 && Higher_Priority(heap[index], heap[parent])) {
            swap(heap[index], heap[parent]);
            HeapUp(parent);
        }
    }

    void Heap_Down(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size && Higher_Priority(heap[left], heap[largest]))
            largest = left;
        if (right < size && Higher_Priority(heap[right], heap[largest]))
            largest = right;

        if (largest != index) {
            swap(heap[index], heap[largest]);
            Heap_Down(largest);
        }
    }

public:
    Max_Heap() : size(0) {}

    void insert(const Patient &patient) {
        if (size >= Max_Patients) {
            cout << "Heap is full, more patients cannot be inserted." << endl;
            return;
        }
        heap[size] = patient;
        HeapUp(size);
        size++;
    }

    Patient Extract_Max() {
        if (size == 0) {
            return Patient();
        }
        Patient Max_Patient = heap[0];
        heap[0] = heap[size - 1];
        size--;
        Heap_Down(0);
        return Max_Patient;
    }

    bool Is_Empty() const {
        return size == 0;
    }

    void Print_Heap() const {
        cout << "[ ";
        for (int i = 0; i < size; ++i)
            cout << heap[i].name << " ";
        cout << "]" << endl;
    }

    void Print_Treated() const {
        for (int i = 0; i < size; ++i)
            cout << i + 1 << "\t  " << heap[i].name << endl;
        cout << endl;
    }
};

int main() {
    Max_Heap Hospital_Queue;
    ifstream infile("patients.txt");

    if (!infile.is_open()) {
        cerr << "Error: Could not open file 'patients.txt'" << endl;
        return 1;
    }
    string name;
    int severity, arrival_time;

    cout << " Heap After Insertion: " << endl;
    cout << "Step \t" << "Inserted \t" << "Heap" << endl;

    int count = 1;
    while (infile >> name >> severity >> arrival_time) {
        Patient p(name, severity, arrival_time);
        cout << left << setw(8) << count << setw(17) << name;
        Hospital_Queue.insert(p);
        Hospital_Queue.Print_Heap();
        count++;
    }


    cout << "\n Treatment Order: " << endl;
    cout << "Order \t" << "Treated Patient" << endl;
    Hospital_Queue.Print_Treated();

    infile.close();
    cout << " Patients in order of treatment priority:" << endl;
    while (!Hospital_Queue.Is_Empty()) {
        Patient next = Hospital_Queue.Extract_Max();
        cout << "Name: " << next.name << ", Severity: " << next.severity << ", Arrival: " << next.arrival_time << endl;
    }

}
