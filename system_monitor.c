#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

void display_uptime() {
    FILE *file = fopen("/proc/uptime", "r");

    if (file == NULL) {
        perror("Unable to read system uptime");
        return;
    }

    double uptime;

    if (fscanf(file, "%lf", &uptime) != 1) {
        printf("Unable to read uptime information.\n");
        fclose(file);
        return;
    }

    int days = (int)uptime / (24 * 3600);
    int hours = ((int)uptime % (24 * 3600)) / 3600;
    int minutes = ((int)uptime % 3600) / 60;

    printf("\nSystem Uptime\n");
    printf("-------------\n");
    printf("%d days, %d hours, %d minutes\n", days, hours, minutes);

    fclose(file);
}

void display_memory() {
    FILE *file = fopen("/proc/meminfo", "r");

    if (file == NULL) {
        perror("Unable to read memory information");
        return;
    }

    char line[256];
    long total_memory = 0;
    long available_memory = 0;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "MemTotal: %ld kB", &total_memory) == 1) {
            continue;
        }

        if (sscanf(line, "MemAvailable: %ld kB", &available_memory) == 1) {
            continue;
        }
    }

    long used_memory = total_memory - available_memory;

    printf("\nMemory Usage\n");
    printf("------------\n");
    printf("Total Memory     : %ld MB\n", total_memory / 1024);
    printf("Available Memory : %ld MB\n", available_memory / 1024);
    printf("Used Memory      : %ld MB\n", used_memory / 1024);

    if (total_memory > 0) {
        double usage_percentage =
            ((double)used_memory / total_memory) * 100;

        printf("Memory Usage     : %.2f%%\n", usage_percentage);
    }

    fclose(file);
}

int is_numeric(const char *name) {
    while (*name) {
        if (!isdigit((unsigned char)*name)) {
            return 0;
        }

        name++;
    }

    return 1;
}

void display_process_count() {
    DIR *directory = opendir("/proc");

    if (directory == NULL) {
        perror("Unable to access /proc");
        return;
    }

    struct dirent *entry;
    int process_count = 0;

    while ((entry = readdir(directory)) != NULL) {
        if (is_numeric(entry->d_name)) {
            process_count++;
        }
    }

    printf("\nProcess Information\n");
    printf("-------------------\n");
    printf("Existing Processes: %d\n", process_count);

    closedir(directory);
}

void display_system_info() {
    FILE *file = fopen("/proc/sys/kernel/hostname", "r");

    if (file == NULL) {
        perror("Unable to read hostname");
        return;
    }

    char hostname[256];

    if (fgets(hostname, sizeof(hostname), file) != NULL) {
        hostname[strcspn(hostname, "\n")] = '\0';

        printf("\nSystem Information\n");
        printf("------------------\n");
        printf("Hostname: %s\n", hostname);
    }

    fclose(file);
}

void display_menu() {
    printf("\n=================================\n");
    printf("       C SYSTEM MONITOR\n");
    printf("=================================\n");
    printf("1. System Uptime\n");
    printf("2. Memory Usage\n");
    printf("3. Process Count\n");
    printf("4. System Information\n");
    printf("5. Display All\n");
    printf("6. Exit\n");
    printf("=================================\n");
}

int main() {
    int choice;

    while (1) {
        display_menu();

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");

            while (getchar() != '\n') {
                /* Clear invalid input */
            }

            continue;
        }

        switch (choice) {
            case 1:
                display_uptime();
                break;

            case 2:
                display_memory();
                break;

            case 3:
                display_process_count();
                break;

            case 4:
                display_system_info();
                break;

            case 5:
                display_system_info();
                display_uptime();
                display_memory();
                display_process_count();
                break;

            case 6:
                printf("\nExiting System Monitor...\n");
                return 0;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}
