//
//  GameView.m
//  Chess
//
//  Created by Adnan Zahid on 3/17/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#import "GameView.h"
#import "GameViewModel.h"
#import "SquareNode.h"
#import "UIAlertView+Blocks.h"

@interface GameView()

@property (weak, nonatomic) IBOutlet UITextField *fromFile;
@property (weak, nonatomic) IBOutlet UITextField *fromRank;
@property (weak, nonatomic) IBOutlet UITextField *toFile;
@property (weak, nonatomic) IBOutlet UITextField *toRank;

@property (strong, nonatomic) NSArray *previousBoardArray;

@property (strong, nonatomic) SCNNode *cameraNode;
@property (strong, nonatomic) SCNNode *liftedPiece;
@property (strong, nonatomic) SCNNode *liftedPieceMovesBoard;

@end

@implementation GameView

- (void)awakeFromNib {
    self.scene = [SCNScene scene];
    
    self.allowsCameraControl = YES;
    self.showsStatistics = YES;
    self.backgroundColor = [UIColor blackColor];
    
    self.cameraNode = [SCNNode node];
    self.cameraNode.camera = [SCNCamera camera];
    [self.scene.rootNode addChildNode:self.cameraNode];
    
    self.cameraNode.position = SCNVector3Make(WHITE_CAMERA_X_POSITION, WHITE_CAMERA_Y_POSITION, WHITE_CAMERA_Z_POSITION);
    self.cameraNode.eulerAngles = SCNVector3Make(WHITE_CAMERA_X_ROTATION, WHITE_CAMERA_Y_ROTATION, WHITE_CAMERA_Z_ROTATION);
    
    SCNNode *cameraTarget = [SCNNode node];
    cameraTarget.position = SCNVector3Make(WHITE_CAMERA_X_POSITION, 0.0f, WHITE_CAMERA_X_POSITION);
    SCNLookAtConstraint *lookAtCenter = [SCNLookAtConstraint lookAtConstraintWithTarget:cameraTarget];
    //    lookAtCenter.gimbalLockEnabled = YES;
    self.cameraNode.constraints = @[lookAtCenter];
    
    SCNNode *lightNode = [SCNNode node];
    lightNode.light = [SCNLight light];
    lightNode.light.type = SCNLightTypeOmni;
    lightNode.position = SCNVector3Make(LIGHT_X_POSITION, LIGHT_Y_POSITION, LIGHT_Z_POSITION);
    [self.scene.rootNode addChildNode:lightNode];
    
    SCNNode *ambientLightNode = [SCNNode node];
    ambientLightNode.light = [SCNLight light];
    ambientLightNode.light.type = SCNLightTypeAmbient;
    ambientLightNode.light.color = [UIColor darkGrayColor];
    [self.scene.rootNode addChildNode:ambientLightNode];
    
    UITapGestureRecognizer *tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleTap:)];
    NSMutableArray *gestureRecognizers = [NSMutableArray array];
    [gestureRecognizers addObject:tapGesture];
    [gestureRecognizers addObjectsFromArray:self.gestureRecognizers];
    self.gestureRecognizers = gestureRecognizers;
}

- (SCNNode *)addChessBoard {
    SCNBox *lightSquare = [SCNBox boxWithWidth:1.0f height:0.2f length:1.0f chamferRadius:0.0f];
    SCNBox *darkSquare = [lightSquare copy];
    
    SCNMaterial *lightMaterial = [SCNMaterial material];
    UIColor *lightColor = [UIColor colorWithRed:0.9f green:0.85f blue:0.8f alpha:1.0f];
    lightMaterial.diffuse.contents = lightColor;
    
    SCNMaterial *darkMaterial = [lightMaterial copy];
    darkMaterial.diffuse.contents = [UIColor colorWithWhite:0.15f alpha:1.0f];
    
    lightSquare.firstMaterial = lightMaterial;
    darkSquare.firstMaterial = darkMaterial;
    
    SCNNode *boardNode = [SCNNode node];
    boardNode.position = SCNVector3Zero;
    
    for (NSInteger rank = 0; rank < NUMBER_OF_RANKS_ON_BOARD; rank ++) {
        for (NSInteger file = 0; file < NUMBER_OF_FILES_ON_BOARD; file ++) {
            
            BOOL isBlack = (rank + file) % 2 != 0;
            SCNGeometry *geometry = isBlack ? darkSquare : lightSquare;
            SquareNode *squareNode = [SquareNode nodeWithGeometry:geometry file:file rank:rank];
            
            squareNode.position = SCNVector3Make(file, 0.0f, rank);
            [boardNode addChildNode:squareNode];
        }
    }
    
    return boardNode;
}

