import time
from enum import Enum

class STATE(Enum):
    IDLE = 0
    START = 1
    COUNT = 2
    WAIT = 3

class TestCase(Enum):
    CASE_0 = 0b000
    CASE_1 = 0b001
    CASE_2 = 0b010
    CASE_3 = 0b011
    CASE_4 = 0b100
    CASE_5 = 0b101
    CASE_6 = 0b110
    CASE_7 = 0b111

def state_to_string(state):
    state_map = {
        STATE.IDLE: "IDLE",
        STATE.START: "START",
        STATE.COUNT: "COUNT",
        STATE.WAIT: "WAIT"
    }
    return state_map.get(state, "UNKNOWN")

def extract_bits(tc):
    value = tc.value
    BCU = bool(value & 0b001)
    BTU = bool((value & 0b010) >> 1)
    Rx = bool((value & 0b100) >> 2)
    return Rx, BTU, BCU

def fsm(state, tc, Rx, BTU, BCU):
    start, load, doit = False, False, False
    
    if state == STATE.IDLE:
        start, load, doit = False, False, False
    elif state == STATE.START:
        start, load, doit = True, False, True
    elif state == STATE.COUNT:
        start, load, doit = False, True, False
    elif state == STATE.WAIT:
        start, load, doit = False, False, True

    if BCU and state == STATE.COUNT:
        state = STATE.IDLE
    elif not Rx and state == STATE.IDLE:
        state = STATE.START
    elif BTU and state == STATE.START or not BCU and state == STATE.COUNT:
        state = STATE.WAIT
    elif BTU and state == STATE.WAIT:
        state = STATE.COUNT

    print(f"Current state: {state_to_string(state)}")
    time.sleep(1)
    return state, start, load, doit

def main():
    print("FSM UART !!\n")
    
    state = STATE.IDLE
    tc = TestCase.CASE_0
    count = 0
    Rx, BTU, BCU = False, False, False
    start, load, doit = True, False, True

    print("\n-------- RERUN IN DEBUG PHASE --------")
    print(f"Starting state: {state_to_string(state)}")
    while True:
        try:
            Rx = bool(int(input("Rx: ")))
            BTU = bool(int(input("BTU: ")))
            BCU = bool(int(input("BCU: ")))
            state, start, load, doit = fsm(state, tc, Rx, BTU, BCU)
        except (ValueError, KeyboardInterrupt, EOFError):
            break

if __name__ == "__main__":
    main()