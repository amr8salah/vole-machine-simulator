#include "vole-machine.h"

Memory::Memory(int size)
{
    try{
        if(size>0){
            cells_.resize(size, "00");
            size_ = size;
        } 
        else{
            throw size;
        }
    } catch(...){
        cerr<<"Memory size should be bigger than 0"<<endl;
    }
    
}
void Memory::setCell(int address, string value)
{
    try
    {
        if (address >= 0 && address < size_)
        {
            cells_[address] = value;
        }
        else
        {
            throw address;
        }
    }
    catch (...)
    {
        cerr << "Invalid Memory address" << endl;
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
            throw address;
        }
    }
    catch (...)
    {
        cerr << "Invalid Memory address" << endl;
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
void Memory::clear() {
    fill(cells_.begin(),cells_.end(),"00");
}




string ALU::hexToBin(string hex_num){
    double dec_num = hexToDec(hex_num);
    string bin_num = decToBin(dec_num);
    return bin_num;
}

void CU::fetch(Memory& memory, int& program_counter){
    //change memory


    program_counter++;
}
