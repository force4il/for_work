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
        data_ = new int[n];
        for (int i = 0; i < n; i++){
            data_[i] = i * 10;
        }
    }
    
    Test(const Test& test) : size_(test.size_) {
        data_ = new int[size_];
        for (int i = 0; i < size_; i++) {
            data_[i] = test.data_[i];
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
    
    void getData() {
        for (int i = 0; i < size_; i++) {
            cout << data_[i] << " ";
        }
        putchar('\n');
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
    buf1.getData();
    
    Test buf2 = buf1; 
    cout << "buf2: ";
    buf2.getData();
    
    cout << "After setData 999" << endl;
    buf1.setData(0, 999);
    cout << "buf1: ";
    buf1.getData();
    cout << "buf2: ";
    buf2.getData();
    
    Test buf3(2);
    buf3 = buf1;
    cout << "buf3: ";
    buf3.getData();

    int n {0};
    cout << "Enter array size_: ";
    cin >> n;
    if (n <= 0) {
        cout << "SizeError" << endl;
        return -1;
    } else {
        Test buf4(n);
        buf4.getData();
    }

    cout << "End of programm" << endl; 

    return 0;
}