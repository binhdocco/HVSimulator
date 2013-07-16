
extern NSString* const kFullscreenWebViewControllerCloseNotification;

@interface PKFullscreenWebViewController : UIViewController <UIWebViewDelegate>

@property (strong, nonatomic, readonly) NSURL* url;
@property (strong, nonatomic, readonly) NSString* webTitle;

- (id) initWithURL:(NSURL*)url title:(NSString*)webTitle;

- (void) backAction;

@end

