#ifndef VOLE_MACHINE_SIMULATOR_SRC_BACK_END_VOLE_MACHINE_H
#define VOLE_MACHINE_SIMULATOR_SRC_BACK_END_VOLE_MACHINE_H

#include <bits/stdc++.h>

using namespace std;


// Note to all: define constructors here before writing them in .cpp file

/*Note for Amr: 
    Understand how the methods will work without taking parameters

    ALU methods and decode in cpu
*/
class Memory{
    private:
        string cells[256];
        int size = 256;
    public:
        string getCell(int address);
        void setCell(int address, string value);
};

class Register{
    private:
        int cells[16];
        int size = 16;
    public:
        int getCell(int address);
        void setCell(int address, int value);
};


class ALU{
    public:
        string hexToDec();
        string decToHex();
        bool isValid(string input);
        void add(int idx_1, int idx_2, int idx_3, Register& rgstr);
};

class CU{
    public:
        void load(int register_label, int memory_address, Register& rgstr, Memory& memory);
        void load(int register_label, int value, Register& rgstr);
        void store(int register_label, int memory_address, Register& rgstr, Memory& memory);
        void move(int register_label_1, int register_label_2, Register& rgstr);
        void jump(int register_label, int memory_address, Register& rgstr, int& program_counter);
        void halt();
};

class CPU{
    private:
        int program_counter;
        string instruction_register;
        Register rgstr;
        ALU alu;
        CU cu;

        void fetch(Memory& memory);
        vector<int> decode();
        //change name of decoded_thing
        void execute(Register& rgstr, Memory& memory, vector<int> decoded_thing);
    public:
        void runNextStep(Memory& memory);
};

class Machine{
    private:
        CPU processor;
        Memory memory;
    public:
        void loadProgramFile();
        void outputState();
};

#endif  // VOLE_MACHINE_SIMULATOR_SRC_BACK_END_VOLE_MACHINE_H