#pragma once

namespace local {

template<typename T>
struct node
{
    using value_type = T;

    node(node* parent, value_type value)
        : m_parent{parent}
        , m_value{value}
    {
    }

    node* m_parent;
    value_type m_value;
    std::vector<Node*> m_children;
};

}
