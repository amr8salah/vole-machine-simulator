#ifndef VOLE_MACHINE_SIMULATOR_SRC_BACK_END_VOLE_MACHINE_H
#define VOLE_MACHINE_SIMULATOR_SRC_BACK_END_VOLE_MACHINE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

class Memory
{
private:
    vector<string> cells_;
    int size_;

public:
    Memory(int size = 256);
    vector<string> getCells();
    int getSize();
    string getCell(int address);
    void setCell(int address, string hex_value);
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

    string formatInstruction(string input);
    void decode(string instruction, string& instruction_register);

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

    //void runNextStep(Memory &memory);
};

class CPU : ALU, CU
{
private:
    int program_counter_=0;
    string instruction_register_="0000";
    Registers registers_;
public:
    void fetch(Memory &memory);
    void execute(Memory &memory);
    void reset();
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