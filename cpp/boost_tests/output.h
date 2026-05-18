#ifndef OUTPUT
#define OUTPUT

#include <sstream>
#include <iostream>

class OutputCapture {
    std::streambuf* old_cout;
    std::stringstream buffer;

public:
    OutputCapture() : old_cout(std::cout.rdbuf(buffer.rdbuf())) {}
    ~OutputCapture() { std::cout.rdbuf(old_cout); }
    std::string get_output() const { return buffer.str(); }
};

#endif