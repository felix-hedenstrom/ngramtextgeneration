#ifndef J_GRAPH
#define J_GRAPH

#include <list>
#include <map>
#include <exception>
#define DEBUG 1

template<class T>
bool default_equals(T a, T b){
  return a == b;
}

template<class T>
class graph{
private:
  graph();
  const std::vector<T> nodes;
  const std::map<T, std::vector<T>> neighbors;
  bool (*equals)(T, T);
public:
  graph(std::vector<T> graph_nodes, std::map<T, std::vector<T>> graph_neighbors) : nodes(graph_nodes), neighbors(graph_neighbors), equals([](T a, T b){return a == b;}) {}
  graph(std::vector<T> graph_nodes, std::map<T, std::vector<T>> graph_neighbors, bool (*equals_function)(T, T)) : nodes(graph_nodes), neighbors(graph_neighbors), equals(equals_function) {}
  std::list<T> bfs(const T & start, const T & end) const {
    std::map<T, bool> visited = std::map<T, bool>();
    std::map<T, T const *> last_node = std::map<T,T const *>();

    for (T edge : this->nodes)
      visited[edge] = false;

    T const * current_element = &start;
    T const * last_element = nullptr;

    std::list<T> queue;
    visited[*current_element] = true;
    queue.push_back(*current_element);

    while(!queue.empty()){
      if(DEBUG){
        std::clog << "was at " << *current_element << std::endl;
        std::clog << "am at" << queue.front() << std::endl;
      }
      current_element = &queue.front();
      queue.pop_front();
      if(*current_element == end){
        if(DEBUG){
          std::cerr << "Found end!" << std::endl;
        }
        last_element = current_element;
        break;
      }

      for(const T & neighbor : this->neighbors.find(*current_element)->second){

        if(!visited[neighbor]){
          visited[neighbor] = true;
          queue.push_back(neighbor);
          last_node[neighbor] = current_element;
        }
      }
    }

    if(last_element == nullptr){
      if(DEBUG){
        std::cerr << "Didn't find any path..." << std::endl;
      }
      return std::list<T>();
    }else if (DEBUG){
      std::cerr << "Found a path!" << std::endl;
    }
    std::list<T> answer = std::list<T>({*last_element});
    if(DEBUG){
      std::clog << "Ends with " << *last_element << std::endl;
      std::clog << "and you can get there from " << *last_node[*last_element] << std::endl;
    }
    while(*last_node[answer.front()] != start){
      answer.push_front(*last_node[answer.front()]);
    }
    answer.push_front(start);
    return answer;

  }
};
#endif
