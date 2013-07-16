//
//  InstallBundleViewController.m
//  PresentationKitExample
//
//  Created by drcom_developer on 6/19/13.
//  Copyright (c) 2013 Jason Allum. All rights reserved.
//

#import "InstallBundleViewController.h"
#import "ZipArchive.h"

@interface InstallBundleViewController ()

@end

@implementation InstallBundleViewController
@synthesize bundleFiles,pTable,filterString, serverURL, branchTitle;

- (IBAction) onDoneClick :(id)sender {
    [self dismissModalViewControllerAnimated:true];
}

- (void) getBundleFiles: (NSString*) urlString {
    //NSString* urlString = @"http://yourserve.com/hello.php";
    NSURL *theURL = [NSURL URLWithString:urlString];
    NSArray *a = [NSArray arrayWithContentsOfURL:theURL];
    NSMutableArray *mutA = [NSMutableArray arrayWithArray:a];
    [self searchTableView:mutA];
    //bundleFiles
    //NSLog(@"bundleFiles: %@", bundleFiles);
    
}

- (void) searchTableView: (NSMutableArray *)allList {
    
    if ([filterString isEqualToString:@"ALL"]) {
        bundleFiles = [allList copy ];
    } else {
        NSMutableArray *searchResults = [[NSMutableArray alloc] init];
        
        for (NSString *objectName in allList) {
            
            NSRange resultsRange = [objectName rangeOfString:filterString options:NSCaseInsensitiveSearch];
            
            if (resultsRange.length > 0)
                [searchResults addObject:objectName];
        }
        bundleFiles = [searchResults copy ];
        searchResults = nil;
    }
    

}

- (void) addFilter: (NSString*) f {
    [self setFilterString:f];
    
}

-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [bundleFiles count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
   
    static NSString *cellIdentifier = @"BundleCell";
    
    UITableViewCell *cell = nil;//[tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    if (cell == nil) {
        
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIdentifier] ;
    }
    
    cell.textLabel.text = [bundleFiles objectAtIndex:indexPath.row];
        
    UIButton *playButton = [UIButton buttonWithType:UIButtonTypeContactAdd];
    playButton.frame = CGRectMake(950.0f, 9.0f, 30.0f, 30.0f);
    playButton.tag=indexPath.row;
    //[addFriendButton setBackgroundColor: [UIColor blueColor]];
    //[playButton setTitle:@"Add" forState:UIControlStateNormal];
    [cell addSubview:playButton];
    [playButton addTarget:self
                   action:@selector(playPrez:)
         forControlEvents:UIControlEventTouchUpInside];

    //add to prez list if it is not existed
    NSMutableArray* prezList = [[[NSUserDefaults standardUserDefaults] arrayForKey:@"PresentationsList"] mutableCopy];
    //NSLog(@"prezList: %@", prezList);
    //NSLog(@"afileName: %@", cell.textLabel.text);
    if ([prezList indexOfObject:[[cell.textLabel.text componentsSeparatedByString:@"."] objectAtIndex:0] ] == NSNotFound) {
        UIImageView *imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"icon_new_small.png"]];
        imageView.frame = CGRectMake(0.0f, 0.0f, 30.0f, 30.0f);
        cell.accessoryView = imageView;
        imageView = nil;

    }
    
    return cell;
}

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

- (IBAction)playPrez:(id)sender
{
    // NSLog(@"playPrez clicked.");
    selectedPrez = [bundleFiles objectAtIndex:[sender tag]];
    UIAlertView *wantDown = [[UIAlertView alloc] initWithTitle:@"Hi there!" message:@"Do you want to install the selected presentation ?" delegate:self cancelButtonTitle:@"NO" otherButtonTitles:@"YES", nil];
    [wantDown show];
    wantDown = nil;

}
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 1) {
        //NSLog(@"YES, Downloading %@...", selectedPrez);
        myAlertView = [[UIAlertView alloc] initWithTitle:@"DOWNLOADING..." message:selectedPrez delegate:nil cancelButtonTitle:nil otherButtonTitles:nil];
        [myAlertView show];
        UIActivityIndicatorView *progress= [[UIActivityIndicatorView alloc] initWithFrame: CGRectMake(125, 100, 30, 30)];
        progress.activityIndicatorViewStyle = UIActivityIndicatorViewStyleWhiteLarge;
        [progress startAnimating];
        [myAlertView addSubview:progress];
        progress = nil;
        
        [self startDownloadingURL:selectedPrez];
    } else {
        NSLog(@"NO");
    }
}
/*
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    //explorerView.urlField.text = [bookmarks objectAtIndex:indexPath.row];
    //[explorerView textFieldShouldReturn:explorerView.urlField];
    //[self dismissModalViewControllerAnimated:true];
    
    
}
*/


