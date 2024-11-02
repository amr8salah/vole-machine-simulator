#include "vole-machine.h"

Memory::Memory(int size)
{
    try
    {
        if (size > 0)
        {
            cells_.resize(size, "00");
            size_ = size;
        }
        else
        {
            throw size;
        }
    }
    catch (...)
    {
        cerr << "Memory size should be bigger than 0" << endl;
    }
}
void Memory::setCell(int address, string hex_value)
{
    try
    {
        if (address >= 0 && address < size_)
        {
            if (regex_match(hex_value, regex("[0-9a-fA-f]{2}")))
            {
                for (auto &c : hex_value)
                    c = toupper(c);
                cells_[address] = hex_value;
            }
            else
            {
                throw 2;
            }
        }
        else
        {
            throw 1;
        }
    }
    catch (int e)
    {
        if (e == 1)
        {
            cerr << "Invalid memory address" << endl;
        }
        else if (e == 2)
        {
            cerr << "Invalid hex_value in memory" << endl;
        }
    }
}
string Memory::getCell(int address)
{
    try
    {
        if (address >= 0 && address < size_)
        {
            return cells_[address];
        }
        else
        {
            throw 1;
        }
    }
    catch (...)
    {
        cerr << "Invalid memory address" << endl;
        return "";
    }
}
int Memory::getSize()
{
    return size_;
}
vector<string> Memory::getCells()
{
    return cells_;
}
void Memory::clear()
{
    fill(cells_.begin(), cells_.end(), "00");
}

string ALU::hexToBin(string hex_num)
{
    double dec_num = hexToDec(hex_num);
    string bin_num = decToBin(dec_num);
    return bin_num;
}

void ALU::decode(string instruction, string &instruction_register)
{
    instruction_register = instruction;
};
string ALU::formatInstruction(string instruction)
{
    // If valid instruction returns formatted one else returns empty string

    try
    {
        if (regex_match(instruction, regex("(0x)?[0-9a-cA-C][0-9a-fA-f]{3}")))
        {
            if (instruction.size() == 6)
            {
                instruction = instruction.substr(2);
            }
            for (auto &c : instruction)
                c = toupper(c);
            if (instruction[0] == '4' && instruction[1] != '0')
            {
                throw 1;
            }
            else if (instruction[0] == 'A' && instruction[2] != '0')
            {
                throw 1;
            }
            else if (instruction[0] == 'C' && (instruction[1] != '0' || instruction[2] != '0' || instruction[3] != '0'))
            {
                throw 1;
            }

            return instruction;
        }
        else
        {
            throw 1;
        }
    }
    catch (...)
    {
        cerr << "Invalid instruction format" << endl;
        return "";
    }
};

void CPU::execute(Memory &memory)
{
    // if op-code = 1->C do action
    if (instruction_register_[0] == '1')
    {
    }
    else if (instruction_register_[0] == '2')
    {
    }
    else if (instruction_register_[0] == '3')
    {
    }
    else if (instruction_register_[0] == '4')
    {
    }
    else if (instruction_register_[0] == '5')
    {
    }
    else if (instruction_register_[0] == '6')
    {
    }
    else if (instruction_register_[0] == '7')
    {
    }
    else if (instruction_register_[0] == '8')
    {
    }
    else if (instruction_register_[0] == '9')
    {
    }
    else if (instruction_register_[0] == 'A')
    {
    }
    else if (instruction_register_[0] == 'B')
    {
    }
    else if (instruction_register_[0] == 'C')
    {
        halt();
    }
}

void CPU::fetch(Memory &memory)
{
    while (true)
    {
        string instruction = memory.getCell(program_counter_) + memory.getCell(program_counter_ + 1);
        int memory_size = memory.getSize();
        instruction = formatInstruction(instruction);
        if (instruction != "")
        {
            program_counter_ += 2;
            decode(instruction, instruction_register_);
            execute(memory);
            break;
        }
        else
        {
            program_counter_++;
            if (program_counter_ == (memory_size - 1))
            {

                // there is no more instructions or memory full
                // handle it
                //(eg., end program,...)

                cerr << "There is no instruction found in memory, program_counter exited" << endl;

                break;
            }
        }
    }
}

void CPU::reset()
{
    program_counter_ = 0;
    instruction_register_ = "0000";
    registers_.clear();
};
