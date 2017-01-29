#pragma once

#include <iterator>

namespace local {

template <typename StringT,
          typename MappedT,
          typename AllocatorT = std::allocator<MappedT> >
class prefix_tree;

template <typename I>
class prefix_tree_const_iterator;

template <typenamt T>
class node;

template <typename T>
class prefix_tree_iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using self = prefix_tree_iterator<T>;
    using pointer = T*;
    using reference = T&;

public:
    prefix_tree_iterator()
        : m_node()
    {
    }

    prefix_tree_iterator(node<T>* n)
        m_node{n}
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
    }

    self operator++(int)
    {
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

    node<T>* m_node;
};

template <typename T>
class prefix_tree_const_iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using self = prefix_tree_const_iterator<T>;
    using pointer = const T*;
    using reference = const T&;

public:
    prefix_tree_const_iterator()
        : m_node()
    {
    }

    prefix_tree_const_iterator(node<T>* n)
        m_node{n}
    {
    }

    prefix_tree_const_iterator(const prefix_tree_iterator<T> iter)
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
    }

    self operator++(int)
    {
        self temp = *this;
        m_node
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
    node<T>* m_node;
};


}