- (void)movePiece:(Index)fromIndex to:(Index)toIndex {
    SCNNode *capturedPieceNode = [self.previousBoardArray[toIndex.y][toIndex.x] pieceNode];
    if (capturedPieceNode != nil) {
        //        [self animateWithAction:^{
        //            [self moveCapturedPiece:capturedPieceNode direction:-1];
        //        }];
        [capturedPieceNode removeFromParentNode];
    }
    
    GameViewModel *viewModel = self.previousBoardArray[fromIndex.y][fromIndex.x];
    SCNNode *pieceNode = viewModel.pieceNode;
    [self.previousBoardArray[toIndex.y][toIndex.x] setPieceNode:pieceNode];
    [self animateWithAction:^{
        pieceNode.position = SCNVector3Make(toIndex.x, 0.0f, -toIndex.y + 7);
    }];
    viewModel.pieceNode = nil;
    [self createPieceOnFile:fromIndex.y rank:fromIndex.x type:EMPTY color:white viewModel:viewModel];
    [self nullifyLiftedPiece];
}

- (void)cannotMovePiece {
    [self liftPiece:self.liftedPiece direction:-1];
    [self nullifyLiftedPiece];
}

- (void)nullifyLiftedPiece {
    self.liftedPiece = nil;
    [self.liftedPieceMovesBoard removeFromParentNode];
    self.liftedPieceMovesBoard = nil;
}

- (void)createAllPieces:(NSMutableArray *)rankArray {
    self.previousBoardArray = rankArray;
    [self.scene.rootNode addChildNode:[self addChessBoard]];
    NSUInteger rank = 0;
    for (NSArray *fileArray in rankArray) {
        NSUInteger file = 0;
        for (GameViewModel *viewModel in fileArray) {
            switch (viewModel.value) {
                case EMPTY: {
                    [self createPieceOnFile:file rank:rank type:EmptyType color:white viewModel:viewModel];
                    break;
                }
                    
                case PAWN: {
                    [self createPieceOnFile:file rank:rank type:PawnType color:white viewModel:viewModel];
                    break;
                }
                case KNIGHT: {
                    [self createPieceOnFile:file rank:rank type:KnightType color:white viewModel:viewModel];
                    break;
                }
                case BISHOP: {
                    [self createPieceOnFile:file rank:rank type:BishopType color:white viewModel:viewModel];
                    break;
                }
                case ROOK: {
                    [self createPieceOnFile:file rank:rank type:RookType color:white viewModel:viewModel];
                    break;
                }
                case QUEEN: {
                    [self createPieceOnFile:file rank:rank type:QueenType color:white viewModel:viewModel];
                    break;
                }
                case KING: {
                    [self createPieceOnFile:file rank:rank type:KingType color:white viewModel:viewModel];
                    break;
                }
                    
                    
                case -PAWN: {
                    [self createPieceOnFile:file rank:rank type:PawnType color:black viewModel:viewModel];
                    break;
                }
                case -KNIGHT: {
                    [self createPieceOnFile:file rank:rank type:KnightType color:black viewModel:viewModel];
                    break;
                }
                case -BISHOP: {
                    [self createPieceOnFile:file rank:rank type:BishopType color:black viewModel:viewModel];
                    break;
                }
                case -ROOK: {
                    [self createPieceOnFile:file rank:rank type:RookType color:black viewModel:viewModel];
                    break;
                }
                case -QUEEN: {
                    [self createPieceOnFile:file rank:rank type:QueenType color:black viewModel:viewModel];
                    break;
                }
                case -KING: {
                    [self createPieceOnFile:file rank:rank type:KingType color:black viewModel:viewModel];
                    break;
                }
            }
            file ++;
        }
        rank ++;
    }
}

- (void)createPieceOnFile:(NSUInteger)file rank:(NSUInteger)rank type:(NSString *)type color:(Color)color viewModel:(GameViewModel *)viewModel {
    
    if ([type isEqualToString:EmptyType] == NO) {
        SCNScene *pieces = [SCNScene sceneNamed:@"art.scnassets/chess pieces.dae"];
        
        SCNNode *node = [pieces.rootNode childNodeWithName:type recursively:YES];
        
        if (color == black) {
            SCNMaterial *blackMaterial = node.geometry.firstMaterial;
            blackMaterial.diffuse.contents = [UIColor colorWithWhite:0.35 alpha:1.0];
            node.geometry.firstMaterial = blackMaterial;
        }
        
        node.position = SCNVector3Make(file, 0, - rank + 7);
        node.rotation = SCNVector4Make(1.0f, 0, 0, M_PI_2);
        node.scale = SCNVector3Make(.67, .67, .67);
        
        [self.scene.rootNode addChildNode:node];
        viewModel.pieceNode = node;
    }
    
    viewModel.file = file;
    viewModel.rank = rank;
}

- (IBAction)submit:(id)sender {
    NSString *fromFile = self.fromFile.text;
    NSString *fromRank = self.fromRank.text;
    NSString *toFile = self.toFile.text;
    NSString *toRank = self.toRank.text;
    
    Position fromPosition;
    fromPosition.rank = [fromRank characterAtIndex:0];
    fromPosition.file = [fromFile characterAtIndex:0];
    
    Position toPosition;
    toPosition.rank = [toRank characterAtIndex:0];
    toPosition.file = [toFile characterAtIndex:0];
    
    [self.gameViewDelegate inputTakenFrom:fromPosition to:toPosition];
}

