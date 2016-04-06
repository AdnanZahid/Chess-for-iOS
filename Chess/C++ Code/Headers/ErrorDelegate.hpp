//
//  ErrorDelegate.cpp
//  Chess
//
//  Created by Adnan Zahid on 3/8/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#include <string>

class ErrorDelegate {
    
public:
    virtual void error(std::string message) = 0;
};