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

@interface GameView()

@property (weak, nonatomic) IBOutlet UITextField *fromFile;
@property (weak, nonatomic) IBOutlet UITextField *fromRank;
@property (weak, nonatomic) IBOutlet UITextField *toFile;
@property (weak, nonatomic) IBOutlet UITextField *toRank;

@property (strong, nonatomic) NSArray *previousBoardArray;

@property (strong, nonatomic) SCNNode *liftedPiece;

@end

@implementation GameView

- (void)awakeFromNib {
    self.scene = [SCNScene scene];
    
    self.allowsCameraControl = YES;
    self.showsStatistics = YES;
    self.backgroundColor = [UIColor blackColor];
    
    SCNNode *cameraNode = [SCNNode node];
    cameraNode.camera = [SCNCamera camera];
    [self.scene.rootNode addChildNode:cameraNode];
    
    cameraNode.position = SCNVector3Make(CAMERA_X_POSITION, CAMERA_Y_POSITION, CAMERA_Z_POSITION);
    cameraNode.eulerAngles = SCNVector3Make(CAMERA_X_ROTATION, CAMERA_Y_ROTATION, CAMERA_Z_ROTATION);
    
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
    SCNBox *lightSquare = [SCNBox boxWithWidth:1 height:0.2 length:1 chamferRadius:0];
    SCNBox *darkSquare = [lightSquare copy];
    
    SCNMaterial *lightMaterial = [SCNMaterial material];
    UIColor *lightColor = [UIColor colorWithRed:0.9 green:0.85 blue:0.8 alpha:1.0];
    lightMaterial.diffuse.contents = lightColor;
    
    SCNMaterial *darkMaterial = [lightMaterial copy];
    darkMaterial.diffuse.contents = [UIColor colorWithWhite:.15 alpha:1.0];
    
    lightSquare.firstMaterial = lightMaterial;
    darkSquare.firstMaterial = darkMaterial;
    
    SCNNode *boardNode = [SCNNode node];
    boardNode.position = SCNVector3Make(0, 0, 0);
    
    for (NSInteger rank = 0; rank < NUMBER_OF_RANKS_ON_BOARD; rank ++) {
        for (NSInteger file = 0; file < NUMBER_OF_FILES_ON_BOARD; file ++) {
            
            BOOL isBlack = (rank + file) % 2 != 0;
            SCNGeometry *geometry = isBlack ? darkSquare : lightSquare;
            SquareNode *squareNode = [SquareNode nodeWithGeometry:geometry file:file rank:rank];
            
            squareNode.position = SCNVector3Make(file, 0, rank);
            [boardNode addChildNode:squareNode];
        }
    }
    
    return boardNode;
}

- (void)movePiece:(Index)fromIndex to:(Index)toIndex {
    GameViewModel *viewModel = self.previousBoardArray[fromIndex.y][fromIndex.x];
    SCNNode *pieceNode = viewModel.pieceNode;
    [self.previousBoardArray[toIndex.y][toIndex.x] setPieceNode:pieceNode];
    pieceNode.position = SCNVector3Make(toIndex.x, 0.0f, -toIndex.y + 7);
    viewModel.pieceNode = nil;
    [self createPieceOnFile:fromIndex.y rank:fromIndex.x type:EMPTY color:white viewModel:viewModel];
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
    
}

- (void)liftPieceUp:(SquareNode *)pieceNode {
    self.liftedPiece = pieceNode;
    SCNVector3 position = self.liftedPiece.position;
    position.y += LIFT_PIECE_Y_DISTANCE;
    self.liftedPiece.position = position;
}

- (void)moveToSquare:(SquareNode *)squareNode {
    
    Index fromIndex;
    fromIndex.x = self.liftedPiece.position.x;
    fromIndex.y = - self.liftedPiece.position.z + 7;
    
    Index toIndex;
    toIndex.x = (int)squareNode.file;
    toIndex.y = - (int)squareNode.rank + 7;
    
    [self.gameViewDelegate inputTakenFromIndex:fromIndex toIndex:toIndex];
}

- (void)handleTap:(UIGestureRecognizer*)gestureRecognize {
    
    // check what nodes are tapped
    CGPoint p = [gestureRecognize locationInView:self];
    NSArray *hitResults = [self hitTest:p options:nil];
    
    // check that we clicked on at least one object
    if([hitResults count] > 0){
        // retrieved the first clicked object
        SCNHitTestResult *result = [hitResults objectAtIndex:0];
        
        [SCNTransaction begin];
        [SCNTransaction setAnimationDuration:0.5];
        
        SquareNode *squareNode = (SquareNode *)result.node;
        
        if ([result.node isKindOfClass:[SquareNode class]]) {
            [self moveToSquare:squareNode];
        } else {
            [self liftPieceUp:squareNode];
        }
        
        [SCNTransaction commit];
    }
}

@end
