#include "lib.h"

Matrix::Matrix(int rows, int cols) : rows(rows+1), cols(cols+1) {
    data = std::shared_ptr<uint>(new uint[(this->rows) * (this->cols)]);
    for (int x = 0; x < this->cols; x++) {
        data.get()[x] = 0;
    }
    for (int y = 0; y < this->rows; y++) {
        data.get()[y * this->cols] = 0;
    }
}

uint& Matrix::operator()(int row, int col) {
    return data.get()[(row+1) * cols + col+1];
}

void Matrix::operator()(int row, int col, uint value) {
    data.get()[(row+1) * cols + col+1] = value;
}

void Matrix::print() {
    printf("Matrix %d x %d\n", rows-1, cols-1);
    for (int y = 1; y < rows; y++) {
        for (int x = 1; x < cols; x++) {
            printf("%d ", data.get()[y * cols + x]);
        }
        printf("\n");
    }
}

void State::parseInput(int y, int x, uint value) {
    static size_t sIndex = 0;
    static int prevY = 0;
    static int rowSectorChanges = 0;

    values(y, x, value);
    colPrefixes(y, x) = colPrefixes(y-1, x) + value;
    rowPrefixes(y, x) = rowPrefixes(y, x-1) + value;
    // sector detection
    bool isValSector = value == 0;
    colSectorPrefixes(y, x) = colSectorPrefixes(y-1, x) + isValSector;
    rowSectorPrefixes(y, x) = rowSectorPrefixes(y, x-1) + isValSector;
    // sectors prefix sums
    bool isPrevColSector = x != 0 ? values(y, x-1) == 0 : false;
    bool isPrevRowSector = y != 0 ? values(y-1, x) == 0 : false;
    int val = isValSector && !isPrevRowSector && !isPrevColSector ? 1 : 0;
    rowSectorChanges += val; 
    sectorPrefixes(y, x) = sectorPrefixes(y-1, x) + rowSectorChanges;

    if (prevY != y) {
        rowSectorChanges = 0;
        prevY = y;
    }
    sIndex++;
}

// bool containsHalfOfAllSectors(int startX, int startY, int endX, int endY, int sectorCount) {
//     int sectorsInside = sSectorPrefixes(endY, endX) - sSectorPrefixes(startY-1, endX) - sSectorPrefixes(endY, startX-1) + sSectorPrefixes(startY-1, startX-1);
//     return sectorsInside == sectorCount / 2;
// }

bool State::containsHalfOfAllSectors(int startX, int startY, int endX, int endY, int sectorCount) {
    int sectorsInside = sectorPrefixes(endY, endX) - sectorPrefixes(startY-1, endX) - sectorPrefixes(endY, startX-1) + sectorPrefixes(startY-1, startX-1);
    return sectorsInside == sectorCount / 2;
}

bool State::containsRowEdgeSector(int startX, int endX, int y) {
    if (values(y, startX) == 0)
        return true;
    return rowSectorPrefixes(y, endX) - rowSectorPrefixes(y, startX) > 0;
}

bool State::containsColEdgeSector(int startY, int endY, int x) {
    if (values(startY, x) == 0)
        return true;
    return colSectorPrefixes(endY, x) - colSectorPrefixes(startY, x) > 0;
}

bool State::containsAnyEdgeSector(int startX, int startY, int endX, int endY) {
    return containsRowEdgeSector(startX, endX, startY) 
        || containsRowEdgeSector(startX, endX, endY) 
        || containsColEdgeSector(startY, endY, startX) 
        || containsColEdgeSector(startY, endY, endX);
}

uint State::getBorderSum(int startX, int startY, int endX, int endY) {
    uint top = rowPrefixes(startY, endX) - rowPrefixes(startY, startX-1);
    uint bottom = rowPrefixes(endY, endX) - rowPrefixes(endY, startX-1);
    uint left = colPrefixes(endY-1, startX) - colPrefixes(startY, startX);
    uint right = colPrefixes(endY-1, endX) - colPrefixes(startY, endX);
    return top + bottom + left + right;
}

void State::print() {
    printf("State R:%d x C:%d\n", rows, cols);
    values.print();
    colPrefixes.print();
    rowPrefixes.print();
    colSectorPrefixes.print();
    rowSectorPrefixes.print();
    sectorPrefixes.print();
}


