
#include <stdint.h>
#include <stddef.h>
#include <utility>
#include <vector>
#include <string>
#include <tuple>

class BaseDump {
    protected:
        uint8_t *mem;
        size_t size;
    public:
        BaseDump() = delete;
        BaseDump(uint8_t *ram, size_t size);
        BaseDump(BaseDump&& other);
        ~BaseDump();
        bool operator==(const BaseDump& other);
        void write(std::string name);
};

class MemoryDump : public BaseDump {
    public:
        MemoryDump(uint8_t *ram, size_t size) : BaseDump(ram, size) {}
        MemoryDump(MemoryDump&& other) : BaseDump(std::move(other)) {}
        ~MemoryDump() {}
};


using CelData = std::tuple<uint32_t *, size_t, size_t>;

class CelDump : public BaseDump {

        void DumpSection(const CelData &data);
        void Dump() {}
        template <typename T, typename... Types>
        void Dump(T data, Types... datas) {
            DumpSection(data);
            Dump(datas...);
        }
    public:

        template <typename... Types>
        CelDump (size_t size, Types... data) : BaseDump(nullptr, size) {
            Dump(data...);
        }
        CelDump (CelDump&& cel) : BaseDump(std::move(cel)) {}
        ~CelDump() {}
};

class SimData {
    public:
        MemoryDump mem;
        CelDump cel;
        SimData (MemoryDump &&mem, CelDump &&cel) :
            mem(std::move(mem)), cel(std::move(cel)) {}
        SimData (SimData &&other) : mem(std::move(other.mem)), cel(std::move(other.cel)) {}
};

class SimFactory {
    private:
        size_t maxItems, itemsCount;
        std::string testName;
        std::vector<SimData> simData;
        std::vector<SimData> simDataCheck;

        bool Add(std::vector<SimData> &data, MemoryDump&& memDump, CelDump&& celDump);
        void Write(std::vector<SimData> &data, std::string name);
    public:
        SimFactory(std::string testName, size_t maxItems);
        ~SimFactory();

        bool AddSim(MemoryDump&& memDump, CelDump&& celDump, bool is_verification, std::string test_name);
        bool isFull() {
            return itemsCount >= maxItems;
        }
        void WriteData(void);
};