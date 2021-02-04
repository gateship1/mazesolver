#ifndef COMPARE_PAIRS_HEADER_FILE
#define COMPARE_PAIRS_HEADER_FILE

#include <utility> // std::pair

/* compare_pairs
  
  compares a pair by compairing the first elements, and if necessary, the second
  
  parameters:
    pair1, pair2, the pairs to compare

  return:
    if the first element of both pairs are equal, 
      returns true is the second element of the first pair is less than the second element of the second pair
      otherwise returns false
    if the first element of both pairs are not equal,
      returns true is the first element of the first pair is less than the first element of the second pair
      otherwise returns false
*/
template <typename type>
auto compare_pairs(const std::pair<type, type>& pair1, const std::pair<type, type>& pair2) -> bool {
    return (pair1.first == pair2.first) ? (pair1.second < pair2.second) : (pair1.first < pair2.first);
}

#endif // COMPARE_PAIRS_HEADER_FILE