#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <iostream>
#include "graph.hpp"
#include "test.hpp"

#define TEST 1

int main(){
  if(TEST){
    int result = test_all();
    if (result != 0){
      return result;
    }
  }

  Json::Value ngrams;

  std::ifstream ngramfile("talk3gram.json", std::ifstream::binary);

  ngramfile >> ngrams;

  std::cout << ngrams["jag"]["heter"] << std::endl;
}
