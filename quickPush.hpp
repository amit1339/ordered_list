#include <semaphore>
#include <mutex>
#include <thread>

template <class T>
class QuickPushDataStructure
{
public:
    explicit QuickPushDataStructure(int (*compfunc)(const T lhs, const T rhs));
    void Push(T val);
    T Pop();

private:
    struct Node
    {
        Node* next;
        T data;
    };

    struct Node* NewNode(T val)
    {
        Node* node = new struct Node;
        node->data = val;
        node->next = nullptr;
        return node;
    }


    int (*m_compfunc)(const T lhs, const T rhs);
    Node* m_head;
    std::counting_semaphore<1> m_sem;
    std::mutex m_mutex;
};

template <class T>
QuickPushDataStructure<T>::QuickPushDataStructure(int (*compfunc)(const T lhs, const T rhs)): m_compfunc(compfunc),m_head(nullptr) ,m_sem(0)
{
}

template <class T>
void QuickPushDataStructure<T>::Push(T val)
{
    std::scoped_lock<std::mutex> lock(m_mutex);
    Node* node = NewNode(val);
    
    node->next = m_head;
    m_head = node;

    m_sem.release();
}

template <class T>
T QuickPushDataStructure<T>::Pop()
{
    m_sem.acquire();
    std::scoped_lock<std::mutex> lock(m_mutex);
    Node* node = m_head;
    Node* prev = m_head;
    Node* max = m_head;
    while (node->next != nullptr)
    {
        if (0 < m_compfunc(node->next->data, max->data))
        {
            max = node->next;
            prev = node;
        }
        node = node->next;
    }

    T val = max->data;

    if (nullptr == max->next)
    {
        delete max;
        prev->next = nullptr;
        return val;
    }

    node = max->next;

    max->data = node->data;
    max->next = node->next;
    delete node;

    return val;
}

