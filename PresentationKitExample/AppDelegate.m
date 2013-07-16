#import "AppDelegate.h"
#import <PresentationKit/PresentationKit+Private.h>
#import "ManagePresentationViewController.h"

/*
@interface AppDelegate () <
PKPresentationViewControllerDelegate
>

@end
*/
@implementation AppDelegate

- (BOOL) application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.viewController = [[ManagePresentationViewController alloc] initWithNibName:@"ManagePresentationViewController" bundle:nil];
    //[self.viewController setApp:self];
    //[self.window.rootViewController presentModalViewController:self.viewController animated:true];
    self.window.rootViewController = self.viewController;
    /*
    NSURL *docPath = [self applicationDocumentsDirectory];
    NSLog(@"docPath: %@", docPath.relativePath);
   
    NSError* error = nil;
    if (![PKPackage loadPackagesAtPath:docPath.relativePath error:&error]) {
        NSLog(@"%@", error);
    }
    
    PKPresentation* presentation = [PKPresentation presentationWithName:@"Example"];
    NSAssert(presentation != nil, @"Why is there no presentation named 'Example'?");
    
    PKPresentationViewController* controller = (PKPresentationViewController*)[[self window] rootViewController];
    [controller setFlow:[presentation defaultFlow]];
    [controller setDelegate:self];
     */
    [[self window] makeKeyAndVisible];
    return YES;
}
- (void) loadPresentation: (NSString *) bundleFilename {
    NSURL *docPath = [self applicationDocumentsDirectory];
    NSLog(@"docPath: %@", docPath.relativePath);
    
    NSError* error = nil;
    if (![PKPackage loadPackagesAtPath:docPath.relativePath error:&error]) {
        NSLog(@"%@", error);
    }
    
    PKPresentation* presentation = [PKPresentation presentationWithName: bundleFilename];
    NSAssert(presentation != nil, @"Why is there no presentation named '%@'?", bundleFilename);
    
    PKPresentationViewController* controller = (PKPresentationViewController*)[[self window] rootViewController];
    [controller setFlow:[presentation defaultFlow]];
    [controller setDelegate:self];
}

- (void) applicationDidEnterBackground:(UIApplication*)application
{
}

- (void) applicationDidBecomeActive:(UIApplication *)application
{
}

- (void) applicationWillTerminate:(UIApplication*)application
{
}

- (void) presentationViewControllerDidRequestExit:(PKPresentationViewController *)controller
{
    // Nothing
}

- (NSURL*) presentationViewController:(PKPresentationViewController*)slidePresenter willLoadContentFromURL:(NSURL*)url
{
    if ([[url scheme] isEqualToString:@"package"]) {
        return [NSURL fileURLWithPath:[PresentationKit pathToResourceForPackageURL:url]];
    } else {
        return url;
    }
}


#pragma mark - Paths

- (NSString*) contentPackPath
{
    return [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"Content"];
}

- (NSURL*) applicationDocumentsDirectory
{
    return [[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask] lastObject];
}

@end
