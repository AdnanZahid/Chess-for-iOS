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
- (void)cannotMovePiece;
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
        
        for (int rank = 0; rank < NUMBER_OF_RANKS_ON_BOARD; rank ++) {
            
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
                    
                    Piece *piece = this->board->pieceArray[rank][file];
                    [fileArray addObject:[GameViewModel modelWithValue:sign * piece->value order:piece->order]];
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
        } else {
            this->cannotMovePiece();
        }
    }
    
    void inputTaken(Index fromIndex, Index toIndex) {
        Position from = this->board->indexToPosition(fromIndex.x, fromIndex.y);
        Position to = this->board->indexToPosition(toIndex.x, toIndex.y);
        this->inputTaken(from, to);
    }
    
    void movePiece(Position from, Position to) {
        Index fromIndex = this->board->positionToIndex(from);
        Index toIndex = this->board->positionToIndex(to);
        [this->gameViewController movePiece:fromIndex to:toIndex];
    }
    
    NSMutableArray *generateMoves(NSUInteger file, NSUInteger rank) {
        return this->convertMovesToArray(this->board->pieceArray[rank][file]->pieceStrategy);
    }
    
    NSMutableArray *convertMovesToArray(PieceStrategy *pieceStrategy) {
        
        NSMutableArray *movesArray = [[NSMutableArray alloc] initWithCapacity:NUMBER_OF_RANKS_ON_BOARD];
        
        for (int file = 0; file < NUMBER_OF_FILES_ON_BOARD; file ++) {
            [movesArray addObject:[NSMutableArray arrayWithObjects:
                                   [NSNumber numberWithBool:NO],
                                   [NSNumber numberWithBool:NO],
                                   [NSNumber numberWithBool:NO],
                                   [NSNumber numberWithBool:NO],
                                   [NSNumber numberWithBool:NO],
                                   [NSNumber numberWithBool:NO],
                                   [NSNumber numberWithBool:NO],
                                   [NSNumber numberWithBool:NO],
                                   nil]];
        }
        
        DecentralBitboard *decentralBitboard = pieceStrategy->decentralBitboard;
        std::list<Position> moves = pieceStrategy->centralBitboard->computePositionsFromBitboard(decentralBitboard->moves);
        for(std::list<Position>::iterator iterator = moves.begin(); iterator != moves.end(); iterator++) {
            Index index = this->board->positionToIndex(*iterator);
            movesArray[index.y][index.x] = [NSNumber numberWithBool:YES];
        }
        
        return movesArray;
    }
    
    void cannotMovePiece() {
        [this->gameViewController cannotMovePiece];
    }
    
    void startNewGame() {
        
    }
};

@implementation GameViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    OTHER_QUEUE
        self.controller = new Controller(self);
    });
}

- (void)displayError:(NSString *)message {
    MAIN_QUEUE
        [self.gameView displayError:message];
    });
}

- (void)createAllPieces:(NSMutableArray *)rankArray {
    MAIN_QUEUE
        [self.gameView createAllPieces:rankArray];
    });
}

- (void)movePiece:(Index)fromIndex to:(Index)toIndex {
    MAIN_QUEUE
        [self.gameView movePiece:fromIndex to:toIndex];
    });
}

- (void)cannotMovePiece {
    MAIN_QUEUE
        [self.gameView cannotMovePiece];
    });
}

- (void)canTakeInput:(Color)color {
    MAIN_QUEUE
        [self.gameView canTakeInput:color];
    });
}

- (void)inputTakenFrom:(Position)from to:(Position)to {
    OTHER_QUEUE
        self.controller->inputTaken(from, to);
    });
}

- (void)inputTakenFromIndex:(Index)fromIndex toIndex:(Index)toIndex {
    OTHER_QUEUE
        self.controller->inputTaken(fromIndex, toIndex);
    });
}

- (NSMutableArray *)generateMovesForPieceOnFile:(NSUInteger)file rank:(NSUInteger)rank {
    return self.controller->generateMoves(file, rank);
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

@end
