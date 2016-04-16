//
//  GameView.h
//  Chess
//
//  Created by Adnan Zahid on 3/17/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#import "../C++ Code/Others/BasicStructs.cpp"
#import "../C++ Code/Others/Constants.cpp"
#import <SceneKit/SceneKit.h>

@protocol GameViewDelegate <NSObject>

- (void)inputTakenFrom:(Position)from to:(Position)to;
- (void)inputTakenFromIndex:(Index)fromIndex toIndex:(Index)toIndex;

@end

@interface GameView : SCNView

@property (weak, nonatomic) IBOutlet id <GameViewDelegate> gameViewDelegate;

- (void)createAllPieces:(NSMutableArray *)rankArray;
- (void)movePiece:(Index)fromIndex to:(Index)toIndex;
- (void)cannotMovePiece;
- (void)canTakeInput:(Color)color;

@end
