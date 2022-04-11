#ifndef HUFFMAN_CPP_
#define HUFFMAN_CPP_

#include "../lib/huffman.hpp"

#include <iostream>
#include <algorithm>

#define kAsciiMin 32
#define kAsciiMax 165


Huffman::Huffman(){}

Huffman::Huffman(std::string inputfile) {
  inputFileName_ = inputfile;
  inputfile_.open(inputfile.c_str());
  repetitions_.resize(kAsciiMax - kAsciiMin);
  encode();
  createTree();
}

Huffman::~Huffman(){}

void Huffman::encode(void) {
  buildFreqVector();
  buildStructVector();
  createTree();

}

void Huffman::buildStructVector(void) {
  for (int i = 0; i < repetitions_.size(); i++) {
    if (repetitions_.at(i) != 0) {
      Data a;
      a.ascii = i;
      a.chance = repetitions_.at(i);
      data_vector_.push_back(a);
    }
  }
  std::sort(data_vector_.begin(),data_vector_.end());

}

void Huffman::createTree(void) {

}

void Huffman::buildFreqVector(void) {
  int lines = Count_lines(inputFileName_);
  std::string temp;
  char char_ascii;
  int total = 0;
  for (int i = 1; i <= lines; i++) {
    temp = Get_line(inputFileName_,i);
    for (int j = 0; j < temp.size(); j++) {
      char_ascii = temp.at(j);
      repetitions_.at(int(char_ascii) - kAsciiMin) += 1;
      total++;
    }
  }
  for (int i = 0; i < repetitions_.size(); i++) {
    repetitions_.at(i) /= total;
  }
}

std::string Huffman::Get_line(const std::string& filename, const int& line_number) {
  std::ifstream inputfile(filename);
  auto temp(1);
  std::string line;
  while( (!(inputfile.eof())) && (temp < line_number)) {
    std::getline(inputfile, line);
    ++temp;
  }
  std::getline(inputfile, line);
  return line;
}

unsigned Huffman::Count_lines (const std::string file) {
    unsigned lines = 0;
    std::ifstream file_to_count(file);
    std::string unused;
    while (std::getline(file_to_count, unused)) {
        ++lines;
    }
    return lines;
}

std::vector<std::string> Huffman::Split (std::string str, std::string delim) {
  /// @brief this func split in 2 the string and store them in vector, 
  //         depending of the char
  std::vector<std::string> tokens;
  size_t prev = 0, pos = 0;
  do {
    pos = str.find(delim, prev);
    if (pos == std::string::npos) pos = str.length();
    std::string token = str.substr(prev, pos-prev);
    if (!token.empty()) tokens.push_back(token);
    prev = pos + delim.length();
  }
  while (pos < str.length() && prev < str.length());
  return tokens;
}

#endif