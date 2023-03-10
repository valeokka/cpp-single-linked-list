#pragma once

#include <cstddef>
#include <string>
#include <utility>
#include <iterator>
#include <algorithm>
#include <vector>

template <typename Type>
class SingleLinkedList
{
    struct Node
    {
        Node() = default;
        Node(const Type &val, Node *next)
            : value(val), next_node(next)
        {
        }
        Type value;
        Node *next_node = nullptr;
    };

    template <typename ValueType>
    class BasicIterator
    {

        friend class SingleLinkedList;

        explicit BasicIterator(Node *node)
        {
            node_ = node;
        }

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Type;
        using difference_type = std::ptrdiff_t;
        using pointer = ValueType *;
        using reference = ValueType &;

        BasicIterator() = default;

        BasicIterator(const BasicIterator<Type> &other) noexcept
        {
            node_ = other.node_;
        }

        BasicIterator &operator=(const BasicIterator &rhs) = default;

        [[nodiscard]] bool operator==(const BasicIterator<const Type> &rhs) const noexcept { return node_ == rhs.node_; }
        [[nodiscard]] bool operator!=(const BasicIterator<const Type> &rhs) const noexcept { return node_ != rhs.node_; }
        [[nodiscard]] bool operator==(const BasicIterator<Type> &rhs) const noexcept { return node_ == rhs.node_; }
        [[nodiscard]] bool operator!=(const BasicIterator<Type> &rhs) const noexcept { return node_ != rhs.node_; }
        [[nodiscard]] reference operator*() const noexcept {
            assert(node_ != nullptr);
            return node_->value; 
        }
        [[nodiscard]] pointer operator->() const noexcept { 
            assert(node_ != nullptr);
            return &node_->value; 
        }

        BasicIterator &operator++() noexcept
        {
            assert (node_);
            {
                node_ = node_->next_node;
            }
            return *this;
        }

        BasicIterator operator++(int) noexcept
        {
            auto old_value(*this);
            ++(*this);
            return old_value;
        }

    private:
        Node *node_ = nullptr;
    };

public:
    using value_type = Type;
    using reference = value_type &;
    using const_reference = const value_type &;
    using Iterator = BasicIterator<Type>;
    using ConstIterator = BasicIterator<const Type>;
    [[nodiscard]] size_t GetSize() const noexcept { return size_; }
    [[nodiscard]] bool IsEmpty() const noexcept { return size_ == 0; }
    [[nodiscard]] Iterator begin() noexcept { return Iterator(head_.next_node); }
    [[nodiscard]] Iterator end() noexcept { return Iterator(nullptr); }
    [[nodiscard]] Iterator before_begin() noexcept { return Iterator(&head_); }
    [[nodiscard]] ConstIterator before_begin() const noexcept { return ConstIterator{const_cast<Node *>(&head_)}; }
    [[nodiscard]] ConstIterator begin() const noexcept { return ConstIterator(head_.next_node); }
    [[nodiscard]] ConstIterator end() const noexcept { return ConstIterator(nullptr); }
    [[nodiscard]] ConstIterator cbegin() const noexcept { return ConstIterator(head_.next_node); }
    [[nodiscard]] ConstIterator cend() const noexcept { return ConstIterator(nullptr); }
    [[nodiscard]] ConstIterator cbefore_begin() const noexcept { return ConstIterator{const_cast<Node *>(&head_)}; }

    SingleLinkedList() = default;
    SingleLinkedList(std::initializer_list<Type> values) { CopyInThis(values); }

    SingleLinkedList(const SingleLinkedList &other)
    {
        if (other.GetSize() != 0)
        {
            CopyInThis(other);
        }
    }

    SingleLinkedList &operator=(const SingleLinkedList &rhs)
    {
        if (this != &rhs)
        {
            SingleLinkedList temp(rhs);
            swap(temp);
        }
        return *this;
    }

    void swap(SingleLinkedList &other) noexcept
    {
        std::swap(size_,other.size_);
        std::swap( head_.next_node,other.head_.next_node);
    }

    ~SingleLinkedList()
    {
        Clear();
    }
    void PushFront(const Type &value)
    {
        auto ptr = new Node(value, head_.next_node);
        head_.next_node = ptr;
        ++size_;
    }

    void PopFront() noexcept
    {
        assert(head_.next_node != nullptr);
        auto deleted = head_.next_node;
        head_.next_node = deleted->next_node;
        delete deleted;
        --size_;
    }

    Iterator InsertAfter(ConstIterator pos, const Type &value)
    {
        assert(pos.node_ != nullptr);
        auto ptr = new Node(value, pos.node_->next_node);
        pos.node_->next_node = ptr;
        ++size_;
        return Iterator(pos.node_->next_node);
    }

    Iterator EraseAfter(ConstIterator pos) noexcept
    {
        assert(pos.node_ != nullptr);
        assert(pos.node_->next_node != nullptr);
        auto deleted = pos.node_->next_node;
        pos.node_->next_node = deleted->next_node;
        --size_;
        delete deleted;
        return Iterator(pos.node_->next_node);
    }

    void Clear() noexcept
    {
        if (!IsEmpty())
        {
            Node *next = head_.next_node;
            Node *that = nullptr;
            while (next)
            {
                that = next;
                next = that->next_node;
                delete that;
            }

            next = nullptr;
            that = nullptr;
            size_ = 0;
            head_.next_node = nullptr;
        }
    }

private:
    size_t size_ = 0;
    Node head_;

    template <typename Container>
    void CopyInThis(Container other)
    {
        SingleLinkedList temp;
        for (auto val = other.end() - 1; val != other.begin(); --val)
        {
            temp.PushFront(*val);
        }
        temp.PushFront(*other.begin());
        swap(temp);
    }
};

template <typename Type>
void swap(SingleLinkedList<Type> &lhs, SingleLinkedList<Type> &rhs) noexcept
{
    lhs.swap(rhs);
}

template <typename Type>
bool operator==(const SingleLinkedList<Type> &lhs, const SingleLinkedList<Type> &rhs)
{
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
bool operator!=(const SingleLinkedList<Type> &lhs, const SingleLinkedList<Type> &rhs)
{
    return !(lhs == rhs);
}

template <typename Type>
bool operator<(const SingleLinkedList<Type> &lhs, const SingleLinkedList<Type> &rhs)
{

    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
bool operator<=(const SingleLinkedList<Type> &lhs, const SingleLinkedList<Type> &rhs)
{
    return !(rhs < lhs);
}

template <typename Type>
bool operator>(const SingleLinkedList<Type> &lhs, const SingleLinkedList<Type> &rhs)
{
    return rhs < lhs;
}

template <typename Type>
bool operator>=(const SingleLinkedList<Type> &lhs, const SingleLinkedList<Type> &rhs)
{
    return !(lhs < rhs);
}

// внешние функции разместите здесь
