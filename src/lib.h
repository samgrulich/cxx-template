#pragma once
#include <cstdio>
#include <memory>

typedef unsigned int uint;

struct Matrix {
    int rows;
    int cols;
    std::shared_ptr<uint> data;

    Matrix() : rows(0), cols(0), data(nullptr) {}
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, uint data[]);

    uint& operator()(int row, int col);
    void operator()(int row, int col, uint value);
    bool operator==(const Matrix& other) const;
    void print();
    std::string toString();
};

struct State {
    int rows;
    int cols;
    Matrix values;
    Matrix colPrefixes;
    Matrix rowPrefixes;
    Matrix colSectorPrefixes;
    Matrix rowSectorPrefixes;
    Matrix sectorPrefixes;

    State(int rows, int cols) : rows(rows), cols(cols) {
        values = Matrix(rows, cols);
        colPrefixes = Matrix(rows, cols);
        rowPrefixes = Matrix(rows, cols);
        colSectorPrefixes = Matrix(rows, cols);
        rowSectorPrefixes = Matrix(rows, cols);
        sectorPrefixes = Matrix(rows, cols);
    }

    void parseInput(int y, int x, uint value);
    void parseInputs(uint data[]);
    bool containsHalfOfAllSectors(int startX, int startY, int endX, int endY, int sectorCount);
    bool containsRowEdgeSector(int startX, int endX, int y);
    bool containsColEdgeSector(int startY, int endY, int x);
    bool containsAnyEdgeSector(int startX, int startY, int endX, int endY);
    uint getBorderSum(int startX, int startY, int endX, int endY);
    void print();
};
