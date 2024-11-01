#ifndef VOLE_MACHINE_SIMULATOR_SRC_BACK_END_VOLE_MACHINE_H
#define VOLE_MACHINE_SIMULATOR_SRC_BACK_END_VOLE_MACHINE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <stdfloat>

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

class Registers : public Memory
{
public:
    Registers(int size = 16) : Memory(size) {};
};

class ALU
{
protected:
    double hexToDec(string hex_num);
    double binToDec(string bin_num);
    string decToHex(double dec_num);
    string decToBin(double dec_num);
    string hexToBin(string hex_num);
    string binToHex(string bin_num);

    bool isValid(string input);
    //Operation code: 5
    void add(int register_address_1, int register_address_2, Registers &rgstr);
};

class CU
{
protected:
    //Operation code: 1
    void load(int register_address, int memory_address, Registers &rgstr, Memory &memory);
    //Operation code: 2
    void load(int register_address, int value, Registers &rgstr);
    //Operation code: 3
    void store(int register_address, int memory_address, Registers &rgstr, Memory &memory);
    //Operation code: 4
    void move(int register_address_1, int register_address_2, Registers &rgstr);
    void jump(int register_address, int memory_address, Registers &rgstr, int &program_counter);
    void halt();

    void fetch(Memory &memory, int& program_counter);
    //vector<int> decode();
    //void execute(Registers &rgstr, Memory &memory, vector<int> instructions);
    //void runNextStep(Memory &memory);
};

class CPU : public ALU, public CU
{
private:
    int program_counter_=0;
    string instruction_register_;
    Registers registers_; 
};

class Machine
{
private:
    CPU cpu_;
    Memory memory_;

public:
    //void loadProgramFile();
    //void outputState();
};

#endif // VOLE_MACHINE_SIMULATOR_SRC_BACK_END_VOLE_MACHINE_H