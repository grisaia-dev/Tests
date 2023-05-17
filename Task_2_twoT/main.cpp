#include <iostream>
#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_message.hpp>

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {       
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};

TEST_CASE("PushBack, PushFront, PopBack, PopFront", "[List add and remove]") {
    List v1;
    INFO("Add element to back");
    v1.PushBack(15);
    CHECK(v1.Size() == 1);
    v1.PushBack(10);
    CHECK(v1.Size() == 2);

    INFO("Add element to front");
    v1.PushFront(192);
    CHECK(v1.Size() == 3);

    INFO("Remove element in back");
    v1.PopBack();
    CHECK(v1.Size() == 2);

    INFO("Remove element in front");
    v1.PopFront();
    CHECK(v1.Size() == 1);

    INFO("Check pop in list");
    v1.Clear();
    REQUIRE(v1.Size() == 0);
    try {
        v1.PopBack();
    } catch (const std::exception& ex) {
        CHECK(v1.Empty() == true);
    }
    try {
        v1.PopFront();
    } catch (const std::exception& ex) {
        CHECK(v1.Empty() == true);
    }
}

int main(void) {
    return Catch::Session().run();
}