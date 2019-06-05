#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

string fileAsString(string filename);
string cleanString(string file);
string LCSubStr(string X, string Y);

int main() {
  string subsequence, file1, file2, filename1("B1.txt"), filename2("B2.txt");
  file1 = fileAsString(filename1);
  file2 = fileAsString(filename2);
  file1 = cleanString(file1);
  file2 = cleanString(file2);
  subsequence = LCSubStr(file1, file2);
  cout << subsequence << endl;
  return 0;
}

string fileAsString(string filename){
  string line, test, file;
  ifstream fin(filename.c_str());
  if (!fin){
    cout << "Error! Incorrect file." << endl;
    exit(EXIT_FAILURE);
  }
  getline(fin, line);
  while (!fin.eof()){
    getline(fin, line);
    file.append(" ");
    file.append(line);
  }
  return file;
}

string cleanString(string file){
  file.erase(remove(file.begin(), file.end(), '.'), file.end());
  file.erase(remove(file.begin(), file.end(), '?'), file.end());
  file.erase(remove(file.begin(), file.end(), '!'), file.end());
  file.erase(remove(file.begin(), file.end(), '*'), file.end());
  return file;
}

string LCSubStr(string X, string Y)
{
    int m = X.length();
    int n = Y.length();
    int result = 0;
    int end;
    int len[2][n];
    int currRow = 0;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                len[currRow][j] = 0;
            }
            else if (X[i - 1] == Y[j - 1]) {
                len[currRow][j] = len[1 - currRow][j - 1] + 1;
                if (len[currRow][j] > result) {
                    result = len[currRow][j];
                    end = i - 1;
                }
            }
            else {
                len[currRow][j] = 0;
            }
        }
        currRow = 1 - currRow;
    }
    if (result == 0) {
        return "-1";
    }
    return X.substr(end - result + 1, result);
}
