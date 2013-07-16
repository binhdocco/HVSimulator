@class PKBreadcrumbItem;
@class PKFlow;

@interface PKBreadcrumbView : UIView

@property (nonatomic, strong) PKBreadcrumbItem* selectedItem;
@property (nonatomic, strong, readonly) NSArray* divergentSection;
@property (nonatomic, strong, readonly) PKBreadcrumbItem* divergentSectionAnchor;
@property (nonatomic, strong) UIColor* breadcrumbMainColor;
@property (nonatomic, strong) UIColor* breadcrumbSubColor;
@property (nonatomic, strong) UIColor* breadcrumbSelectedColor;
@property (nonatomic, strong) UIColor* breadcrumbLineColor;
@property (nonatomic) BOOL showBreadcrumbLine;

-(void) setBreadcrumbsBySection:(NSArray *)breadcrumbsBySection withSelectedFlow:(PKFlow*)selectedFlow;
-(void) setDivergentSection:(NSArray *)divergentSection relativeToBreadcrumb:(PKBreadcrumbItem*)breadcrumb;

@end