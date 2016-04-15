//
//  GameViewModel.h
//  Chess
//
//  Created by Adnan Zahid on 4/15/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GameViewModel : NSObject

@property (nonatomic) NSUInteger value;
@property (nonatomic) NSUInteger order;

+ (id)modelWithValue:(NSUInteger)value order:(NSUInteger)order;

@end
