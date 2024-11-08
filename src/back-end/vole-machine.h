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
    void addTwoComplement(int register_address_1, int register_address_2, int register_address_3, Registers &registers);
    // Operation code: 6
    void addFloat(int register_address_1, int register_address_2, int register_address_3, Registers &registers);
    // Operation code: 7
    void OR(int register_address_1, int register_address_2, int register_address_3, Registers &registers);
    // Operation code: 8
    void AND(int register_address_1, int register_address_2, int register_address_3, Registers &registers);
    // Operation code: 9
    void XOR(int register_address_1, int register_address_2, int register_address_3, Registers &registers);
    // Operation code: A
    void rotate(int register_address, int times, Registers &registers);
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
    void move(int register_address_1, int register_address_2, Registers &registers);

    // Operation code: B
    void jump(int register_address, int memory_address, int& program_counter);

    // Operation code: C
    void halt();
};

class CPU : ALU, CU {
private:
    int program_counter_ = 2;
    int halt_position_ = 2;

    string instruction_register_ = "0000";
    Registers registers_;

    void fetch(Memory &memory);
    void decode(Memory& memory);
    void execute(Memory &memory);

public:
    bool is_halt_ = false;

    void oneStep(Memory &memory);

    void setProgramCounter(int value);
    void setHaltPosition(int value);

    void reset();
    void outputState(Memory& memory);
};

class Machine {
private:
    CPU cpu_;
    Memory memory_;

public:
    void storeInput(vector<string> &instructions, int program_counter);

    void runOneStep(bool &is_halt); //return true is halt

    void runUntilHalt();

    void resetCPU();

    void clearMemory();

    void reset();

    void outputState();
};
class MainUI {
private:
    int choice_;
    vector<string> user_instructions_;

    void inputChoice(char till);

    bool inputDecision();

    void loadFile();

    void formatInput(string &instruction);

    void menu1(Machine &machine);

    void menu2();

    void menu3();

    void menu4(Machine &machine);

    void menu5(Machine &machine);

    void menu6(Machine &machine);

public:
    void startProgram(Machine &machine);

    void exitProgram();
};

#endif // VOLE_MACHINE_SIMULATOR_SRC_BACK_END_VOLE_MACHINE_H
