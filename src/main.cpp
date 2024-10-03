#include <cstdio>
#include <chrono>
#include "lib.h"

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    int rows, cols;
    scanf("%d %d", &rows, &cols);
    State state(rows, cols);
    auto initialization = std::chrono::high_resolution_clock::now();

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            uint value;
            scanf("%d", &value);
            state.parseInput(y, x, value);
        }
    }
    auto input = std::chrono::high_resolution_clock::now();

    uint sectorCount = state.sectorPrefixes(rows-1, cols-1);
    uint sectorHalf = sectorCount / 2;
    uint maxSum = 0;
    uint maxStartX = 0, maxStartY = 0, maxEndX = 0, maxEndY = 0;
    for (int startY = 0; startY < rows; startY++) {
        for (int startX = 0; startX < cols; startX++) {
            // todo add sector fields sqrt skipping
            for (int endY = startY; endY < rows; endY++) {
                for (int endX = startX; endX < cols; endX++) {
                    // idea: check if the corners are sector values (if so, skip)
                    //  1. check if it contains half of all sectors
                    if (!state.containsHalfOfAllSectors(startX, startY, endX, endY, sectorHalf)) {
                        continue;
                    }
                    //  2. check if there is a sector on any of the edges
                    if (state.containsAnyEdgeSector(startX, startY, endX, endY)) {
                        continue;
                    }
                    //  3. generate the sum of the inner rectangle
                    uint sum = state.getBorderSum(startX, startY, endX, endY);
                    if (sum > maxSum) {
                        maxSum = sum;
                        maxStartX = startX;
                        maxStartY = startY;
                        maxEndX = endX;
                        maxEndY = endY;
                    }
                }
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    fprintf(stderr, "%d %d %d %d (%d)\n", maxStartY, maxStartX, maxEndY, maxEndX, maxSum);
    fprintf(stderr, "Initialization: %ld\n", std::chrono::duration_cast<std::chrono::microseconds>(initialization - start).count());
    fprintf(stderr, "Input: %ld\n", std::chrono::duration_cast<std::chrono::microseconds>(input - initialization).count());
    fprintf(stderr, "End: %ld\n", std::chrono::duration_cast<std::chrono::microseconds>(end - input).count());
    fprintf(stderr, "Total: %ld\n", std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
    fprintf(stderr, "Loop count: %d\n", rows * cols * rows * cols);
    printf("%d\n", maxSum);

    return 0;
}

