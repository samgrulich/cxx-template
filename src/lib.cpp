#include "lib.h"
#include <string>

Matrix::Matrix(int rows, int cols) : rows(rows+1), cols(cols+1) {
    data = std::shared_ptr<uint>(new uint[(this->rows) * (this->cols)]);
    for (int x = 0; x < this->cols; x++) {
        data.get()[x] = 0;
    }
    for (int y = 0; y < this->rows; y++) {
        data.get()[y * this->cols] = 0;
    }
}

Matrix::Matrix(int rows, int cols, uint data[]) : Matrix(rows, cols) {
    for (int y = 1; y < this->rows; y++) {
        for (int x = 1; x < this->cols; x++) {
            this->data.get()[y * this->cols + x] = data[(y-1) * cols + (x-1)];
        }
    }
}

uint& Matrix::operator()(int row, int col) {
    return data.get()[(row+1) * cols + col+1];
}

void Matrix::operator()(int row, int col, uint value) {
    data.get()[(row+1) * cols + col+1] = value;
}

bool Matrix::operator==(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        return false;
    for (int y = 1; y < rows; y++) {
        for (int x = 1; x < cols; x++) {
            if (data.get()[y * cols + x] != other.data.get()[y * cols + x])
                return false;
        }
    }
    return true;
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

std::string Matrix::toString() {
    std::string result("");
    result += "Matrix " + std::to_string(rows-1) + " x " + std::to_string(cols-1) + "\n";
    for (int y = 1; y < rows; y++) {
        for (int x = 1; x < cols; x++) {
            result += std::to_string(data.get()[y * cols + x]) + " ";
        }
        result += "\n";
    }
    return result;
}

void State::parseInput(int y, int x, uint value) {
    static size_t sIndex = 0;

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
    sectorPrefixes(y, x) = sectorPrefixes(y-1, x) + sectorPrefixes(y, x-1) - sectorPrefixes(y-1, x-1) + val;

    sIndex++;
}

void State::parseInputs(uint data[]) {
    for (int i = 0; i < rows * cols; i++) {
        int y = i / cols;
        int x = i % cols;
        parseInput(y, x, data[i]);
    }
}

bool State::containsHalfOfAllSectors(int startX, int startY, int endX, int endY, int sectorHalf) {
    int rect1 = sectorPrefixes(endY, endX);
    int rect2 = sectorPrefixes(startY-1, startX-1);
    int rect3 = sectorPrefixes(startY-1, endX);
    int rect4 = sectorPrefixes(endY, startX-1);

    if (rect1 < sectorHalf)
        return false;
    if (rect1 - rect2 < sectorHalf)
        return false;

    int sectorSum = rect1 - rect2 - rect3 + rect4;
    return sectorSum == sectorHalf;
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


