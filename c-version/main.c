#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep((x) * 1000)
#else
#include <unistd.h> // for sleep function
#endif

typedef enum {
    IDLE,
    START,
    COUNT,
    WAIT
} STATE;

typedef enum {
    CASE_0 = 0b000,
    CASE_1 = 0b001,
    CASE_2 = 0b010,
    CASE_3 = 0b011,
    CASE_4 = 0b100,
    CASE_5 = 0b101,
    CASE_6 = 0b110,
    CASE_7 = 0b111
} test_case;

const char* stateToString(STATE state) {
    switch(state) {
        case IDLE:  return "IDLE";
        case START: return "START";
        case COUNT: return "COUNT";
        case WAIT:  return "WAIT";
        default: return "UNKNOWN";
    }
}

void extractBits(test_case tc, int* Rx, int* BTU, int* BCU) {
    int value = (int)tc;
    
    *BCU = value & 0b001;
    *BTU = (value & 0b010) >> 1;
    *Rx  = (value & 0b100) >> 2;
}

void fsm(STATE* state, test_case tc, int* Rx, int* BTU, int* BCU, int* start, int* load, int* doit) {
    switch (*state) {
        case IDLE:
            *start = 0;
            *load = 0;
            *doit = 0;
            break;
        case START:
            *start = 1;
            *load = 0;
            *doit = 1;
            break;
        case COUNT:
            *start = 0;
            *load = 1;
            *doit = 0;
            break;
        case WAIT:
            *start = 0;
            *load = 0;
            *doit = 1;
            break;
    }

    if (*BCU && *state == COUNT) {
        *state = IDLE;
    } else if (!*Rx && *state == IDLE) {
        *state = START;
    } else if (*BTU && *state == IDLE || !*BCU && *state == COUNT) {
        *state = WAIT;
    } else if (*BTU && *state == WAIT) {
        *state = COUNT;
    }
    
    printf("Current state: %s\n", stateToString(*state));   
    sleep(1);
}

int main() {
    printf("FSM UART !!\n\n");

    STATE state = IDLE;
    test_case tc = CASE_0;
    unsigned int count = 0;
    int Rx = 0;
    int BTU = 0;
    int BCU = 0;
    int start = 1;
    int load = 0;
    int doit = 1;

    printf("\n-------- DEBUG PHASE --------\n");
    printf("Starting state: %s\n", stateToString(state));
    while (1) {
        printf("-------- RERUN IN DEBUG PHASE -------");
        printf("Rx: ");
        if (scanf("%d", &Rx) != 1) break;
        printf("BTU: ");
        if (scanf("%d", &BTU) != 1) break;
        printf("BCU: ");
        if (scanf("%d", &BCU) != 1) break;
        fsm(&state, tc, &Rx, &BTU, &BCU, &start, &load, &doit);
    }

    return 0;
}