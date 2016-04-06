//
//  LinkedList.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/15/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

template <class T>
class LinkedList {

public:
    struct Node;
    
    Node *head;
    
    LinkedList();
    
    ~LinkedList();
    
    void add(T *value);
    
    void remove(T *value);
};