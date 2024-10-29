#ifndef VOLE_MACHINE_SIMULATOR_SRC_BACK_END_VOLE_MACHINE_H
#define VOLE_MACHINE_SIMULATOR_SRC_BACK_END_VOLE_MACHINE_H

#include <bits/stdc++.h>

using namespace std;

// Note to all: define constructors here before writing them in .cpp file
class Memory
{
protected:
    vector<string> cells_;
    int size_;

public:
    Memory(int size = 256);
    vector<string> getCells();
    int getSize();
    string getCell(int address);
    void setCell(int address, string value);
    void clear();
};

class Register : public Memory
{
public:
    Register(int size = 16) : Memory(size) {};
};

class ALU
{
public:
    int hexToDec(string hex_number);
    string decToHex(int dec_number);
    bool isValid(string input);
    void add(int idx_1, int idx_2, int idx_3, Register &rgstr);
};

class CU
{
public:
    void load(int register_label, int memory_address, Register &rgstr, Memory &memory);
    void load(int register_label, int value, Register &rgstr);
    void store(int register_label, int memory_address, Register &rgstr, Memory &memory);
    void move(int register_label_1, int register_label_2, Register &rgstr);
    void jump(int register_label, int memory_address, Register &rgstr, int &program_counter);
    void halt();
};

class CPU
{
private:
    int program_counter_;
    string instruction_register_;
    Register rgstr_;
    ALU alu_;
    CU cu_;

    void fetch(Memory &memory);
    vector<int> decode();
    // change name of decoded_thing
    void execute(Register &rgstr, Memory &memory, vector<int> decoded_thing);

public:
    void runNextStep(Memory &memory);
};

class Machine
{
private:
    CPU cpu_;
    Memory memory_;

public:
    void loadProgramFile();
    void outputState();
};

#endif // VOLE_MACHINE_SIMULATOR_SRC_BACK_END_VOLE_MACHINE_H