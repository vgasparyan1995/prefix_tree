#pragma once

#include <memory>

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
    using char_type         = key_type::value_type;
    using size_type         = std::size_t;
    using allocator_type    = AllocatorT;
    using reference         = mapped_type&;
    using const_reference   = const mapped_type&;
    using pointer           = typename std::allocator_traits<allocator_type>::pointer;
    using const_pointer     = typename std::allocator_traits<allocator_type>::const_pointer;

public:
    /* Constructors, assignment and destructor */
    explicit prefix_tree(const allocator_type& a = allocator_type());
    prefix_tree(const prefix_tree&);
    prefix_tree(prefix_tree&&);
    prefix_tree(std::initializer_list<value_type>& il, const allocator_type& a = allocator_type());

    template <typename FwdIterT>
    prefix_tree(FwdIterT first, FwdIterT last, const allocator_type& a = allocator_type());

    prefix_tree& (const prefix_tree&);
    prefix_tree& (prefix_tree&&);

    ~prefix_tree();

    /* Selectors */
    const_iterator find(const key_type& key) const;
    const_reference& operator[] (const key_type& key) const;
    size_type size() const;
    bool empty() const;

    /* Mutators */
    iterator find(const key_type& key);
    iterator insert(const key_type& key, const mapped_type& value);
    iterator insert(const value_type& value);
    reference& operator[] (const key_type& key);
    void erase(const key_type& key);
    iterator erase(const iterator pos);
    void clear();

    /* Iterators */
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    /* Allocator */
    allocator_type get_allocator() const;

private:
    /* private members go here */
};

#include "_prefix_tree_impl.h"

} // namespace local
