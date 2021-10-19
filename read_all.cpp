//
// Created by milen on 2021-09-15.
//

#include <iostream>
#include <filesystem>
#include <regex>
#include <set>

using namespace std;
namespace fs = filesystem;

void tmp() {
    fs::path folderName = "s2 t5 n5 r42";
    set<fs::path> sortedFiles;

    for (const auto &entry : fs::directory_iterator(folderName))
        sortedFiles.insert(entry.path());

    for (auto &file : sortedFiles) {

        string name = file.filename().string();

        regex rgx("ex(\\d*)_(\\d*)");
        std::smatch matches;

        if(std::regex_search(name, matches, rgx)) {
            int size = stoi(matches[1].str());
            int instance = stoi(matches[2].str());


        }
    }
}