//
//  FilterTableViewController.m
//  PresentationKitExample
//
//  Created by drcom_developer on 7/10/13.
//  Copyright (c) 2013 Jason Allum. All rights reserved.
//

#import "FilterTableViewController.h"

@interface FilterTableViewController ()

@end

@implementation FilterTableViewController

@synthesize delegate, displayedRecentSearches;

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (id) initWithTitleAndWidthHeight: (NSString *) title andWidth: (CGFloat) width andHeight: (CGFloat) height {
	self = [super initWithStyle: UITableViewStylePlain];
	if (self) {
		self.title = title;
		self.contentSizeForViewInPopover = CGSizeMake(width, height);
	}
	return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
 
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (void) addList:(NSMutableArray *)data {
	
    self.displayedRecentSearches = data;
	// NSLog(@"[addToRecentSearches]len = %d", [self.displayedRecentSearches count]);
    [self.tableView reloadData];
	
    /*
	NSIndexPath *indexPath =[NSIndexPath indexPathForRow:0 inSection:0];
    [self.tableView selectRowAtIndexPath:indexPath animated:NO                          scrollPosition:UITableViewScrollPositionNone];
	UITableViewCell *thisCell = [self.tableView cellForRowAtIndexPath:indexPath];
	thisCell.textLabel.textColor = [UIColor blueColor];
	thisCell.accessoryType = UITableViewCellAccessoryCheckmark;*/
    
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
#warning Potentially incomplete method implementation.
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
#warning Incomplete method implementation.
    // Return the number of rows in the section.
    return displayedRecentSearches.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellAccessoryDisclosureIndicator reuseIdentifier:CellIdentifier];
		cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    }
    
    cell.textLabel.text = [self.displayedRecentSearches objectAtIndex:indexPath.row];

    return cell;
}


// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return NO;
}


/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
{
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    int i = 0;
	for (i = 0 ; i< [displayedRecentSearches count]; i++) {
		
		NSIndexPath *iP =[NSIndexPath indexPathForRow:i inSection:0];
		UITableViewCell *cell = [self.tableView cellForRowAtIndexPath:iP];
		cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
		cell.textLabel.textColor = [UIColor blackColor];
		
	}
	UITableViewCell *thisCell = [tableView cellForRowAtIndexPath:indexPath];
	thisCell.accessoryType = UITableViewCellAccessoryCheckmark;
	thisCell.textLabel.textColor = [UIColor blueColor];
	
	[delegate filterDidSeclecteRow: self didSelectString:[displayedRecentSearches objectAtIndex: indexPath.row]];
	
}

@end
