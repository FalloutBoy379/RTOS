#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "delay.h"
#include "scheduler.h"

Task createTask(const char *name, int8_t priority);
void initialize(TaskList *taskList);
void cleanup(TaskList *taskList);

// Task 1 (completes immediately)
void onTask1Initialize(void) { printf("Task 1 initialized.\n"); }
void runTask1(void) { printf("Running Task 1\n"); }
bool checkTask1(void) { return true; }
void finallyTask1(void) { printf("Task 1 cleaned up.\n"); }

// Task 2 (delays for 3s using delayNonBlocking)
static int task2Time = 3;
void onTask2Initialize(void) { printf("Task 2 initialized.\n"); }
void runTask2(void) { printf("Waiting in Task 2...\n"); }
bool checkTask2(void) { return delayNonBlocking(task2Time); }
void finallyTask2(void) { printf("Task 2 finished.\n"); }

// Task 3 (lower priority)
void onTask3Initialize(void) { printf("Task 3 initialized.\n"); }
void runTask3(void) { printf("Quick run from Task 3\n"); }
bool checkTask3(void) { return delayNonBlocking(1); }
void finallyTask3(void) { printf("Task 3 done.\n"); }

int main()
{
    TaskList myTaskList;
    initialize(&myTaskList);

    Task task1 = createTask("FastTask", 4);
    task1.onInitialize = onTask1Initialize;
    task1.run = runTask1;
    task1.checkCompletion = checkTask1;
    task1.finally = finallyTask1;

    Task task2 = createTask("DelayedTask", 2);
    task2.onInitialize = onTask2Initialize;
    task2.run = runTask2;
    task2.checkCompletion = checkTask2;
    task2.finally = finallyTask2;

    Task task3 = createTask("LowPriorityTask", 3);
    task3.onInitialize = onTask3Initialize;
    task3.run = runTask3;
    task3.checkCompletion = checkTask3;
    task3.finally = finallyTask3;

    addTaskToScheduler(&myTaskList, &task1);
    addTaskToScheduler(&myTaskList, &task2);
    addTaskToScheduler(&myTaskList, &task3);

    // while(1){
    //     if(delayNonBlocking(1)){
    //         printf("Executing scheduler...\n");
    //     }

    // }
    while (myTaskList.taskCount > 0)
    {
        executeScheduler(&myTaskList);
        if (delay(1) == -1)
        {
            perror("Delay failed");
            break;
        }
    }

    cleanup(&myTaskList);
    return 0;
}

void initialize(TaskList *taskList)
{
    initializeScheduler(taskList);
    printf("Scheduler initialized.\n");
}

void cleanup(TaskList *taskList)
{
    cleanupScheduler(taskList);
    printf("Scheduler cleaned up.\n");
}

Task createTask(const char *name, int8_t priority)
{
    Task task;
    task.priority = priority;
    strncpy(task.name, name, TASK_NAME_MAX - 1);
    task.name[TASK_NAME_MAX - 1] = '\0';
    task.onInitialize = NULL;
    task.run = NULL;
    task.checkCompletion = NULL;
    task.finally = NULL;
    return task;
}
