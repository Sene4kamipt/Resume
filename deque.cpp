#include <iostream>

#include <vector>

#include <iostream>

#include <cassert>

template < typename T >
class Deque {
private:
  //help_function
  void SetThreeArrays(std::vector<T*>& external_);

public:

  //default constructor
  Deque() 
      : first_elem_(0), 
        first_pointer_(0), 
        last_elem_(0), 
        last_pointer_(0), 
        sz_(0) {
    external_ = std::vector<T*>(3, nullptr);
    SetThreeArrays(external_);
    iter_on_begin_ = Deque<T>::iterator(&external_[0], first_elem_);
    iter_on_end_ = Deque<T>::iterator(&external_[0], last_elem_);
  }

  //copying constructor
  Deque(const Deque& deq) : Deque() {
    for (size_t i = 0; i < deq.size(); ++i) {
      try {
        this->push_back(deq[i]);
      }
      catch (...) {
        for (size_t j = 0; j < i; ++j) {
          this->pop_back();
        }
        throw;
      }
    }
    for (size_t i = 0; i < this->size() - deq.size(); ++i) {
      this->pop_front();
    }
  }

  //Constructor of int
  Deque(const size_t size) : Deque() {
    external_.resize((size / size_of_arrays_) + 2);  
    for (size_t i = 0; i < external_.size(); ++i) {  
      T* arr = reinterpret_cast<T*> (new uint8_t[(size_of_arrays_ + 2) * sizeof(T)]);
      T* pointer = &(arr[0]);
      external_[i] = pointer;
    }
    first_elem_ = 0;
    sz_ = size;
    first_pointer_ = 1;
    last_elem_ = size % size_of_arrays_;
    last_pointer_ = size / size_of_arrays_ + 1;
    iter_on_begin_ = Deque<T>::iterator(&external_[1], first_elem_);
    iter_on_end_ = Deque<T>::iterator(&external_[1], last_elem_);
  }

  //constructor of int & value
  Deque(const size_t size,
    const T& value) : Deque() {
    for (size_t i = 0; i < size; ++i) {
      try {
        this->push_back(value);
      }
      catch (...) {
        for (size_t j = 0; j < i; ++j) {
          this->pop_back();
        }
      }
    }
    iter_on_begin_ = Deque<T>::iterator(&external_[first_pointer_]
      , first_elem_);
    iter_on_end_ = Deque<T>::iterator(&external_[last_pointer_]
      , last_elem_);
  }

  //operator =
  Deque& operator=(const Deque& deq);

  //destructor
  ~Deque() {
    if (!external_.empty()) {
      for (size_t i = first_elem_; i < size_of_arrays_; ++i) {
        (external_[first_pointer_] + i)->~T();
      }
      for (size_t i = first_pointer_ + 1; i < last_pointer_; ++i) {
        for (size_t j = 0; j < size_of_arrays_; ++j) {
          (external_[i] + j)->~T();
        }
      }
      if (first_pointer_ != last_pointer_) {
        for (size_t i = 0; i < last_elem_; ++i) {
          (external_[last_pointer_] + i)->~T();
        }
      }
    }
    for (size_t i = 0; i < external_.size(); ++i) {
      if (external_[i] != nullptr) { 
        delete[] reinterpret_cast<uint8_t*> (external_[i]);
      }
    }
  }

  //method size()
  size_t size() const;

  //notconst method []
  T& operator[](const size_t index_);

  //const method []
  const T& operator[](const size_t index_) const;

  // notconst method at()
  T& at(const size_t index_);

  //const method at()
  const T& at(const size_t index_) const;

  //method push_back() 
  void push_back(const T& value);

  //method pop_back
  void pop_back();

  //method push_front
  void push_front(const T& value);

  //method pop_front
  void pop_front();
    
  //struct random-access iterator
  template <bool constancy>
  class Iterator {
  private:
    T** pointer_to_array_ = nullptr;
    long long index_ = 0;
    friend class Deque<T>;
  public:
    using pointer = typename std::conditional<constancy, const T*, T*>::type;
    using reference = typename std::conditional<constancy, const T&, T&>::type;
    using iterator_category = std::random_access_iterator_tag;
    using value_type = std::conditional_t<constancy, const T, T>;
    using difference_type = int;
    using iterator_traits = std::iterator_traits<Iterator<constancy>>;
        
    //default constructor
    Iterator() = default;

    //default destructor
    ~Iterator() = default;

    //constructor of pointer_to_array and index
    Iterator(T** pointer, size_t index_) : pointer_to_array_(pointer),
      index_(index_) {}

    //copy constructor
    Iterator(const Iterator<false>& iter) {
      pointer_to_array_ = iter.pointer_to_array_;
      index_ = iter.index_;
    }

