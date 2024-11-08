#include "vole-machine.h"

Memory::Memory(int size) {
    if (size > 0) {
        cells_.resize(size, "00");
        size_ = size;
    } else {
        throw invalid_argument("Memory size should be bigger than 0");
    }
}

void Memory::setCell(int address, string hex_value) {
    if (address >= 0 && address < size_) {
        if (regex_match(hex_value, regex("[0-9a-fA-F]{2}"))) {
            for (auto &c: hex_value)
                c = toupper(c);
            cells_[address] = hex_value;
        } else {
            throw invalid_argument("Invalid hex_value in memory");
        }
    } else {
        throw invalid_argument("Invalid memory address");
    }
}

string Memory::getCell(int address) {
    if (address >= 0 && address < size_) {
        return cells_[address];
    } else {
        throw invalid_argument("Invalid memory address");
    }
}

int Memory::getSize() {
    return size_;
}

vector<string> Memory::getCells() {
    return cells_;
}

void Memory::clear() {
    fill(cells_.begin(), cells_.end(), "00");
}

string &Memory::operator[](int address) {
    return cells_[address];
}

void Memory::print() {
    cout << "      ";
    for (int i = 0; i < 16; i++) {
        cout << "0";
        if (i < 10)
            cout << i;
        else {
            cout << char(i + 55);
        }
        cout << " ";
    }
    cout << endl;
    cout << "    " << string(53, '-') << endl;
    for (int i = 0; i < 16; i++) {
        cout << "0x";
        if (i < 10)
            cout << i;
        else {
            cout << char(i + 55);
        }
        cout << "0";
        cout << "| ";
        for (int j = i*16; j < (i*16+16); j++) {
            cout << cells_[j] << " ";
        }
        cout << endl;
    }
    cout << "    " << string(53, '-') << endl;
}

void Registers::print() {
    cout << string(41, '-') << endl; //10*(size_/columns)+1
    for (int register_address = 0; register_address < 16; register_address++) {
        string str_address = "00";
        if (register_address < 10)
            str_address[1] += register_address;
        else {
            str_address[0] = '1';
            str_address[2] += register_address / 10;
        }
        cout << "| R" << str_address << ": " << cells_[register_address] << " ";

        if ((register_address + 1) % 4 == 0) cout << "|" << endl;
    }
    cout << string(41, '-') << endl; //10*(size_/columns)+1
}

void ALU::formatInstruction(string &instruction) {
    // If valid instruction returns formatted one else returns empty string

    if (regex_match(instruction, regex("(0x)?[1-9a-cA-C][0-9a-fA-F]{3}"))) {
        if (instruction.size() == 6) {
            instruction = instruction.substr(2);
        }
        for (auto &c: instruction)
            c = toupper(c);
        if ((instruction[0] == '4' && instruction[1] != '0') || (instruction[0] == 'A' && instruction[2] != '0') ||
            (instruction[0] == 'C' && (instruction[1] != '0' || instruction[2] != '0' || instruction[3] != '0'))) {
            instruction = "";
        }
    } else {
        instruction = "";
    }
}

void ALU::addTwoComplement(int register_address_1, int register_address_2, int register_address_3,
    Registers &registers) {

}

void ALU::addFloat(int register_address_1, int register_address_2, int register_address_3, Registers &registers) {
}

void ALU::OR(int register_address_1, int register_address_2, int register_address_3, Registers &registers) {
}

void ALU::AND(int register_address_1, int register_address_2, int register_address_3, Registers &registers) {
}

void ALU::XOR(int register_address_1, int register_address_2, int register_address_3, Registers &registers) {
}

void ALU::rotate(int register_address, int times, Registers &registers) {
}

int ALU::baseToDec(string &base_num, int base) {
    if (base != 2 && base != 16) {
        throw invalid_argument("Unsupported base. Only base 2 and base 16 are supported.");
    }

    double dec_num = 0;
    int k = 1;

    for (int i = base_num.size() - 1; i >= 0; i--, k *= base) {
        char digit = base_num[i];

        if (base == 2 && (digit == '0' || digit == '1')) {
            dec_num += (digit - '0') * k;
        } else if (base == 16) {
            if ('0' <= digit && digit <= '9') {
                dec_num += (digit - '0') * k;
            } else if ('A' <= digit && digit <= 'F') {
                dec_num += (digit - 'A' + 10) * k;
            } else {
                throw invalid_argument("Invalid character in base-16 string.");
            }
        } else {
            throw invalid_argument("Invalid character in base-2 string.");
        }
    }
    return dec_num;
}

