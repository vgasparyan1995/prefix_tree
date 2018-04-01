#include <algorithm>
#include <limits>
#include <stdexcept>

namespace local {

template <typename StringT, typename MappedT, typename AllocatorT>
prefix_tree<StringT, MappedT, AllocatorT>::prefix_tree(const allocator_type& a/* = allocator_type()*/)
    : m_impl(a)
{
}

template <typename StringT, typename MappedT, typename AllocatorT>
prefix_tree<StringT, MappedT, AllocatorT>::prefix_tree(std::initializer_list<value_type> il, const allocator_type& a/* = allocator_type()*/)
    : m_impl(a)
{
    for (const auto& v : il) {
        m_impl.insert(v.first, v.second);
    }
}

template <typename StringT, typename MappedT, typename AllocatorT>
template <typename FwdIterT>
prefix_tree<StringT, MappedT, AllocatorT>::prefix_tree(FwdIterT first, FwdIterT last, const allocator_type& a/* = allocator_type()*/)
    : m_impl(a)
{
    for (auto it = first; it != last; ++it) {
        m_impl.insert(it->first, it->second);
    }
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::find(const key_type& key) const -> const_iterator
{
    auto node = m_impl.find(key);
    if (node == nullptr) {
        node = m_impl.root();
    }
    return const_iterator(node);
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::size() const -> size_type
{
    return m_impl.size();
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::max_size() const -> size_type
{
    return std::numeric_limits<size_type>::max();
}

template <typename StringT, typename MappedT, typename AllocatorT>
bool prefix_tree<StringT, MappedT, AllocatorT>::empty() const
{
    return m_impl.empty();
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::at(const key_type& key) -> reference
{
    auto node = m_impl.find(key);
    if (node == nullptr) {
        throw std::out_of_range("prefix_tree::at");
    }
    return *(node->m_value);
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::at(const key_type& key) const -> const_reference
{
    auto node = m_impl.find(key);
    if (node == nullptr) {
        throw std::out_of_range("prefix_tree::at");
    }
    return *(node->m_value);
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::find(const key_type& key) -> iterator
{
    auto node = m_impl.find(key);
    if (node == nullptr) {
        node = m_impl.root();
    }
    return iterator(node);
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::insert(const key_type& key, const mapped_type& value) -> std::pair<iterator, bool>
{
    auto insertion_result = m_impl.insert(key, value);
    return std::make_pair(iterator(insertion_result.first), insertion_result.second);
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::insert(const value_type& value) -> std::pair<iterator, bool>
{
    return insert(value.first, value.second);
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::insert(const_iterator hint, const value_type& value) -> iterator
{
    return insert(value).first;
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::operator[] (const key_type& key) -> reference
{
    auto node = m_impl.find(key);
    if (node == nullptr) {
        node = m_impl.insert(key, mapped_type()).first;
    }
    return *(node->m_value);
}

template <typename StringT, typename MappedT, typename AllocatorT>
void prefix_tree<StringT, MappedT, AllocatorT>::erase(const key_type& key)
{
    auto node = m_impl.find(key);
    if (node != nullptr) {
        m_impl.erase(node);
    }
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::erase(iterator pos) -> iterator
{
    auto it = pos;
    ++it;
    m_impl.erase(pos.m_node);
    return it;
}

template <typename StringT, typename MappedT, typename AllocatorT>
void prefix_tree<StringT, MappedT, AllocatorT>::clear()
{
    m_impl.clear();
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::begin() -> iterator
{
    if (empty()) {
        return end();
    } else {
        return iterator(m_impl.root()->leftmostfirst());
    }
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::begin() const -> const_iterator
{
    if (empty()) {
        return end();
    } else {
        return const_iterator(m_impl.root()->leftmostfirst());
    }
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::cbegin() const -> const_iterator
{
    return begin();
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::end() -> iterator
{
    return iterator(m_impl.root());
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::end() const -> const_iterator
{
    return const_iterator(m_impl.root());
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::cend() const -> const_iterator
{
    return end();
}

template <typename StringT, typename MappedT, typename AllocatorT>
auto prefix_tree<StringT, MappedT, AllocatorT>::get_allocator() const -> allocator_type
{
    return static_cast<allocator_type>(m_impl);
}

template <typename StringT, typename MappedT, typename AllocatorT>
bool operator== (const prefix_tree<StringT, MappedT, AllocatorT>& lhs,
                 const prefix_tree<StringT, MappedT, AllocatorT>& rhs)
{
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename StringT, typename MappedT, typename AllocatorT>
bool operator!= (const prefix_tree<StringT, MappedT, AllocatorT>& lhs,
                 const prefix_tree<StringT, MappedT, AllocatorT>& rhs)
{
    return !(lhs == rhs);
}

template <typename StringT, typename MappedT, typename AllocatorT>
bool operator< (const prefix_tree<StringT, MappedT, AllocatorT>& lhs,
                const prefix_tree<StringT, MappedT, AllocatorT>& rhs)
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(),
            [] (const typename prefix_tree<StringT, MappedT, AllocatorT>::value_type& lhs,
                const typename prefix_tree<StringT, MappedT, AllocatorT>::value_type& rhs)
            {
                return lhs.first < rhs.first;
            });
}

template <typename StringT, typename MappedT, typename AllocatorT>
bool operator<= (const prefix_tree<StringT, MappedT, AllocatorT>& lhs,
                 const prefix_tree<StringT, MappedT, AllocatorT>& rhs)
{
    return !(lhs > rhs);
}

template <typename StringT, typename MappedT, typename AllocatorT>
bool operator> (const prefix_tree<StringT, MappedT, AllocatorT>& lhs,
                const prefix_tree<StringT, MappedT, AllocatorT>& rhs)
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(),
            [] (const typename prefix_tree<StringT, MappedT, AllocatorT>::value_type& lhs,
                const typename prefix_tree<StringT, MappedT, AllocatorT>::value_type& rhs)
            {
                return lhs.first > rhs.first;
            });
}

template <typename StringT, typename MappedT, typename AllocatorT>
bool operator>= (const prefix_tree<StringT, MappedT, AllocatorT>& lhs,
                 const prefix_tree<StringT, MappedT, AllocatorT>& rhs)
{
    return !(lhs < rhs);
}

} // namespace local
