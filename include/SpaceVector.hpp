#pragma once

#include <array>
#include <cmath>
#include <initializer_list>
#include <iostream>

/// templated vector type supporting many operator overloads
template <class T, unsigned D = 3> struct SpaceVector {
  std::array<T, D> x = {};

  template <class... ARGS>
  SpaceVector(ARGS &&...args)
      : x{static_cast<T>(std::forward<ARGS>(args))...} {}

  template <class ARG> SpaceVector(ARG &&init) {
    std::fill(x.begin(), x.end(), static_cast<T>(std::forward<ARG>(init)));
  }

  SpaceVector operator+(const SpaceVector &other) const {
    SpaceVector res;
    for (unsigned i = 0; i < D; ++i) {
      res[i] = x[i] + other.x[i];
    }
    return res;
  }

  SpaceVector operator-(const SpaceVector &other) const {
    SpaceVector res;
    for (unsigned i = 0; i < D; ++i) {
      res[i] = x[i] - other.x[i];
    }
    return res;
  }

  // subtract scalar
  template <class U> SpaceVector operator-(U sub) const {
    SpaceVector res;
    for (unsigned i = 0; i < D; ++i) {
      res[i] = x[i] - sub;
    }
    return res;
  }

  /// Element-wise multiplication
  SpaceVector operator*(const SpaceVector &other) const {
    SpaceVector res;
    for (unsigned i = 0; i < D; ++i) {
      res[i] = x[i] * other.x[i];
    }
    return res;
  }

  // divide by scalar
  template <class U> SpaceVector operator/(const U &divisor) const {
    SpaceVector res;
    for (unsigned i = 0; i < D; ++i) {
      res[i] = x[i] / divisor;
    }
    return res;
  }

  template <class U> T &operator[](const U &index) { return x[index]; }

  template <class U> const T &operator[](const U &index) const {
    return x[index];
  }
};

// sqrt function for SpaceVector
template <class T, unsigned D>
SpaceVector<T, D> sqrt(const SpaceVector<T, D> &vec) {
  SpaceVector<T, D> res;
  for (unsigned i = 0; i < D; ++i) {
    res[i] = sqrt(vec[i]);
  }
  return res;
}

// ostream overload for output
template <class T, unsigned D>
std::ostream &operator<<(std::ostream &os, const SpaceVector<T, D> &vec) {
  os << "[ ";
  for (unsigned i = 0; i < D - 1; ++i) {
    os << vec[i] << ", ";
  }
  os << vec[D - 1] << " ]";
  return os;
}