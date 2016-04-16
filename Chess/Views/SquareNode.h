//
//  SquareNode.h
//  Chess
//
//  Created by Adnan Zahid on 4/16/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#import <SceneKit/SceneKit.h>

@interface SquareNode : SCNNode

@property (nonatomic) NSUInteger file;
@property (nonatomic) NSUInteger rank;

+ (id)nodeWithGeometry:(SCNGeometry *)geometry file:(NSUInteger)file rank:(NSUInteger)rank;

@end
