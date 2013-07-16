//
//  FilterTableViewController.h
//  PresentationKitExample
//
//  Created by drcom_developer on 7/10/13.
//  Copyright (c) 2013 Jason Allum. All rights reserved.
//

#import <UIKit/UIKit.h>
@class FilterTableViewController;

@protocol FilterTableViewDelegate
// Sent when the user selects a row in the recent searches list.
@optional
- (void)filterDidSeclecteRow:(FilterTableViewController *)controller didSelectString:(NSString *)rowSelected;
@end

@interface FilterTableViewController : UITableViewController <UIActionSheetDelegate>{
    id <FilterTableViewDelegate> delegate;
    
	NSArray *displayedRecentSearches;
}

@property (nonatomic, retain) id <FilterTableViewDelegate> delegate;
@property (nonatomic, retain) NSArray *displayedRecentSearches;

- (id) initWithTitleAndWidthHeight: (NSString *) title andWidth: (CGFloat) width andHeight: (CGFloat) height;
- (void) addList:(NSMutableArray *)data;

@end
