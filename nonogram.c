#include "nonogram.h"

int main(int argc, char* argv[]) {
    srand(time(NULL)); // set random seed

    int dim = 5;             // default
    float fillChance = 0.6f; // default
    const char* fill = ":black_large_square:";      // default
    const char* unfill = ":white_large_square:";    // default

    for (int i = 1; i < argc; i++) {
        if ((strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--dim") == 0) && i + 1 < argc) {
            dim = atoi(argv[++i]);
        } else if ((strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--chance") == 0) && i + 1 < argc) {
            fillChance = atof(argv[++i]);
        } else if (strcmp(argv[i], "--fill") == 0 && i + 1 < argc) {
            fill = argv[++i];
        } else if (strcmp(argv[i], "--unfill") == 0 && i + 1 < argc) {
            unfill = argv[++i];
        } else {
            fprintf(stderr, "Syntax error: Usage: %s [-d n | --dim n] [-c p | --chance p] [--fill EMOJI] [--unfill EMOJI]\n", argv[0]);
            return 1;
        }
    }


    // validate arguments
    if (dim <= 0) {
        fprintf(stderr, "Invalid dimension: Must be > 0\n");
        return 1;
    }
    if (fillChance < 0.0f || fillChance > 1.0f) {
        fprintf(stderr, "Invalid fill chance: Must be between 0.0 and 1.0\n");
        return 1;
    }

    Nonogram* nonogram = createNonogram(dim, fillChance);
    if (nonogram == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    printDiscord(nonogram, fill, unfill);
    freeNonogram(nonogram);

    return 0;
}

// memory allocates a nonogram
// returns NULL if it failed
Nonogram* allocNonogram(uint8_t dim, double fillChance) {
    Nonogram* nonogram = malloc(sizeof(Nonogram*));
    if (!nonogram) return NULL;

    nonogram->dim = dim;
    nonogram->fillChance = fillChance;

    nonogram->raster = malloc(dim * sizeof(bool*));
    if (!nonogram->raster) {
        freeNonogram(nonogram);
        return NULL;
    }

    for (int i = 0; i < dim; i++) {
        nonogram->raster[i] = calloc(dim, sizeof(bool));
        if (!nonogram->raster[i]) {
            freeNonogram(nonogram);
            return NULL;
        }
    }

    return nonogram;
}

// fill allocated nonogram's raster
void fillNonogram(Nonogram* nonogram) {
    for (int i = 0; i < nonogram->dim; i++) {
        for (int j = 0; j < nonogram->dim; j++) {
            double r = (double) rand() / RAND_MAX;
            nonogram->raster[i][j] = r <= nonogram->fillChance;
        }
    }
}

// allocate nonogram and fill it's raster
// returns NULL if memory allocation failed
Nonogram* createNonogram(uint8_t dim, double fillChance) {
    Nonogram* nonogram = allocNonogram(dim, fillChance);
    if (nonogram != NULL) fillNonogram(nonogram);
    return nonogram;
}

// frees a nonogram pointer safely
void freeNonogram(Nonogram* nonogram) {
    if (nonogram) {
        if (nonogram->raster) {
            for (int i = 0; i < nonogram->dim; i++) {
                if (nonogram->raster[i]) free(nonogram->raster[i]);
            }
            free(nonogram->raster);
        }
        free(nonogram);
    }
}

// help function to calculate colNumbers and rowNumbers
void calculateNumbers(Nonogram* nonogram, int max, bool row, int numbers[][max]) {
    for (int i = 0; i < nonogram->dim; i++) {
        int count = 0;
        int numbersIndex = 0;
        for (int j = row ? 0 : nonogram->dim - 1; row ? j < nonogram->dim : j >= 0; row ? j++ : j--) {
            if (row ? nonogram->raster[i][j] : nonogram->raster[j][i]) {
                count++;
            } else if (count != 0) {
                numbers[i][numbersIndex++] = count;
                count = 0;
            }
        }
        if (count != 0) {
            numbers[i][numbersIndex] = count;
        }
    }
}

void printNumber(int number) {
    if (!number) printf(" ");
    else printf("%d", number);
}

// print a string that can be copy/pasted into Discord to solve the puzzle there
void printDiscord(Nonogram* nonogram, const char* fill, const char* unfill) {
    // print info
    printf("Nonogram (%dx%d)\nFill chance: %f\n\n", nonogram->dim, nonogram->dim, nonogram->fillChance);
    
    int max = (nonogram->dim + 1) / 2;

    int rowNumbers[nonogram->dim][max]; 
    memset(rowNumbers, 0, sizeof(rowNumbers));  
    calculateNumbers(nonogram, max, true, rowNumbers);

    int colNumbers[nonogram->dim][max]; 
    memset(colNumbers, 0, sizeof(colNumbers)); 
    calculateNumbers(nonogram, max, false, colNumbers);

    // print col numbers
    for (int j = max - 1; j >= 0; j--) {
        printf("`");
        for (int i = 0; i < nonogram->dim; i++) {
            printNumber(colNumbers[i][j]);
            if (i != nonogram->dim - 1) printf("  ");
        }
        printf("`\n");
    }

    for (int i = 0; i < nonogram->dim; i++) {
        for (int j = 0; j < nonogram->dim; j++) {
            printf("||%s||", nonogram->raster[i][j] ? fill : unfill);
        }
        // print row numbers
        printf(" `");
        for (int j = 0; j < max; j++) {
            printNumber(rowNumbers[i][j]);
            if (j != max - 1) printf(" ");
        }
        printf("`\n");
    }
}

