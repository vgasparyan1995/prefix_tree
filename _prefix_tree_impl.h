#pragma once

#include "node.h"

template <typename StringT,
          typename MappedT,
          typename AllocatorT,
          int CHILDREN>
struct prefix_tree_impl : public AllocatorT
{
    prefix_tree_impl()
    {

    }

    ~prefix_tree_impl()
    {
        if (m_root != nullptr) {
            m_root->clean_recursively();
            delete m_root;
            m_root = nullptr;
        }
    }
    
    node<MappedT, CHILDREN>* m_root;
};
