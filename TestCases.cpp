//
//  TestCases.cpp
//  FM131ProjectTest
//
//  Created by Suraj Dayma on 14/05/24.
//

#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include "src/BFS.h"
#include "src/DFS.h"
#include "src/Grid.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace fs = std::__fs::filesystem;
using namespace std;
using namespace std::chrono;

/**
 * @brief Load Image and Populate Grid
 * @param file_path from GlobalVariables.h
 * @return pointer to Grid object
 */
Grid* loadImage(char* file_path) {
    int gridWidth, gridHeight, channels;
    unsigned char *img = stbi_load(
                                   file_path,
                                   &gridWidth,
                                   &gridHeight,
                                   &channels,
                                   0
                                   );
    if(img == NULL) {
        cout << "Error in loading the image" << endl;
        exit(1);
    }
    cout << gridHeight << "x" << gridWidth << " px image loaded with " << channels << " channels." << endl;
    
    Grid* grid = new Grid(gridHeight, gridWidth);
    grid->populateGrid(img, channels);
    
    return grid;
}

// Function to perform BFS and record time
void performBFS(const fs::path& imagePath, ofstream& logFile) {
    cout << "Running BFS on image: " << imagePath << endl;
    
    // Convert fs::path to char*
    string imagePathString = imagePath.string();
    char* imagePathStr = new char[imagePathString.length() + 1]; // +1 for null terminator
    strcpy(imagePathStr, imagePathString.c_str()); // Copying string to char*
    
    Grid* grid = loadImage(imagePathStr);

    auto start = high_resolution_clock::now();
    BFS search(*grid);
    search.solve();
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    
    logFile << "BFS on " << imagePathString << ": " << duration.count() << " microseconds" << endl;

    // Don't forget to deallocate the memory allocated for imagePathStr
    delete[] imagePathStr;
}

void performDFS(const fs::path& imagePath, ofstream& logFile) {
    cout << "Running DFS on image: " << imagePath << endl;
    
    // Convert fs::path to char*
    string imagePathString = imagePath.string();
    char* imagePathStr = new char[imagePathString.length() + 1]; // +1 for null terminator
    strcpy(imagePathStr, imagePathString.c_str()); // Copying string to char*
    
    Grid* grid = loadImage(imagePathStr);

    auto start = high_resolution_clock::now();
    DFS search(*grid);
    search.solve();
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    
    logFile << "DFS on " << imagePathString << ": " << duration.count() << " microseconds" << endl;

    // delete memory allocated for imagePathStr
    delete[] imagePathStr;
}


int main() {
    const string imageFolder = "images/in/"; // Change this to your image folder path
    const string logFilePath = "execution_log.txt"; // Path for the log file
    ofstream logFile(logFilePath);

    if (!logFile.is_open()) {
        cerr << "Error opening log file!" << endl;
        return 1;
    }

    // Iterate over images in the folder
    for (const auto& entry : fs::directory_iterator(imageFolder)) {
        if (entry.is_regular_file()) {
            const fs::path& imagePath = entry.path();
            performBFS(imagePath, logFile);
            performDFS(imagePath, logFile);
        }
    }

    logFile.close();
    cout << "Execution log saved to " << logFilePath << endl;
    return 0;
}
