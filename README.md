# FSM UART Controller

A finite state machine implementation for UART communication control with interactive debugging capabilities.

## Overview

This project implements a 4-state finite state machine (FSM) that controls UART communication flow. The FSM transitions between IDLE, START, COUNT, and WAIT states based on three input signals: Rx (receive), BTU (buffer timeout), and BCU (buffer clear).

## State Machine Diagram

![FSM State Diagram](fsm.png)

The FSM contains four states:

- **IDLE**: Initial state with all outputs low (start=0, load=0, doit=0)
- **START**: Begin transmission (start=1, load=0, doit=1)
- **COUNT**: Data counting phase (start=0, load=1, doit=0)
- **WAIT**: Waiting for buffer operations (start=0, load=0, doit=1)

## State Transitions

| Current State | Input Condition | Next State |
|---------------|----------------|------------|
| IDLE | ~Rx (Rx=0) | START |
| START | BTU=1 | WAIT |
| COUNT | BCU=1 | IDLE |
| COUNT | ~BCU (BCU=0) | WAIT |
| WAIT | BTU=1 | COUNT |

## Input Signals

- **Rx**: Receive signal (0 = data available, 1 = no data)
- **BTU**: Buffer Timeout Unit signal
- **BCU**: Buffer Clear Unit signal

## Output Signals

- **start**: Initiate transmission
- **load**: Load data into buffer
- **doit**: Execute current operation

## Features

- Interactive debugging mode with manual input control
- Automatic test case generation for all 8 possible input combinations
- Real-time state visualization
- Bit manipulation utilities for input extraction

## Compilation and Usage

### Prerequisites
- C++11 compatible compiler
- Standard libraries: iostream, fstream, thread, chrono

### Compile
```bash
g++ -std=c++11 -o fsm_uart fsm_uart.cpp
```

### Run
```bash
./fsm_uart
```

## Interactive Mode

The program enters debug mode where you can manually control the FSM:

```
-------- RERUN IN DEBUG PHASE --------
Rx: 0
BTU: 1
BCU: 0
Current state: WAIT
```

Enter values for Rx, BTU, and BCU (0 or 1) to see state transitions in real-time.

## Code Structure

### Enumerations
- `STATE`: Defines the four FSM states
- `test_case`: Represents all 8 possible input combinations (3-bit values)

### Key Functions
- `stateToString()`: Converts state enum to readable string
- `extractBits()`: Extracts individual signal bits from test case
- `fsm()`: Main FSM logic implementing state transitions and output generation

### Test Cases
The program supports 8 predefined test cases covering all input combinations:
- CASE_0 (000): Rx=0, BTU=0, BCU=0
- CASE_1 (001): Rx=0, BTU=0, BCU=1
- ...
- CASE_7 (111): Rx=1, BTU=1, BCU=1

## State Behavior

Each state sets specific output values:

| State | start | load | doit |
|-------|-------|------|------|
| IDLE  | 0     | 0    | 0    |
| START | 1     | 0    | 1    |
| COUNT | 0     | 1    | 0    |
| WAIT  | 0     | 0    | 1    |

## Example Usage

```cpp
// Initialize FSM
STATE state = STATE::IDLE;
bool Rx = 0, BTU = 1, BCU = 0;
bool start, load, doit;

// Execute FSM step
fsm(state, tc, Rx, BTU, BCU, start, load, doit);
```

## Applications

This FSM controller is suitable for:
- UART communication protocols
- Serial data transmission control
- Buffer management systems
- Real-time embedded system control

## License

Open source - feel free to modify and distribute.

## Contributing

Contributions welcome! Please ensure all state transitions follow the documented behavior and add appropriate test cases.