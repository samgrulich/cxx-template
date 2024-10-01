#include <cstdio>
#include <memory>

typedef unsigned int uint;

struct Matrix {
    int rows;
    int cols;
    std::shared_ptr<uint> data;

    Matrix() : rows(0), cols(0), data(nullptr) {}
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data = std::shared_ptr<uint>(new uint[(rows+1) * (cols+1)]);
        for (int x = 0; x < cols; x++) {
            data.get()[x] = 0;
        }
        for (int y = 0; y < rows; y++) {
            data.get()[y * cols] = 0;
        }
    }
    ~Matrix() {}

    uint& operator()(int row, int col) {
        return data.get()[row+1 * cols + col+1];
    }
    
    void operator()(int row, int col, uint value) {
        data.get()[row+1 * cols + col+1] = value;
    }
};

static int sRows;
static int sCols;
static Matrix sValues;
static Matrix sColPrefixes;
static Matrix sRowPrefixes;
static Matrix sColSectorPrefixes;
static Matrix sRowSectorPrefixes;
static Matrix sSectorPrefixes;

void initializeMatrices(int rows, int cols);
void parseInput(int row, int col, uint value);

bool containsHalfOfAllSectors(int startX, int startY, int endX, int endY, int sectorCount);
bool containsAnyEdgeSector(int startX, int startY, int endX, int endY);
uint getBorderSum(int startX, int startY, int endX, int endY);

int main() {
    scanf("%d %d", &sRows, &sCols);

    initializeMatrices(sRows, sCols);

    for (int y = 0; y < sRows; y++) {
        for (int x = 0; x < sCols; x++) {
            uint value;
            scanf("%d", &value);
            parseInput(x, y, value);
        }
    }

    uint sectorCount = sSectorPrefixes(sRows-1, sCols-1);
    uint maxSum = 0;
    uint maxStartX = 0, maxStartY = 0, maxEndX = 0, maxEndY = 0;
    for (int startY = 0; startY < sRows; startY++) {
        for (int startX = 0; startX < sCols; startX++) {
            // todo add sector fields sqrt skipping
            for (int endY = startY; endY < sRows; endY++) {
                for (int endX = startX; endX < sCols; endX++) {
                    // idea: check if the corners are sector values (if so, skip)
                    // todo
                    //  1. check if it contains half of all sectors
                    if (!containsHalfOfAllSectors(startX, startY, endX, endY, sectorCount)) {
                        continue;
                    }
                    //  2. check if there is a sector on any of the edges
                    if (containsAnyEdgeSector(startX, startY, endX, endY)) {
                        continue;
                    }
                    //  3. generate the sum of the inner rectangle
                    uint sum = getBorderSum(startX, startY, endX, endY);
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

    printf("%d %d %d %d (%d)\n", maxStartY, maxStartX, maxEndY, maxEndX, maxSum);

    return 0;
}

void initializeMatrices(int rows, int cols) {
    sRows = rows;
    sCols = cols;

    sValues = Matrix(rows, cols);
    sColPrefixes = Matrix(rows, cols);
    sRowPrefixes = Matrix(rows, cols);
    sColSectorPrefixes = Matrix(rows, cols);
    sRowSectorPrefixes = Matrix(rows, cols);
    sSectorPrefixes = Matrix(rows, cols);
}

void parseInput(int row, int col, uint value) {
    static size_t sIndex = 0;

    sValues(row, col, value);
    sColPrefixes(row, col) = sColPrefixes(row, col - 1) + value;
    sRowPrefixes(row, col) = sRowPrefixes(row - 1, col) + value;
    // sector detection
    bool isValSector = value == 0;
    sColSectorPrefixes(row, col) = sColSectorPrefixes(row, col - 1) + isValSector;
    sRowSectorPrefixes(row, col) = sRowSectorPrefixes(row - 1, col) + isValSector;
    // sectors prefix sums
    bool isPrevColSector = sValues(row, col - 1) == 0;
    bool isPrevRowSector = sValues(row - 1, col) == 0;
    int val = !isPrevColSector && !isPrevRowSector && isValSector ? 1 : 0;
    sSectorPrefixes(row, col) = sSectorPrefixes(row-1, col) + val;

    sIndex++;
}

bool containsHalfOfAllSectors(int startX, int startY, int endX, int endY, int sectorCount) {
    int sectorsInside = sSectorPrefixes(endY, endX) - sSectorPrefixes(startY-1, endX) - sSectorPrefixes(endY, startX-1) + sSectorPrefixes(startY-1, startX-1);
    return sectorsInside == sectorCount / 2;
}

bool containsRowEdgeSector(int startX, int endX, int y) {
    if (sValues(y, startX) == 0)
        return true;
    return sRowSectorPrefixes(y, endX) - sRowSectorPrefixes(y, startX) > 0;
}

bool containsColEdgeSector(int startY, int endY, int x) {
    if (sValues(startY, x) == 0)
        return true;
    return sColSectorPrefixes(endY, x) - sColSectorPrefixes(startY, x) > 0;
}

bool containsAnyEdgeSector(int startX, int startY, int endX, int endY) {
    return containsRowEdgeSector(startX, endX, startY) 
        || containsRowEdgeSector(startX, endX, endY) 
        || containsColEdgeSector(startY, endY, startX) 
        || containsColEdgeSector(startY, endY, endX);
}

uint getBorderSum(int startX, int startY, int endX, int endY) {
    uint top = sRowPrefixes(startY, endX) - sRowPrefixes(startY, startX-1);
    uint bottom = sRowPrefixes(endY, endX) - sRowPrefixes(endY, startX-1);
    uint left = sColPrefixes(endY-1, startX) - sColPrefixes(startY, startX);
    uint right = sColPrefixes(endY-1, endX) - sColPrefixes(startY, endX);
    return top + bottom + left + right;
}
