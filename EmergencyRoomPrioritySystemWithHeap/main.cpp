#include <iostream>

using namespace std;

void simulatePatientArrival(Patient patients[], int size, MaxHeap& heap) {
    for (int i = 0; i < size; ++i) {
        cout << "Inserting: \n" << patients[i].name << endl;
        heap.insert(patients[i]);
        cout << "Heap: ";
        heap.printHeap();
    }
    cout << endl;
}

void treatPatients(MaxHeap& heap) {
    cout << "Treatment Order: " << endl;
    while (!heap.isEmpty()) {
        Patient p = heap.extractMax();
        cout << "Treating: " << p.name << endl;
    }
}

int main() {

    return 0;
}
