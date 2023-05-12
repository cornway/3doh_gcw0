
#include <stdint.h>
#include <vector>
#include <cassert>
#include <iostream>
#include <cstring>

#include <simdata.hpp>



bool BaseDump::operator==(const BaseDump& other) {
    if (size != other.size) {
        return false;
    }
    return !std::memcmp(mem, other.mem, size);
}

BaseDump::BaseDump(uint8_t *ram, size_t size) {
    this->mem = new uint8_t[size];
    this->size = size;
    std::memset(this->mem, 0, this->size);

    if (ram != nullptr)
        std::memcpy(this->mem, ram , size);
}

BaseDump::BaseDump(BaseDump&& other) : mem(nullptr), size(0) {
    std::cout << "BaseDump.copy" << std::endl;
    std::swap(mem, other.mem);
    std::swap(size, other.size);
}

BaseDump::~BaseDump() {
    std::cout << "BaseDump deleting" << std::endl;
    if (this->mem) {
        delete this->mem;
    }
    this->size = 0;
}

void BaseDump::write(std::string name) {
    FILE *fd = fopen(name.c_str(), "w+");

    if (fd == nullptr) {
        throw std::logic_error("");
    }

    fwrite(mem, size, 1, fd);
    fclose(fd);
}


//Cel Dump
void CelDump::DumpSection(const CelData &data) {
    uint32_t *ptr = std::get<0>(data);
    size_t offset = std::get<2>(data);
    uint32_t *memptr = (uint32_t *)(this->mem + (offset / sizeof(this->mem[0])));
    size_t size = std::get<1>(data) / sizeof(this->mem[0]);
    for (int i = 0; i < size; i++) {
        memptr[i] = ptr[i];
    }
}

//Factory
SimFactory::SimFactory(std::string testName, size_t maxItems) :
    testName(testName), maxItems(maxItems), itemsCount(0), simData(), simDataCheck() {
}

SimFactory::~SimFactory() {
    simData.clear();
    simDataCheck.clear();

}

bool SimFactory::Add(std::vector<SimData> &data, MemoryDump&& memDump, CelDump&& celDump) {
    if (itemsCount >= maxItems) {
        return false;
    }
    for (auto &d : data) {
        if (memDump == d.mem) {
            return false;
        }
        if (celDump == d.cel) {
            return false;
        }
    }
    data.push_back(SimData(std::move(memDump), std::move(celDump)));
    itemsCount++;
    return true;
}

bool SimFactory::AddSim(MemoryDump&& memDump, CelDump&& celDump, bool is_verification, std::string test_name) {
    if (testName != test_name) {
        return false;
    }
    return Add(is_verification ? simDataCheck : simData, std::move(memDump), std::move(celDump));
}

void SimFactory::Write(std::vector<SimData> &data, std::string name) {
    int i = 0;
    for (auto &d : data) {
        d.mem.write(name + "_" + std::to_string(i) + "_memory.bin");
        d.cel.write(name + "_" + std::to_string(i) + "_cel.bin");
        i++;
    }
    data.clear();
}

void SimFactory::WriteData (void) {
    Write(simData, testName + "_setup");
    Write(simDataCheck, testName + "_check");
}