- (void)canTakeInput:(Color)color {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.6f * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
        if (color == white) {
            [self animateWithAction:^{
                self.cameraNode.position = SCNVector3Make(WHITE_CAMERA_X_POSITION, WHITE_CAMERA_Y_POSITION, WHITE_CAMERA_Z_POSITION);
                self.cameraNode.eulerAngles = SCNVector3Make(WHITE_CAMERA_X_ROTATION, WHITE_CAMERA_Y_ROTATION, WHITE_CAMERA_Z_ROTATION);
            }];
        } else {
            [self animateWithAction:^{
                self.cameraNode.position = SCNVector3Make(BLACK_CAMERA_X_POSITION, BLACK_CAMERA_Y_POSITION, BLACK_CAMERA_Z_POSITION);
                self.cameraNode.eulerAngles = SCNVector3Make(BLACK_CAMERA_X_ROTATION, BLACK_CAMERA_Y_ROTATION, BLACK_CAMERA_Z_ROTATION);
            }];
        }
    });
}

- (void)moveCapturedPiece:(SCNNode *)pieceNode direction:(int)direction {
    SCNVector3 position = pieceNode.position;
    position.z += CAPTURED_PIECE_Z_DISTANCE * direction;
    pieceNode.position = position;
}

- (void)liftPiece:(SCNNode *)pieceNode direction:(int)direction {
    self.liftedPiece = pieceNode;
    SCNVector3 position = self.liftedPiece.position;
    position.y += LIFT_PIECE_Y_DISTANCE * direction;
    self.liftedPiece.position = position;
    
    if (direction == 1) {
        [self showMoves];
    }
}

- (void)showMoves {
    NSMutableArray *moves = [self.gameViewDelegate generateMovesForPieceOnFile:self.liftedPiece.position.x rank:-self.liftedPiece.position.z + 7];
    self.liftedPieceMovesBoard = [self drawMovesBoard:moves];
    [self.scene.rootNode addChildNode:self.liftedPieceMovesBoard];
}

- (SCNNode *)drawMovesBoard:(NSMutableArray *)moves {
    SCNBox *square = [SCNBox boxWithWidth:1.0f height:0.2f length:1.0f chamferRadius:0.0f];
    
    SCNMaterial *material = [SCNMaterial material];
    UIColor *color = [UIColor colorWithRed:0.0f green:0.75f blue:0.0f alpha:0.5f];
    material.diffuse.contents = color;
    
    square.firstMaterial = material;
    
    SCNNode *boardNode = [SCNNode node];
    boardNode.position = SCNVector3Zero;
    
    for (NSInteger rank = 0; rank < NUMBER_OF_RANKS_ON_BOARD; rank ++) {
        for (NSInteger file = 0; file < NUMBER_OF_FILES_ON_BOARD; file ++) {
            if ([moves[rank][file] boolValue] == YES) {
                SCNNode *node = [SCNNode nodeWithGeometry:square];
                node.position = SCNVector3Make(file, 0.0f, -rank + 7);
                [boardNode addChildNode:node];
            }
        }
    }
    
    return boardNode;
}

- (void)moveToSquare:(id)node {
    
    Index fromIndex;
    fromIndex.x = self.liftedPiece.position.x;
    fromIndex.y = - self.liftedPiece.position.z + 7;
    
    Index toIndex;
    
    if ([node isKindOfClass:[SquareNode class]] == YES) {
        SquareNode *squareNode = (SquareNode *)node;
        toIndex.x = (int)squareNode.file;
        toIndex.y = - (int)squareNode.rank + 7;
    } else {
        SCNNode *pieceNode = (SCNNode *)node;
        toIndex.x = pieceNode.position.x;
        toIndex.y = - pieceNode.position.z + 7;
    }
    
    [self.gameViewDelegate inputTakenFromIndex:fromIndex toIndex:toIndex];
}

- (void)displayError:(NSString *)message {
//    [UIAlertView showWithTitle:message
//                       message:nil
//             cancelButtonTitle:@"Okay"
//             otherButtonTitles:nil
//                      tapBlock:nil];
}

- (void)handleTap:(UIGestureRecognizer*)gestureRecognizer {
    
    // check what nodes are tapped
    CGPoint point = [gestureRecognizer locationInView:self];
    NSArray *hitResults = [self hitTest:point options:nil];
    
    // check that we clicked on at least one object
    if([hitResults count] > 0){
        // retrieved the first clicked object
        SCNHitTestResult *result = [hitResults objectAtIndex:0];
        
        SCNNode *node = result.node;
        
        [self animateWithAction:^{
            if ([result.node isKindOfClass:[SquareNode class]]) {
                [self moveToSquare:node];
            } else if (self.liftedPiece == nil) {
                [self liftPiece:node direction:1];
            } else {
                [self moveToSquare:node];
            }
        }];
    }
}

- (void)animateWithAction:(void (^)())action {
    [SCNTransaction begin];
    [SCNTransaction setAnimationDuration:0.5f];
    action();
    [SCNTransaction commit];
}

@end
