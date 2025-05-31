#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

enum class STATE {
    IDLE,
    START,
    COUNT,
    WAIT
};

enum test_case {
    CASE_0 = 0b000,  // Rx=0, BTU=0, BCU=0
    CASE_1 = 0b001,  // Rx=0, BTU=0, BCU=1
    CASE_2 = 0b010,  // Rx=0, BTU=1, BCU=0
    CASE_3 = 0b011,  // Rx=0, BTU=1, BCU=1
    CASE_4 = 0b100,  // Rx=1, BTU=0, BCU=0
    CASE_5 = 0b101,  // Rx=1, BTU=0, BCU=1
    CASE_6 = 0b110,  // Rx=1, BTU=1, BCU=0
    CASE_7 = 0b111   // Rx=1, BTU=1, BCU=1
};

std::string stateToString(STATE state) {
    switch(state) {
        case STATE::IDLE:  return "IDLE";
        case STATE::START: return "START";
        case STATE::COUNT: return "COUNT";
        case STATE::WAIT:  return "WAIT";
        default: return "UNKNOWN";
    }
}

void extractBits(test_case tc, bool& Rx, bool& BTU, bool& BCU) {
    int value = static_cast<int>(tc);
    
    BCU = value & 0b001;        // Extract bit 0
    BTU = (value & 0b010) >> 1; // Extract bit 1
    Rx  = (value & 0b100) >> 2; // Extract bit 2
}

void fsm (STATE& state, test_case& tc, bool& Rx, bool& BTU, bool& BCU, bool& start, bool& load, bool& doit) {
    // Component state
    switch (state) {
        case STATE::IDLE:
            start = 0;
            load = 0;
            doit = 0;
            break;
        case STATE::START:
            start = 1;
            load = 0;
            doit = 1;
            break;
        case STATE::COUNT:
            start = 0;
            load = 1;
            doit = 0;
            break;
        case STATE::WAIT:
            start = 0;
            load = 0;
            doit = 1;
            break;
    }

    if (BCU && state == STATE::COUNT) {
        state = STATE::IDLE;
    } else if (!Rx && state == STATE::IDLE) {
        state = STATE::START;
    } else if (BTU && state == STATE::START || !BCU && state == STATE::COUNT) {
        state = STATE::WAIT;
    } else if (BTU && state == STATE::WAIT) {
        state = STATE::COUNT;
    }
    std::cout << "Current state: " << stateToString(state) << std::endl; 
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main () {
    std::cout << "FSM UART !!\n\n" << std::endl;

    STATE state = STATE::IDLE;
    test_case tc = CASE_0;
    unsigned int count = 0;
    bool Rx = 0;
    bool BTU = 0;
    bool BCU = 0;
    bool start = 1;
    bool load = 0;
    bool doit = 1;

    // // // Debug code
    state = STATE::START;
    std::cout << "\n-------- RERUN IN DEBUG PHASE -------- \n";
    std::cout << "Starting state: " << stateToString(state) << std::endl; 
    while (true) {
        std::cout << "Rx: ";
        if (!(std::cin >> Rx)) break;
        std::cout << "BTU: ";
        if (!(std::cin >> BTU)) break;
        std::cout << "BCU: ";
        if (!(std::cin >> BCU)) break;
        // extractBits(tc, Rx, BTU, BCU);     
        fsm(state, tc, Rx, BTU, BCU, start, load, doit);
    }
}