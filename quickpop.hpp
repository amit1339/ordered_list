#include <semaphore>
#include <mutex>

template <class T>
class QuickPopDataStructure
{
public:
    explicit QuickPopDataStructure(int (*compfunc)(const T lhs, const T rhs));
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
QuickPopDataStructure<T>::QuickPopDataStructure(int (*compfunc)(const T lhs, const T rhs)): m_compfunc(compfunc),
m_sem(0)
{
}

template <class T>
void QuickPopDataStructure<T>::Push(T val)
{
    std::scoped_lock<std::mutex> lock(m_mutex);
    if (IsEmpty())
    {
        m_head = NewNode(val);
    }
    
    else
    {
        struct node* node = m_head;
        while (node != nullptr)
        {
            if (0 > m_compfunc(node->data,val))
            {
                struct node* temp = NewNode(val);
                temp->next = node->next;
                node->next = temp;
            }
            node = node->next;
        }
    }
    m_sem.release();
}

template <class T>
T QuickPopDataStructure<T>::Pop()
{
    m_sem.acquire();
    std::scoped_lock<std::mutex> lock(m_mutex);
    T& val = m_head->data;
    struct node* temp = m_head->next;
    delete m_head;
    m_head = temp;
    return val;
}

template <class T>
bool QuickPopDataStructure<T>::IsEmpty()
{
    return m_head == nullptr;
}



