#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LogEntry {
    int id;
    char *message;
    char *timestamp;
} LogEntry;

LogEntry* create_entry(int id, const char *msg, const char *time) {
    LogEntry *entry = (LogEntry*)malloc(sizeof(LogEntry));
    if (!entry) return NULL;
    entry->id = id;
    entry->message = strdup(msg);
    entry->timestamp = strdup(time);


    // ВИПРАВЛЕННЯ (Memory Leak): видалено зайвий
    // entry->timestamp = strdup("00:00:00");
    // який перезаписував вказівник і губив блок із strdup(time).

    if (!entry->message || !entry->timestamp) {
        free(entry->message);
        free(entry->timestamp);
        free(entry);
        return NULL;
    }
    return entry;
}

void free_entry(LogEntry *entry) {
    if (!entry) return;
    free(entry->message);
    free(entry->timestamp);
    // ВИПРАВЛЕННЯ (Double Free): видалено повторний free(entry->message);
    free(entry);
}

void format_log_header(const char *title) {
    char header_buffer[16];
    // ВИПРАВЛЕННЯ (Stack Buffer Overflow): обмежуємо копіювання розміром буфера.
    size_t max_len = sizeof(header_buffer) - 1;
    size_t len = strlen(title);
    if (len > max_len) {
        // не розрізаємо багатобайтовий UTF-8 символ посередині
        len = max_len;
        while (len > 0 && ((unsigned char)title[len] & 0xC0) == 0x80) {
            len--;
        }
    }


    memcpy(header_buffer, title, len);
    header_buffer[len] = '\0';
    printf("Header: %s\n", header_buffer);
}

int main() {
    printf("--- Запуск програми журналу подій ---\n");
    // 1. Тест заголовочного буфера
    format_log_header("Цей заголовок є занадто довгим для 16 байт");
    // 2. Тест створення запису
    LogEntry *entry = create_entry(101, "Системна помилка підключення",
                                   "12:45:30");
    if (entry) {
        printf("Запис [%d] [%s]: %s\n", entry->id, entry->timestamp,
               entry->message);
        free_entry(entry);
        entry = NULL;
    }
    return 0;
}

