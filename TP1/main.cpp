#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <getopt.h>
#include <cmath>
#include "Matrix.h"
#include "Algorithm.h"
#include "chrono"
#include "Strassen.hpp"

using namespace std;

static int printFlag;
static int timeFlag;
static string algorithmType;
static string pathM1;
static string pathM2;

//From https://slaystudy.com/c-split-string-by-space-into-vector/
void splitString(const string& s, vector<int> &v){

    string temp;
    for(char i : s) {
        if(i == ' ') {
            v.push_back(stoi(temp));
            temp = "";
        }
        else {
            temp.push_back(i);
        }
    }
    v.push_back(stoi(temp));
}

Matrix getMatrixFromFileName(const string& fileName) {
    ifstream fileStream(fileName);
    string line;
    getline(fileStream, line);
    int size = (int)pow(2, stoi(line));
    int** matrixData = new int*[size];

    for(int i=0; i<size; i++)
        matrixData[i] = new int[size];

    for (int i = 0; i < size; ++i) {
        getline(fileStream, line);
        vector<int> matrixLine;
        splitString(line, matrixLine);
        for (int j=0;j<size;j++) {
            matrixData[i][j] = matrixLine[j];
        }
    }
    fileStream.close();

    return {matrixData, size};
}

Matrix getResult(const Matrix &matrix1, const Matrix &matrix2, const string &algorithmType) {
    if (algorithmType == "conv") {
        return Algorithm::classic(matrix1, matrix2);
    }
    if (algorithmType == "strassen") {
        return Algorithm::recursif(matrix1, matrix2);
    }
    return Algorithm::recursifAvecLimite(matrix1, matrix2, 16);
}

// Inspired from https://linux.die.net/man/3/getopt_long_only
void parseFlags(int argc, char** argv) {
    int c;

    while (true)
    {
        static struct option long_options[] =
                {
                        /* These options set a flag. */
                        {"p", no_argument,       &printFlag, 1},
                        {"t", no_argument,       &timeFlag, 1},
                        /* These options don’t set a flag.
                           We distinguish them by their indices. */
                        {"a", required_argument, 0, 'a'},
                        {"e1", required_argument, 0, 'b'},
                        {"e2", required_argument,0, 'c'},
                        {0, 0, 0, 0}
                };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long_only(argc, argv, "a:b:c:",
                             long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c)
        {
            case 'a':
                algorithmType = optarg;
                break;

            case 'b':
                pathM1 = optarg;
                break;

            case 'c':
                pathM2 = optarg;
                break;
        }
    }
    /* Print any remaining command line arguments (not options). */
    if (optind < argc)
    {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        putchar ('\n');
    }
}

int main(int argc, char** argv) {
    parseFlags(argc, argv);
    Matrix matrix1 = getMatrixFromFileName(pathM1);
    Matrix matrix2 = getMatrixFromFileName(pathM2);
    auto start = chrono::steady_clock::now();

    Matrix result = getResult(matrix1, matrix2, algorithmType);

    auto end = chrono::steady_clock::now();
    auto diff = end - start;

    if (printFlag) {
        cout << result.toString();
    }
    if (timeFlag) {
        cout <<  chrono::duration <double, milli> (diff).count();
    }
    cout << endl;





    /*auto start2 = chrono::steady_clock::now();

    int** result2 = strassenMultiply(matrix1.getData(), matrix2.getData(), matrix1.getSize());

    auto end2 = chrono::steady_clock::now();
    auto diff2 = end2 - start2;

        cout << "\n test: \n";

        cout <<  chrono::duration <double, milli> (diff2).count();*/

    return 0;
}
