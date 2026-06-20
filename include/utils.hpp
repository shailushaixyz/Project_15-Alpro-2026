#pragma once
#include <string>
#include <vector>

using namespace std;

string getCurrentDate();
void clearScreen();
void pauseScreen();
void bersihkanLayar();
void jedaLayar();

int inputChoice(int min, int max);

const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";
const string MAGENTA = "\033[35m";
const string BOLD = "\033[1m";