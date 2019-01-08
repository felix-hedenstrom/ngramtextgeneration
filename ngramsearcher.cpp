#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <iostream>
#include "graph.hpp"

int main(){

  Json::Value ngrams;

  std::ifstream ngramfile("talk3gram.json", std::ifstream::binary);

  ngramfile >> ngrams;

  std::cout << ngrams["jag"]["heter"] << std::endl;
}
