//
//  GameViewController.m
//  Chess
//
//  Created by Adnan Zahid on 3/17/16.
//  Copyright (c) 2016 Adnan Zahid. All rights reserved.
//

#import "GameViewController.h"
#import "../Views/GameView.h"

#import <string>

#import "../C++ Code/Headers/GameLogic.hpp"
class Controller;

@interface GameViewController()

@property (nonatomic) Controller *controller;
@property (strong, nonatomic) GameView *gameView;

- (void)displayError:(NSString *)message;
- (void)displayView:(NSMutableArray *)rankArray;
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
        
        this->displayView();
        this->canTakeInputOrGenerateMove();
    }
    
    void displayView() {
        NSMutableArray *rankArray = [NSMutableArray arrayWithCapacity:NUMBER_OF_RANKS_ON_BOARD];
        
        for (int a = NUMBER_OF_RANKS_ON_BOARD - 1; a >= 0; a --) {
            
            NSMutableArray *fileArray = [NSMutableArray arrayWithCapacity:NUMBER_OF_FILES_ON_BOARD];
            
            for (int b = 0; b < NUMBER_OF_FILES_ON_BOARD; b ++) {
                if (this->board->pieceArray[a][b] != nullptr) {
                    
                    int sign;
                    
                    Color color = this->board->pieceArray[a][b]->color;
                    if (color == white) {
                        sign = 1;
                    } else {
                        sign = -1;
                    }
                    
                    [fileArray addObject:[NSNumber numberWithInt:sign * this->board->pieceArray[a][b]->value]];
                } else {
                    [fileArray addObject:[NSNumber numberWithInt:EMPTY]];
                }
            }
            
            [rankArray addObject:fileArray];
        }
        
        [this->gameViewController displayView:rankArray];
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
            this->displayView();
            this->canTakeInputOrGenerateMove();
        }
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

- (void)displayView:(NSMutableArray *)rankArray {
    [self.gameView displayView:rankArray];
}

- (void)canTakeInput:(Color)color {
    [self.gameView canTakeInput:color];
}

- (void)inputTaken:(Position)from to:(Position)to {
    
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end
