#include <cstdio>
#include "lib.h"

int main() {
    int rows, cols;
    scanf("%d %d", &rows, &cols);
    State state(rows, cols);

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            uint value;
            scanf("%d", &value);
            state.parseInput(y, x, value);
        }
    }

    state.print();

    // uint sectorCount = sSectorPrefixes(sRows-1, sCols-1);
    // uint maxSum = 0;
    // uint maxStartX = 0, maxStartY = 0, maxEndX = 0, maxEndY = 0;
    // for (int startY = 0; startY < sRows; startY++) {
    //     for (int startX = 0; startX < sCols; startX++) {
    //         // todo add sector fields sqrt skipping
    //         for (int endY = startY; endY < sRows; endY++) {
    //             for (int endX = startX; endX < sCols; endX++) {
    //                 // idea: check if the corners are sector values (if so, skip)
    //                 // todo
    //                 //  1. check if it contains half of all sectors
    //                 if (!containsHalfOfAllSectors(startX, startY, endX, endY, sectorCount)) {
    //                     continue;
    //                 }
    //                 //  2. check if there is a sector on any of the edges
    //                 if (containsAnyEdgeSector(startX, startY, endX, endY)) {
    //                     continue;
    //                 }
    //                 //  3. generate the sum of the inner rectangle
    //                 uint sum = getBorderSum(startX, startY, endX, endY);
    //                 if (sum > maxSum) {
    //                     maxSum = sum;
    //                     maxStartX = startX;
    //                     maxStartY = startY;
    //                     maxEndX = endX;
    //                     maxEndY = endY;
    //                 }
    //             }
    //         }
    //     }
    // }
    //
    // printf("%d %d %d %d (%d)\n", maxStartY, maxStartX, maxEndY, maxEndX, maxSum);

    return 0;
}

