#pragma once

#include <iterator>

namespace local {

template <typename StringT,
          typename MappedT,
          typename AllocatorT>
class prefix_tree;

template <typename StringT, typename CharT, typename MappedT>
class prefix_tree_const_iterator;

template <typename StringT, typename CharT, typename MappedT>
struct node;

template <typename StringT, typename CharT, typename MappedT>
class prefix_tree_iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using key_type = StringT;
    using mapped_type = MappedT;
    using value_type = std::pair<const key_type, mapped_type&>;
    using difference_type = std::ptrdiff_t;
    using self = prefix_tree_iterator<StringT, CharT, MappedT>;
    using pointer = value_type*;
    using reference = value_type&;

public:
    prefix_tree_iterator()
        : m_node(nullptr)
        , m_pair(nullptr)
    {
    }

    explicit prefix_tree_iterator(node<StringT, CharT, MappedT>* n)
        : m_node{n}
        , m_pair(new value_type(n->key(), *n->m_value))
    {
    }

    prefix_tree_iterator(const prefix_tree_iterator& other)
        : m_node(other.m_node)
        , m_pair(new value_type(*other.m_pair))
    {
    }

    prefix_tree_iterator& operator= (const prefix_tree_iterator& other)
    {
        if (this == &other) {
            return *this;
        }
        m_node = other.m_node;
        m_pair.reset(new value_type(*other.m_pair));
        return *this;
    }

    reference operator*() const
    {
        return *m_pair;
    }

    pointer operator->() const
    {
        return m_pair.get();
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
                    } else {
                        done = true;
                    }
                } else {
                    m_node = m_node->m_parent;
                    done = (m_node->m_parent == nullptr);
                }
            } while (!done);
        }
        m_pair.reset(new value_type(m_node->key(), m_pair->second));
        return *this;
    }

    self operator++(int)
    {
        auto tmp = *this;
        ++(*this);
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

    node<StringT, CharT, MappedT>* m_node;
    std::unique_ptr<value_type> m_pair;
};

template <typename StringT, typename CharT, typename MappedT>
class prefix_tree_const_iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using key_type = StringT;
    using mapped_type = MappedT;
    using value_type = std::pair<const key_type, mapped_type&>;
    using difference_type = std::ptrdiff_t;
    using self = prefix_tree_const_iterator<StringT, CharT, MappedT>;
    using pointer = const value_type*;
    using reference = const value_type&;

public:
    prefix_tree_const_iterator()
        : m_node(nullptr)
        , m_pair(nullptr)
    {
    }

    explicit prefix_tree_const_iterator(const node<StringT, CharT, MappedT>* n)
        : m_node{n}
        , m_pair(new value_type(n->key(), *n->m_value))
    {
    }

    explicit prefix_tree_const_iterator(const prefix_tree_iterator<StringT, CharT, MappedT> iter)
        : m_node{iter.m_node}
        , m_pair(new value_type(*(iter.m_pair)))
    {
    }

    prefix_tree_const_iterator(const prefix_tree_const_iterator& other)
        : m_node(other.m_node)
        , m_pair(new value_type(*other.m_pair))
    {
    }

    prefix_tree_const_iterator& operator= (const prefix_tree_const_iterator& other)
    {
        if (this == &other) {
            return *this;
        }
        m_node = other.m_node;
        m_pair.reset(new value_type(*other.m_pair));
        return *this;
    }

    reference operator*() const
    {
        return *m_pair;
    }

    pointer operator->() const
    {
        return m_pair.get();
    }

    self& operator++()
    {
        if (!m_node->m_children.empty()) {
            m_node = m_node->leftmostfirst();
        } else {
            bool done = true;
            do {
                auto it = m_node->m_parent.find(m_node->m_key);
                ++it;
                if (it != m_node->m_parent.end()) {
                    m_node = it->second;
                    if (m_node->m_value == nullptr) {
                        m_node = m_node->leftmostfirst();
                    } else {
                        done = true;
                    }
                } else {
                    m_node = m_node->m_parent;
                    done = (m_node->m_parent == nullptr);
                }
            } while (!done);
        }
        m_pair.reset(new value_type(m_node->key(), m_pair->second));
        return *this;
    }

    self operator++(int)
    {
        auto tmp = *this;
        ++(*this);
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

    const node<StringT, CharT, MappedT>* m_node;
    std::unique_ptr<value_type> m_pair;
};

}
