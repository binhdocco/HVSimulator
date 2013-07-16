//
//  ManagePresentationViewController.m
//  PresentationKitExample
//
//  Created by drcom_developer on 6/18/13.
//  Copyright (c) 2013 Jason Allum. All rights reserved.
//

#import "ManagePresentationViewController.h"
#import "HVPlayerViewController.h"
#import "InstallBundleViewController.h"
#import "FilterTableViewController.h"

@interface ManagePresentationViewController ()

@end

@implementation ManagePresentationViewController
@synthesize prezList, pTable, branchTitle;

- (IBAction) onVersionClick:(id)sender {
    NSString *msg = @"*** 0.1.3 *** \nFixed issue with thumbnail creation.\n*** 0.1.2 ***\nAdded Filter option.\n*** 0.1.1 ***\n Fixed PI button to open slide with name 'Prescribing Infomation'\n**** 0.1.0 ***\n Initial release";
    UIAlertView *wantDown = [[UIAlertView alloc] initWithTitle:@"Revision History" message:msg delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    [wantDown show];
    wantDown = nil;
}

- (IBAction) onFilterClick:(id)sender {
    
    if (popover) {
        NSURL *theURL = [NSURL URLWithString:[filterURL stringByAppendingPathComponent:@"filter.php"]];
        NSArray *a = [NSArray arrayWithContentsOfURL:theURL];
        //bundleFiles = [NSMutableArray arrayWithArray:a];
        [filterController addList:[NSMutableArray arrayWithArray:a]];
        
        [popover presentPopoverFromBarButtonItem:sender permittedArrowDirections:UIPopoverArrowDirectionAny animated:YES];
    }
}

- (void)filterDidSeclecteRow:(FilterTableViewController *)controller didSelectString:(NSString *)rowSelected {
     [popover dismissPopoverAnimated:YES];
    //NSLog(@"Selected branch: %@", rowSelected);
    [self searchTableView:rowSelected];
}

- (void) searchTableView: (NSString *)searchText {
    filterString = searchText;
    [branchTitle setTitle:[NSString stringWithFormat:@"Product: %@",searchText]];
    
    if ([searchText isEqualToString:@"ALL"]) {
        prezList = [allList copy ];
    } else {
        NSMutableArray *searchResults = [[NSMutableArray alloc] init];
        
        for (NSString *objectName in allList) {
            
            NSRange resultsRange = [objectName rangeOfString:searchText options:NSCaseInsensitiveSearch];
            
            if (resultsRange.length > 0)
                [searchResults addObject:objectName];
        }
        prezList = [searchResults copy ];
        searchResults = nil;
    }
    
    //NSLog(@"FILTER: %@", prezList);
    if (pTable)
        [pTable reloadData];

}
    
- (IBAction) onRemoveAllClick:(id)sender {
    [popover dismissPopoverAnimated:NO];
    UIAlertView *wantDown = [[UIAlertView alloc] initWithTitle:@"DELETE ALL" message:@"Are you sure ???" delegate:self cancelButtonTitle:@"NO" otherButtonTitles:@"YES", nil];
    [wantDown show];
    wantDown = nil;
    
}
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 1) {
        for (NSString *filaname in prezList) {
            [self deleteFile:filaname];
        }
        [allList removeAllObjects];
        allList = [[NSMutableArray alloc] init];
        prezList = [allList copy];
        [[NSUserDefaults standardUserDefaults] setObject:prezList forKey:@"PresentationsList"];
        [NSUserDefaults resetStandardUserDefaults] ;
        [pTable reloadData];
    } else {
        NSLog(@"NO");
    }

}

- (void) deleteFile: (NSString *)filename {
    filename = [filename stringByAppendingString:@".bundle"];
    NSString *fileUrl = [self applicationDocumentsDirectory];
    fileUrl = [fileUrl stringByAppendingPathComponent:filename];
    //delete zip file
    NSFileManager *filemgr;
    filemgr = [NSFileManager defaultManager];
    [filemgr removeItemAtPath:fileUrl error:NULL];
}

- (IBAction) onInstallMoreClick:(id)sender {
    [popover dismissPopoverAnimated:NO];
    InstallBundleViewController *instal = [[InstallBundleViewController alloc] initWithNibName:@"InstallBundleViewController" bundle:nil];
    [instal setServerURL:filterURL];
    [instal addFilter:filterString];
    [self presentModalViewController:instal animated:true];
    
    instal = nil;
}

-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [prezList count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *cellIdentifier = @"Cell";
    
    UITableViewCell *cell = nil;//[tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    if (cell == nil) {
        
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIdentifier] ;
    }
    
    NSString *pName = (NSString *)[prezList objectAtIndex:indexPath.row];
    cell.textLabel.text = pName;
  
    //add Play button if it is _P_
   
    if (!([pName rangeOfString:@"_P_"].location == NSNotFound)) {
        NSString *imageURL = [serverURL stringByAppendingString:@"/"];
        imageURL = [imageURL stringByAppendingString:cell.textLabel.text];
        imageURL = [imageURL stringByAppendingString:@".bundle/Presentation/cover/Preview.png"];
        UIImage *image = [UIImage imageWithContentsOfFile:imageURL];
        cell.imageView.image = image;
        
        UIButton *playButton = [UIButton buttonWithType:UIButtonTypeDetailDisclosure];
        playButton.frame = CGRectMake(900.0f, 75.0f, 75.0f, 30.0f);
        playButton.tag=indexPath.row;
        //[addFriendButton setBackgroundColor: [UIColor blueColor]];
        //[playButton setTitle:@"Play" forState:UIControlStateNormal];
        [cell addSubview:playButton];
        [playButton addTarget:self
                        action:@selector(playPrez:)
              forControlEvents:UIControlEventTouchUpInside];
    } else {
        UIImage *image = [UIImage imageNamed:@"data.png"];
        cell.imageView.image = image;
    }
    return cell;
}

