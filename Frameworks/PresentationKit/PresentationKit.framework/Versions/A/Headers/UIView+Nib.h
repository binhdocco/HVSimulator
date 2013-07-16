#import <UIKit/UIKit.h>

@interface UIView (Nib)

+ (id) viewWithNibNamed:(NSString*)nibNameOrNil;
+ (id) viewWithNibNamed:(NSString*)nibNameOrNil inBundle:(NSBundle*)bundle owner:(id)owner options:(NSDictionary*)options;

@end
