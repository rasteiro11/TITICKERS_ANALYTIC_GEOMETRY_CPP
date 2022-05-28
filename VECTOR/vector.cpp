#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <vector>

class DiffVecSpaceError : std::exception {};

class Vector {
private:
  std::vector<double> vec;

public:
  Vector(std::vector<double> vec);
  double get(size_t index);
  void set(size_t index, double value);
  std::vector<double> &getVector();
  friend std::ostream &operator<<(std::ostream &o, const Vector &vec);
  Vector &operator+(const Vector &other);
};

Vector::Vector(std::vector<double> vec) { this->vec = vec; }

std::ostream &operator<<(std::ostream &out, const Vector &vec) {
  std::vector<double> temp_vec = vec.vec;
  out << "(";
  for (int i = 0; i < temp_vec.size(); i++) {
    (i == temp_vec.size() - 1) ? out << temp_vec.at(i)
                               : out << temp_vec.at(i) << ", ";
  }
  out << ")";
  return out;
}

std::vector<double> &Vector::getVector() { return this->vec; }

double Vector::get(size_t index) { return this->vec.at(index); }

void Vector::set(size_t index, double value) {
  this->getVector()[index] = value;
}

Vector &Vector::operator+(const Vector &other) {

  if (this->vec.size() != other.vec.size()) {
    throw DiffVecSpaceError();
  }

  Vector *temp = new Vector(other.vec);
  int i = 0;
  for (double d : this->getVector()) {
    temp->vec[i] += d;
    i++;
  }
  return *temp;
}

int main() {
  Vector *vec = new Vector(std::vector<double>({1, 2, 3, 4, 5, 6}));
  std::cout << *vec << std::endl;
  std::cout << vec->getVector().at(0) << std::endl;
  vec->set(0, 69);
  std::cout << vec->getVector().at(0) << std::endl;

  Vector *vec_1 = new Vector(std::vector<double>({210, 210}));
  Vector *vec_2 = new Vector(std::vector<double>({210, 210}));
  Vector vec_3 = *vec_1 + *vec_2;
  std::cout << vec_3 << std::endl;
}