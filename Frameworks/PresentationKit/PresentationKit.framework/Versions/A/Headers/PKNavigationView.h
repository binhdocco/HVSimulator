
@class PKBreadcrumbView;
@class PKBreadcrumbItem;
@class PKNavigationView;
@class PKFlow;
@class PKThumbnailMapView;

typedef enum {
    NegativeAttitudinalState,
    NeutralAttitudinalState,
    PositiveAttitudinalState
} AttitudinalState;

@protocol NavigationViewDelegate <NSObject>
- (void) brandButtonDoubleTapped:(PKNavigationView*)navView;
- (void) navigationView:(PKNavigationView*)navView selectedAttitudinalState:(AttitudinalState)state;
- (void) navigationView:(PKNavigationView*)navView executeJavascriptActionWithName:(NSString*)name;

- (void) signPressedForClass:(PKNavigationView*)navView;
- (void) screenLock:(BOOL)locked ForClass:(PKNavigationView*)navView;
- (void) highlight:(BOOL)enabled ForClass:(PKNavigationView*)navView;
- (void) showDoctorsPressedForClass:(PKNavigationView*)navView;
- (void) closePressedForClass:(PKNavigationView*)navView withButton:(UIButton*)button;
- (void) thumbnailMapOpenedForClass:(PKNavigationView*)navView;
- (void) thumbnailMapClosedForClass:(PKNavigationView*)navView;
@optional
- (void) showBriefcasePressedForClass:(PKNavigationView*)navView;
@end


@interface PKNavigationView : UIControl

@property (nonatomic, weak) IBOutlet id <NavigationViewDelegate> delegate;
@property (nonatomic, strong) IBOutlet UIButton* brandsButton; // Deprecated in version 0.9.8
@property (nonatomic, strong) IBOutletCollection(UIButton) NSArray* brandsButtons;
@property (nonatomic, weak) IBOutlet UIViewController* controller;
@property (nonatomic, strong) NSDictionary* viewsByName;

@property (strong, nonatomic) IBOutlet UILabel* slideTitle;
@property (strong, nonatomic) IBOutlet UIButton* homeButton;
@property (strong, nonatomic) IBOutlet UIButton* menuButton;
@property (strong, nonatomic) IBOutlet UIButton* piButton;
@property (strong, nonatomic) IBOutlet UIButton* briefcaseButton;
@property (strong, nonatomic) IBOutlet UISlider* lockSlider;
@property (strong, nonatomic) IBOutlet UIButton* highlightButton;
@property (strong, nonatomic) IBOutlet UIButton* attitudinalButtonPositive;
@property (strong, nonatomic) IBOutlet UIButton* attitudinalButtonNegative;
@property (strong, nonatomic) IBOutlet UIButton* attitudinalButtonNeutral;
@property (strong, nonatomic) IBOutlet UIView* menuView;
@property (strong, nonatomic) IBOutlet UIView* menuLocationReferenceView;
@property (strong, nonatomic) IBOutlet UIView* thumbMap;
@property (strong, nonatomic) IBOutlet UIView* gestureBox;
@property (strong, nonatomic) IBOutlet PKBreadcrumbView* breadcrumbView;
@property (strong, nonatomic) IBOutlet UIView* breadcrumbContainerView;
@property (strong, nonatomic) IBOutlet UIImageView* hcpFlag;
@property (strong, nonatomic) IBOutletCollection(UIView) NSArray* passThroughViews;
@property (strong, nonatomic) PKThumbnailMapView* thumbnailMapView;

+ (PKNavigationView*) navigationViewInBundle:(NSBundle*)bundle withOwner:(id)owner menuDescriptor:(NSDictionary*)menuDescriptor;

- (void) changeToBradcrumbItem:(PKBreadcrumbItem*)item;

- (NSArray*) divergentSection;
- (PKBreadcrumbItem*)divergentSectionAnchor;
- (void) setDivergentSection:(NSArray*)section relativeToBreadcrumb:(PKBreadcrumbItem*)breadcrumb;

- (void) setBreadcrumbsBySection:(NSArray*)breadcrumbsBySection withSelectedFlow:(PKFlow*)selectedFlow;
- (void) populateMapWithActiveBreadcrumbArrays:(NSArray*)activeBreadcrumbs andDivergentBreadcrumbsArrays:(NSArray*)divergentBreadcrumbs;

- (void) setFlowForThumbnailMap:(PKFlow*)flow;

- (void) showHighlightIfDrawingIsEnabled:(BOOL)isDrawingEnabled;

- (void) showScreenLockedIfEnabled:(BOOL)screenLockEnabled;
- (void) addDoubleTapToExitPresentation;

- (IBAction) homeButtonPressed:(id)sender;
- (IBAction) piButtonPressed:(id)sender;
- (IBAction) closeButtonPressed:(id)sender;
- (IBAction) showDoctorsPressed:(id)sender;
- (IBAction) executeJavascriptAction:(id)sender;
- (IBAction) signPressed:(id)sender;
- (IBAction) briefcasePressed:(id)sender;
- (IBAction) buttonPressed:(UIButton*)sender;
- (IBAction) lockSliderTouchEnd:(id)sender;
- (IBAction) attitudinalButtonPressed:(id)sender;

@end