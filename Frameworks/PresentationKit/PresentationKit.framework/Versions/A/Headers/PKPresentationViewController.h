#import <UIKit/UIKit.h>

typedef enum {
    kDeploymentModeProduction,
    kDeploymentModePreview,
    kDeploymentModeTraining,
    kDeploymentModeAssessment,
    kDeploymentModeDraft
} DeploymentMode;

@class PKPresentationViewController;
@class PKCallBuilder;
@class PKBreadcrumbItem;

@protocol PKExitPresentationViewController <NSObject>

@property (copy, nonatomic) void(^exitBlock)(void);
@property (copy, nonatomic) void(^cancelBlock)(void);

@end

@protocol PKPresentationViewControllerDelegate <NSObject>

@required
- (void) presentationViewControllerDidRequestExit:(PKPresentationViewController*)controller;

@optional
- (void) presentationViewController:(PKPresentationViewController*)controller requestedSubmitCall:(PKCall*)call;
- (UIViewController<PKExitPresentationViewController>*) presentationViewControllerRequestedExitViewController:(PKPresentationViewController*)controller;
- (UIViewController*) presentationViewControllerRequestedExitConfirmationViewController:(PKPresentationViewController*)controller;
- (void) presentationViewControllerDidPressSignButton:(PKPresentationViewController*)controller;
- (void) presentationViewController:(PKPresentationViewController*)controller userDidSelfCertifyForPresentation:(PKPresentation*)presentation;
- (NSURL*) presentationViewController:(PKPresentationViewController*)controller willLoadContentFromURL:(NSURL*)url;
- (void) presentationViewController:(PKPresentationViewController *)controller prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender;
- (void) presentationViewControllerRequestedNextPresentation:(PKPresentationViewController*)controller;

@end


@interface PKPresentationViewController : UIViewController

@property (nonatomic, weak) id <PKPresentationViewControllerDelegate> delegate;

@property (nonatomic, strong) PKFlow* flow;

@property (nonatomic, strong) PKCallBuilder* callBuilder;
@property (nonatomic) DeploymentMode deploymentMode;
@property (nonatomic, strong) PKRepresentative* representative;

- (void) divergeToBreadcrumb:(PKBreadcrumbItem*)breadcrumb;

- (void) restartActiveCall;

- (void) resetPresentation;
- (void) setUpPresentationEnvironment;
- (void) startPresentation;

@end