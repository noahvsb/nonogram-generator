#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#ifndef NONOGRAM_H
#define NONOGRAM_H

typedef struct {
    bool** raster;
    uint8_t dim;
    double fillChance;
} Nonogram;

Nonogram* allocNonogram(uint8_t, double);
void fillNonogram(Nonogram*);
Nonogram* createNonogram(uint8_t, double);

void freeNonogram(Nonogram*);

void printDiscord(Nonogram*, const char*, const char*);

#endif
