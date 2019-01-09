#ifndef J_NGRAM
#define J_NGRAM

#include <string>
#include <vector>
#include <iostream>

template<class T>
class ngram{
private:
  const size_t n;
  const std::vector<T> * const elements;
  ngram() : n(0), elements(new std::vector<T>()) {}
public:
  ngram(const std::vector<T> & ngram_elements) :
    n(ngram_elements.size()),
    elements(new std::vector<T>(ngram_elements.begin(), ngram_elements.end())) {}
  size_t size() const {return this->n; }
  size_t get_size() const {return this->size(); }

  // Return a copy of the elements in the ngram
  const std::vector<T> & get_elements() const { return *this->elements; }

  // Overloading [] operator
  const T operator[](const size_t & i) const {
    return (*this->elements)[i];
  }

  // Overloading << needs access to private variables
  template <class Y>
  friend std::ostream& operator<<(std::ostream& stream, const ngram<Y> n);

};

// Overloading <
template<class T>
bool operator< (const ngram<T>& lhs, const ngram<T>& rhs){
  if(lhs.get_size() < rhs.get_size())
    return true;
  else if(rhs.get_size() < lhs.get_size())
    return false;
  for (size_t i = 0; i < lhs.get_size(); i++){
    const T & lhs_val = lhs.get_elements()[i];
    const T & rhs_val = rhs.get_elements()[i];
    if(lhs_val < rhs_val){
      return true;
    }else if(rhs_val < lhs_val){
      return false;
    }
  }
  return false;
}

// Overloading <<
template<class T>
std::ostream& operator<<(std::ostream& stream, const ngram<T> n){
  stream << "{" << (*n.elements)[0];
  for (size_t i = 1; i < (*n.elements).size(); i++){
    stream << ", " << (*n.elements)[i];
  }
  stream << "}";
  return stream;
}

// Overloading ==
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

// Overloading == for strings
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

// Overloading !=
template<class T>
bool operator!= (const ngram<T>& lhs, const ngram<T>& rhs){
  return !(lhs == rhs);
}

#endif
