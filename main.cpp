#include <iostream>
#include <vector>
#include <iomanip>

class CPU8Bit {
private:
    uint8_t A;
    uint8_t PC;
    uint8_t SP;
    uint8_t flags;
    std::vector<uint8_t> memory;

public:
    CPU8Bit() {
        reset();
    }

    void reset() {
        A = 0;
        PC = 0;
        SP = 0xFF;
        flags = 0;
        memory.assign(256, 0);
    }

    void loadProgram(const std::vector<uint8_t>& program) {
        for (size_t i = 0; i < program.size() && i < memory.size(); ++i) {
            memory[i] = program[i];
        }
    }

    void execute() {
        bool running = true;
        while (running && PC < memory.size()) {
            uint8_t opcode = memory[PC++];
            
            switch (opcode) {
                case 0x01: {
                    A = memory[PC++];
                    break;
                }
                case 0x02: {
                    uint8_t val = memory[PC++];
                    uint16_t result = A + val;
                    flags = (result > 0xFF) ? 0x01 : 0x00;
                    A = static_cast<uint8_t>(result);
                    if (A == 0) flags |= 0x02;
                    break;
                }
                case 0x03: {
                    running = false;
                    break;
                }
                default:
                    std::cout << "Unknown Opcode: 0x" << std::hex << (int)opcode << std::endl;
                    running = false;
                    break;
            }
        }
        std::cout << "Execution finished. Accumulator A: 0x" << std::hex << (int)A << std::endl;
    }
};

int main() {
    CPU8Bit cpu;
    std::vector<uint8_t> program = {0x01, 0x0F, 0x02, 0x0A, 0x03};
    cpu.loadProgram(program);
    cpu.execute();
    return 0;
}
