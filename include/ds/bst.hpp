#pragma once

#include <cstddef>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <utility>


namespace dsa{

template <typename T>

class BST{
private:

    struct Node{
        T value;

        Node* left;
        Node* right;

        Node(const T& value) : value(value), left(nullptr), right(nullptr) {}
    };

    Node* root_;
    std::size_t size_;

    void destroy_(Node* node){
        if(node == nullptr) return;

        destroy_(node->left);
        destroy_(node->right);

        delete node;
    }

    Node* clone_(Node* node) {
        if(node == nullptr) {
            return nullptr;
        }

        Node* newNode = new Node(node->value);

        newNode->left = clone_(node->left);
        newNode->right = clone_(node->right);

        return newNode;
    }

    

    Node* insert_(Node* root, const T& value){
        if(root == nullptr){
            size_++;
            return new Node(value);
        }

        if(root->value > value){
            root->left = insert_(root->left,value);
        }
        else if(root->value < value){
            root->right = insert_(root->right,value);
        }

        return root;

    }

    bool contains_(Node* root, const T& value) const {
        if(root == nullptr){
            return false;
        }

        if(value == root->value){
            return true;
        }

        if(value < root->value){
            return contains_(root->left, value);
        }

        return contains_(root->right, value);
    }

    Node* min_node_(Node* node) const {
        while(node->left != nullptr) {
            node = node->left;
        }

        return node;
    }

    Node* max_node_(Node* node) const {
        while(node->right != nullptr) {
            node = node->right;
        }

        return node;
    }

    Node* remove_(Node* root, const T& value){
        if(root == nullptr){
            return nullptr;
        }

        if(value < root->value) {
            root->left = remove_(root->left, value);
            return root;
        }

        if(value > root->value) {
            root->right = remove_(root->right, value);
            return root;
        }

        if(root->left == nullptr && root->right == nullptr){
            delete root;
            size_--;
            return nullptr;
        }

        if(root->left == nullptr){
            Node* temp = root->right;
            delete root;
            size_--;
            return temp;
        }

        if(root->right == nullptr){
            Node* temp = root->left;
            delete root;
            size_--;
            return temp;
        }

        Node* min = min_node_(root->right);

        root->value = min->value;

        root->right = remove_(root_->right,min->value);

        return root;

    }

public:

    BST() : root_(nullptr), size_(0) {}

    ~BST(){
        destroy_(root_);
    }

    BST(const BST& t) : root_(clone_(t.root_)), size_(t.size_) {}

    BST& operator=(const BST& t){
        if(this == &t){
            return *this;
        }

        destroy_(root_);

        root_ = clone_(t.root_);
        size_ = t.size_;

        return *this;
    }

    BST(BST&& t) noexcept {
        root_ = t.root_;
        size_ = t.size_;

        t.root_ = nullptr;
        t.size_ = 0;
    }

    BST& operator=(BST&& t) noexcept {
        if(this == &t) {
            return *this;
        }

        destroy_(root_);

        root_ = t.root_;
        size_ = t.size_;

        t.root_ = nullptr;
        t.size_ = 0;

        return *this;
    }

    void insert(const T& value){
        root_ = insert_(root_,value);
    }

    bool contains(const T& value) const {
        return contains_(root_,value);
    }

    std::size_t size() const {
        return size_;
    }

    bool isempty() const {
        return size_ == 0;
    }

    const T& min() const {
        if(isempty()) {
            throw std::out_of_range("BST is empty");
        }

        return min_node_(root_)->value;
    }

    const T& max() const {
        if(isempty()) {
            throw std::out_of_range("BST is empty");
        }

        return max_node_(root_)->value;
    }

    void remove(const T& value){
        root_=remove_(root_,value);
    }


};
}