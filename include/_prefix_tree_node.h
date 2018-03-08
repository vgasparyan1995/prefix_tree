#pragma once

#include <algorithm>
#include <map>

namespace local {

template <typename StringT,
          typename CharT,
          typename MappedT>
struct node
{
    using mapped_type = MappedT;
    using key_type = CharT;
    using string_type = StringT;
    using children_type = std::map<key_type, node*>;

    explicit node(node* parent = nullptr,
                  const key_type key = key_type(),
                  mapped_type* value = nullptr)
        : m_parent{parent}
        , m_key{key}
        , m_value{value}
    {
    }

    node(const node&) = delete;
    node(node&&) = delete;
    node& operator= (const node&) = delete;
    node& operator= (node&&) = delete;
    ~node() = default;

    template <typename AllocatorT, typename ... Args>
    void set_value(AllocatorT alloc, Args&& ... args)
    {
        if (m_value != nullptr) {
            remove_value(alloc);
        }
        m_value = alloc.allocate(1);
        alloc.construct(m_value, std::forward<Args>(args)...);
    }

    template <typename AllocatorT>
    void remove_value(AllocatorT alloc)
    {
        alloc.destroy(m_value);
        alloc.deallocate(m_value, 1);
        m_value = nullptr;
    }

    template <typename AllocatorT>
    void clean_recursively(AllocatorT alloc)
    {
        for (auto& child : m_children) {
            child.second->clean_recursively(alloc);
            delete child.second;
            child.second = nullptr;
        }
        m_children.clear();
        if (m_value != nullptr) {
            remove_value(alloc);
        }
    }

    template <typename AllocatorT>
    node* clone(AllocatorT alloc, node* parent = nullptr)
    {
        node* result = new node(parent, m_key);
        if (m_value != nullptr) {
            result->set_value(alloc, *m_value);
        }
        for (const auto& child : m_children) {
            result->m_children[child.first] = child.second->clone(alloc, result);
        }
        return result;
    }

    node* leftmostfirst()
    {
        node* result = this;
        do {
            result = result->m_children.begin()->second;
        } while (result->m_value == nullptr);
        return result;
    }

    string_type key() const
    {
        string_type result;
        auto current_node = this;
        while (current_node->m_parent != nullptr) {
            result.push_back(current_node->m_key);
            current_node = current_node->m_parent;
        }
        std::reverse(result.begin(), result.end());
        return std::move(result);
    }

    bool is_leaf() const
    {
        return m_children.empty();
    }

    node* m_parent;
    key_type m_key;
    mapped_type* m_value;
    children_type m_children;
};

}
