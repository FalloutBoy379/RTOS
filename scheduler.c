#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scheduler.h"

static int compareTasksByPriority(const void* a, const void* b) {
    return ((Task*)b)->priority - ((Task*)a)->priority;
}

void initializeScheduler(TaskList* taskList) {
    taskList->taskCount = 0;
    taskList->tasks = NULL;
}

bool addTaskToScheduler(TaskList* taskList, Task *task) {
    Task* newTasks = realloc(taskList->tasks, (taskList->taskCount + 1) * sizeof(Task));
    if (newTasks == NULL) {
        return false;
    }
    taskList->tasks = newTasks;
    task->id = taskList->taskCount + 1;
    task->completed = false;
    task->interrupted = false;
    task->initialized = false;
    taskList->tasks[taskList->taskCount] = *task;
    taskList->taskCount++;
    return true;
}

int executeScheduler(TaskList* taskList) {
    // Sort by priority descending
    qsort(taskList->tasks, taskList->taskCount, sizeof(Task), compareTasksByPriority);

    for (int i = 0; i < taskList->taskCount; i++) {
        Task* task = &taskList->tasks[i];
        if (!task->initialized && task->onInitialize) {
            printf("[Init] %s\n", task->name);
            task->onInitialize();
            task->initialized = true;
        }
        if (task->run) {
            printf("[Run] %s\n", task->name);
            task->run();
        }
        if (task->checkCompletion && task->checkCompletion()) {
            printf("[Check] %s marked complete.\n", task->name);
            task->completed = true;
        }
        if ((task->completed || task->interrupted) && task->finally) {
            printf("[Finally] %s\n", task->name);
            task->finally();
        }
    }

    // Remove completed tasks
    for (int i = 0; i < taskList->taskCount; ) {
        if (taskList->tasks[i].completed) {
            for (int j = i; j < taskList->taskCount - 1; j++) {
                taskList->tasks[j] = taskList->tasks[j + 1];
            }
            taskList->taskCount--;
            if (taskList->taskCount > 0) {
                Task* newTasks = realloc(taskList->tasks, taskList->taskCount * sizeof(Task));
                if (newTasks == NULL) {
                    perror("Memory reallocation failed");
                    exit(EXIT_FAILURE);
                }
                taskList->tasks = newTasks;
            } else {
                free(taskList->tasks);
                taskList->tasks = NULL;
            }
        } else {
            i++;
        }
    }

    return taskList->taskCount;
}

void cleanupScheduler(TaskList* taskList) {
    free(taskList->tasks);
    taskList->tasks = NULL;
    taskList->taskCount = 0;
}
