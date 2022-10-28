#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>

namespace ft {
template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>
>
class map {
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef std::pair<const Key, T> value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef Allocator::pointer pointer;
    typedef Allocator::const_pointer const_pointer;
    // typedef iterator;
    // typedef const_iterator;
    // typedef std::reverse_iterator<iterator> reverse_iterator;
    // typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    class value_compare {
    public:
        typedef bool result_type;
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;

        bool operator()(const value_type& lhs, const value_type& rhs);

    protected:
        Compare comp;
        value_compare(Compare c);
    }

    map();
    explicit map(const Compare& comp, const Allocator& alloc = Allocator());
    template<class InputIt>
    map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator());
    map(const map& other);

    ~map();

    map& operator=(const map& other);

    allocator_type get_allocator() const;
    T& at(const Key& key);
    const T& at(const Key& key) const;
    T& operator[](const Key& key);
    // iterator begin();
    // const_iterator begin() const;
    // iterator end();
    // const_iterator end() const;
    // reverse_iterator rbegin();
    // const_reverse_iterator rbegin() const;
    // reverse_iterator rend();
    // const_reverse_iterator rend() const;
    bool empty();
    size_type size() const;
    size_type max_size() const;
    void clear();
    std::pair<iterator, bool> insert(const value_type& value);
    iterator insert(iterator pos, const value_type& value);
    template<class InputIt>
    void insert(InputIt first, InputIt last);
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);
    size_type erase(const Key& key);
    void swap(map& other);
    size_type count(const Key& key) const;
    iterator find(const Key& key);
    const_iterator find(const Key& key) const;
    std::pair<iterator, iterator> equal_range(const Key& key);
    std::pair<const_iterator, const_iterator> equal_range(const Key& key) const;
    iterator lower_bound(const Key& key);
    const_iterator lower_bound(const Key& key) const;
    iterator upper_bound(const Key& key);
    const_iterator upper_bound(const Key& key) const;
    key_compare key_comp() const;
    value_compare value_comp() const;
};

// compare operators
template<class Key, class Compare, class Alloc>
bool operator==(const ft::map<Key, Compare, Alloc>& lhs, const ft::map<Key, Compare, Alloc>& rhs);
template<class Key, class Compare, class Alloc>
bool operator!=(const ft::map<Key, Compare, Alloc>& lhs, const ft::map<Key, Compare, Alloc>& rhs);
template<class Key, class Compare, class Alloc>
bool operator>(const ft::map<Key, Compare, Alloc>& lhs, const ft::map<Key, Compare, Alloc>& rhs);
template<class Key, class Compare, class Alloc>
bool operator<(const ft::map<Key, Compare, Alloc>& lhs, const ft::map<Key, Compare, Alloc>& rhs);
template<class Key, class Compare, class Alloc>
bool operator>=(const ft::map<Key, Compare, Alloc>& lhs, const ft::map<Key, Compare, Alloc>& rhs);
template<class Key, class Compare, class Alloc>
bool operator<=(const ft::map<Key, Compare, Alloc>& lhs, const ft::map<Key, Compare, Alloc>& rhs);

// swap
template<class Key, class Compare, class Alloc>
void swap(ft::map<Key, Compare, Alloc>& lhs, ft::map<Key, Compare, Alloc>& rhs);
};

#endif
