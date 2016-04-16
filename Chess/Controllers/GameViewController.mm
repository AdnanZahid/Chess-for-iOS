//
//  GameViewController.m
//  Chess
//
//  Created by Adnan Zahid on 3/17/16.
//  Copyright (c) 2016 Adnan Zahid. All rights reserved.
//

#import "GameViewController.h"
#import "../Views/GameView.h"
#import "../Views/GameViewModel.h"

#import <string>

#import "../C++ Code/Models/GameLogic.cpp"
class Controller;

@interface GameViewController()

@property (nonatomic) Controller *controller;
@property (strong, nonatomic) GameView *gameView;

- (void)displayError:(NSString *)message;
- (void)createAllPieces:(NSMutableArray *)rankArray;
- (void)movePiece:(Index)fromIndex to:(Index)toIndex;
- (void)canTakeInput:(Color)color;

@end

class Controller : ErrorDelegate, InputDelegate {
    
private:
    GameViewController *gameViewController;
    GameLogic *gameLogic;
    Board *board;
    
public:
    Controller(GameViewController *gameViewController) {
        this->gameViewController = gameViewController;
        
        this->gameLogic = new GameLogic(this, this);
        this->board = gameLogic->getBoard();
        
        this->createAllPieces();
        this->canTakeInputOrGenerateMove();
    }
    
    void createAllPieces() {
        NSMutableArray *rankArray = [NSMutableArray arrayWithCapacity:NUMBER_OF_RANKS_ON_BOARD];
        
        for (int rank = NUMBER_OF_RANKS_ON_BOARD - 1; rank >= 0; rank --) {
            
            NSMutableArray *fileArray = [NSMutableArray arrayWithCapacity:NUMBER_OF_FILES_ON_BOARD];
            
            for (int file = 0; file < NUMBER_OF_FILES_ON_BOARD; file ++) {
                if (this->board->pieceArray[rank][file] != nullptr) {
                    
                    int sign;
                    
                    Color color = this->board->pieceArray[rank][file]->color;
                    if (color == white) {
                        sign = 1;
                    } else {
                        sign = -1;
                    }
                    
                    [fileArray addObject:[GameViewModel modelWithValue:sign * this->board->pieceArray[rank][file]->value order:this->board->pieceArray[rank][file]->order]];
                } else {
                    [fileArray addObject:[GameViewModel modelWithValue:EMPTY order:EMPTY]];
                }
            }
            
            [rankArray addObject:fileArray];
        }
        
        [this->gameViewController createAllPieces:rankArray];
    }
    
    void error(std::string message) {
        [this->gameViewController displayError:@(message.c_str())];
    }
    
    void canTakeInput(Color color) {
        [this->gameViewController canTakeInput:color];
    }
    
    void canTakeInputOrGenerateMove() {
        if (this->gameLogic->shouldTakeInputFromHuman() == true) {
            this->canTakeInput(this->gameLogic->currentPlayer->color);
        } else {
            this->gameLogic->askAIToGenerateMove();
        }
    }
    
    void inputTaken(Position from, Position to) {
        if (this->gameLogic->movePiece(from, to)) {
            this->movePiece(from, to);
            this->canTakeInputOrGenerateMove();
        }
    }
    
    void movePiece(Position from, Position to) {
        Index fromIndex = this->board->positionToIndex(from);
        Index toIndex = this->board->positionToIndex(to);
        [this->gameViewController movePiece:fromIndex to:toIndex];
    }
    
    void startNewGame() {
        
    }
};

@implementation GameViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.controller = new Controller(self);
}

- (void)displayError:(NSString *)message {
    
}

- (void)createAllPieces:(NSMutableArray *)rankArray {
    [self.gameView createAllPieces:rankArray];
}

- (void)movePiece:(Index)fromIndex to:(Index)toIndex {
//    dispatch_async(dispatch_get_main_queue(), ^(void) {
        [self.gameView movePiece:fromIndex to:toIndex];
//    });
}

- (void)canTakeInput:(Color)color {
    [self.gameView canTakeInput:color];
}

- (void)inputTaken:(Position)from to:(Position)to {
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^(void) {
        self.controller->inputTaken(from, to);
    });
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end
