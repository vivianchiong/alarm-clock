#include <iostream>

#include "timer.cpp"

template <typename T>
void enterInput(const std::string& str, T& arg)  {
    do {
        if (std::cout << str && std::cin >> arg) break;
        std::cout << "Invalid input, please re-enter ... " << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (true);

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main(int argc, char* const argv[]) {
    int timerSeconds = 0;
    enterInput<int>("Enter number of seconds: ", timerSeconds);

    setAlarm(timerSeconds);
}