    //operator =
    Iterator& operator=(const Iterator<false>& iter) {
      pointer_to_array_ = iter.pointer_to_array_;
      index_ = iter.index_;
      return *this;
    }

    //operator prefix ++
    Iterator& operator++() {
      if (index_ < size_of_arrays_ - 1) {
        ++index_;
        return *this;
      } else {
        ++pointer_to_array_;
        index_ = 0;
        return *this;
      }
    }

    //operator postfix ++
    Iterator operator++(int) {
      Iterator answer = *this;
      if (index_ < size_of_arrays_ - 1) {
        ++index_;
      } else {
        ++pointer_to_array_;
        index_ = 0;
      }
      return answer;
    }

    Iterator& operator--() {
      if (index_ != 0) {
        --index_;
        return *this;
      } else {
        --pointer_to_array_;
        index_ = size_of_arrays_ - 1;
        return *this;
      }
    }

    Iterator operator--(int) {
      iterator answer = *this;
      if (index_ != 0) {
        --index_;
        return *this;
      } else {
        --pointer_to_array_;
        index_ = size_of_arrays_ - 1;
        return *this;
      }
      return answer;
    }

    Iterator operator+(long long value) const {
      Iterator answer = *this;
      if (value > 0) {
        answer.pointer_to_array_ += (value / size_of_arrays_);
        if (answer.index_ + (value % size_of_arrays_) >
          size_of_arrays_) {
          ++answer.pointer_to_array_;
          answer.index_ = (answer.index_ + (value %
            size_of_arrays_)) % size_of_arrays_;
        } else {
          answer.index_ += (value % size_of_arrays_);
        }
      } else {
        if (value < 0) {
          answer.pointer_to_array_ -= ((-value) / size_of_arrays_);
          if (answer.index_ < ((-value) % size_of_arrays_)) {
            --answer.pointer_to_array_;
            answer.index_ = size_of_arrays_ + answer.index_ -
              ((-value) % size_of_arrays_);
          } else {
            answer.index_ -= (-value) % size_of_arrays_;
          }
        }
      }
      return answer;
    }

    Iterator operator-(long long value) const {
      Iterator answer = *this;
      return answer + (-value);
    }

    bool operator<(const Iterator<constancy>& iter) const {
      if (pointer_to_array_ == iter.pointer_to_array_) {
        return index_ < iter.index_;
      }
      return pointer_to_array_ < iter.pointer_to_array_;
    }

    bool operator==(const Iterator<constancy>& iter) const {
      return (pointer_to_array_ == iter.pointer_to_array_) &&
        (index_ == iter.index_);
    }

    bool operator>(const Iterator<constancy>& iter) const {
      return iter < *this;
    }

    bool operator<=(const Iterator<constancy>& iter) const {
      return !(iter < *this);
    }

    bool operator>=(const Iterator<constancy>& iter) const {
      return !(*this < iter);
    }

    bool operator!=(const Iterator<constancy>& iter) const {
      return !(*this == iter);
    }

    long long operator-(const Iterator& iter) const {
      return (pointer_to_array_ - iter.pointer_to_array_) *
      size_of_arrays_ + index_ - iter.index_;
    }
    
    reference operator*() const {
      return *(*(pointer_to_array_)+index_);
    }

    pointer operator->() const {
      return *pointer_to_array_ + index_;
    }
  };

  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = const std::reverse_iterator<const_iterator>;

  iterator begin() {
    return iterator(&external_[first_pointer_], first_elem_);
  }

  const_iterator begin() const {
    const_iterator answer = iter_on_begin_;
    return answer;
  }

  iterator end() {
    return iterator(&external_[last_pointer_], last_elem_);
  }
  
  const_iterator end() const {
    const_iterator answer = iter_on_end_;
    return answer;
  }

  const_iterator cbegin() const {
    const_iterator answer = iter_on_begin_;
    return answer;
  }

  const_iterator cend() const {
    const_iterator answer = iter_on_end_;
    return answer;
  }

  reverse_iterator rbegin() {
    return reverse_iterator((iter_on_end_ - 1)->pointer_to_array_,
      (iter_on_end_ - 1)->index_);
  }

  const_reverse_iterator rbegin() const {
    const_reverse_iterator answer((iter_on_end_ - 1)->pointer_to_array_,
      (iter_on_end_ - 1)->index_);
    return answer;
  }

  reverse_iterator rend() {
    return reverse_iterator((iter_on_begin_ - 1)->pointer_to_array_,
      (iter_on_begin_ - 1)->index_);
  }

  const_reverse_iterator rend() const {
    const_reverse_iterator answer((iter_on_begin_ - 1)->pointer_to_array_,
      (iter_on_begin_ - 1)->index_);
    return answer;
  }

