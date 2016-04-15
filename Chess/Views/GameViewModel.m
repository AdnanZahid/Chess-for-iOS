//
//  GameViewModel.m
//  Chess
//
//  Created by Adnan Zahid on 4/15/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#import "GameViewModel.h"

@implementation GameViewModel

+ (id)modelWithValue:(NSUInteger)value order:(NSUInteger)order {
    return [[self alloc] initWithValue:value order:order];
}

- (id)initWithValue:(NSUInteger)value order:(NSUInteger)order {
    
    if (self = [super init]) {
        self.value = value;
        self.order = order;
    }
    
    return self;
}

@end