// DOWNLOAD
- (void) startDownloadingURL:(NSString *)fileUrl {
    NSString *downloadUrl = [serverURL stringByAppendingPathComponent:fileUrl];
    //downloadUrl = [serverURL stringByAppendingString:fileUrl];
    // Create the request.
    NSURLRequest *theRequest=[NSURLRequest requestWithURL:[NSURL URLWithString:downloadUrl]
                                              cachePolicy:NSURLRequestUseProtocolCachePolicy
                                          timeoutInterval:60.0];
    
    // create the connection with the request and start loading the data
    NSURLConnection *theConnection=[[NSURLConnection alloc] initWithRequest:theRequest delegate:self];
    if (theConnection) {
        // Create the NSMutableData to hold the received data.
        
        NSLog(@"STARTING DOWNLOADING: %@", downloadUrl);
    } else {
        NSLog(@"Inform the user that the connection failed.");
    }
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
    receivedData = [[NSMutableData alloc] init];
    dataSize = [response expectedContentLength];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    [receivedData appendData:data];
    
    if (dataSize != NSURLResponseUnknownLength) {
        float progress = ((float) [receivedData length] / (float) dataSize)*100;
        //NSLog(@"download: %f", progress);
        [myAlertView setTitle:[NSString stringWithFormat:@"DOWNLOADING %.0f%@", progress,@"%"]];
    }
    
}
- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
    [myAlertView dismissWithClickedButtonIndex:0 animated:YES];
    myAlertView = nil;
    
    UIAlertView* Alert = [[UIAlertView alloc] initWithTitle:@"Download Error !"
                                                    message:nil delegate:nil
                                          cancelButtonTitle:@"OK"
                                          otherButtonTitles:nil];
    [Alert show];
    Alert = nil;
    
}
- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
    //NSLog(@"Succeeded! Received %d bytes of data",[receivedData length]);
    [myAlertView setTitle:@"INSTALLING ..."];
    NSString * docPath =[self applicationDocumentsDirectory];
    docPath = [docPath stringByAppendingPathComponent:selectedPrez];
    //NSLog(@"SAVE TO: %@", docPath);
    [receivedData writeToFile:docPath atomically:YES];
    
    //unzip
    NSString *afileName = ( NSString *)[[selectedPrez componentsSeparatedByString:@"."] objectAtIndex:0];
    [myAlertView setMessage:afileName];
    [self unzipFile:docPath fileName:afileName];
    
    
    //add to prez list if it is not existed
    NSMutableArray* prezList = [[[NSUserDefaults standardUserDefaults] arrayForKey:@"PresentationsList"] mutableCopy];
    //NSLog(@"prezList: %@", prezList);
    //NSLog(@"afileName: %@", afileName);
    if ([prezList indexOfObject:afileName] == NSNotFound) {
        //NSLog(@"add: %@", afileName);
        [prezList addObject:afileName];
    
        [[NSUserDefaults standardUserDefaults] setObject:prezList forKey:@"PresentationsList"];
    }
    //NSLog(@"prezList: %@", prezList);
    prezList = nil;
    
    //waiting for 2 seconds
	[NSTimer scheduledTimerWithTimeInterval:1.5f
									 target: self
								   selector: @selector(doHide:)
								   userInfo: nil
									repeats:NO];
    
    
    
    
    
    // release the connection, and the data object
    connection = nil;
    receivedData = nil;
}

- (void) doHide: (NSTimer *) theTimer {
	[myAlertView dismissWithClickedButtonIndex:0 animated:YES];
    myAlertView = nil;
    
    UIAlertView* Alert = [[UIAlertView alloc] initWithTitle:@"Install Complete !"
                                                    message:nil delegate:nil
                                          cancelButtonTitle:@"OK"
                                          otherButtonTitles:nil];
    [Alert show];
    Alert = nil;
    
    [self onDoneClick:nil];
}

- (void) unzipFile: (NSString *) fileUrl fileName: (NSString *)afileName {
    //NSLog(@"Unzipping %@", fileUrl);
	NSString *docPath = [self applicationDocumentsDirectory];
	
   
	ZipArchive* za = [[ZipArchive alloc] init];
    
    if( [za UnzipOpenFile:fileUrl])
    {
        BOOL ret = [za UnzipFileTo:docPath overWrite:YES];
        //NSLog(@"ret: %d ", ret);
        if( NO==ret )
        {
            NSLog(@"fail to unzip");
        }
        
        [za UnzipCloseFile];
    }
    
    //delete zip file
    NSFileManager *filemgr;
    filemgr = [NSFileManager defaultManager];
    [filemgr removeItemAtPath:fileUrl error:NULL];
    
    za = nil;
    
	
}



///////////

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
    //bundleFiles = [[NSArray alloc] init];
    
    //serverURL = @"http://cadmos.int-prod.drcom.asia/DRCA/OTA_PAGE/HVSimulatorFiles";
    //serverURL = @"http://192.168.1.14:8080/HVSimulatorFiles";
    
    NSString *indexUrl = [serverURL stringByAppendingString:@"/index.php"];
    [self getBundleFiles:indexUrl];
    
    UIImageView *iView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"launch.jpg"]];
    [iView setAlpha:0.3f];
    //iView.frame = pTable.frame;
    pTable.backgroundView = iView;
    [branchTitle setTitle:[NSString stringWithFormat:@"Product: %@",filterString]];
    
}

- (void)viewDidAppear:(BOOL)animated {
    //get bundle files from server
   
    [super viewDidAppear:animated];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void) viewDidUnload {
    bundleFiles = nil;
    //webData = nil;
    [super viewDidUnload];
    
}

- (NSString*) applicationDocumentsDirectory
{
    NSURL *url = [[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask] lastObject];
    return url.relativePath;
}

@end
