//
//  GameView.m
//  Chess
//
//  Created by Adnan Zahid on 3/17/16.
//  Copyright © 2016 Adnan Zahid. All rights reserved.
//

#import "GameView.h"
#import "GameViewModel.h"

@interface GameView()

@property (weak, nonatomic) IBOutlet UITextField *fromFile;
@property (weak, nonatomic) IBOutlet UITextField *fromRank;
@property (weak, nonatomic) IBOutlet UITextField *toFile;
@property (weak, nonatomic) IBOutlet UITextField *toRank;

@property (strong, nonatomic) NSMutableArray *rankArray;
@property (nonatomic) BOOL isFirstTime;

@end

@implementation GameView

- (void)awakeFromNib {
    self.isFirstTime = YES;
    self.scene = [SCNScene scene];
    
    self.allowsCameraControl = YES;
    self.showsStatistics = YES;
    self.backgroundColor = [UIColor blackColor];
    
    SCNNode *cameraNode = [SCNNode node];
    cameraNode.camera = [SCNCamera camera];
    [self.scene.rootNode addChildNode:cameraNode];
    
    cameraNode.position = SCNVector3Make(CAMERA_X_POSITION, CAMERA_Y_POSITION, CAMERA_Z_POSITION);
    cameraNode.eulerAngles = SCNVector3Make(-0.5f, 0.0f, 0.0f);
    
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
    
    [self.scene.rootNode addChildNode:[self addChessBoard]];
}

- (SCNNode *)addChessBoard {
    SCNBox* lightSquare = [SCNBox boxWithWidth:1 height:0.2 length:1 chamferRadius:0];
    SCNBox* darkSquare = [lightSquare copy];
    
    SCNMaterial* lightMaterial = [SCNMaterial material];
    UIColor *lightColor = [UIColor colorWithRed:0.9 green:0.85 blue:0.8 alpha:1.0];
    lightMaterial.diffuse.contents = lightColor;
    
    SCNMaterial* darkMaterial = [lightMaterial copy];
    darkMaterial.diffuse.contents = [UIColor colorWithWhite:.15 alpha:1.0];
    
    lightSquare.firstMaterial = lightMaterial;
    darkSquare.firstMaterial = darkMaterial;
    
    SCNNode* boardNode = [SCNNode node];
    boardNode.position = SCNVector3Make(0, 0, 0);
    
    for (NSInteger rank = 0; rank < NUMBER_OF_RANKS_ON_BOARD; rank ++) {
        for (NSInteger file = 0; file < NUMBER_OF_FILES_ON_BOARD; file ++) {
            
            BOOL isBlack = (rank + file) % 2 != 0;
            SCNGeometry* geometry = isBlack ? darkSquare : lightSquare;
            SCNNode* squareNode = [SCNNode nodeWithGeometry:[geometry copy]];
            
            squareNode.position = SCNVector3Make(file, 0, rank);
            [boardNode addChildNode:squareNode];
        }
    }
    
    return [boardNode flattenedClone];
}

- (void)displayView:(NSMutableArray *)rankArray {
    self.rankArray = rankArray;
    if (self.isFirstTime == YES) {
        self.isFirstTime = NO;
        [self createAllPieces:rankArray];
    } else {
        [self movePieces:rankArray];
    }
}

- (void)movePieces:(NSMutableArray *)rankArray {
    
    for (NSUInteger i = 0; i < rankArray.count; i ++) {
        NSArray *fileArray = rankArray[i];
        NSArray *localFileArray = self.rankArray[i];
        for (NSUInteger j = 0; j < fileArray.count; j ++) {
            GameViewModel *viewModel = fileArray[j];
            GameViewModel *localViewModel = localFileArray[j];
            
            if (viewModel.order == localViewModel.order) {
                
            } else {
                
                int a = 10 + 5;
            }
        }
    }
}

- (void)createAllPieces:(NSMutableArray *)rankArray {
    NSUInteger rank = 0;
    
    for (NSArray *fileArray in rankArray) {
        NSUInteger file = 0;
        for (GameViewModel *viewModel in fileArray) {
            switch (viewModel.value) {
                case PAWN: {
                    [self createPieceOnX:file y:rank type:PawnType color:white];
                    break;
                }
                case KNIGHT: {
                    [self createPieceOnX:file y:rank type:KnightType color:white];
                    break;
                }
                case BISHOP: {
                    [self createPieceOnX:file y:rank type:BishopType color:white];
                    break;
                }
                case ROOK: {
                    [self createPieceOnX:file y:rank type:RookType color:white];
                    break;
                }
                case QUEEN: {
                    [self createPieceOnX:file y:rank type:QueenType color:white];
                    break;
                }
                case KING: {
                    [self createPieceOnX:file y:rank type:KingType color:white];
                    break;
                }
                    
                    
                case -PAWN: {
                    [self createPieceOnX:file y:rank type:PawnType color:black];
                    break;
                }
                case -KNIGHT: {
                    [self createPieceOnX:file y:rank type:KnightType color:black];
                    break;
                }
                case -BISHOP: {
                    [self createPieceOnX:file y:rank type:BishopType color:black];
                    break;
                }
                case -ROOK: {
                    [self createPieceOnX:file y:rank type:RookType color:black];
                    break;
                }
                case -QUEEN: {
                    [self createPieceOnX:file y:rank type:QueenType color:black];
                    break;
                }
                case -KING: {
                    [self createPieceOnX:file y:rank type:KingType color:black];
                    break;
                }
            }
            file ++;
        }
        rank ++;
    }
}

- (void)createPieceOnX:(NSUInteger)x y:(NSUInteger)y type:(NSString *)type color:(Color)color {
    
    SCNScene *pieces = [SCNScene sceneNamed:@"art.scnassets/chess pieces.dae"];
    
    SCNNode *node = [pieces.rootNode childNodeWithName:type recursively:YES];
    node = [node copy];
    
    if (color == black) {
        node.geometry = [node.geometry copy];
        SCNMaterial *blackMaterial = [node.geometry.firstMaterial copy];
        blackMaterial.diffuse.contents = [UIColor colorWithWhite:0.35 alpha:1.0];
        node.geometry.firstMaterial = blackMaterial;
    }
    
    node.position = SCNVector3Make(x, 0, y);
    node.rotation = SCNVector4Make(1.0f, 0, 0, M_PI_2);
    node.scale = SCNVector3Make(.67, .67, .67);
    
    [self.scene.rootNode addChildNode:node];
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
    
    [self.gameViewDelegate inputTaken:fromPosition to:toPosition];
}

- (void)canTakeInput:(Color)color {
    
}

@end