int ALU::hexToDec(string &hex_num) {
    return baseToDec(hex_num, 16);
}

int ALU::hexToDec(char hex_num) {
    string temp = {hex_num};
    return baseToDec(temp, 16);
}

string ALU::hexToBin(string &hex_num) {
    int dec_num = hexToDec(hex_num);
    string bin_num = decToBin(dec_num);
    return bin_num;
}

string ALU::binToHex(string &bin_num) {
    int dec_num = binToDec(bin_num);
    string hex_num = decToHex(dec_num);
    return hex_num;
}

int ALU::binToDec(string &bin_num) {
    return baseToDec(bin_num, 2);
}

int ALU::binToDec(char bin_num) {
    string temp = {bin_num};
    return baseToDec(temp, 2);
}

string ALU::decToHex(int dec_num) {
    string hex_num = "";
    while (dec_num) {
        int remainder = dec_num % 16;
        char hex_digit;

        if (remainder < 10) {
            hex_digit = remainder + 48; // 48 = '0'
        } else {
            hex_digit = remainder + 55; // 55 = 'A'-10
        }
        hex_num += hex_digit;
        dec_num /= 16;
    }
    // reversing the hex_num to get the final result
    for (int i = 0, j = hex_num.size() - 1; i <= j; i++, j--) {
        swap(hex_num[i], hex_num[j]);
    }
    return hex_num;
}

string ALU::decToBin(int dec_num) {
    string bin_num = "";
    while (dec_num) {
        int remainder = dec_num % 2;
        char bin_digit;
        bin_digit = remainder + 48; // 48 = '0'

        bin_num += bin_digit;

        dec_num /= 2;
    }
    // reversing the bin_num to get the final result
    for (int i = 0, j = bin_num.size() - 1; i <= j; i++, j--) {
        swap(bin_num[i], bin_num[j]);
    }
    return bin_num;
}


void CU::store(int register_address, int memory_address, Registers &registers, Memory &memory) {
    memory[memory_address] = registers[register_address];
    if (memory_address == 0) {
        cout << memory[memory_address] << endl;
    }
}

void CU::move(int register_address_1, int register_address_2, Registers &registers) {
}

void CU::jump(int register_address, int memory_address, int &program_counter) {
}

void CU::load(int register_address, int memory_address, Registers &registers, Memory &memory) {
    registers[register_address] = memory[memory_address];
}

void CU::load(int register_address, string value, Registers &registers) {
    registers[register_address] = value;
}

void CU::halt() {

}


void CPU::execute(Memory &memory) {
    // if op-code = 1-> C do action
    if (instruction_register_[0] == '1') {
        int register_address = hexToDec(instruction_register_[1]);
        string hex_memory_address = instruction_register_.substr(2);
        int memory_address = hexToDec(hex_memory_address);

        load(register_address, memory_address, registers_, memory);
    } else if (instruction_register_[0] == '2') {
        int register_address = hexToDec(instruction_register_[1]);
        string value = instruction_register_.substr(2);

        load(register_address, value, registers_);
    } else if (instruction_register_[0] == '3') {
        int register_address = hexToDec(instruction_register_[1]);
        string hex_memory_address = instruction_register_.substr(2);
        int memory_address = hexToDec(hex_memory_address);

        store(register_address, memory_address, registers_, memory);
    } else if (instruction_register_[0] == '4') {
        int register_address_1 = hexToDec(instruction_register_[2]);
        int register_address_2 = hexToDec(instruction_register_[3]);
        move(register_address_1, register_address_2, registers_);
    } else if (instruction_register_[0] >= '6' && instruction_register_[0] <= '9') {
        int register_address_1 = hexToDec(instruction_register_[1]);
        int register_address_2 = hexToDec(instruction_register_[2]);
        int register_address_3 = hexToDec(instruction_register_[3]);
        if (instruction_register_[0] == '5') {
            addTwoComplement(register_address_1, register_address_2, register_address_3, registers_);
        } else if (instruction_register_[0] == '6') {
            addFloat(register_address_1, register_address_2, register_address_3, registers_);
        } else if (instruction_register_[0] == '7') {
            OR(register_address_1, register_address_2, register_address_3, registers_);
        } else if (instruction_register_[0] == '8') {
            AND(register_address_1, register_address_2, register_address_3, registers_);
        } else if (instruction_register_[0] == '9') {
            XOR(register_address_1, register_address_2, register_address_3, registers_);
        }
    } else if (instruction_register_[0] == 'A') {
        int register_address = hexToDec(instruction_register_[1]);
        int x_times = hexToDec(instruction_register_[3]);
        rotate(register_address, x_times, registers_);
    } else if (instruction_register_[0] == 'B') {
        int register_address = hexToDec(instruction_register_[1]);
        string hex_memory_address = instruction_register_.substr(2);
        int memory_address = hexToDec(hex_memory_address);

        jump(register_address, memory_address, program_counter_);
    } else if (instruction_register_[0] == 'C') {
        halt();
    }
}

