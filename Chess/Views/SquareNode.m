//
//  SquareNode.m
//  Chess
//
//  Created by Adnan Zahid on 4/16/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#import "SquareNode.h"

@implementation SquareNode

+ (id)nodeWithGeometry:(SCNGeometry *)geometry file:(NSUInteger)file rank:(NSUInteger)rank {
    return [[self alloc] initWithGeometry:geometry file:file rank:rank];
}

- (id)initWithGeometry:(SCNGeometry *)geometry file:(NSUInteger)file rank:(NSUInteger)rank {
    
    if (self = [super init]) {
        self.geometry = geometry;
        self.file = file;
        self.rank = rank;
    }
    
    return self;
}

@end
