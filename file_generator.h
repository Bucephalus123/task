#ifndef FILE_GENERATOR_H
#define FILE_GENERATOR_H

#include <string>

// Функция для удаления директории
void clear_directory(const std::string& directory);

// Функция для создания директории
void create_directory(const std::string& directory);

// Функция для генерации случайной строки
std::string generate_random_string(int length);

// Функция для генерации файлов
void generate_files(const std::string& directory, int file_count, int max_random);

#endif // FILE_GENERATOR_H
