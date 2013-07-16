@class PageScrubberView;
@class PDFPageZoomView;
@class ThumbPopover;
@class TOCpopup;

extern NSString* const kPDFViewControllerPageNotification;
extern NSString* const kPDFViewControllerBookmarkNotification;
extern NSString* const kPDFViewControllerCloseNotification;


@class PDFPageZoomView;


@interface PagingPDFViewController : UIViewController

@property (nonatomic, strong) NSMutableSet* recycledPages;
@property (nonatomic, strong) NSMutableSet* visiblePages;
@property (nonatomic, strong) NSString* trackingFileName;
@property (nonatomic, strong) NSString* trackingTitle;

- (id)initWithPDFFile:(NSURL*)file title:(NSString*)title;

- (void)tilePages;
- (void)tilePageRange:(NSUInteger)startIndex endIndex:(NSUInteger)endIndex;
- (void)configurePage:(PDFPageZoomView*)page forIndex:(NSUInteger)index;
- (PDFPageZoomView*)dequeueRecycledPage;

- (CGRect)frameForUIView;
- (CGRect)frameForPagingScrollView:(UIInterfaceOrientation)interfaceOrientation;
- (CGRect)frameForPageAtIndex:(NSUInteger)index;
- (BOOL)isDisplayingPageForIndex:(NSUInteger)index;
- (int)currentPage;
- (void)gotoPage:(NSInteger)index;

- (void)readPDF_TOC:(CGPDFDocumentRef)docRef;
- (void)readPDF_TOC_Items:(CGPDFDocumentRef)document outline:(CGPDFDictionaryRef)outline level:(int)level;
- (void)readPDF_TOC_Item:(int)level title:(CFStringRef)title isOpen:(bool)isOpen;
static NSInteger PageNumberFromPageDictionary(CGPDFDictionaryRef target);

- (void)updateInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation;

- (void)toggleToolbars;
- (void)hideToolbars;
- (void)showToolbars;

- (void)backAction;
- (void)tocAction;

@end
