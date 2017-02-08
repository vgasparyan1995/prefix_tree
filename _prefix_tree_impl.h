#pragma once

#include "node.h"

template <typename StringT,
          typename MappedT,
          typename AllocatorT>
class prefix_tree_impl : public AllocatorT
{
private:
    using tree_node = node<StringT::value_type, MappedT>;
    using key_type = StringT;
    using mapped_type = MappedT;

public:
    explicit prefix_tree_impl(const AllocatorT& a = AllocatorT())
        : AllocatorT(a)
        , m_root(nullptr)
        , m_size(0)
    {
    }

    prefix_tree_impl(const prefix_tree_impl& other)
        : AllocatorT(other)
        , m_root(nullptr)
        , m_size(other.m_size)
    {
        m_root = other.m_root->clone();
    }

    prefix_tree_impl(prefix_tree_impl&& other)
        : AllocatorT(other)
        , m_root(other.m_root)
        , m_size(other.m_size)
    {
        other.m_root = nullptr;
    }

    prefix_tree_impl& operator= (const prefix_tree_impl& other)
    {
        if (this != &other) {
            *static_cast<AllocatorT*>(this) = other;
            m_root = other.m_root->clone();
            m_size = other.m_size;
        }
        return *this;
    }

    prefix_tree_impl& operator= (prefix_tree_impl&& other)
    {
        if (this != &other) {
            *static_cast<AllocatorT*>(this) = std::move(static_cast<AllocatorT>(other));
            m_root = other.m_root;
            other.m_root = nullptr;
            m_size = other.m_size;
        }
        return *this;
    }

    ~prefix_tree_impl()
    {
        clear();
    }

    tree_node* find(const key_type& key) const
    {
        auto current_node = m_root;
        for (const auto character : key) {
            if (current_node == nullptr) {
                break;
            }
            current_node = current_node->m_children[character];
        }
        return current_node;
    }

    std::pair<tree_node*, bool> insert(const key_type& key, const mapped_type& value)
    {
        auto current_node = m_root;
        auto parent_node = current_node;
        for (const auto character : key) {
            parent_node = current_node;
            current_node = current_node->m_children[character];
            if (current_node == nullptr) {
                current_node = new tree_node(parent_node, character);
            }
        }
        if (current_node->m_value != nullptr) {
            return std::make_pair(current_node, false);
        }
        current_node->set_value(*this, key, value);
        ++m_size;
        return std::make_pair(current_node, true);
    }

    void erase(tree_node* node)
    {
        auto child = node;
        auto parent = node->m_parent;
        while (parent->m_children.size() == 1) {
            child = parent;
            parent = parent->m_parent;
        }
        child->clean_recursively(*this);
        parent->m_children.erase(child.m_key);
        --m_size;
    }

    void clear()
    {
        if (m_root != nullptr) {
            m_root->clean_recursively();
            delete m_root;
            m_root = nullptr;
            m_size = 0;
        }
    }

    std::size_t size() const
    {
        return m_size;
    }

    bool empty() const
    {
        return m_size == 0;
    }

private:
    tree_node* m_root;
    std::size_t m_size;
};

