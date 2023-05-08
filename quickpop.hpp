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
    struct Node
    {
        Node *next;
        T data;
    };

    Node* NewNode(T val)
    {
        Node* node = new Node;
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
QuickPopDataStructure<T>::QuickPopDataStructure(int (*compfunc)(const T lhs, const T rhs)): m_compfunc(compfunc)
,m_head(nullptr) ,m_sem(0)
{
}

template <class T>
void QuickPopDataStructure<T>::Push(T val)
{
    std::scoped_lock<std::mutex> lock(m_mutex);
    Node** ppNode = &m_head;
    while (*ppNode != nullptr && m_compfunc(val, (*ppNode)->data) <= 0)
    {
        ppNode = &((*ppNode)->next);
    }
    Node* newNode = NewNode(val);
    newNode->next = *ppNode;
    *ppNode = newNode;
    m_sem.release();
}

template <class T>
T QuickPopDataStructure<T>::Pop()
{
    m_sem.acquire();
    std::scoped_lock<std::mutex> lock(m_mutex);
    T val = m_head->data;
    Node* temp = m_head->next;
    delete m_head;
    m_head = temp;
    return val;
}





