#include <fstream>      // ifstream
#include <iostream>     // cout
#include <string>       // string, stoi
#include <string_view>  // string_view
#include <chrono>       // high_resolution_clock, duration_cast, nanoseconds
#include <filesystem>

#include "red_black_tree.hpp"

using namespace std;
using namespace itis;

namespace fs = std::filesystem;

void runFile(string &path, int operationCode, RedBlackTree* tree);
void runAmount(string &rootPath, int amount, ofstream &out);

int main() {
  string dataPath = fs::current_path().string();
  dataPath = dataPath.substr(0, dataPath.size() - 27) + "dataset/data";

  ofstream out;
  out.open("metrics.tsv", ios::app);


  int amounts[] = {100, 500, 5000, 20000, 100000, 500000, 1000000, 2500000, 5000000, 7500000, 10000000};
  out << "set\tamount\ttry\tadd\tsearch\tremove" << "\n";
  cout << "set\tamount\ttry\tadd\tsearch\tremove" << "\n";
  for (int& i : amounts) {
    runAmount(dataPath, i, out);
  }

  out << endl;
  out.close();

  return 0;
}

void runAmount(string &rootPath, int amount, ofstream &out) {
  for (int datasetNumber = 1; true; datasetNumber++) {

      string add = rootPath + "/add/";
      add = add.append(to_string(datasetNumber))
                .append("/")
                .append(to_string(amount))
                .append(".txt");

      string search = rootPath + "/search/";
      search = search.append(to_string(datasetNumber))
                   .append("/")
                   .append(to_string(amount))
                   .append(".txt");

      string remove = rootPath + "/remove/";
      remove = remove.append(to_string(datasetNumber))
                   .append("/")
                   .append(to_string(amount))
                   .append(".txt");

      if (!fs::exists(add) || !fs::exists(search) || !fs::exists(remove))
        break;

    for (int Try = 1; Try < 11; Try++) {
      auto *tree = new RedBlackTree;

      out << datasetNumber << "\t" << amount << "\t" << Try << "\t";
      const auto preAddStamp = chrono::high_resolution_clock::now();

      runFile(add, 0, tree);
      const auto postAddStamp = chrono::high_resolution_clock::now();
      out << chrono::duration_cast<chrono::nanoseconds>(postAddStamp - preAddStamp).count() << "\t";

      runFile(search, 1, tree);
      const auto postSearchStamp = chrono::high_resolution_clock::now();
      out << chrono::duration_cast<chrono::nanoseconds>(postSearchStamp - postAddStamp).count() << "\t";

      runFile(remove, 2, tree);
      const auto postRemoveStamp = chrono::high_resolution_clock::now();
      out << chrono::duration_cast<chrono::nanoseconds>(postRemoveStamp - postSearchStamp).count() << "\t" << "\n";

      cout << datasetNumber << "\t" << amount << "\t" << Try << "\t";
      cout << chrono::duration_cast<chrono::nanoseconds>(postAddStamp - preAddStamp).count() << "\t";
      cout << chrono::duration_cast<chrono::nanoseconds>(postSearchStamp - postAddStamp).count() << "\t";
      cout << chrono::duration_cast<chrono::nanoseconds>(postRemoveStamp - postSearchStamp).count() << "\t" << "\n";

      delete tree;
    }
  }
}

void runFile(string &path, int operationCode, RedBlackTree* tree) {
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
