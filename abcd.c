#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_TASK_LENGTH 50
#define FILENAME "tasklist.txt"

struct Task {
    char description[MAX_TASK_LENGTH];
    int completed;
};

struct Task taskList[MAX_TASKS];
int numTasks = 0;

void addTask(const char *description) {
    if (numTasks < MAX_TASKS) {
        strcpy(taskList[numTasks].description, description);
        taskList[numTasks].completed = 0;
        numTasks++;
        printf("Task added: %s\n", description);
    } else {
        printf("Task list full, cannot add more tasks.\n");
    }
}

void markCompleted(int index) {
    if (index >= 0 && index < numTasks) {
        taskList[index].completed = 1;
        printf("Task marked as completed: %s\n", taskList[index].description);
    } else {
        printf("Invalid task index.\n");
    }
}

void removeCompletedTasks() {
    int count = 0;
    for (int i = 0; i < numTasks; ++i) {
        if (taskList[i].completed) {

            for (int j = i; j < numTasks - 1; ++j) {
                strcpy(taskList[j].description, taskList[j + 1].description);
                taskList[j].completed = taskList[j + 1].completed;
            }
            count++;
            numTasks--;
            i--;
        }
    }
    printf("%d completed task(s) removed.\n", count);
}

void displayTasks() {
    printf("Task List:\n");
    printf("----------\n");
    for (int i = 0; i < numTasks; ++i) {
        printf("%d. [%s] %s\n", i + 1, (taskList[i].completed ? "X" : " "), taskList[i].description);
    }
    printf("----------\n");
}

void saveTasksToFile() {
    FILE *file = fopen(FILENAME, "w");
    if (file != NULL) {
        for (int i = 0; i < numTasks; ++i) {
            fprintf(file, "%d %s\n", taskList[i].completed, taskList[i].description);
        }
        fclose(file);
        printf("Tasks saved to %s\n", FILENAME);
    } else {
        printf("Error opening file for writing.\n");
    }
}

void loadTasksFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if (file != NULL) {
        while (fscanf(file, "%d", &taskList[numTasks].completed) == 1) {
            fscanf(file, " %[^\n]", taskList[numTasks].description);
            numTasks++;
            if (numTasks >= MAX_TASKS) {
                printf("Maximum number of tasks reached. Some tasks may not be loaded.\n");
                break;
            }
        }
        fclose(file);
        printf("Tasks loaded from %s\n", FILENAME);
    } else {
        printf("Creating a new task list file.\n");
        saveTasksToFile();
    }
}

void editTaskDescription(int index) {
    if (index >= 0 && index < numTasks) {
        printf("Enter the new description for task %d: ", index + 1);
        scanf(" %[^\n]", taskList[index].description);
        printf("Task description updated.\n");
    } else {
        printf("Invalid task index.\n");
    }
}

void displayTaskStats() {
    int completedTasks = 0;
    int incompleteTasks = 0;

    for (int i = 0; i < numTasks; ++i) {
        if (taskList[i].completed) {
            completedTasks++;
        } else {
            incompleteTasks++;
        }
    }

    printf("Task Statistics:\n");
    printf("Completed Tasks: %d\n", completedTasks);
    printf("Incomplete Tasks: %d\n", incompleteTasks);
}

void clearAllTasks() {
    numTasks = 0;
    printf("All tasks cleared.\n");
}

int getUserChoice() {
    int choice;
    printf("\nTask List Menu:\n");
    printf("1. Add Task\n");
    printf("2. Mark Task as Completed\n");
    printf("3. Remove Completed Tasks\n");
    printf("4. Display Tasks\n");
    printf("5. Save Tasks to File\n");
    printf("6. Edit Task Description\n");
    printf("7. Display Task Statistics\n");
    printf("8. Clear All Tasks\n");
    printf("9. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    return choice;
}

int getTaskIndex() {
    int index;
    printf("Enter task index: ");
    scanf("%d", &index);
    return index - 1;
}

void getUserInput(char *description) {
    printf("Enter task description: ");
    scanf(" %[^\n]", description);
}

int main() {
    int choice;
    char description[MAX_TASK_LENGTH];

    loadTasksFromFile();

    do {
        choice = getUserChoice();

        switch (choice) {
            case 1:
                getUserInput(description);
                addTask(description);
                break;
            case 2:
                markCompleted(getTaskIndex());
                break;
            case 3:
                removeCompletedTasks();
                break;
            case 4:
                displayTasks();
                break;
            case 5:
                saveTasksToFile();
                break;

            case 6:
                editTaskDescription(getTaskIndex());
                break;
            case 7:
                displayTaskStats();
                break;
            case 8:
                clearAllTasks();
                break;
            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);

    return 0;
}
