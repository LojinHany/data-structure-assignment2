#include <iostream>
#include <string>
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

    string* binary=new string();
    cin >> *binary;
    for (char c : *binary) {
        if (c != '0' && c != '1') {
            cout << "Error: Input must be a binary number." << endl;
            return 1;
        }
    }
    int n=binary->length();
    int *arr=new int[n];
    arr[0]=binary->at(0) - '0';
    cout<<"arr= ["<< arr[0];
    for(int i=1;i<n;i++){
        arr[i]=binary->at(i) - '0';
        cout<<"," << arr[i];   
    }
    cout<<"]"<<endl;
    int k;
    cout<<"k= ";
    cin>>k;
    cout<<SegmentFlip(arr,n,k);
    delete[] arr;
    delete binary;
    return 0;

}