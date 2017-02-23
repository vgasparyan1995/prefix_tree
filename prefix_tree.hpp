#define TEMPLATE_DECL template <typename StringT,\
                                typename MappedT,\
                                typename AllocatorT>
#define CLASS_DECL prefix_tree<StringT, MappedT, AllocatorT>

TEMPLATE_DECL
CLASS_DECL::prefix_tree(const allocator_type& a/* = allocator_type()*/)
    : m_impl(a)
{
}

TEMPLATE_DECL
CLASS_DECL::prefix_tree(std::initializer_list<value_type> il, const allocator_type& a/* = allocator_type()*/)
    : m_impl(a)
{
    for (const auto& v : il) {
        m_impl.insert(v.first, v.second);
    }
}

TEMPLATE_DECL
template <typename FwdIterT>
CLASS_DECL::prefix_tree(FwdIterT first, FwdIterT last, const allocator_type& a/* = allocator_type()*/)
    : m_impl(a)
{
    for (auto it = first; it != last; ++it) {
        m_impl.insert(it->first, it->second);
    }
}

TEMPLATE_DECL
auto CLASS_DECL::find(const key_type& key) const -> const_iterator
{
    auto node = m_impl.find(key);
    if (node == nullptr) {
        node = m_impl.root();
    }
    return const_iterator(node);
}

TEMPLATE_DECL
auto CLASS_DECL::size() const -> size_type
{
    return m_impl.size();
}

TEMPLATE_DECL
bool CLASS_DECL::empty() const
{
    return m_impl.empty();
}

TEMPLATE_DECL
auto CLASS_DECL::find(const key_type& key) -> iterator
{
    auto node = m_impl.find(key);
    if (node == nullptr) {
        node = m_impl.root();
    }
    return iterator(node);
}

TEMPLATE_DECL
auto CLASS_DECL::insert(const key_type& key, const mapped_type& value) -> std::pair<iterator, bool>
{
    auto insertion_result = m_impl.insert(key, value);
    return std::make_pair(iterator(insertion_result.first), insertion_result.second);
}

TEMPLATE_DECL
auto CLASS_DECL::insert(const value_type& value) -> std::pair<iterator, bool>
{
    return insert(value.first, value.second);
}

TEMPLATE_DECL
auto CLASS_DECL::operator[] (const key_type& key) -> reference&
{
    auto node = m_impl.find(key);
    if (node == nullptr) {
        node = m_impl.insert(key, mapped_type()).first;
    }
    return *(node->m_value);
}

TEMPLATE_DECL
void CLASS_DECL::erase(const key_type& key)
{
    auto node = m_impl.find(key);
    if (node != nullptr) {
        m_impl.erase(node);
    }
}

TEMPLATE_DECL
auto CLASS_DECL::erase(iterator pos) -> iterator
{
    auto it = pos;
    ++it;
    m_impl.erase(pos.m_node);
    return it;
}

TEMPLATE_DECL
void CLASS_DECL::clear()
{
    m_impl.clear();
}

TEMPLATE_DECL
auto CLASS_DECL::begin() -> iterator
{
    if (empty()) {
        return end();
    } else {
        return iterator(m_impl.root()->leftmostfirst());
    }
}

TEMPLATE_DECL
auto CLASS_DECL::begin() const -> const_iterator
{
    if (empty()) {
        return end();
    } else {
        return const_iterator(m_impl.root()->leftmostfirst());
    }
}

TEMPLATE_DECL
auto CLASS_DECL::cbegin() const -> const_iterator
{
    return begin();
}

TEMPLATE_DECL
auto CLASS_DECL::end() -> iterator
{
    return iterator(m_impl.root());
}

TEMPLATE_DECL
auto CLASS_DECL::end() const -> const_iterator
{
    return const_iterator(m_impl.root());
}

TEMPLATE_DECL
auto CLASS_DECL::cend() const -> const_iterator
{
    return end();
}

TEMPLATE_DECL
auto CLASS_DECL::get_allocator() const -> allocator_type
{
    return static_cast<allocator_type>(m_impl);
}

#undef CLASS_DECL
#undef TEMPLATE_DECL

