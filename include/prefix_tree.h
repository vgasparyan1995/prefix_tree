#pragma once

#include <initializer_list>
#include <memory>

#include "_prefix_tree_iterator.h"
#include "_prefix_tree_impl.h"

namespace local {

template <typename StringT,
          typename MappedT,
          typename AllocatorT = std::allocator<MappedT> >
class prefix_tree
{
public:
    using key_type          = StringT;
    using mapped_type       = MappedT;
    using value_type        = std::pair<const key_type, mapped_type>;
    using char_type         = typename key_type::value_type;
    using size_type         = std::size_t;
    using allocator_type    = AllocatorT;
    using reference         = mapped_type&;
    using const_reference   = const mapped_type&;
    using pointer           = typename std::allocator_traits<allocator_type>::pointer;
    using const_pointer     = typename std::allocator_traits<allocator_type>::const_pointer;
    using iterator          = prefix_tree_iterator<key_type, char_type, mapped_type>;
    using const_iterator    = prefix_tree_const_iterator<key_type, char_type, mapped_type>;

public:
    /* Constructors, assignment and destructor */
    explicit prefix_tree(const allocator_type& a = allocator_type());
    prefix_tree(const prefix_tree&) = default;
    prefix_tree(prefix_tree&&) = default;
    prefix_tree(std::initializer_list<value_type> il, const allocator_type& a = allocator_type());

    template <typename FwdIterT>
    prefix_tree(FwdIterT first, FwdIterT last, const allocator_type& a = allocator_type());

    prefix_tree& operator= (const prefix_tree&) = default;
    prefix_tree& operator= (prefix_tree&&) = default;

    ~prefix_tree() = default;

    /* Selectors */
    const_iterator find(const key_type& key) const;
    size_type size() const;
    size_type max_size() const;
    bool empty() const;

    /* Mutators */
    iterator find(const key_type& key);
    std::pair<iterator, bool> insert(const key_type& key, const mapped_type& value);
    std::pair<iterator, bool> insert(const value_type& value);
    reference operator[] (const key_type& key);
    void erase(const key_type& key);
    iterator erase(iterator pos);
    void clear();

    /* Iterators */
    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    /* Allocator */
    allocator_type get_allocator() const;

    /* Non member functions */
    template <typename ST, typename MT, typename AT>
    friend bool operator== (const prefix_tree<ST, MT, AT>& lhs,
                            const prefix_tree<ST, MT, AT>& rhs);

    template <typename ST, typename MT, typename AT>
    friend bool operator!= (const prefix_tree<ST, MT, AT>& lhs,
                            const prefix_tree<ST, MT, AT>& rhs);

    template <typename ST, typename MT, typename AT>
    friend bool operator< (const prefix_tree<ST, MT, AT>& lhs,
                           const prefix_tree<ST, MT, AT>& rhs);

    template <typename ST, typename MT, typename AT>
    friend bool operator<= (const prefix_tree<ST, MT, AT>& lhs,
                            const prefix_tree<ST, MT, AT>& rhs);

    template <typename ST, typename MT, typename AT>
    friend bool operator> (const prefix_tree<ST, MappedT, AT>& lhs,
                           const prefix_tree<ST, MappedT, AT>& rhs);

    template <typename ST, typename MT, typename AT>
    friend bool operator>= (const prefix_tree<ST, MT, AT>& lhs,
                            const prefix_tree<ST, MT, AT>& rhs);

private:
    using impl_type = local::prefix_tree_impl<key_type, mapped_type, allocator_type>;

private:
    impl_type m_impl;
};

} // namespace local

#include "prefix_tree.hpp"
