#pragma once
#include <stdint.h>
#include <deque>
#include <vector>
struct SerialFake {
    std::deque<int> input;
    unsigned long baud = 0;
    int reads = 0;
    void begin(unsigned long value) { baud = value; }
    int available() const { return static_cast<int>(input.size()); }
    int read() { ++reads; if (input.empty()) return -1; int v=input.front(); input.pop_front(); return v; }
};
extern SerialFake Serial;
extern std::vector<unsigned long> delays;
inline void delay(unsigned long ms) { delays.push_back(ms); }
