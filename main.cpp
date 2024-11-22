#include <iostream>
#include "file_generator.h"
#include <vector>
#include <algorithm>
#include <string>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = filesystem; // Для лаконичности

struct FileData
{
    int depth;
    string name;
    vector<string> content;
};

// Функция для чтения файла
FileData readFile(const fs::path& filepath) // Принимает путь к файлу
{
    ifstream file(filepath);
    FileData fileData;
    file >> fileData.depth; // Записываем глубину
    fileData.name = filepath.filename().string(); // Записываем имя файла при помощи .filename()

    string line;
    while (!file.eof())
    {
        getline(file, line); // Считываем текст
        fileData.content.push_back(line); // Записываем текст в структуру
    }

    return fileData; // Функция возвращает структуру
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Генерируем файлы
    const int N = 10000; // Максимальная глубина
    const int file_count = 200; // Количество файлов
    const string directory = "output_files";
    create_directory(directory);
    generate_files(directory, file_count, N);
    wcout << L"Файлы успешно созданы" << endl;

    vector<FileData> files; // Создаём вектор структур, чтобы хранить данные обо всех файлах

    // Обход всех файлов в каталоге
    // При помощи filesystem запускаем iterator для нашей директории directory
    for (const auto& file : fs::directory_iterator(directory))
    {
        FileData fileData = readFile(file.path()); // Считываем данные из файла в структуру
        files.push_back(fileData); // Добавляем структуру в вектор структур
    }

    // Сортировка файлов по глубине
    sort(files.begin(), files.end(), [](const FileData& a, const FileData& b)
    {
        return a.depth < b.depth;
    });

    for (const auto& file : files)
    {
        wcout << L"Имя файла: ";
        cout << file.name;
        wcout << L", Глубина: ";
        cout << file.depth << endl;
    }

    return 0;
}
