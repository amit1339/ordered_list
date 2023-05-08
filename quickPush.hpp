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
    struct node
    {
        struct node *next;
        T data;
    };

    struct node* NewNode(T val)
    {
        struct node* node = new struct node;
        node->data = val;
        node->next = nullptr;
        return node;
    }

    bool IsEmpty();
    int (*m_compfunc)(const T lhs, const T rhs);
    struct node* m_head;
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
    struct node* node = NewNode(val);

    if (IsEmpty())
    {
        m_head = node;
        m_head->next = nullptr;
    }
    else
    {
        node->next = m_head;
        m_head = node;
    }

    m_sem.release();
}

template <class T>
T QuickPushDataStructure<T>::Pop()
{
    m_sem.acquire();
    std::scoped_lock<std::mutex> lock(m_mutex);
    struct node* node = m_head->next;
    struct node* temp = m_head;
    while (node != nullptr)
    {
        std::cout << node->data << " " << temp->data << std::endl;
        if (0 < m_compfunc(node->data, temp->data))
        {
            temp = node;
        }
        node = node->next;
    }

    T val = temp->data;
    if (nullptr == temp->next)
    {
        delete node;
    }
    
    node = temp->next;
    temp->data = node->data;
    temp->next = node->next;
    delete node;

    return val;
}

template <class T>
bool QuickPushDataStructure<T>::IsEmpty()
{
    return m_head == nullptr;
}
