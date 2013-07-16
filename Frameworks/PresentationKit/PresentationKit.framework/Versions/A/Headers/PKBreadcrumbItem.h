@class PKSlide;

@interface PKBreadcrumbItem : NSObject

@property (nonatomic, strong) PKSlide* slide;
@property (nonatomic, strong) PKBreadcrumbItem* leftNeighbor;
@property (nonatomic, strong) PKBreadcrumbItem* rightNeighbor;
@property (nonatomic, strong) PKBreadcrumbItem* topNeighbor;
@property (nonatomic, strong) PKBreadcrumbItem* bottomNeighbor;

@property (nonatomic) int horizontalIndex;
@property (nonatomic) int verticalIndex;

@property (nonatomic) BOOL isSelected;
@property (nonatomic) BOOL isActiveCall;


@end
