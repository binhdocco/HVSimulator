@class PKFlow;
@class PKSlide;

@interface PKFlowSlide : NSManagedObject

@property (nonatomic, strong) PKFlow* flow;
@property (nonatomic, strong) NSOrderedSet* slides;

@end
