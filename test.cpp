#include "graph.hpp"
#include "ngram.hpp"
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <utility>

const std::string test_simple_path(){
  std::clog << "Starting simple path test..."  << std::endl;
  std::map<int, std::vector<int>> neighbors;

  neighbors.insert({1, {2, 3, 4}});
  neighbors.insert({2, {1, 3, 4}});
  neighbors.insert({3, {1, 2, 4}});
  neighbors.insert({4, {1, 2, 3}});
  graph<int> g ({1, 2, 3, 4}, neighbors);
  std::list<int> right_path = {1, 4};
  std::list<int> path = g.bfs(1, 4);

  if(path != right_path){
    return "Return did not find the right path.";
  }

  return "";
}

const std::string test_non_existing_path(){
  std::cerr << "Starting non existing path test..." << std::endl;
  std::map<int, std::vector<int>> neighbors;

  neighbors.insert({1, {2, 3, 4}});
  neighbors.insert({2, {1, 3, 4}});
  neighbors.insert({3, {1, 2, 4}});
  neighbors.insert({4, {1, 2, 3}});
  graph<int> g ({1, 2, 3, 4}, neighbors);
  std::list<int> path = g.bfs(1, 5);
  if(path.size() != 0){
    return "Returned a path when there was none.";
  }
  return "";
}

const std::string test_custom_comparator(){
  std::cerr << "Starting custom comparator test..." << std::endl;
  std::map<int, std::vector<int>> neighbors;

  neighbors.insert({1, {2, 4, 5}});
  neighbors.insert({2, {1}});
  neighbors.insert({3, {2, 4}});
  neighbors.insert({4, {1, 3}});
  graph<int> g ({1, 2, 3, 4, 5, 10}, neighbors, [](int a, int b){return (a % 2) == (b % 2);});
  std::list<int> path = g.bfs(1, 10);
  if(path.size() == 2){
    return "";
  }
  return "Returned wrong path.";
}

const std::string test_2gram(){
  ngram<int> n = ngram<int>({1, 2, 3});
  const std::vector<int> elements = n.get_elements();
  for(int i = 0; i < 3; i++){

    if(elements[i] != i + 1){
      return "Elements did not match!";
    }
  }
  return "";
}

const std::string test_accessor(){
  ngram<std::string> n = ngram<std::string>({"This", "is", "a", "test"});
  std::string error = "Wrong access.";
  if(n[0] != "This")
    return error;
  if(n[0] != "is")
    return error;
  if(n[0] != "a")
    return error;
  if(n[0] != "test")
    return error;
  return "";
}

const std::string test_ngram_comparator(){
  if (ngram<std::string>({"I", "am"}) == ngram<std::string>({"am", "a"}))
    return "Found equality when there was none.";
  if (ngram<std::string>({"I", "am"}) != ngram<std::string>({"I", "am"}))
    return "Did not find an equality when there was one.";
  return "";
}

const std::string test_ngram_path(){
  std::clog << "Starting ngram path test..." << std::endl;
  typedef ngram<std::string> testngram;
  std::map<testngram, std::vector<testngram>> neighbors;
  neighbors.insert({ngram<std::string>({"this", "is", "a"}), {ngram<std::string>({"is", "a", "test"}),
                                                             ngram<std::string>({"is", "a", "thing"}),
                                                             ngram<std::string>({"is", "a", "bad"})}});

  neighbors.insert({ngram<std::string>({"is", "a", "test"}), {ngram<std::string>({"a", "test", "to"})}});
  neighbors.insert({ngram<std::string>({"a", "test", "to"}), {ngram<std::string>({"test", "to", "see"})}});
  neighbors.insert({ngram<std::string>({"test", "to", "see"}), {ngram<std::string>({"to", "see", "if"}), ngram<std::string>({"to", "see", "when"})}});
  neighbors.insert({ngram<std::string>({"to", "see", "if"}), {ngram<std::string>({"see", "if", "it"})}});
  neighbors.insert({ngram<std::string>({"see", "if", "it"}), {ngram<std::string>({"if", "it", "works"})}});

  graph<testngram> g ({ngram<std::string>({"this", "is", "a"}), ngram<std::string>({"is", "a", "test"}), ngram<std::string>({"is", "a", "thing"}),
                 ngram<std::string>({"is", "a", "bad"}), ngram<std::string>({"a", "test", "to"}), ngram<std::string>({"test", "to", "see"}),
                 ngram<std::string>({"to", "see", "if"}), ngram<std::string>({"to", "see", "when"}), ngram<std::string>({"see", "if", "it"}),
                 ngram<std::string>({"if", "it", "works"})}, neighbors);


  testngram tn1 = testngram({"this", "is", "a"});
  testngram tn2 = testngram({"if", "it", "works"});
  std::list<testngram> path = g.bfs(tn1, tn2);
  if(path.size() != 7){
    return "Wrong sized path.";
  }
  return "";
}


int main(){
  typedef const std::string (*fp)();
  std::list<fp> tests = {test_custom_comparator, test_simple_path, test_non_existing_path, test_2gram,
                         test_ngram_comparator, test_ngram_path};
  int tests_failed = 0;
  int i = 1;
  for(fp f : tests){
    const std::string answer = (*f)();
    if(answer != ""){
      std::cerr << "Test " << i << " failed with message \"" << answer << "\"."<< std::endl;
      tests_failed++;
    }else{
      std::cerr << "Test " << i << " passed!" << std::endl;
    }
    i++;
  }
  i--;
  std::cerr << "Passed " << i - tests_failed << "/" << i << " tests." << std::endl;
  return tests_failed;
}
