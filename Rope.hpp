/*
 * Незавершенная реализация структуры данных "Декартово дерево по неявному ключу"
 * TODO:
 * 1) Нужно реализовать метод copy.
 * 2) После Rope с = a + b,    a, b и с - указывают на один и тот же treap.
 */

#ifndef TREAP_IMPLICITKEY_ROPE_HPP
#define TREAP_IMPLICITKEY_ROPE_HPP

#include <memory>
#include <cstdlib>

template<typename T>
class Rope {
public:
    class Node;
    using NodePtr = std::shared_ptr<Node>;
    using NodePair = std::pair<NodePtr, NodePtr>;

    class Node {
    public:
        explicit Node (T val, int y = rand())
                : data_(val)
                , priority_(y)
                , size_(1)
                , left_ (nullptr)
                , right_(nullptr)
        {}

        Node(Node const & node)
        {
            data_ = node.data_;
            priority_ = node.priority_;
            size_ = 1;
            left_ = nullptr;
            right_ = nullptr;
        }

        NodePtr copy(Node const & node)
        {
            NodePtr new_node = std::make_shared<Node>(node);
        }

        ~Node()
        { }

        size_t size() const {
            return (this) ? size_ : 0;
        }

        void update() {
            if (this) size_ = left_->size() + right_->size() + 1;
        }

        void printData() const {
            if (this != nullptr) {
                std::cout << data_ << " (pr = " << priority_ << ", size = " << size_ << ", (";
                left_ ? std::cout << left_->data_ << " ; " : std::cout << "null; ";
                right_ ? std::cout << right_->data_ << "))\n" : std::cout << "null))\n";
            }
        }

        void treeWalk() const {
            if (this != nullptr) {
                left_->treeWalk();
                std::cout << data_ << ' ';
                right_->treeWalk();
            }
        }

        static NodePtr merge(NodePtr &L, NodePtr &R) {
            if (L == nullptr) return R;
            if (R == nullptr) return L;
            if (L->priority_ > R->priority_) {
                L->right_ = merge(L->right_, R);
                L->update();
                return L;
            } else {
                R->left_ = merge(L, R->left_);
                R->update();
                return R;
            }
        }

    public:
        T data_;
        int priority_;
        size_t size_;
        NodePtr left_;
        NodePtr right_;
    };

public:

    Rope()
            :root_ (nullptr) {}

    Rope(T val)
            : root_ (std::make_shared<Node>(Node(val))) {}

    Rope(NodePtr & p)
            : root_ (p) {}

//    Rope(Rope const & p)
//    { }

    ~Rope()
    { }

    void clear() {
        root_ = nullptr;
    }

    size_t size() const {
        return root_->size();
    }

    void print() const {
        if (root_)
            root_->Node::treeWalk();
        std::cout << "\n";
    }

    NodePair split(NodePtr &root, size_t index) {
        if (root == nullptr)
            return NodePair(nullptr, nullptr);
        NodePtr L = nullptr;
        NodePtr R = nullptr;
        /* Порядковый номер корня currentIndex равен размеру левого поддерева
         * Если индекс разбиения index больше currentIndex, то разбивать нужно
         * правое поддерево.
         */
        size_t currentIndex = root->left_->size();
        if (index > currentIndex) {
            // Сам корень и его левое поддерево уже отсеклись влево,
            // поэтому индекс разбиения нужно уменьшить на currentIndex + 1.
            NodePair t = split(root->right_, index - currentIndex - 1);
            root->right_ = t.first;
            L = root;
            R = t.second;
        } else {
            NodePair t = split(root->left_, index);
            root->left_ = t.second;
            R = root;
            L = t.first;
        }
        L->update();
        R->update();
        return NodePair(L, R);
    }

    static Rope merge(Rope L, Rope R) {
        NodePtr t = Node::merge(L.root_, R.root_);
        return Rope(t);
    }

    void insert(T key) {
        insert(root_, key, rand(), size());
    }

    void insert(NodePtr &root, T key, int y, size_t index) {
        if (root == nullptr)
            root = std::make_shared<Node> (Node(key, y));
        else if (y > root->priority_) {
            NodePtr node(new Node(key, y));
            NodePair t = split(root, index);
            node->left_ = t.first;
            node->right_ = t.second;
            root = node;
        } else {
            size_t currentIndex = root->left_->size();
            if (currentIndex > index)
                insert(root->left_, key, y, index);
            else
                insert(root->right_, key, y, index - currentIndex - 1);
        }
        root->update();
    }

    void moveToBegin(size_t left, size_t right) {
        NodePtr root = root_;
        NodePair t1 = split(root, left);
        NodePair t2 = split(t1.second, right - left + 1);
        NodePtr x = Node::merge(t1.first, t2.second);
        root_ = Node::merge(t2.first, x);
    }

    void remove(size_t left, size_t right) {
        NodePtr root = root_;
        NodePair t1 = split(root, left);
        NodePair t2 = split(t1.second, right - left + 1);
        NodePtr x = Node::merge(t1.first, t2.second);
        root_ = x;
    }

    Rope operator+ (Rope & r) const
    {
        Rope n = merge(*this, r);
        return n;
    }

private:
    NodePtr root_;
};

#endif //TREAP_IMPLICITKEY_ROPE_HPP
