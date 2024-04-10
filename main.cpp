/*
  CSV READER FOR NBA REGULAR SEASON
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Function to split a string based on a delimiter
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
      tokens.push_back(token);
    }
    return tokens;
}

// Function to read CSV file and store data in a vector of vectors
vector<vector<string>> readCSV(const string &filename) {
  vector<vector<string>> data;
  ifstream file(filename);

  if (!file.is_open()) {
    cerr << "Error opening file: " << filename << endl;
    return data; // Return empty vector if file opening fails
  }

  string line;
  while (getline(file, line)) {
    // Skip empty lines
    if (line.empty()) { continue; }

    // Check if line starts with "West" or "East" to separate divisions
    if (line == "West" || line == "East") { continue; }

    vector<string> row = split(line, ',');
    std::string formatted_row;
    for (size_t i = 0; i < row.size(); ++i) {
        formatted_row += row[i];
        if (i != row.size() - 1) // Add tab after every token except the last one
            formatted_row += "\t";
    }
    data.push_back(row);
  }
  file.close();

  return data;
}

void printBox(const std::vector<std::vector<std::string>>& data) {
    const int colWidth = 30; // Adjust the column width as needed
    for (const auto &row : data) {
        for (const auto &cell : row) {
            // Adjust setw for win/loss columns
            if (cell.length() == 2) {
              cout << "| " << setw(3)  << cell;
            } else if (cell.length() > 2) {
              cout << "| " << setw(colWidth) << left << cell;
            }
        }
        cout << "|"<< endl;
    }
}

int main() {
    vector<vector<string>> data = readCSV("nba_regular_season_standings.csv");

    printBox(data);

    return 0;
}