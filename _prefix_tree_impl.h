#pragma once

#include "node.h"

template <typename StringT,
          typename MappedT,
          typename AllocatorT>
class prefix_tree_impl : public AllocatorT
{
private:
    using tree_node = node<StringT::value_type, MappedT>;

public:
    explicit prefix_tree_impl(const AllocatorT& a = AllocatorT())
        : AllocatorT(a)
        , m_root(nullptr)
    {
    }

    prefix_tree_impl(const prefix_tree_impl& other)
        : AllocatorT(other)
        , m_root(nullptr)
    {
        m_root = other.m_root->clone();
    }

    prefix_tree_impl(prefix_tree_impl&& other)
        : AllocatorT(other)
        , m_root(other.m_root)
    {
        other.m_root = nullptr;
    }

    prefix_tree_impl& operator= (const prefix_tree_impl& other)
    {
        if (this != &other) {
            *static_cast<AllocatorT*>(this) = other;
        }
    }

    ~prefix_tree_impl()
    {
        if (m_root != nullptr) {
            m_root->clean_recursively();
            delete m_root;
            m_root = nullptr;
        }
    }
    
    tree_node* m_root;
};


