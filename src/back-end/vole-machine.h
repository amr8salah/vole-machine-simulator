#ifndef VOLE_MACHINE_SIMULATOR_SRC_BACK_END_VOLE_MACHINE_H
#define VOLE_MACHINE_SIMULATOR_SRC_BACK_END_VOLE_MACHINE_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <stdexcept>
#include <cstdlib>

using namespace std;

class Memory {
protected:
    vector<string> cells_;
    int size_;

public:
    Memory(int size = 256);

    vector<string> getCells();

    int getSize();

    string getCell(int address);

    void setCell(int address, string hex_value);

    void clear();

    void print();

    string &operator[](int address);
};

class Registers : public Memory {
public:
    Registers(int size = 16) : Memory(size) {
    };
    void print();
};

class ALU {
protected:
    bool is_halt_ = false;

    int baseToDec(string &base_num, int base);

    int hexToDec(string &hex_num);

    int hexToDec(char hex_num);

    int binToDec(string &bin_num);

    int binToDec(char bin_num);

    string decToHex(int dec_num);

    string decToBin(int dec_num);

    string hexToBin(string &hex_num);

    string binToHex(string &bin_num);

    void formatInstruction(string &input);

    // Operation code: 5
    void add(int register_address_1, int register_address_2);
};

class CU {
protected:
    // Operation code: 1
    void load(int register_address, int memory_address, Registers &registers, Memory &memory);

    // Operation code: 2
    void load(int register_address, string value, Registers &registers);

    // Operation code: 3
    void store(int register_address, int memory_address, Registers &registers, Memory &memory);

    // Operation code: 4
    void move(int register_address_1, int register_address_2);

    void jump(int register_address, int memory_address);

    void halt();
};

class CPU : ALU, CU {
private:
    int program_counter_ = 2;
    string instruction_register_ = "0000";
    Registers registers_;

    void fetch(Memory &memory);
    void decode(string instruction,Memory& memory);
    void execute(Memory &memory);

public:
    void runNextStep(Memory &memory);

    void setProgramCounter(int value);

    void reset();
    void outputState(Memory& memory);
};

class Machine {
private:
    CPU cpu_;
    Memory memory_;

public:
    void storeInstructions(vector<string> &instructions, int program_counter);

    void reset();

    void outputState();
};
class MainUI {
private:
    int choice_;
    vector<string> instructions_;

    void inputChoice(const char till);

    bool inputDecision();

    void loadFile();

    void formatInstruction(string &instruction);

    void menu1(Machine &machine);

    void menu2();

    void menu3();

    void menu4(Machine &machine);

    void menu5(Machine &machine);

public:
    void startProgram(Machine &machine);

    void exitProgram();
};

#endif // VOLE_MACHINE_SIMULATOR_SRC_BACK_END_VOLE_MACHINE_H