  const_reverse_iterator crbegin() const {
    const_reverse_iterator answer((iter_on_end_ - 1)->pointer_to_array_,
      (iter_on_end_ - 1)->index_);
    return answer;
  }

  const_reverse_iterator crend() const {
    const_reverse_iterator answer((iter_on_begin_ - 1)->pointer_to_array_,
      (iter_on_begin_ - 1)->index_);
    return answer;
  }

  void insert(iterator it, const T& elem);

  void erase(iterator it);

private:
  static const int size_of_arrays_ = 32;
  std::vector<T*> external_;
  size_t first_elem_;
  size_t first_pointer_;
  size_t last_elem_;
  size_t last_pointer_;
  size_t sz_;
  Deque<T>::Iterator<false> iter_on_begin_;
  Deque<T>::Iterator<false> iter_on_end_;
};

template <typename T>
void Deque<T>::SetThreeArrays(std::vector<T*>& external_) {
  T* arr = reinterpret_cast<T*>(new uint8_t[(size_of_arrays_ + 2) * sizeof(T)]);
  T* pointer = &(arr[0]);
  external_[2] = pointer;
  arr = reinterpret_cast<T*> (new uint8_t[(size_of_arrays_ + 2) * sizeof(T)]);
  pointer = &(arr[0]);
  external_[1] = pointer;
  arr = reinterpret_cast<T*> (new uint8_t[(size_of_arrays_ + 2) * sizeof(T)]);
  pointer = &(arr[0]);
  external_[0] = pointer;
}

template <typename T>
Deque<T>& Deque<T>::operator=(const Deque<T>& deq) {
  for (size_t i = 0; i < deq.sz_; ++i) {
    try {
      this->push_back(deq[i]);
    }
    catch (...) {
      for (size_t j = 0; j < i; ++j) {
        this->pop_back();
        throw;
      }
    }
  }
  for (size_t i = 0; i < this->size() - deq.size(); ++i) {
    this->pop_front();
  }
  return *this;
}

template <typename T>
size_t Deque<T>::size() const {
  return sz_;
}

template <typename T>
T& Deque<T>::operator[](const size_t index_) {
  return *(external_[(first_pointer_ * 32 + first_elem_ + index_) / 32
  ] + (first_elem_ + index_) % 32);
}

template <typename T>
const T& Deque<T>::operator[](const size_t index_) const {
    return *(external_[(first_pointer_ * 32 + first_elem_ + index_) / 32
    ] + (first_elem_ + index_) % 32);
}

template <typename T>
T& Deque<T>::at(const size_t index_) {
  if (index_ >= sz_ || index_ < 0) {
    throw std::out_of_range("Deque index_ is out of range");
  }
  return (*this)[index_];
}

template <typename T>
const T& Deque<T>::at(const size_t index_) const {
    if (index_ >= sz_ || index_ < 0) {
        throw std::out_of_range("Deque index_ is out of range");
    }
    return (*this)[index_];
}

template <typename T>
void Deque<T>::push_back(const T& value) {
  if ((last_elem_ != size_of_arrays_ - 1) && (sz_ != 0)) {
    new(external_[last_pointer_] + last_elem_) T(value);
    last_elem_ += 1;
  } else {
    if (sz_ == 0) {
      T* new_arr = reinterpret_cast<T*> (new uint8_t[
        size_of_arrays_ * sizeof(T)]);
      try {
        new(new_arr + 1) T(value);
      }
      catch (...) {
        delete[] new_arr;
        throw;
      }
      T* pointer = new_arr;
      delete[] external_[external_.size() / 2];
      external_[external_.size() / 2] = pointer;
      first_elem_ = 1;
      last_elem_ = 2;
      first_pointer_ = external_.size() / 2;
      last_pointer_ = external_.size() / 2;
    } else {
      if ((last_pointer_ == external_.size() - 1) && (
        last_elem_ == size_of_arrays_ - 1)) {
        std::vector<T*> new_external_(external_.size() *
          3, nullptr);
        for (size_t i = 0; i < external_.size(); ++i) {
          new_external_[i + external_.size()] = external_[i];
        }
        first_pointer_ += external_.size();
        last_pointer_ += external_.size();
        for (size_t i = 0; i < first_pointer_; ++i) {
          T* new_arr = reinterpret_cast<T*> (new uint8_t[
            size_of_arrays_ * sizeof(T)]);
          T* pointer = new_arr;
          new_external_[i] = pointer;
        }
        for (size_t i = last_pointer_ + 1; i < new_external_.size()
          ; ++i) {
          T* new_arr = reinterpret_cast<T*> (new uint8_t[
            size_of_arrays_ * sizeof(T)]);
          T* pointer = new_arr;
          new_external_[i] = pointer;
        }
        try {
          new(new_external_[last_pointer_] + size_of_arrays_ -
            1) T(value);
        }
        catch (...) {
          throw;
        }
        external_ = new_external_;
        ++last_pointer_;
        last_elem_ = 0;
      } else {
        if (last_elem_ == size_of_arrays_ - 1) {
          try {
            new(external_[last_pointer_] + size_of_arrays_ -
              1) T(value);
          }
          catch (...) {
            throw;
          }
          last_elem_ = 0;
          ++last_pointer_;
        }
      }
    }
  }
  ++sz_;
  ++iter_on_end_;
}

