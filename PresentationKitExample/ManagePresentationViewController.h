//
//  ManagePresentationViewController.h
//  PresentationKitExample
//
//  Created by drcom_developer on 6/18/13.
//  Copyright (c) 2013 Jason Allum. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FilterTableViewController.h"

@interface ManagePresentationViewController : UIViewController <UITableViewDelegate, FilterTableViewDelegate> {
    NSMutableArray *prezList;
    NSMutableArray *allList;
    NSString *serverURL;
    NSString *filterURL;
    NSString *filterString;
    IBOutlet UITableView *pTable;
    
    UIPopoverController *popover;
	FilterTableViewController *filterController;
    
    IBOutlet UIBarButtonItem *branchTitle;
}

@property(nonatomic, retain) NSMutableArray *prezList;
@property(nonatomic, retain) IBOutlet UITableView *pTable;
@property(nonatomic, retain) IBOutlet UIBarButtonItem *branchTitle;
//@property(nonatomic, retain) UIResponder *app;
- (IBAction) onInstallMoreClick:(id)sender;
- (IBAction) onRemoveAllClick:(id)sender;
- (IBAction) onFilterClick:(id)sender;
- (IBAction) onVersionClick:(id)sender;
@end
