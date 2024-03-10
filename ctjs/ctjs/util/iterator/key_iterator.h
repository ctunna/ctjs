#pragma once

namespace ctjs::util::iterator {
template <typename Iterator>
class KeyIterator : public Iterator {
 public:
  using Iterator::Iterator;

  typename Iterator::value_type::first_type& operator*() const {
    return Iterator::operator*().first;
  }
};

template <typename Iterator>
KeyIterator<Iterator> make_key_iterator(const Iterator& it) {
  return KeyIterator<Iterator>(it);
}
}  // namespace ctjs::util