#include <iostream>
#include <vector>
#include <iomanip>

class SparseMatrix {
private:
    int numRows;
    int numCols;
    int numNonZero;
    std::vector<int> rowIndices;
    std::vector<int> colIndices;
    std::vector<int> values;

public:
    // Constructor now only initializes the dimensions
    SparseMatrix(int rows, int cols) : numRows(rows), numCols(cols), numNonZero(0) {}
    
    // Convert from dense matrix input to sparse representation
    void createFromInput() {
        std::cout << "Enter the elements of the " << numRows << "x" << numCols << " matrix:\n";
        
        // Clear existing data
        rowIndices.clear();
        colIndices.clear();
        values.clear();
        numNonZero = 0;
        
        // Read the full matrix and store non-zero elements
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                int value;
                std::cin >> value;
                
                if (value != 0) {
                    rowIndices.push_back(i);
                    colIndices.push_back(j);
                    values.push_back(value);
                    numNonZero++;
                }
            }
        }
    }
    
    // Print the original dense matrix format
    void printDense() const {
        std::cout << "\nOriginal Matrix:\n";
        std::vector<std::vector<int>> dense(numRows, std::vector<int>(numCols, 0));
        
        // Fill in the non-zero values
        for (int i = 0; i < numNonZero; i++) {
            dense[rowIndices[i]][colIndices[i]] = values[i];
        }
        
        // Print the matrix
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                std::cout << std::setw(4) << dense[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
    
    // Print the compact sparse representation
    void printSparse() const {
        std::cout << "\nSparse Matrix Representation:\n";
        std::cout << "Number of Rows: " << numRows << "\n";
        std::cout << "Number of Columns: " << numCols << "\n";
        std::cout << "Number of Non-zero elements: " << numNonZero << "\n\n";
        
        // Print header
        std::cout << "Row\tColumn\tValue\n";
        std::cout << "---\t------\t-----\n";
        
        // Print each non-zero element
        for (int i = 0; i < numNonZero; i++) {
            std::cout << rowIndices[i] << "\t" << colIndices[i] << "\t" << values[i] << "\n";
        }
    }
    
    // Add two sparse matrices
    SparseMatrix add(const SparseMatrix& other) const {
        if (numRows != other.numRows || numCols != other.numCols) {
            throw std::invalid_argument("Matrix dimensions must match for addition");
        }
        
        // Create result matrix
        SparseMatrix result(numRows, numCols);
        
        // Convert both matrices to dense format for addition
        std::vector<std::vector<int>> dense1(numRows, std::vector<int>(numCols, 0));
        std::vector<std::vector<int>> dense2(numRows, std::vector<int>(numCols, 0));
        
        // Fill first matrix
        for (int i = 0; i < numNonZero; i++) {
            dense1[rowIndices[i]][colIndices[i]] = values[i];
        }
        
        // Fill second matrix
        for (int i = 0; i < other.numNonZero; i++) {
            dense2[other.rowIndices[i]][other.colIndices[i]] = other.values[i];
        }
        
        // Perform addition and store non-zero results
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                int sum = dense1[i][j] + dense2[i][j];
                if (sum != 0) {
                    result.rowIndices.push_back(i);
                    result.colIndices.push_back(j);
                    result.values.push_back(sum);
                    result.numNonZero++;
                }
            }
        }
        
        return result;
    }
};

int main() {
    int rows, cols;
    
    // Get matrix dimensions
    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> cols;
    
    // Create and input first matrix
    SparseMatrix matrix(rows, cols);
    matrix.createFromInput();
    
    // Display both representations
    matrix.printDense();
    matrix.printSparse();
    
    // Example of matrix addition
    std::cout << "\nWould you like to add another matrix? (1 for yes, 0 for no): ";
    int choice;
    std::cin >> choice;
    
    if (choice == 1) {
        std::cout << "\nEnter the elements of the second " << rows << "x" << cols << " matrix:\n";
        SparseMatrix matrix2(rows, cols);
        matrix2.createFromInput();
        
        std::cout << "\nSecond Matrix:";
        matrix2.printDense();
        matrix2.printSparse();
        
        std::cout << "\nSum of matrices:";
        SparseMatrix sum = matrix.add(matrix2);
        sum.printDense();
        sum.printSparse();
    }
    
    return 0;
}