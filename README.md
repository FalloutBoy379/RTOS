# 🕒 Lightweight Cooperative Task Scheduler in C

This project is a lightweight task scheduler written in C, inspired by Real-Time Operating Systems (RTOS) principles. It allows cooperative multitasking with user-defined task life cycles, prioritization, and non-blocking delay functionality. Designed for educational purposes or lightweight embedded systems.

---

## 📂 Project Structure

.
├── main.c        # Entry point: creates tasks and runs the scheduler loop
├── scheduler.c   # Implements task list handling and execution
├── scheduler.h   # Defines Task and TaskList structures and scheduler API
├── delay.c       # Provides blocking and non-blocking delay mechanisms
├── delay.h       # Delay function declarations
└── README.md     # You're reading it :)


---

## 🛠 Features

- ✅ **Task Prioritization**: Tasks are sorted and executed based on descending priority.
- ✅ **Lifecycle Hooks**:
    - `onInitialize()`
    - `run()`
    - `checkCompletion()`
    - `finally()`
- ✅ **Dynamic Task Management**: Tasks can be added and removed at runtime.
- ✅ **Non-blocking Delay Support**: Delay task execution without halting the entire scheduler.
- ✅ **Named Tasks**: For better debugging and introspection.
- ✅ **Safe Memory Handling**: Dynamic memory with proper `realloc` safety checks.

---

## 🚀 Getting Started

### 🔧 Build

Compile using `gcc`:

```bash
gcc main.c scheduler.c delay.c -o scheduler_app
```

▶️ Run

```bash
./scheduler_app
```

👨‍💻 Usage Example
Create a task:
```c
Task task = createTask("ExampleTask", 5);
task.onInitialize = onExampleInit;
task.run = runExample;
task.checkCompletion = isExampleDone;
task.finally = cleanupExample;

addTaskToScheduler(&myTaskList, &task);
```

Main Loop:

```C
while (myTaskList.taskCount > 0) {
    executeScheduler(&myTaskList);
    delay(1); // 1-second delay between cycles
}
```


🧪 Built-in Test Tasks
The current version includes:

FastTask: Completes immediately.
DelayedTask: Completes after 3 seconds using non-blocking delay.
LowPriorityTask: Lower priority task that also waits 1 second.
These demonstrate task initialization, execution, and clean-up order based on priority.

🧠 Design Philosophy
This project emphasizes:

Simplicity and readability
RTOS-style behavior using cooperative multitasking
Extensibility for embedded platforms or OS abstraction
💡 Future Enhancements
Here's how this project can evolve into a more full-featured RTOS:

Scheduler Features

Time-based execution (run at time $t$)
Repeating tasks (run every $n$ ms)
Preemptive multitasking (via interrupts)
Task yielding and suspension
Communication & Sync

Semaphores / Mutexes
Message queues
Event flags
Debugging Tools

Task state tracking
Logging with timestamps
Stack usage monitoring
Platform Integration

Port to STM32, ESP32, or Arduino
Integration with hardware timers and interrupts
📚 Dependencies
Standard C library (stdio.h, stdlib.h, stdbool.h, string.h, unistd.h, time.h)
Compatible with Unix-like OSes (Linux/macOS)
🙋‍♂️ Author
Crafted with 💻 and ☕ by Ansh Mehta