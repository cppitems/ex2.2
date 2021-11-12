#include <cmath>
#include <vector>

/*
  Part 1:
  Implement a type "Distribution" here with the following properties:
  - "Distribution" should be a class template with a single template type
  - two public member variables "mean" and "stddev"
  - public member typedef "value_type" which aliases the template parameter
  - two constructors:
    - Distribution(T mean, T stddev) which sets the two member variables
    - Distribution(const std::vector<T> &data) which calculates
      the two member variables from a Distribution of data
  Part 2:
  Change the constructor "Distribution(const std::vector<T>&)" so it
  accepts any STL data structure (not just std::vector) and 
  the class template parameter T is still deduced automatically,
  so an object can be constructed using "Distribution(<anySTLcontainer>)"
*/