template <typename T>
void Deque<T>::pop_back() {
  if (last_elem_ != 0) {
    try {
      (external_[last_pointer_] + (--last_elem_))->~T();
    }
    catch (...) {
      throw;
    }
  } else {
    try {
      (external_[--last_pointer_] + size_of_arrays_ - 1)->~T();
      last_elem_ = size_of_arrays_ - 1;
    }
    catch (...) {
      throw;
    }
  }
  --sz_;
  --iter_on_end_;
}

template <typename T>
void Deque<T>::pop_front() {
  try {
    (external_[first_pointer_] + first_elem_)->~T();
  }
  catch (...) {
    throw;
  }
  if (first_elem_ == size_of_arrays_ - 1) {
    first_elem_ = 0;
    first_pointer_++;
  } else {
    first_elem_++;
  }
  --sz_;
  ++iter_on_begin_;
}

template <typename T>
void Deque<T>::insert(iterator it, const T& elem) {
  Deque<T> deq_copy = *this;
  push_back(elem);
  iterator curr_pos = end() - 1;
  while (curr_pos > it) {
    try {
      *curr_pos = *(curr_pos - 1);
    }
    catch (...) {
      *this = deq_copy;
      throw;
    }
    --curr_pos;
  }
  (*curr_pos) = elem;
  ++sz_;
}
template <typename T>
void Deque<T>::push_front(const T& value) {
  if ((first_elem_ != 1) && (sz_ != 0)) {
    if (first_elem_ == 0) {
      try {
        new(external_[--first_pointer_] + size_of_arrays_ - 1) T(value);
        first_elem_ = size_of_arrays_ - 1;
      } catch (...) {
        throw;
      }
    } else {
      try {
        new(external_[first_pointer_] + first_elem_ - 1) T(value);
        --first_elem_;
      } catch (...) {
        throw;
      }
    }
  } else {
    if (sz_ == 0) {
      T* new_arr = reinterpret_cast <T*> (new uint8_t[size_of_arrays_ * sizeof(T)]);
      try {
        new(new_arr) T(value);
      } catch (...) {
        throw;
      }
      T* pointer = new_arr;
      external_[external_.size() / 2] = pointer;
      first_elem_ = 0;
      last_elem_ = 1;
      first_pointer_ = external_.size() / 2;
      last_pointer_ = external_.size() / 2;
    } else {
      if ((first_pointer_ == 0) && (first_elem_ == 1)) {
        std::vector <T*> new_external_(external_.size() * 3, nullptr);
        for (size_t i = 0; i < external_.size(); ++i) {
          new_external_[i + external_.size()] = external_[i];
        }
        first_pointer_ += external_.size();
        last_pointer_ += external_.size();
        for (size_t i = 0; i < first_pointer_; ++i) {
          T* new_arr = reinterpret_cast <T*> (new uint8_t[size_of_arrays_ * sizeof(T)]);
          T* pointer = new_arr;
          new_external_[i] = pointer;
        }
        for (size_t i = last_pointer_ + 1; i < new_external_.size(); ++i) {
          T* new_arr = reinterpret_cast <T*> (new uint8_t[size_of_arrays_ * sizeof(T)]);
          T* pointer = new_arr;
          new_external_[i] = pointer;
        }
        external_ = new_external_;
        try {
          new(external_[first_pointer_] + --first_elem_) T(value);
        } catch (...) {
          throw;
        }
      } else {
      try {
        new(external_[first_pointer_] + --first_elem_) T(value);
      } catch (...) {
        throw;
      }
    }
  }
  }
  ++sz_;
  --iter_on_begin_;
}
template <typename T>
void Deque<T>::erase(iterator it) {
  Deque<T> deq_copy = *this;
  Deque<T>::iterator next_it = it + 1;
  T value = *next_it;
  while ((next_it) != this->end()) {
    value = *next_it;
    try {
      *it = *next_it;
    }
    catch (...) {
      *this = deq_copy;
      throw;
    }
    ++it;
    ++next_it;
  }
  pop_back();
}
