#include <iostream>
#include <cstdio>
#include <vector>
#include <Windows.h>

std::string generateRandomName(const std::vector<std::string>& possibleNames) {
    std::srand(static_cast<unsigned>(std::time(0)));
    int randomIndex = std::rand() % possibleNames.size();
    return possibleNames[randomIndex];
}

void renameFile() {
    //std::vector<std::string> possibleNames = { "steam" };
    //std::string randomFileName = generateRandomName(possibleNames);

    //char buffer[MAX_PATH];
    //GetModuleFileName(nullptr, buffer, MAX_PATH);
    //std::string currentExecutable = buffer;

    //std::string newFileName = randomFileName + ".exe";

    //if (std::rename(currentExecutable.c_str(), newFileName.c_str()) == 0) {
    //    std::cout << "";
    //}
    //else {
    //    std::cerr << "";
    //}
}
