#import <PresentationKit/PKPresentationViewController+Private.h>

@class PKNavigationView;
@class PKPresentationContentScrollView;
@class PKCallBuilder;
@class PKBreadcrumbItem;

@interface PKPresentationViewController ()
@property (nonatomic, weak, readonly) IBOutlet PKNavigationView* navigationView;
@property (nonatomic, strong, readonly) PKPresentationContentScrollView* contentScroller;

@property (nonatomic, strong) PKBreadcrumbItem* currentBreadcrumbItem;
@property (nonatomic, assign) BOOL thumbMapActive;
@property (nonatomic, assign) BOOL briefcaseActive;

- (BOOL) goToSlideWithIdentifier:(NSString*)identifier;

@end
