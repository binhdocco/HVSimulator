@class PKPresentation;

typedef enum {
    modalTypePdf,
    modalTypePopup,
    modalTypeVideo,
} ModalType;

@interface PKSlideModal : NSManagedObject

@property (strong, nonatomic) NSString* title;
@property (strong, nonatomic) NSString* path;
@property (strong, nonatomic) NSString* sectionTitle;
@property (strong, nonatomic) PKPresentation* presentation;
@property (nonatomic) ModalType modalType;
@property (strong, nonatomic) NSURL* previewImageLocation;
@property (strong, nonatomic) NSURL* thumbnailImageLocation;
@property (strong, nonatomic) NSString* assetID;
@property (strong, nonatomic) NSSet* dependentAssets;
@property (strong, nonatomic) NSString* status;
@property (strong, nonatomic) NSString* message;
@property (strong, nonatomic) NSString* menuVisibility;

@property (nonatomic, retain) NSSet *brands;

@property (strong, nonatomic) UIImage* previewImage;
@property (strong, nonatomic) UIImage* thumbnailImage;
@property (nonatomic, strong, readonly) NSString* displayedBrandTitle;

+ (void) createThumbnailImageForSlideModal:(PKSlideModal*)slideModal;

@end

@interface PKSlideModal (CoreDataGeneratedAccessors)

- (void) addBrandsObject:(PKBrand*)value;
- (void) removeBrandsObject:(PKBrand*)value;
- (void) addBrands:(NSSet*)values;
- (void) removeBrands:(NSSet*)values;

@end
