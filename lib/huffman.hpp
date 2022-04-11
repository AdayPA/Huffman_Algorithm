#ifndef HUFFMAN_HPP_
#define HUFFMAN_HPP_

#include <string>
#include <fstream>
#include <vector>

struct Data {
  int ascii;
  float chance;
  bool operator <( Data a) {
    if (this->chance < a.chance) return true;
    else return false;
  }   
};


class Huffman {

  public:

    Huffman();
    Huffman(std::string);
    ~Huffman();
    
  private:
    void encode(void);
    void buildFreqVector(void);
    void buildStructVector(void);
    void createTree(void);
    unsigned Count_lines (const std::string);
    std::string Get_line (const std::string&, const int&);
    std::vector<std::string> Split (std::string, std::string);

    std::ifstream inputfile_;
    std::string inputFileName_;
    std::vector<float> repetitions_;
    std::vector<Data> data_vector_;

};

#endif