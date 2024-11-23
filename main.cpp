#include <iostream>
#include "file_generator.h"
#include <vector>
#include <algorithm>
#include <string>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = filesystem; // Для лаконичности

// Функция для чтения файла
void  readFile(const fs::path& filePath, vector<string>& content) // Принимает путь к файлу
{
    ifstream file(filePath);

    // Вычисляем глубину
    int depth = distance(filePath.begin(), filePath.end()) - 2; // Глубина относительно директории output_files
    string fileName = filePath.filename().string(); // Получаем имя файла

    // Очищаем вектор для записи содержимого файла
    content.clear();
    file >> depth; // Перезаписываем глубину из файла, хотя можно это не делать
    string line;
    while (!file.eof())
    {
        getline(file, line); // Считываем текст
        content.push_back(line); // Записываем текст в вектор
    }
    wcout << L"Имя файла: ";
    cout << fileName;
    wcout << L", Глубина: ";
    cout << depth << endl;
    /*for (const string& line : content) {
        cout << line << endl; // Проверка содержимого файла
    }*/
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Генерируем файлы
    const int N = 10; // Максимальная глубина
    const int file_count = 200; // Количество файлов
    const string directory = "output_files";
    clear_directory(directory); /* Чтобы при перезапуске программы не накапливались
                                файлы в поддиректориях*/
    create_directory(directory);
    generate_files(directory, file_count, N);
    wcout << L"Файлы успешно созданы" << endl;

    vector<string> fileContent;

    // Обход всех файлов в каталоге
    // При помощи filesystem запускаем рекурсивный итератор для директории output_files
    // Если у файлов одна глубина, то вывод происходит в лексиграфическом порядке по названию файлов
    for (const auto& file : fs::recursive_directory_iterator(directory))
    {
        if (file.is_regular_file()) // Проверка, что это файл
        {
            readFile(file.path(), fileContent); // Читаем файл и выводим информацию
        }

    }
    return 0;
}