void CPU::fetch(Memory &memory) {
    string instruction = memory[program_counter_] + memory[program_counter_ + 1];
    // Merges data in memory[pc] and memory[pc+1]
    instruction_register_ = instruction;
}

void CPU::decode(Memory &memory) {
    string instruction = instruction_register_;
    formatInstruction(
        instruction); // Checks instruction validity

    // If valid instruction
    if (!instruction.empty()) {
        execute(memory);
    }
    // If not valid instruction
    else {
        cout << "Invalid instruction" << endl;
    }
}

void CPU::oneStep(Memory &memory) {
    if (program_counter_ < halt_position_) {
        fetch(memory);
        program_counter_ += 2;
        decode(memory);
    } else {
        is_halt_=true;
    }
}

void CPU::reset() {
    program_counter_ = 2;
    halt_position_ = 2;
    is_halt_ = false;
    instruction_register_ = "0000";
    registers_.clear();
}

void CPU::setProgramCounter(int value) {
    program_counter_ = value;
}

void CPU::setHaltPosition(int value) {
    halt_position_ = value;
}

void CPU::outputState(Memory &memory) {
    cout << "Program Counter: 0x" << decToHex(program_counter_) << endl;
    cout << "Instruction Register: 0x" << instruction_register_ << endl;
    cout << "Registers:" << endl;
    registers_.print();
    cout << "Memory: " << endl;
    memory.print();
}

void Machine::storeInput(vector<string> &instructions, int program_counter) {
    cpu_.setProgramCounter(program_counter);
    int exit_position = program_counter;
    for (int i = 0, j = program_counter; i < instructions.size() && j < 255; i++, j += 2, exit_position += 2) {
        memory_[j] = instructions[i].substr(0, 2);
        memory_[j + 1] = instructions[i].substr(2);
    }
    cpu_.setHaltPosition(exit_position);
}


void Machine::reset() {
    cpu_.reset();
    memory_.clear();
}
void Machine::runOneStep(bool& is_halt) {
    cpu_.oneStep(memory_);
    is_halt = cpu_.is_halt_;
}

void Machine::runUntilHalt() {
    while(!cpu_.is_halt_) {
        cpu_.oneStep(memory_);
    }
}

void Machine::resetCPU() {
    cpu_.reset();
}

void Machine::clearMemory() {
    memory_.clear();
}


void Machine::outputState() {
    cpu_.outputState(memory_);
}

void MainUI::startProgram(Machine &machine) {
    menu1(machine);
}

void MainUI::menu1(Machine &machine) {
    machine.reset();
    cout << "*****Welcome to VMS:*****" << endl;
    cout << "1. Choose file" << endl;
    cout << "2. Input instructions manually" << endl;
    cout << "3. Exit program" << endl;
    cout << "Enter your choice: ";
    inputChoice('3');

    switch (choice_) {
        case 1:
            menu2();
            break;
        case 2:
            menu3();
            break;
        case 3:
            exitProgram();
            break;
    }
    menu4(machine);
}

void MainUI::menu2() {
    loadFile();
}

void MainUI::menu3() {
    cout << "Enter instructions(hex format): ";

    // Input instructions manually
    int n_instructions = 0;
    string instruction;
    while (n_instructions++) {
        while (true) {
            cin >> instruction;
            for (auto &c: instruction)
                c = toupper(c);
            if (instruction == "run" || instruction == "RUN") {
                break;
            }
            formatInput(instruction);
            if (instruction.empty()) {
                cout << "Please input instruction between 0x0000 and 0xFFFF: ";
                continue;
            } else {
                cout << "Note: Input \"run\" to stop entering" << endl;
                break;
            }
        }
        if (instruction == "run" || instruction == "RUN") {
            break;
        } else {
            user_instructions_.push_back(instruction);
        }
    }
}

