#pragma once

#include <iterator>

#include "_prefix_tree_util.h"

namespace local {

template <typename StringT,
          typename MappedT,
          typename AllocatorT>
class prefix_tree;

template <typename StringT, typename CharT, typename MappedT>
class prefix_tree_const_iterator;

template <typename StringT, typename CharT, typename ValueT>
struct node;

template <typename StringT, typename CharT, typename MappedT>
class prefix_tree_iterator
{
private:
    using key_type      = StringT;
    using mapped_type   = MappedT;
    using self          = prefix_tree_iterator<key_type, CharT, mapped_type>;

public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type        = std::pair<const key_type, mapped_type>;
    using difference_type   = std::ptrdiff_t;
    using pointer           = value_type*;
    using reference         = value_type&;

public:
    prefix_tree_iterator()
        : m_node(nullptr)
    {
    }

    explicit prefix_tree_iterator(node<StringT, CharT, value_type>* n)
        : m_node{n}
    {
    }

    prefix_tree_iterator(const prefix_tree_iterator& other)
        : m_node(other.m_node)
    {
    }

    prefix_tree_iterator& operator= (const prefix_tree_iterator& other)
    {
        if (this == &other) {
            return *this;
        }
        m_node = other.m_node;
        return *this;
    }

    reference operator*() const
    {
        return *m_node->m_value;
    }

    pointer operator->() const
    {
        return m_node->m_value;
    }

    self& operator++()
    {
        if (!m_node->m_children.empty()) {
            m_node = m_node->leftmostfirst();
        } else {
            bool done = true;
            do {
                auto it = m_node->m_parent->m_children.find(m_node->m_key);
                ++it;
                if (it != m_node->m_parent->m_children.end()) {
                    m_node = it->second;
                    if (m_node->m_value == nullptr) {
                        m_node = m_node->leftmostfirst();
                    }
                    done = true;
                } else {
                    m_node = m_node->m_parent;
                    done = (m_node->m_parent == nullptr);
                }
            } while (!done);
        }
        return *this;
    }

    self operator++(int)
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    self& operator--()
    {
        if (!m_node->m_children.empty()) {
            m_node = m_node->rightmostfirst();
        } else {
            bool done = true;
            do {
                auto it = std::make_reverse_iterator(m_node->m_parent->m_children.find(m_node->m_key));
                if (it != m_node->m_parent->m_children.rend()) {
                    m_node = it->second;
                    if (m_node->m_value == nullptr) {
                        m_node = m_node->rightmostfirst();
                    }
                    done = true;
                } else {
                    m_node = m_node->m_parent;
                    done = (m_node->m_parent == nullptr);
                }
            } while (!done);
        }
        return *this;
    }

    self operator--(int)
    {
        auto tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const self& other) const
    {
        return m_node == other.m_node;
    }

    bool operator!=(const self& other) const
    {
        return m_node != other.m_node;
    }

private:
    template <typename S,
              typename C,
              typename M>
    friend class prefix_tree_const_iterator;

    template <typename StringTT,
              typename MappedTT,
              typename AllocatorT>
    friend class prefix_tree;

    node<StringT, CharT, value_type>*   m_node;
};

template <typename StringT, typename CharT, typename MappedT>
class prefix_tree_const_iterator
{
private:
    using key_type      = StringT;
    using mapped_type   = MappedT;
    using self          = prefix_tree_const_iterator<key_type, CharT, mapped_type>;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = std::pair<const key_type, mapped_type>;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const value_type*;
    using reference         = const value_type&;

public:
    prefix_tree_const_iterator()
        : m_node(nullptr)
    {
    }

    explicit prefix_tree_const_iterator(const node<StringT, CharT, value_type>* n)
        : m_node{n}
    {
    }

    explicit prefix_tree_const_iterator(const prefix_tree_iterator<StringT, CharT, MappedT> iter)
        : m_node{iter.m_node}
    {
    }

    prefix_tree_const_iterator(const prefix_tree_const_iterator& other)
        : m_node(other.m_node)
    {
    }

    prefix_tree_const_iterator& operator= (const prefix_tree_const_iterator& other)
    {
        if (this == &other) {
            return *this;
        }
        m_node = other.m_node;
        return *this;
    }

    reference operator*() const
    {
        return *m_node->m_value;
    }

    pointer operator->() const
    {
        return m_node->m_value;
    }

    self& operator++()
    {
        if (!m_node->m_children.empty()) {
            m_node = m_node->leftmostfirst();
        } else {
            bool done = true;
            do {
                auto it = m_node->m_parent->m_children.find(m_node->m_key);
                ++it;
                if (it != m_node->m_parent->m_children.end()) {
                    m_node = it->second;
                    if (m_node->m_value == nullptr) {
                        m_node = m_node->leftmostfirst();
                    }
                    done = true;
                } else {
                    m_node = m_node->m_parent;
                    done = (m_node->m_parent == nullptr);
                }
            } while (!done);
        }
        return *this;
    }

    self operator++(int)
    {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    self& operator--()
    {
        if (!m_node->m_children.empty()) {
            m_node = m_node->rightmostfirst();
        } else {
            bool done = true;
            do {
                auto it = std::make_reverse_iterator(m_node->m_parent->m_children.find(m_node->m_key));
                if (it != m_node->m_parent->m_children.rend()) {
                    m_node = it->second;
                    if (m_node->m_value == nullptr) {
                        m_node = m_node->rightmostfirst();
                    }
                    done = true;
                } else {
                    m_node = m_node->m_parent;
                    done = (m_node->m_parent == nullptr);
                }
            } while (!done);
        }
        return *this;
    }

    self operator--(int)
    {
        auto tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const self& other) const
    {
        return m_node == other.m_node;
    }

    bool operator!=(const self& other) const
    {
        return m_node != other.m_node;
    }

private:
    template <typename StringTT,
              typename MappedTT,
              typename AllocatorT>
    friend class prefix_tree;

    const node<StringT, CharT, value_type>* m_node;
};

} // namespace local
