#include <iostream>
#include "file_generator.h"
#include <fstream>
#include <filesystem>
#include <ctime>


using namespace std;

void create_directory(const string& directory)
{
    filesystem::create_directories(directory);
}

string generate_random_string(int length)
{
    string letters = "abcdefghijklmnopqrstuvwxyz";
    string result = "";
    for (int i = 0; i < length; i++) {
        result += letters[rand() % letters.size()];
    }
    return result;
}

void generate_files(const string& directory, int file_count,  int max_random)
{
    srand((time(NULL)));
    for (int fileIndex = 0; fileIndex < file_count; fileIndex++)
        {
        string fileName = directory + "/file_" + to_string(fileIndex) + ".txt";
        ofstream file(fileName);

        if (file.is_open())
        {
            int max_len = rand() % 2048 + 2048; // От 2 до 4 Кб
            string random_word = generate_random_string(max_len);
            file << (rand() % max_random + 1) << " " << random_word;
            file.close();
        } else
        {
            wcout << L"Не удалось открыть файл для записи: ";
            cout << fileName << endl;
        }
    }
}
