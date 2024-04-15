#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int findMinimumPath(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<int>> dp(rows, vector<int>(cols, 0));
    dp[0][0] = grid[0][0];

    // Initialize first row
    for(int i = 1; i < cols; ++i)
        dp[0][i] = dp[0][i-1] + grid[0][i];

    // Initialize first column
    for(int i = 1; i < rows; ++i)
        dp[i][0] = dp[i-1][0] + grid[i][0];

    // Fill in the rest of the dp grid
    for(int i = 1; i < rows; ++i) {
        for(int j = 1; j < cols; ++j) {
            dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1]);
        }
    }

    return dp[rows-1][cols-1];
}

void processFile(const char* inputFile, const char* outputFile) {
    ifstream file(inputFile);
    ofstream outFile(outputFile);

    if (!file.is_open()) {
        cerr << "Error opening file: " << inputFile << endl;
        return;
    }

    int testCases;
    file >> testCases;

    while (testCases--) {
        int rows, cols;
        file >> rows >> cols;

        vector<vector<int>> grid(rows, vector<int>(cols, 0));

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                file >> grid[i][j];

        int result = findMinimumPath(grid);
        outFile << result << endl;
    }

    file.close();
    outFile.close();
}

void usage(char* program) {
    std::cerr << "Usage: " << program << " <input file> <output file>" << endl;
    exit(1);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        usage(argv[0]);
    }

    const char* inputFile = argv[1];
    const char* outputFile = argv[2];

    processFile(inputFile, outputFile);

    return 0;
}
