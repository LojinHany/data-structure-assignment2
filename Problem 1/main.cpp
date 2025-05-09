//Problem 1
#include <iostream>
#include <fstream>
using namespace std;
class Stack{
private:
    int top;
    int capacity;
    string* stackArr;

public:
    Stack(): top(-1), capacity(4), stackArr(new string[capacity]){}

    void resize() {
        capacity *= 2;
        string* newStack = new string[capacity];
        for (int i=0; i<=top; ++i) {
            newStack[i] = stackArr[i];
        }
        delete[] stackArr;
        stackArr = newStack;
    }

    ~Stack(){
        delete[] stackArr;
    }

    bool isEmpty(){
        return(top==-1)?true: false;
    }

    bool isFull(){
        return (top==capacity-1)?true: false;
    }

    void push(string &value){
        if(isFull())resize();
        top++;
        stackArr[top]=value;
    }

    string pop(){
        if(isEmpty()){
            cout<<"Stack underflow"<<endl;
            return "";
        }
        string popValue = stackArr[top];
        stackArr[top]="";
        top--;
        return popValue;
    }

     void clear(){top = -1;}

     string peek(){
         if(isEmpty()){
            cout<<"Stack underflow"<<endl;
            return "";
         }
         return stackArr[top];
     }

     int count(){return (top+1);}

     void display(){
         cout<<"[";
         for(int i= 0; i<=top; ++i){
            cout<<stackArr[i];
            if(i<top)cout<<", ";
         }
         cout<<"]"<<endl;
     }
};

class BrowserHistroy{
private:
    Stack backStack;
    Stack forwardStack;
    string currentUrl;
public:
    void visit(string url){
        forwardStack.clear();
        currentUrl=url;
        backStack.push(currentUrl);
    }

    string goBack(){
        if(backStack.count()==1){
            cout<<"No URL to return back to"<<endl;
            return currentUrl;
        }
        forwardStack.push(currentUrl);
        backStack.pop();
         if (!backStack.isEmpty()) {
            currentUrl = backStack.peek();
        } else {
            currentUrl = "";
        }
        return currentUrl;
    }

    string goForward(){
        if(forwardStack.isEmpty()){
            cout<<"No more URLs to visit"<<endl;
            return currentUrl;
        }
        currentUrl=forwardStack.peek();
        backStack.push(currentUrl);
        forwardStack.pop();

        return currentUrl;
    }

    void displayAll(){
        cout<<"BackStack: ";
        backStack.display();
        cout<<"ForwardStack: ";
        forwardStack.display();
        cout<<"Current URL: "<<currentUrl<<endl;
    }
    void reset(){
        backStack.clear();
        forwardStack.clear();
        currentUrl="";
    }
};

int main()
{
    BrowserHistroy browser;
    while (true) {
        cout << "\n\t\t\t***Browser History***\n1- File Input \n2- Manual Testing\n3- Exit\nEnter your choice (1-3): ";
        string option;
        cin>>option;
        if (option == "1") {
            ifstream file("input.txt");
            string line;
            while (getline(file, line)) {

                if (line.empty()) continue;
                if (line.find("Test Case") != string::npos) {
                    cout << "\n=== " << line << " ===" << endl;
                    browser.reset();
                    continue;
                }

                if (line.find("visit(") == 0) {
                    size_t startPos = line.find("\"") + 1;
                    size_t endPos = line.find_last_of("\"");
                    if (startPos != string::npos && endPos != string::npos && startPos < endPos) {
                        string url = line.substr(startPos, endPos - startPos);
                        browser.visit(url);
                        cout << "\n--Visited: " << url << endl;
                    }
                } else if (line == "goBack()") {
                    browser.goBack();
                    cout << "\n--GoBack" << endl;
                } else if (line == "goForward()") {
                    browser.goForward();
                    cout << "\n--GoForward" << endl;
                }
                browser.displayAll();
            }
            file.close();

        } else if (option == "2") {
            while (true) {
                cout << "\n1- Visit URL\n2- Go Back\n3- Go Forward\n4- Exit\nEnter your choice (1-4): ";
                cin >> option;
                cin.ignore();

                if (option== "1") {
                    cout << "Enter URL: ";
                    string URL;
                    getline(cin, URL);
                    cout << "Visit: "<<URL<<endl;
                    browser.visit(URL);
                    browser.displayAll();

                } else if (option== "2") {
                    cout <<"GoBack"<< endl;
                    browser.goBack();
                    browser.displayAll();

                } else if (option== "3") {
                    cout << "GoForward" << endl;
                    browser.goForward();
                    browser.displayAll();

                } else if (option == "4") {
                     browser.reset();
                    cout<<"Program Exited"<<endl;
                    break;

                } else {
                    cout << "Invalid! Please enter a valid choice (1-4)\n"<<endl;
                }
            }
        }else if (option== "3") {
            cout << "Program Exited"<<endl;;
            break;
        } else {
            cout << "Invalid! Please enter a valid choice (1-3)\n";
        }
    }

    return 0;
}
