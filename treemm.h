#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED
#include <list>
//#include <memory>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
    struct Node;
public:
    
    class Iterator
    {

    public:
        Iterator() : m_nodes(nullptr) , m_list_size(0), m_list_it() , m_pos(0){}

        Iterator(typename std::list<ValueType>::iterator itr, Node* nodes, size_t size) : 
            m_list_it(itr), m_nodes(nodes) , m_list_size(size) , m_pos(0) {}

        ValueType& get_value() const {
            return *m_list_it;
        }

        bool is_valid() const {
            return !(m_pos >= m_list_size); //pos < size
        }

        void advance() {
            if (!is_valid()) { return; }
            m_list_it++;
            m_pos++;
        }

    private:
        typename std::list<ValueType>::iterator m_list_it;
        Node* m_nodes;
        size_t m_list_size;
        size_t m_pos;
    };

    TreeMultimap() : m_root(nullptr){}

    ~TreeMultimap(){ clear(m_root); }

    void insert(const KeyType& key, const ValueType& value) { insertHelper(m_root, key, value); }

    Iterator find(const KeyType& key) const {   
        Node* current = m_root;
        return findHelper(key, current);
    }

private:

    struct Node {
        Node(const KeyType& key, const ValueType& val) : m_key(key), m_val(), left(nullptr), right(nullptr) {
            m_val.emplace_back(val);
        }
        KeyType m_key;
        std::list<ValueType> m_val;  // tree -> nodes (dyn) -> users (dyn)
        Node* left;
        Node* right;
    };

    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }
        clear(node->left); clear(node->right);  delete node;
    }

    void insertHelper(Node*& node, const KeyType& key, const ValueType& value) {
        if (node == nullptr) {
            node = new Node(key, value); return;
        }
        if (key < node->m_key) {
            insertHelper(node->left, key, value);
        }
        else if (key > node->m_key) {
            insertHelper(node->right, key, value);
        }
        else {
            node->m_val.emplace_back(value);
        }
    }

    Iterator findHelper(const KeyType& key, Node* current) const {
        if (current == nullptr) {
            return Iterator();
        }
        else if (key < current->m_key) {
            return findHelper(key, current->left);
        }
        else if (key > current->m_key) {
            return findHelper(key, current->right);
        }
        else {
            return Iterator(current->m_val.begin(), current, current->m_val.size());
        }
    }
    Node* m_root;
};

#endif // TREEMULTIMAP_INCLUDED
//42 lines of code