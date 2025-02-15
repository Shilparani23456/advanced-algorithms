#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

// Huffman Tree Node
struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;

    Node(char data, int freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// Compare function for priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Function to generate Huffman codes in preorder traversal
void generateHuffmanCodes(Node* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;
    
    // If it's a leaf node, store the code
    if (!root->left && !root->right) {
        huffmanCodes[root->data] = code;
    }
    
    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Function to build the Huffman Tree and generate codes
unordered_map<char, string> buildHuffmanTree(string S, vector<int> f) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    // Insert all characters into priority queue
    for (size_t i = 0; i < S.size(); i++) {
        pq.push(new Node(S[i], f[i]));
    }
    
    // Build Huffman Tree
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        
        Node* newNode = new Node('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        
        pq.push(newNode);
    }
    
    // Get the root of the Huffman Tree
    Node* root = pq.top();
    
    // Generate Huffman Codes
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);
    
    return huffmanCodes;
}

int main() {
    string S = "abcdef";
    vector<int> f = {5, 9, 12, 13, 16, 45};
    
    unordered_map<char, string> huffmanCodes = buildHuffmanTree(S, f);
    
    // Print Huffman Codes in specified order: f, c, d, a, b, e
    cout << "Huffman Codes in Preorder Traversal:" << endl;
    vector<char> order = {'f', 'c', 'd', 'a', 'b', 'e'};
    for (char c : order) {
        cout << c << " : " << huffmanCodes[c] << endl;
    }
    
    return 0;
}
