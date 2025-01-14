#include "console_title_animator.h"
#include <cstdlib>
#include <ctime>
#include <Windows.h>

std::string generateRandomAlphaNumeric() {
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const int length = 50;

    std::string randomAlphaNumeric;
    for (int i = 0; i < length; ++i) {
        randomAlphaNumeric += characters[rand() % characters.length()];
    }
    return randomAlphaNumeric;
}

void animateConsoleTitle() {
    while (true) {
        std::string randomAlphaNumeric = generateRandomAlphaNumeric();
        SetConsoleTitleA(randomAlphaNumeric.c_str());
        Sleep(100);
    }
}