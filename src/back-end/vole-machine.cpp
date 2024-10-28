#include "vole-machine.h"

Memory::Memory(int size)
{
    cells_.resize(size, "00");
    size_ = size;
}
void Memory::setCell(int address, string value)
{
    try
    {
        if (address >= 0 && address <= size_)
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
    return cells_[address];
}
int Memory::getSize()
{
    return size_;
}
vector<string> Memory::getCells()
{
    return cells_;
}
