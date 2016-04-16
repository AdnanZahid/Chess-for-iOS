//
//  GameViewModel.h
//  Chess
//
//  Created by Adnan Zahid on 4/15/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#import <SceneKit/SceneKit.h>

@interface GameViewModel : NSObject

@property (nonatomic) NSUInteger value;
@property (nonatomic) NSUInteger order;

@property (strong, nonatomic) SCNNode *pieceNode;
@property (nonatomic) NSUInteger x;
@property (nonatomic) NSUInteger y;

+ (id)modelWithValue:(NSUInteger)value order:(NSUInteger)order;

@end
