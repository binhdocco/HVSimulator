//
//  HVPlayerViewController.m
//  PresentationKitExample
//
//  Created by drcom_developer on 6/18/13.
//  Copyright (c) 2013 Jason Allum. All rights reserved.
//

#import "HVPlayerViewController.h"
#import <PresentationKit/PresentationKit+Private.h>

@interface HVPlayerViewController () <
PKPresentationViewControllerDelegate
>

@end

@implementation HVPlayerViewController
@synthesize bundleFile;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (NSURL*) presentationViewController:(PKPresentationViewController*)slidePresenter willLoadContentFromURL:(NSURL*)url
{
    if ([[url scheme] isEqualToString:@"package"]) {
        return [NSURL fileURLWithPath:[PresentationKit pathToResourceForPackageURL:url]];
    } else {
        return url;
    }
}


- (void) presentationViewControllerDidRequestExit:(PKPresentationViewController *)controller
{
    // Nothing
    [controller dismissModalViewControllerAnimated:false];
        [self dismissModalViewControllerAnimated:true];
    //canLoadPrez = true;

}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    //self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    canLoadPrez = true;
}

- (void) viewDidAppear:(BOOL)animated {
    if (canLoadPrez) {
        canLoadPrez = false;
    NSURL *docPath = [self applicationDocumentsDirectory];
    //NSLog(@"docPath: %@", docPath.relativePath);
    
    NSError* error = nil;
    if (![PKPackage loadPackagesAtPath:docPath.relativePath error:&error]) {
        NSLog(@"%@", error);
        UIAlertView* Alert = [[UIAlertView alloc] initWithTitle:@"Loading Error"
                                                        message:[NSString stringWithFormat:@"%@", error] delegate:nil
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil];
        [Alert show];
        Alert = nil;
        [self dismissModalViewControllerAnimated:true];
        return;
    }
    //NSLog(@"BUNDLE FILENAME: %@", bundleFile);
    //NSLog(@"PATH: %@", docPath.relativePath);
    
    PKPresentation* presentation = [PKPresentation presentationWithName: bundleFile];
    NSAssert(presentation != nil, @"Why is there no presentation named '%@'?", bundleFile);
    
    //NSLog(@"presentation defaultFlow: %@", [presentation defaultFlow]);
    
    //UIView *temp = [[UIView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
   
    
    PKPresentationViewController* controller = [[PKPresentationViewController alloc] initWithNibName:@"HVPlayerViewController" bundle:nil];
    //[controller setView: [[UIView alloc] initWithFrame:[[UIScreen mainScreen] bounds]]];
    [controller setFlow:[presentation defaultFlow]];
    [controller setDelegate:self];
    
    [self presentModalViewController:controller animated:true];
    controller = nil;
    }
    
}

- (NSURL*) applicationDocumentsDirectory
{
    return [[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask] lastObject];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
