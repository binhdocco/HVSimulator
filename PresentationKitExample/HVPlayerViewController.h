//
//  HVPlayerViewController.h
//  PresentationKitExample
//
//  Created by drcom_developer on 6/18/13.
//  Copyright (c) 2013 Jason Allum. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <PresentationKit/PresentationKit+Private.h>
#

@interface HVPlayerViewController : UIViewController  {
    NSString *bundleFile;
    UIWindow *window;
    Boolean canLoadPrez;
}

@property(nonatomic, retain) NSString *bundleFile;
@end