void MainUI::menu4(Machine &machine) {
    cout << "Do you want to change program counter(Default: 0x02)? (Y/N)" << endl;
    cout << "Note: If instructions were more than available memory size they will be ignored automatically" << endl;
    int program_counter = 2;
    if (inputDecision()) {
        //Input program counter from user
        string input;
        cout << "Enter decimal value: ";
        while (true) {
            cin >> input;
            try {
                int int_input = stoi(input);
                if (0 <= int_input && int_input < 255) {
                    program_counter = int_input;
                    break;
                } else {
                    cout << "Invalid value, input pc between 0 - 254: ";
                }
            } catch (...) {
                cout << "Invalid value, input pc between 0 - 254: ";
            }
        }
    }
    machine.storeInput(user_instructions_, program_counter);
    menu5(machine);
}

void MainUI::menu5(Machine &machine) {
    cout << "1. Run one instruction" << endl;
    cout << "2. Run all instructions/until halt" << endl;
    cout << "3. Print memory and registers" << endl;
    cout << "Enter your choice: ";
    inputChoice('3');
    bool is_halt = false;
    switch (choice_) {
        case 1:
            machine.runOneStep(is_halt);
            break;
        case 2:
            machine.runUntilHalt();
            is_halt = true;
            break;
        case 3:
            machine.outputState();
            menu5(machine);
            break;
    }
    if (is_halt) {
        machine.outputState();
        menu6(machine);
    }

}

void MainUI::menu6(Machine &machine) {
    cout << "1. Reset CPU" << endl;
    cout << "2. Clear memory" << endl;
    cout << "3. New machine" << endl;
    inputChoice('3');
    switch (choice_) {
        case 1:
            machine.resetCPU();
            break;
        case 2:
            machine.clearMemory();
            break;
        case 3:
            machine.reset();
            break;
    }
    menu1(machine);
}

void MainUI::inputChoice(const char till) {
    string choice;
    while (true) {
        cin >> choice;
        if (choice.size() == 1) {
            if ('1' <= choice[0] && choice[0] <= till) {
                choice_ = (choice[0] - '0');
                break;
            } else {
                cout << "Please enter valid choice: ";
            }
        } else {
            cout << "Please enter valid choice: ";
        }
    }
}

bool MainUI::inputDecision() {
    string decision;
    while (true) {
        cin >> decision;
        if (decision.size() == 1) {
            decision[0] = toupper(decision[0]);
            if (decision[0] == 'Y') {
                return true;
            } else if (decision[0] == 'N') {
                return false;
            } else {
                cout << "Please enter Y or N: ";
            }
        } else {
            cout << "Please enter Y or N: ";
        }
    }
}

void MainUI::loadFile() {
    ifstream instruction_file;
    string path = "vole-machine-simulator/input files/";
    string file_name;
    cout << "Note: Valid instructions are between 0x0000 - 0xFFFF, anything else will be ignored" << endl;
    cin.ignore();
    while (true) {
        cout << "Enter file name: ";
        getline(cin, file_name);
        instruction_file.open("../input files/" + file_name);
        if (!instruction_file) {
            cerr << "Couldn't open " << file_name
                    << ", make sure it is a valid name with extension(example.txt) and that is located inside \"input files\""
                    << endl;
        } else {
            break;
        }
    }

    int n_instructions = 0;
    string instruction;
    while (getline(instruction_file, instruction)) {
        formatInput(instruction);
        //If valid instruction
        if (!instruction.empty()) {
            n_instructions++;
            user_instructions_.push_back(instruction);
        }
        // Maximum instruction that memory can hold exceeded
        if (n_instructions == 128) {
            break;
        }
    }
    instruction_file.close();
}

void MainUI::exitProgram() {
    cout << "***Thank you for using VMS***" << endl;
    exit(0);
}

void MainUI::formatInput(string &instruction) {
    // If memory can store returns formatted one else returns empty string
    if (regex_match(instruction, regex("(0x)?[0-9a-fA-F]{4}"))) {
        if (instruction.size() == 6) {
            instruction = instruction.substr(2);
        }
        for (auto &c: instruction)
            c = toupper(c);
    } else {
        instruction = "";
    }
}
