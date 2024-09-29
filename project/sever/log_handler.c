#include "main.h"

// 简单日志记录器
void log_message(const char *message) {
    FILE *log_file = fopen("server_log.txt", "a");
    if (log_file != NULL) {
        fprintf(log_file, "%s\n", message);
        fclose(log_file);
    }
}
