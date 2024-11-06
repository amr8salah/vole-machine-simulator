#include "vole-machine.h"

Memory::Memory(int size)
{
    if (size > 0)
    {
        cells_.resize(size, "00");
        size_ = size;
    }
    else
    {
        throw invalid_argument("Memory size should be bigger than 0");
    }
}
void Memory::setCell(int address, string hex_value)
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
            throw invalid_argument("Invalid hex_value in memory");
        }
    }
    else
    {
        throw invalid_argument("Invalid memory address");
    }
}
string Memory::getCell(int address)
{
    if (address >= 0 && address < size_)
    {
        return cells_[address];
    }
    else
    {
        throw invalid_argument("Invalid memory address");
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

string ALU::hexToBin(string& hex_num)
{
    double dec_num = hexToDec(hex_num);
    string bin_num = decToBin(dec_num);
    return bin_num;
}

void ALU::decode(string& instruction, string &instruction_register)
{
    instruction_register = instruction;
};
string ALU::formatInstruction(string& instruction)
{
    // If valid instruction returns formatted one else returns empty string

    if (regex_match(instruction, regex("(0x)?[0-9a-cA-C][0-9a-fA-f]{3}")))
        {
            if (instruction.size() == 6)
            {
                instruction = instruction.substr(2);
            }
            for (auto &c : instruction)
                c = toupper(c);
            if ((instruction[0] == '4' && instruction[1] != '0')||(instruction[0] == 'A' && instruction[2] != '0')||(instruction[0] == 'C' && (instruction[1] != '0' || instruction[2] != '0' || instruction[3] != '0')))
            {
                cerr<<"Invalid instruction format"<<endl;
                return "";
            }
            return instruction;
        }
        else
        {
            cerr<<"Invalid instruction format"<<endl;
            return "";
        }
};

int ALU::baseToDec(string &base_num, int base)
{
    if (base != 2 && base != 16)
    {
        throw invalid_argument("Unsupported base. Only base 2 and base 16 are supported.");
    }

    double dec_num = 0;
    int k = 1;

    for (int i = base_num.size() - 1; i >= 0; i--, k *= base)
    {
        char digit = base_num[i];

        if (base == 2 && (digit == '0' || digit == '1'))
        {
            dec_num += (digit - '0') * k;
        }
        else if (base == 16)
        {
            if ('0' <= digit && digit <= '9')
            {
                dec_num += (digit - '0') * k;
            }
            else if ('A' <= digit && digit <= 'F')
            {
                dec_num += (digit - 'A' + 10) * k;
            }
            else
            {
                throw invalid_argument("Invalid character in base-16 string.");
            }
        }
        else
        {
            throw invalid_argument("Invalid character in base-2 string.");
        }
    }
    return dec_num;
}

int ALU::hexToDec(string &hex_num)
{
    return baseToDec(hex_num, 16);
};
int ALU::hexToDec(char hex_num)
{
    string temp = {hex_num};
    return baseToDec(temp, 16);
};

int ALU::binToDec(string &bin_num)
{
    return baseToDec(bin_num, 2);
};
int ALU::binToDec(char bin_num)
{
    string temp = {bin_num};
    return baseToDec(temp, 2);
};

void CU::store(int register_address, int memory_address, Registers& registers, Memory &memory)
{
    memory.setCell(memory_address,registers.getCell(register_address));
}

void CPU::execute(Memory &memory)
{
    // if op-code = 1-> C do action
    if (instruction_register_[0] == '1')
    {
    }
    else if (instruction_register_[0] == '2')
    {
    }
    else if (instruction_register_[0] == '3')
    {
        int register_address = hexToDec(instruction_register_[1]);
        string hex_memory_address = instruction_register_.substr(2);
        int memory_address = hexToDec(hex_memory_address);
        store(register_address, memory_address, registers_, memory);
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
    program_counter_ = 2;
    instruction_register_ = "0000";
    registers_.clear();
};
