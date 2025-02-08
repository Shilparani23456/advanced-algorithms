#include <iostream>
#include <vector>
using namespace std;

// Function to find the longest common substring
string longestCommonSubstring(const string &str1, const string &str2) {
    int n = str1.length();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    int maxLength = 0;
    int endIndex = 0;

    // Build the lookup table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i - 1;
                }
            }
        }
    }

    // Print lookup table
    cout << "Lookup Table:" << endl;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    // Extract the longest common substring
    return str1.substr(endIndex - maxLength + 1, maxLength);
}

int main() {
    string str1, str2;
    cout << "Enter first string: ";
    cin >> str1;
    cout << "Enter second string: ";
    cin >> str2;

    if (str1.length() != str2.length()) {
        cout << "Error: Strings must be of the same length!" << endl;
        return 1;
    }

    string result = longestCommonSubstring(str1, str2);
    cout << "Longest Common Substring: " << result << endl;

    return 0;
}
