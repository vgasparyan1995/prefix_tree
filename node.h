#pragma once

namespace local {

template <typename MappedT,
          int CHILDREN>
struct node
{
    using mapped_type = MappedT;

    explicit node(node* parent = nullptr,
                  mapped_type* value = nullptr)
        : m_parent{parent}
        , m_value{value}
    {
        for (auto& child : m_children) {
            child = nullptr;
        }
    }

    template <typename AllocatorT>
    void clean_recursively(AllocatorT alloc)
    {
        for (auto& child : m_children) {
            child->clean_recursively();
            delete child;
            child = nullptr;
        }
        if (m_value != nullptr) {
            alloc.destroy(m_value);
            alloc.deallocate(m_value, 1);
            m_value = nullptr;
        }
    }

    node* m_parent;
    mapped_type* m_value;
    std::array<node*, CHILDREN> m_children;
};

}
