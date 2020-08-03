//
//  BST.hpp
//  BinarySearchTree
//
//  Created by Roy Rao on 2020/7/14.
//  Copyright © 2020 RoyRao. All rights reserved.
//

#ifndef BST_hpp
#define BST_hpp

#include <iostream>
using namespace std;

template<typename T> class BSTNode {
public:
    BSTNode(T _data): data(_data), leftChild(nullptr), rightChild(nullptr) {}
public:
    T data;
    BSTNode *leftChild;
    BSTNode *rightChild;
};

template<typename T> class BSTree {
public:
    BSTree();
    ~BSTree();
    BSTNode<T>* insert(T data);
    BSTNode<T>* find(T data);
    BSTNode<T>* findMinimum(BSTNode<T> *iter);
    BSTNode<T>* findMaximum(BSTNode<T> *iter);
    bool deleteWith(T data);
    BSTNode<T>* getParent(BSTNode<T> *ptr);
    int getLength();
    void traverse(BSTNode<T> *ptr);
    void clear();
private:
    BSTNode<T>* insert(BSTNode<T> *iter, T data);
    BSTNode<T>* find(BSTNode<T> *iter, T data);
    bool deleteWith(BSTNode<T> *iter, T data);
    void clear(BSTNode<T> *iter);
private:
    BSTNode<T> *root;
    int length;
};




// MARK: - CONSTRUCT AND DESTRUCT
template<typename T> BSTree<T>::BSTree() {
    this->root = nullptr;
    this->length = 0;
}

template<typename T> BSTree<T>::~BSTree() {
    this->clear();
}

// MARK: - INSERT
template<typename T> BSTNode<T>* BSTree<T>::insert(T data) {
    return insert(this->root, data);
}

template<typename T> BSTNode<T>* BSTree<T>::insert(BSTNode<T> *iter, T data) {
    if (iter == nullptr) {
        iter = new BSTNode<T>(data);
        return iter;
    } else if (data < iter->data) {
        return iter->leftChild = insert(iter->leftChild, data);
    } else if (data > iter->data) {
        return iter->rightChild = insert(iter->rightChild, data);
    }
    return iter;
}

// MARK: - DELETE
template<typename T> bool BSTree<T>::deleteWith(T data) {
    return this->deleteWith(this->root, data);
}

template<typename T> bool BSTree<T>::deleteWith(BSTNode<T> *iter, T data) {
    if (iter == nullptr) {
        cout << "No element to delete!" << endl;
        return false;
    }
    BSTNode<T> *temp = nullptr;
    if (data < iter->data) {
        return this->deleteWith(iter->leftChild, data);
    } else if (data > iter->data) {
        return this->deleteWith(iter->rightChild, data);
    } else {
        if (iter->leftChild != nullptr && iter->rightChild != nullptr) {
            /// two children
            temp = this->findMinimum(iter->rightChild);
            iter->data = temp->data;
        } else {
            /// have one or none
            temp = iter;
            if (iter->leftChild == nullptr) {
                iter = iter->rightChild;
            } else {
                iter = iter->leftChild;
            }
        }
        delete temp;
        temp = nullptr;
    }
    return true;
}

// MARK: - FIND
template<typename T> BSTNode<T>* BSTree<T>::find(T data) {
    return this->find(this->root, data);
}

template<typename T> BSTNode<T>* BSTree<T>::find(BSTNode<T> *iter, T data) {
    if (iter == nullptr) {
        cout << "No element found!" << endl;
        return nullptr;
    }
    if (data < iter->data) {
        return this->find(iter->leftChild, data);
    } else if (data > iter->data) {
        return this->find(iter->rightChild, data);
    } else {
        return iter;
    }
}

template<typename T> BSTNode<T>* BSTree<T>::findMinimum(BSTNode<T> *iter) {
    if (iter == nullptr) {
        cout << "No element found!" << endl;
        return nullptr;
    }
    if (iter->leftChild == nullptr) {
        return iter;
    } else {
        return this->findMinimum(iter->leftChild);
    }
}

template<typename T> BSTNode<T>* BSTree<T>::findMaximum(BSTNode<T> *iter) {
    if (iter == nullptr) {
        cout << "No element found!" << endl;
        return nullptr;
    }
    if (iter->rightChild == nullptr) {
        return iter;
    } else {
        return this->findMaximum(iter->rightChild);
    }
}

// MARK: - TOOLS
template<typename T> void BSTree<T>::clear() {
    if (this->root == nullptr) {
        return;
    }
    this->clear(this->root);
}

template<typename T> void BSTree<T>::clear(BSTNode<T> *iter) {
    if (iter->leftChild != nullptr) {
        this->clear(iter->leftChild);
        iter->leftChild = nullptr;
    }
    if (iter->rightChild != nullptr) {
        this->clear(iter->rightChild);
        iter->rightChild = nullptr;
    }
    delete iter;
    iter = nullptr;
    this->length--;
}

template<typename T> int BSTree<T>::getLength() {
    return this->length;
}

#endif /* BST_hpp */
