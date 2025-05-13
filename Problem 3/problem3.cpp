#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int SegmentFlip(int *arr,int n,int k) {
    int count=0;
    int i=0;
    while(n>0){
        int Subcount=0;
        if(arr[i]== 0){
            count++;
            if(k>n){
                return -1;
            }
            for(int j=i;j<i+k;j++){
                if(arr[j]==0){
                    arr[j]=1;
                    
                }else{
                    arr[j]=0;
                    Subcount++;
                }
            }
            i+=(k-Subcount);
            n-=(k-Subcount);
        }else{
            i+=1;
            n-=1;
        }
       
    }
    return count;
}

int main() {
    cout<<"example 1:\n";
    
    ifstream file("example1.txt");
    if (!file) {
        cout << "Error opening file!" << endl;
        return 1;
    }
    string* binary=new string();
    getline(file, *binary);  // Read the entire line from file
    for (char c : *binary) {
        if (c != '0' && c != '1') {
            cout << "Error: Input must be a binary number." << endl;
            return 1;
        }
    }
    int n=binary->length();
    int *arr1=new int[n];
    arr1[0]=binary->at(0) - '0';
    cout<<"arr= ["<< arr1[0];
    for(int i=1;i<n;i++){
        arr1[i]=binary->at(i) - '0';
        cout<<"," << arr1[i];   
    }
    cout<<"]"<<endl;
    int k;
    file>>k;
    file.ignore(); // Ignore the newline character after reading k
    cout<<"k= "<<k<<endl;

    cout<<SegmentFlip(arr1,n,k);
    delete[] arr1;
    delete binary;

    cout<<endl;

    cout<<"\nexample 2:\n";
    binary=new string();
    getline(file, *binary);  // Read the entire line from file

    for (char c : *binary) {
        if (c != '0' && c != '1') {
            cout << "Error: Input must be a binary number." << endl;
            return 1;
        }
    }
    n=binary->length();
    int *arr2=new int[n];
    arr2[0]=binary->at(0) - '0';
    cout<<"arr= ["<< arr2[0];
    for(int i=1;i<n;i++){
        arr2[i]=binary->at(i) - '0';
        cout<<"," << arr2[i];   
    }
    cout<<"]"<<endl;
    file>>k;
    file.ignore(); // Ignore the newline character after reading k

    cout<<"k= "<<k<<endl;
    
    cout<<SegmentFlip(arr2,n,k);
    delete[] arr2;
    delete binary;

    cout<<endl;
    
    cout<<"\nexample 3:\n";
    binary=new string();
    
    getline(file, *binary);  // Read the entire line from file

    for (char c : *binary) {
        if (c != '0' && c != '1') {
            cout << "Error: Input must be a binary number." << endl;
            return 1;
        }
    }
    n=binary->length();
    int *arr3=new int[n];
    arr3[0]=binary->at(0) - '0';
    cout<<"arr= ["<< arr3[0];
    for(int i=1;i<n;i++){
        arr3[i]=binary->at(i) - '0';
        cout<<"," << arr3[i];   
    }
    cout<<"]"<<endl;
    cout<<"k= ";
    file>>k;
    file.ignore(); // Ignore the newline character after reading k

    cout<<SegmentFlip(arr3,n,k);
    delete[] arr3;
    delete binary;
    return 0;

}