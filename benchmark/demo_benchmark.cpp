#include <fstream>      // ifstream
#include <iostream>     // cout
#include <string>       // string, stoi
#include <string_view>  // string_view
#include <chrono>       // high_resolution_clock, duration_cast, nanoseconds
#include <sstream>      // stringstream
#include <filesystem>

// подключаем вашу структуру данных
#include "red_black_tree.hpp"

using namespace std;
using namespace itis;

namespace fs = std::filesystem;

void runFile(string &path, int operationCode, RedBlackTree* tree);
void runAmount(string &rootPath, int amount);

int main() {
  string dataPath = fs::current_path().string();
  dataPath = dataPath.substr(0, dataPath.size() - 27) + "dataset\\data";

  auto* tree  = new RedBlackTree();

  int amounts[] = {100, 500, 5000, 20000, 100000, 500000, 1000000, 2500000, 5000000, 7500000, 10000000};
  cout << "set\tamount\tadd\tsearch\tremove" << endl;
  for (int& i : amounts) {
    runAmount(dataPath, i);
  }

  return 0;
}

void runAmount(string &rootPath, int amount) {
  for (int i = 1; true; i++) {
    auto* tree = new RedBlackTree();

    string add = rootPath + "\\add\\";
    add = add.append(to_string(i))
              .append("\\")
              .append(to_string(amount))
              .append(".txt");

    string search = rootPath + "\\search\\";
    search = search.append(to_string(i))
                 .append("\\")
                 .append(to_string(amount))
                 .append(".txt");

    string remove = rootPath + "\\remove\\";
    remove = remove.append(to_string(i))
                 .append("\\")
                 .append(to_string(amount))
                 .append(".txt");

    if (!fs::exists(add) || !fs::exists(search) || !fs::exists(remove)) break;

    const auto time_point_before = chrono::high_resolution_clock::now();
    cout << i << "\t" << amount << "\t";

    runFile(add, 0, tree);
    const auto time_point_after_add = chrono::high_resolution_clock::now();

    runFile(search, 1, tree);
    const auto time_point_after_search = chrono::high_resolution_clock::now();

    runFile(remove, 2, tree);
    const auto time_point_after_remove = chrono::high_resolution_clock::now();

    cout << chrono::duration_cast<chrono::nanoseconds>(time_point_after_add - time_point_before).count();
    cout << "\t";
    cout << chrono::duration_cast<chrono::nanoseconds>(time_point_after_search - time_point_after_add).count();
    cout << "\t";
    cout << chrono::duration_cast<chrono::nanoseconds>(time_point_after_remove - time_point_after_search).count();
    cout << "\t" << endl;

    delete tree;
  }
}

void runFile(string &path, int operationCode, RedBlackTree* tree) {
  // cout << "BEGU!!1 " << path << endl;

  ifstream file(path);

  string buffer;
  getline(file, buffer);
  int amountOfNumbers = stoi(buffer);
  for (int i = 0; i < amountOfNumbers; ++i) {
    getline(file, buffer);
    int integer = stoi(buffer);
    switch (operationCode) {
      case 0:
        tree->insert(integer);
        break;
      case 1:
        tree->find(integer);
        break;
      case 2:
        tree->remove(integer);
        break;
      default:
        break;
    }
  }
}


// абсолютный путь до набора данных и папки проекта
static constexpr auto kDatasetPath = string_view{PROJECT_DATASET_DIR};
static constexpr auto kProjectPath = string_view{PROJECT_SOURCE_DIR};

int mains(int argc, char **argv) {

  // Tip 1: входные аргументы позволяют более гибко контролировать параметры вашей программы

  // Можете передать путь до входного/выходного файла в качестве аргумента,
  // т.е. не обязательно использовать kDatasetPath и прочие константы

  for (int index = 0; index < argc; index++) {
    cout << "Arg: " << argv[index] << '\n';
  }

  // Tip 2: для перевода строки в число можете использовать функцию stoi (string to integer)

  // можете использовать функционал класса stringstream для обработки строки
  auto ss = stringstream("0 1 2");  // передаете строку (входной аргумент или строку из файла) и обрабатываете ее

  int number = 0;
  ss >> number;  // number = 0
  ss >> number;  // number = 1
  ss >> number;  // number = 2

  // работа с набором данных
  const auto path = string(kDatasetPath);
  cout << "Path to the 'dataset/' folder: " << path << endl;

  auto input_file = ifstream(path + "/dataset-example.csv");

  if (input_file) {
    // чтение и обработка набора данных ...
  }

  // Контрольный тест: операции добавления, удаления, поиска и пр. над структурой данных

  // Tip 3: время работы программы (или участка кода) можно осуществить
  // как изнутри программы (std::chrono), так и сторонними утилитами



  return 0;
}
