#include <iostream>
#include <iomanip>

// Node structure for the linked list
struct Node {
    int row;
    int col;
    int value;
    Node* next;
    
    Node(int r, int c, int v) : row(r), col(c), value(v), next(nullptr) {}
};

class SparseMatrix {
private:
    Node* head;
    int numRows;
    int numCols;
    int numNonZero;
    
    // Helper function to clear the linked list
    void clearList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        numNonZero = 0;
    }

public:
    // Constructor
    SparseMatrix(int rows, int cols) : head(nullptr), numRows(rows), numCols(cols), numNonZero(0) {}
    
    // Destructor
    ~SparseMatrix() {
        clearList();
    }
    
    // Create sparse matrix from user input
    void createFromInput() {
        // Clear existing data if any
        clearList();
        
        std::cout << "Enter the elements of the " << numRows << "x" << numCols << " matrix:\n";
        
        // Read the full matrix
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                int value;
                std::cin >> value;
                
                // Store only non-zero elements
                if (value != 0) {
                    insertNode(i, j, value);
                }
            }
        }
    }
    
    // Insert a new node in the linked list
    void insertNode(int row, int col, int value) {
        Node* newNode = new Node(row, col, value);
        numNonZero++;
        
        // If list is empty or new node should be first
        if (head == nullptr || (row < head->row) || (row == head->row && col < head->col)) {
            newNode->next = head;
            head = newNode;
            return;
        }
        
        // Find the correct position to insert
        Node* current = head;
        while (current->next != nullptr && 
               (current->next->row < row || 
               (current->next->row == row && current->next->col < col))) {
            current = current->next;
        }
        
        newNode->next = current->next;
        current->next = newNode;
    }
    
    // Print the original dense matrix
    void printDense() const {
        std::cout << "\nOriginal Matrix:\n";
        
        // Create temporary array to hold values
        int** matrix = new int*[numRows];
        for (int i = 0; i < numRows; i++) {
            matrix[i] = new int[numCols]();  // Initialize to 0
        }
        
        // Fill in non-zero values
        Node* current = head;
        while (current != nullptr) {
            matrix[current->row][current->col] = current->value;
            current = current->next;
        }
        
        // Print matrix
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                std::cout << std::setw(4) << matrix[i][j] << " ";
            }
            std::cout << "\n";
        }
        
        // Clean up
        for (int i = 0; i < numRows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    
    // Print the sparse matrix representation
    void printSparse() const {
        std::cout << "\nSparse Matrix Linked List Representation:\n";
        std::cout << "Number of Rows: " << numRows << "\n";
        std::cout << "Number of Columns: " << numCols << "\n";
        std::cout << "Number of Non-zero elements: " << numNonZero << "\n\n";
        
        std::cout << "Row\tColumn\tValue\tNext Address\n";
        std::cout << "---\t------\t-----\t------------\n";
        
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->row << "\t" 
                     << current->col << "\t" 
                     << current->value << "\t" 
                     << current->next << "\n";
            current = current->next;
        }
    }
    
    // Add two sparse matrices
    SparseMatrix add(const SparseMatrix& other) const {
        if (numRows != other.numRows || numCols != other.numCols) {
            throw std::invalid_argument("Matrix dimensions must match for addition");
        }
        
        SparseMatrix result(numRows, numCols);
        Node* ptr1 = head;
        Node* ptr2 = other.head;
        
        // Process both lists
        while (ptr1 != nullptr && ptr2 != nullptr) {
            if (ptr1->row < ptr2->row || (ptr1->row == ptr2->row && ptr1->col < ptr2->col)) {
                result.insertNode(ptr1->row, ptr1->col, ptr1->value);
                ptr1 = ptr1->next;
            }
            else if (ptr1->row > ptr2->row || (ptr1->row == ptr2->row && ptr1->col > ptr2->col)) {
                result.insertNode(ptr2->row, ptr2->col, ptr2->value);
                ptr2 = ptr2->next;
            }
            else {
                // Same position - add values
                int sum = ptr1->value + ptr2->value;
                if (sum != 0) {
                    result.insertNode(ptr1->row, ptr1->col, sum);
                }
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }
        }
        
        // Process remaining elements
        while (ptr1 != nullptr) {
            result.insertNode(ptr1->row, ptr1->col, ptr1->value);
            ptr1 = ptr1->next;
        }
        
        while (ptr2 != nullptr) {
            result.insertNode(ptr2->row, ptr2->col, ptr2->value);
            ptr2 = ptr2->next;
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
    
    // Option to add another matrix
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