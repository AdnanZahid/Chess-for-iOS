//
//  GameView.h
//  Chess
//
//  Created by Adnan Zahid on 3/17/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#import "../C++ Code/Headers/BasicStructs.h"
#import "../C++ Code/Headers/Constants.h"
#import <SceneKit/SceneKit.h>

@protocol GameViewDelegate <NSObject>

- (void)inputTaken:(Position)from to:(Position)to;

@end

@interface GameView : SCNView

@property (weak, nonatomic) IBOutlet id <GameViewDelegate> gameViewDelegate;

- (void)displayView:(NSMutableArray *)rankArray;
- (void)canTakeInput:(Color)color;

@end
