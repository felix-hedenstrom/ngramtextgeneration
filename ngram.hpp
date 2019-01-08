#ifndef J_NGRAM
#define J_NGRAM

#include <string>
#include <vector>

template<class T>
class ngram{
private:
  const size_t n;
  const std::vector<T> elements;
  ngram();
public:
  ngram(const std::vector<T> & ngram_elements) :
    n(ngram_elements.size()),
    elements(ngram_elements) {}

  size_t size() const {return this->n; }
  size_t get_size() const {return this->size(); }
  const std::vector<T> & get_elements() const { return this->elements; }

  const T operator[](const size_t & i) const {
    return this->elements[i];
  }
};

template<class T>
bool operator< (const ngram<T>& lhs, const ngram<T>& rhs){
  if(lhs.get_size() < rhs.get_size())
    return true;
  else if(rhs.get_size() < lhs.get_size())
    return false;
  for (size_t i = 0; i < lhs.get_size(); i++){
    T lhs_val = lhs.get_elements()[i];
    T rhs_val = rhs.get_elements()[i];
    if(lhs_val < rhs_val){
      return true;
    }else if(rhs_val < lhs_val){
      return false;
    }
  }
  return false;
}

template<class T>
bool operator== (const ngram<T>& lhs, const ngram<T>& rhs){
  if(lhs.get_size() != rhs.get_size())
    return false;
  for (size_t i = 0; i < lhs.get_size(); i++){
    if(lhs.get_elements()[i] != rhs.get_elements()[i]){
      return false;
    }
  }
  return true;
}

bool operator== (const ngram<std::string>& lhs, const ngram<std::string>& rhs){
  if(lhs.get_size() != rhs.get_size())
    return false;
  for (size_t i = 0; i < lhs.get_size(); i++){
    if(lhs.get_elements()[i].compare(rhs.get_elements()[i]) != 0){
      return false;
    }
  }
  return true;
}

template<class T>
bool operator!= (const ngram<T>& lhs, const ngram<T>& rhs){
  return !(lhs == rhs);
}

#endif