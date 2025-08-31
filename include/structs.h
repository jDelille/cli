#ifndef TYPES_H
#define TYPES_H

typedef struct {
    char *name;
    void (*func)(char *args);
    char *desc;
} Command;

#endif