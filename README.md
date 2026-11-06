# 8-Bit CPU Simulator in C++

A simple 8-bit CPU simulator written in C++. I built it to understand how a CPU executes instructions step by step: it has registers, memory, status flags and a small instruction set.

## Components
- **Accumulator (A):** 8-bit register that holds the result of operations.
- **Program Counter (PC):** Address of the next instruction to run.
- **Stack Pointer (SP):** Starts at `0xFF`. Not used by any instruction yet (reserved for future use).
- **RAM:** 256 bytes (a `std::vector`).
- **Flags:** Carry (`0x01`) and Zero (`0x02`).

## Instructions
| Opcode | Name | What it does |
| :--- | :--- | :--- |
| `0x01` | `LOAD` | Loads an 8-bit value into A |
| `0x02` | `ADD` | Adds an 8-bit value to A. Sets Carry on overflow and Zero if the result is 0 |
| `0x03` | `HALT` | Stops the CPU |

## How it works
The CPU runs a simple loop:
1. **Fetch** the byte at the address in PC.
2. **Decode** it as an opcode.
3. **Execute** it, then move PC forward.

It repeats until it reaches `HALT`.

## Example
This program loads 15, adds 10, then stops:

```
0x01 0x0F   ; LOAD 15
0x02 0x0A   ; ADD 10
0x03        ; HALT
```

Result: A = 25 (`0x19`)

## How to run
You need a C++ compiler such as GCC.

```bash
g++ main.cpp -o cpu_sim
./cpu_sim
```

## Limitations
This is a learning project. It has no jump, store or subtract instructions yet, so it cannot run loops or complex programs.

## Author
Paul Thapa