- (IBAction)playPrez:(id)sender
{
   // NSLog(@"playPrez clicked.");
    NSString *prezName = [prezList objectAtIndex:[sender tag]];
    if (!([prezName rangeOfString:@"_P_"].location == NSNotFound)) {
        //check dependencies
        NSString* plistPath = [self applicationDocumentsDirectory];
        plistPath = [plistPath stringByAppendingPathComponent:prezName];
        plistPath = [plistPath stringByAppendingString:@".bundle"];
        plistPath = [plistPath stringByAppendingPathComponent:@"/Info.plist"];
        NSDictionary *contentDic = [NSDictionary dictionaryWithContentsOfFile:plistPath];
        //NSLog(@"plistPath: %@", plistPath);
        //NSLog(@"INFO PLIST: %@", contentDic);
        
        NSDictionary *packageDes = [contentDic objectForKey:@"Package Description"];
        NSArray *dependencies = (NSArray *)[packageDes objectForKey:@"Dependencies"];
        //NSLog(@"dependencies length: %d", [dependencies count]);
        BOOL isOK = true;
        if ([dependencies count] > 0) {
            NSMutableArray *missPackage = [[NSMutableArray alloc] init];
            for (NSString *pName in dependencies) {
                if ([prezList indexOfObject:pName] == NSNotFound) {
                    [missPackage addObject:pName];
                }
            }
            if ([missPackage count] > 0) {
                // ALERT MISSING
                UIAlertView *wantDown = [[UIAlertView alloc] initWithTitle:@"Ooooops !" message:[NSString stringWithFormat:@"This prensentation need dependency packages: %@.\nPlease install them too.", missPackage] delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
                [wantDown show];
                wantDown = nil;
                isOK = false;
                
            } 
            missPackage = nil;
        }
         //
        if (isOK) {
            //OK TO PLAY
            HVPlayerViewController *hvPlayer = [[HVPlayerViewController alloc] init];
            [hvPlayer setBundleFile: prezName];
            [self presentModalViewController:hvPlayer animated:true];
            hvPlayer = nil;
        }
        /*
        
         */
    } else {
        UIAlertView *wantDown = [[UIAlertView alloc] initWithTitle:@"Ooooops !" message:@"This is not a presentation." delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
        [wantDown show];
        wantDown = nil;
    }
}

/*
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    //explorerView.urlField.text = [bookmarks objectAtIndex:indexPath.row];
    //[explorerView textFieldShouldReturn:explorerView.urlField];
    //[self dismissModalViewControllerAnimated:true];
   
    
   
}
*/
- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.row%2) {
        cell.backgroundColor = [UIColor lightGrayColor];
        cell.textLabel.textColor = [UIColor blackColor];
    } else {
        cell.backgroundColor = [UIColor grayColor];
        cell.textLabel.textColor = [UIColor whiteColor];
    }
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
}

-(void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        NSString *bundleFile = (NSString *)[prezList objectAtIndex:indexPath.row];
        [self deleteFile:bundleFile];
        //[tableView deleteRowsAtIndexPaths:[NSArray arrayWithObjects:indexPath, nil] withRowAnimation:UITableViewRowAnimationFade];
        
        [allList removeObject:bundleFile];
        
        [[NSUserDefaults standardUserDefaults] setObject:allList forKey:@"PresentationsList"];
        
        [self searchTableView:filterString];
    }
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
    prezList = [[[NSUserDefaults standardUserDefaults] arrayForKey:@"PresentationsList"] mutableCopy];
    if (!prezList) {
        prezList = [[NSMutableArray alloc] init];
        [[NSUserDefaults standardUserDefaults] setObject:prezList forKey:@"PresentationsList"];
    }
    
    serverURL = [self applicationDocumentsDirectory];
    
    UIImageView *iView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"launch.jpg"]];
    [iView setAlpha:0.7f];
    pTable.backgroundView = iView;

    //UIEdgeInsets inset = UIEdgeInsetsMake(5, 5, 0,0);
    //pTable.contentInset = inset;
    //serverURL = [serverURL stringByAppendingString:@"/"];
    //[prezList addObject:@"SG_ENG_VIMOVO_P_Presentation"];
    //[prezList addObject:@"MASTER_ENG_SYMBICORT_P_Presentation"];
    //[[NSUserDefaults standardUserDefaults] setObject:prezList forKey:@"PresentationsList"];
    
    filterController = [[FilterTableViewController alloc] initWithTitleAndWidthHeight:@"Products" andWidth: 400 andHeight:300];
	filterController.delegate = self;
	
	UINavigationController *navigationController = [[UINavigationController alloc] initWithRootViewController:filterController];
    popover = [[UIPopoverController alloc] initWithContentViewController:navigationController];
    //popover.delegate = self;
	navigationController = nil;
    
    //filterURL = @"http://cadmos.int-prod.drcom.asia/DRCA/OTA_PAGE/HVSimulatorFiles";
    filterURL = @"http://192.168.1.14:8080/HVSimulatorFiles";
    filterString = @"ALL";
    
}

- (void) viewDidAppear:(BOOL)animated {
    allList = [[[NSUserDefaults standardUserDefaults] arrayForKey:@"PresentationsList"] mutableCopy];
    
    [self searchTableView:filterString ];
    
}



- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewDidUnload {
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
    //[prezList release];
    prezList = nil;
    
}

- (NSString*) applicationDocumentsDirectory
{
    NSURL *url = [[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask] lastObject];
    return url.relativePath;
}

@end
