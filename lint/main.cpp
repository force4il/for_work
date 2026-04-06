#include <iostream>
#include <cstring>

// valgrind --leak-check=full ./some

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
    
    Test(const Test& test) : Test(test.size_) 
    {}

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
    
    void print() {
        for (int i = 0; i < size_; i++) {
            cout << data_[i] << " ";
        }
        putchar('\n');
    }
    
    int getData(int ind) {
        if (ind < 0 || ind > size_) {
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
    Test buf1(5);
    cout << "buf1: ";
    buf1.print();
    
    Test buf2 = buf1; 
    cout << "buf2: ";
    buf2.print();
    
    cout << "After setData 999" << endl;
    buf1.setData(0, 999);
    cout << "buf1: ";
    buf1.print();
    cout << "buf2: ";
    buf2.print();
    
    Test buf3(2);
    buf3 = buf1;
    cout << "buf3: ";
    buf3.print();

    int n {0};
    cout << "Enter array size_: ";
    cin >> n;
    if (n <= 0) {
        cout << "SizeError" << endl;
        return -1;
    } else {
        Test buf4(n);
        buf4.print();
        cout << buf4.getData(n - 1) << endl;
    }

    cout << "End of programm" << endl; 

    return 0;
}