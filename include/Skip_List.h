// UNN, IITMM, Course "Algorithms and Data Structures"
// 
// Noskov I.A.

#pragma once
#include<iostream>
#include<list>
#include<stdlib.h>

struct Node {
public:
    int key;
    Node* next;
    Node* down;
    Node* up;
    Node(int k, Node* d = nullptr, Node* n = nullptr, Node* u = nullptr) : key(k), down(d), next(n), up(u) {};
    ~Node() {
        key = 0;
        next = nullptr;
        down = nullptr;
        up = nullptr;
    }
};

class SkipList {
private:
    Node* head;
    int maxLevel;

    Node* insert(Node* node, int key) {

        while (node->next && node->next->key < key)
            node = node->next;

        Node* downNode;
        if (node->down)
            downNode = insert(node->down, key);
        else
            downNode = nullptr;

        if (downNode || node->down == nullptr) {
            Node* newNode = new Node(key, downNode, node->next);
            node->next = newNode;

            if (downNode) {
                downNode->up = newNode;
                newNode->down = downNode;
            }

            if (rand() % 2 == 0)
                return newNode;
            return nullptr;
        }
        return nullptr;
    }

    void erase(Node* node, int key) {
        if (!find(key))
            throw std::logic_error("Key_not_found");

        while (node->next && node->next->key < key)
            node = node->next;

        if (node->down)
            erase(node->down, key);

        if (node->next && node->next->key == key) {
            Node* temp = node->next;
            node->next = node->next->next;
            delete temp;
        }
    }

public:
    SkipList() = default;
    SkipList(int maxLevel) : maxLevel(maxLevel) {
        head = new Node(0);
        Node* temp = head;

        for (std::size_t i = 1; i < maxLevel; i++) {
            temp->down = new Node(0);
            temp->down->up = temp;
            temp = temp->down;
        }

        temp->down = new Node(0);
    }
    int get_maxLevel() const noexcept {
        return maxLevel;
    }
    void insert(int key) {
        insert(head, key);
    }

    void erase(std::size_t key) {
        erase(head, key);
    }

    Node* find(std::size_t key) const {
        Node* temp = head;

        while (temp) {
            while (temp->next && temp->next->key < key)
                temp = temp->next;

            if (temp->next && temp->next->key == key) {
                Node* search = temp->next;
                while (search->down)
                    search = search->down;
                return search;
            }

            temp = temp->down;
        }
        return nullptr;
    }

    void print_list() const {
        Node* temp_1 = head;
        std::size_t i = 0;
        while (temp_1) {
            std::cout << "Уровень № " << i << " - ";
            i++;
            Node* temp_2 = temp_1->next;

            while (temp_2) {
                std::cout << temp_2->key << " ";
                temp_2 = temp_2->next;
            }

            std::cout << std::endl;
            temp_1 = temp_1->down;
        }
    }

    //void delete_list() {
    //    Node* temp;
    //    if (head != nullptr)
    //        while (head != nullptr) {
    //            temp = head->next;
    //            delete head;
    //            head = temp;
    //        }
    //}

    ~SkipList() {
        Node* NodeLevel = head;
        Node* nextNode;
        Node* temp;
        while (NodeLevel) {
            temp = NodeLevel->down;
            while (head) {
                nextNode = head->next;
                delete head;
                head = nextNode;
            }
            NodeLevel = temp;
        }
    }
};