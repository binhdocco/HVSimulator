//
//  InstallBundleViewController.h
//  PresentationKitExample
//
//  Created by drcom_developer on 6/19/13.
//  Copyright (c) 2013 Jason Allum. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface InstallBundleViewController : UIViewController <UITableViewDelegate>{
    
   
    NSMutableArray *bundleFiles;
    NSString *serverURL;
    NSString *selectedPrez;
    NSMutableData *receivedData;
    UIAlertView *myAlertView;
    NSString *filterString;
    
    long long dataSize;
     IBOutlet UITableView *pTable;
    IBOutlet UIBarButtonItem *branchTitle;

}


@property(nonatomic, retain) NSMutableArray *bundleFiles;
@property(nonatomic, retain) IBOutlet UITableView *pTable;
@property(nonatomic, retain) NSString *filterString;
@property(nonatomic, retain) NSString *serverURL;
@property(nonatomic, retain) IBOutlet UIBarButtonItem *branchTitle;


- (IBAction) onDoneClick :(id)sender;
- (void) addFilter: (NSString*) f;
@end
