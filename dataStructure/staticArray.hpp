#ifndef STATIC_ARRAY_HPP
#define STATIC_ARRAY_HPP
// Includes
#include <stdexcept> // For std::out_of_range
/**
 * Class that defines a static array with a fixed size.
 *
 * @tparam T Type of the elements in the array.
 * @tparam N Number of elements in the array.
 */
template <typename T, unsigned int N> class StaticArray {
public:
  /**
   * Default constructor. The elements are not initialized.
   */
  StaticArray() = default;
  /**
   * Constructor that fills all elements with a value.
   *
   * @param[in] value The value to fill the array with.
   */
  StaticArray(const T &value) {
    for (unsigned int i = 0; i < N; ++i)
      data_[i] = value;
  }
  /**
   * Constructor that copies the elements from an array.
   *
   * @param[in] arr The array to copy.
   */
  StaticArray(const StaticArray &arr) {
    for (unsigned int i = 0; i < N; ++i)
      data_[i] = arr.data_[i];
  }
  /**
   * Copy assignment operator.
   *
   * @param[in] arr The array to copy.
   */
  void operator=(const StaticArray &arr) {
    for (unsigned int i = 0; i < N; ++i)
      data_[i] = arr.data_[i];
  }
  /**
   * Returns the size of the array.
   */
  unsigned int size() const { return N; }
  /**
   * Checks if the array is empty.
   */
  bool empty() const { return N == 0; }
  /**
   * Access an element of the array (without bound checking).
   *
   * @param[in] index The index of the element to access.
   *
   * @return The element at the given index.
   */
  T &operator[](std::size_t index) { return data_[index]; }
  /**
   * Access an element of the array (without bound checking).
   *
   * @param[in] index The index of the element to access.
   *
   * @return The element at the given index.
   */
  const T &operator[](std::size_t index) const { return data_[index]; }
  /**
   * Access an element of the array (with bound checking).
   *
   * @param[in] index The index of the element to access.
   *
   * @return The element at the given index.
   */
  T &at(std::size_t index) {
    if (index >= N)
      throw std::out_of_range("Index out of range");
    return data_[index];
  }
  /**
   * Access an element of the array (with bound checking).
   *
   * @param[in] index The index of the element to access.
   *
   * @return The element at the given index.
   */
  const T &at(std::size_t index) const {
    if (index >= N)
      throw std::out_of_range("Index out of range");
    return data_[index];
  }
  /**
   * Access the first element of the array.
   */
  T &front() { return data_[0]; }
  /**
   * Access the first element of the array.
   */
  const T &front() const { return data_[0]; }
  /**
   * Access the last element of the array.
   */
  T &back() { return data_[N - 1]; }
  /**
   * Access the last element of the array.
   */
  const T &back() const { return data_[N - 1]; }
  /**
   * Fills all elements with a value.
   *
   * @param[in] value The value to fill the array with.
   */
  void fill(const T &value) {
    for (unsigned int i = 0; i < N; ++i)
      data_[i] = value;
  }
  /**
  * Finds the index of a value in the array.
  *
  * @param[in] value The value to be found.
  *
  * @return The index of the value in the array, or -1 if the value is not
  found.
  */
  int find(const T &value) {
    int index = -1;
    for (int i = 0; i < (int)N; ++i) {
      if (data_[i] == value) {
        index = i;
        break;
      }
    }
    return index;
  }

private:
  T data_[N]; /**< Array of elements. */
};
#endif
