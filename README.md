# FSM UART Controller

Dự án đầu tay cho intern - Finite State Machine điều khiển UART đơn giản.

## Mô tả

Chương trình C++ mô phỏng máy trạng thái hữu hạn (FSM) với 4 trạng thái để điều khiển giao tiếp UART.

![FSM State Diagram](fsm.png)

## Các trạng thái

- **IDLE**: Trạng thái chờ (start=0, load=0, doit=0)
- **START**: Bắt đầu truyền (start=1, load=0, doit=1)  
- **COUNT**: Đếm dữ liệu (start=0, load=1, doit=0)
- **WAIT**: Chờ buffer (start=0, load=0, doit=1)

## Input/Output

**Input:**
- Rx: Tín hiệu nhận (0/1)
- BTU: Buffer timeout (0/1)
- BCU: Buffer clear (0/1)

**Output:**
- start, load, doit: Tín hiệu điều khiển

## Cách dùng

```bash
g++ -std=c++11 -o fsm fsm.cpp
./fsm
```

Chương trình sẽ chạy ở chế độ debug, nhập giá trị cho Rx, BTU, BCU để xem FSM chuyển trạng thái.

## Ví dụ

```
Rx: 0
BTU: 1  
BCU: 0
Current state: WAIT
```

## Tính năng

- Chế độ debug tương tác
- 8 test case tự động
- Hiển thị trạng thái real-time
- Logic FSM đơn giản, dễ hiểu

Dự án phù hợp để học về state machine và C++ cơ bản.