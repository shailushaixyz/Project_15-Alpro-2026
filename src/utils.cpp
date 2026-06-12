#include "utils.hpp"
#include <ctime>

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string date = to_string(ltm->tm_mday) + "-" +
                  to_string(1 + ltm->tm_mon) + "-" +
                  to_string(1900 + ltm->tm_year);

    return date;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
