//
//  LinkedList.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/15/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include "../Headers/LinkedList.hpp"

LinkedList() {
    this->head = nullptr;
}

~LinkedList() {
    while(this->head != nullptr) {
        Node *node = this->head->next;
        delete this->head;
        this->head = node;
    }
}

void add(T *value) {
    Node *node = new Node;
    node->value = value;
    if (this->head == nullptr) {
        this->head = node;
        this->head->next = nullptr;
    } else {
        node->next = this->head;
        this->head = node;
    }
}

void remove(T *value) {
    Node *node = this->head;
    Node *prev = this->head;
    while(node != nullptr) {
        if(node->value == value) {
            if(node == this->head) {
                this->head = node->next;
                node = nullptr;
                delete node;
            } else {
                prev->next = node->next;
                node = nullptr;
                delete node;
            }
        } else {
            prev = node;
            node = node->next;
        }
    }
}