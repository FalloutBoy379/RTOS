#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdbool.h>
#include <stdint.h>

#define TASK_NAME_MAX 32

typedef struct Task {
    int id;
    bool completed;
    bool interrupted;
    bool initialized;
    int8_t priority;
    char name[TASK_NAME_MAX];
    void (*onInitialize)(void);
    void (*run)(void);
    bool (*checkCompletion)(void);
    void (*finally)(void);
} Task;

typedef struct {
    Task* tasks;
    int taskCount;
} TaskList;

void initializeScheduler(TaskList* taskList);
bool addTaskToScheduler(TaskList* taskList, Task *task);
int executeScheduler(TaskList* taskList);
void cleanupScheduler(TaskList* taskList);

#endif // SCHEDULER_H
