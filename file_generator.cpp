#include <iostream>
#include "file_generator.h"
#include <fstream>
#include <filesystem>
#include <ctime>


using namespace std;
namespace fs = filesystem;

void create_directory(const string& directory)
{
    filesystem::create_directories(directory);
}

void clear_directory(const string& directory)
{
    if (fs::exists(directory))
    {
        fs::remove_all(directory); // Удаляем все содержимое директории
    }
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

void generate_files(const string& directory, int file_count, int max_depth)
{
    srand(time(NULL));

    for (int fileIndex = 0; fileIndex < file_count; fileIndex++)
    {
        // Генерируем случайную глубину для файла от 0 до max_depth
        int random_depth = rand() % (max_depth + 1);

        // Создаем путь к файлу с учётом глубины
        string file_path = directory;
        for (int depth = 0; depth < random_depth; depth++)
        {
            file_path += "/subdir_" + to_string(depth); // Вложенные директории
        }

        // Создаем необходимые директории
        fs::create_directories(file_path); // Если директория уже существует, то ничего не делает

        // Создаем сам файл
        string fileName = file_path + "/file_" + to_string(fileIndex) + ".txt";
        ofstream file(fileName);

        if (file.is_open())
        {
            int max_len = rand() % 2048 + 2048; // От 2 до 4 Кб текста
            string random_word = generate_random_string(max_len);

            // Записываем глубину в файл и случайный текст
            file << random_depth << " " << random_word;
            file.close();
        }
        else
        {
            wcout << L"Не удалось открыть файл для записи: ";
            cout << fileName << endl;
        }
    }
}
