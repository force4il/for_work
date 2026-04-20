#include <iostream>
#include <cstring>

// valgrind --leak-check=full ./exe
// cppcheck --suppress=misingIncludeSystem

using std::cout;
using std::endl;
using std::cin;

class Test {
private:
    int* data_;   
    int size_;      
    
public:
    Test(int n) : size_(n) {
        if (n <= 0) {
            cout << "Size error" << endl;
        } else {
            data_ = new int[n];
            for (int i = 0; i < n; i++){
                data_[i] = i * 10;
            }
        }
    }
    
    Test(const Test& test) : size_(test.size_) {
        data_ = new int[size_];

        if (test.data_) {
            for (int i = 0; i < size_; i++) {
                data_[i] = test.data_[i];
            }
        }
    }

    ~Test() {
        delete[] data_; 
    }
    
    Test& operator=(const Test& test) {
        if (this == &test) return *this;
        
        delete[] data_; 
        
        size_ = test.size_;
        data_ = new int[size_];
        for (int i = 0; i < size_; i++) {
            data_[i] = test.data_[i];
        }
    
        return *this;
    }
    
    int pop(int ind) {
        if (ind < 0 || ind >= size_) {
            cout << "Index error" << endl;
            return -1;
        }

        int val = data_[ind];
        for (int i = ind; i < size_ - 1; i++) {
            data_[i] = data_[i + 1];
        }

        size_--;
        return val;
    }

    void print() {
        for (int i = 0; i < size_; i++) {
            cout << data_[i] << " ";
        }
        putchar('\n');
    }
    
    int getData(int ind) {
        if (ind < 0 || ind >= size_) {
            cout << "Index error" << endl;
            return -1;
        } 

        return data_[ind];
    }

    void setData(int index, int value) {
        if (index >= 0 && index < size_) {
            data_[index] = value;
        } else {
            cout << "IndexError" << endl;
        }
    }
};

int main() {
    int n {0};
    cout << "Enter array size: ";
    cin >> n;

    if (n <= 0) {
        cout << "SizeError" << endl;
        return -1;
    } else {
        Test buf(n);
        buf.print();
        buf.pop(2);
        buf.print();
        buf.setData(n - 1, 40);
        cout << buf.getData(n - 1) << endl;
    }
    // int arr[2];
    // cout << arr[3] << endl; //ошибка индексации 

    // int* ptr = nullptr; //обращение к нулевому указтелю
    // cout << *ptr << endl;

    cout << "End of programm" << endl; 

    return 0;
}