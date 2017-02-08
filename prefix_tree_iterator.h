#pragma once

#include <iterator>

namespace local {

template <typename StringT,
          typename MappedT,
          typename AllocatorT = std::allocator<MappedT> >
class prefix_tree;

template <typename CharT, typename MappedT>
class prefix_tree_const_iterator;

template <typename CharT, typename MappedT>
class node;

template <typename CharT, typename MappedT>
class prefix_tree_iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = MappedT;
    using difference_type = std::ptrdiff_t;
    using self = prefix_tree_iterator<CharT, MappedT>;
    using pointer = value_type*;
    using reference = value_type&;

public:
    prefix_tree_iterator()
        : m_node(nullptr)
    {
    }

    template <typename CharT, typename MappedT>
    explicit prefix_tree_iterator(node<CharT, MappedT>* n)
        : m_node{n}
    {
    }

    reference operator*() const
    {
        return m_node->m_value;
    }

    pointer operator->() const
    {
        return &m_node->m_value;
    }

    self& operator++()
    {
        // TODO!
        return *this;
    }

    self operator++(int)
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const self& other)
    {
        return m_node == other.m_node;
    }

    bool operator!=(const self& other)
    {
        return m_node != other.m_node;
    }

private:
    template <typename I>
    friend class prefix_tree_const_iterator;

    template <typename StringT,
              typename MappedT,
              typename AllocatorT>
    friend class prefix_tree;

    node<CharT, MappedT>* m_node;
};

template <typename CharT, typename MappedT>
class prefix_tree_const_iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = MappedT;
    using difference_type = std::ptrdiff_t;
    using self = prefix_tree_const_iterator<CharT, MappedT>;
    using pointer = const value_type*;
    using reference = const value_type&;

public:
    prefix_tree_const_iterator()
        : m_node(nullptr)
    {
    }

    template <typename CharT, typename MappedT>
    explicit prefix_tree_iterator(const node<CharT, MappedT>* n)
        m_node{n}
    {
    }

    explicit prefix_tree_const_iterator(const prefix_tree_iterator<CharT, MappedT> iter)
        : m_node{iter.m_node}
    {
    }

    reference operator*() const
    {
        return m_node->m_value;
    }

    pointer operator->() const
    {
        return &m_node->m_value;
    }

    self& operator++()
    {
        // TODO!
        return *this;
    }

    self operator++(int)
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const self& other)
    {
        return m_node == other.m_node;
    }

    bool operator!=(const self& other)
    {
        return m_node != other.m_node;
    }

private:
    template <typename StringT,
              typename MappedT,
              typename AllocatorT>
    friend class prefix_tree;

    const node<CharT, MappedT>* m_node;
};


}
