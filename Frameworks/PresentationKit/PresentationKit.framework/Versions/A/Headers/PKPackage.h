
@class PKBrand;
@class PKPresentation;
@class PKSupplementalMedia;

extern NSString* const kPackageAssetTypePresentation;
extern NSString* const kPackageAssetTypeHelp;
extern NSString* const kPackageAssetTypeBriefcase;
extern NSString* const kPackageAssetTypeContent;

@interface PKPackage : NSManagedObject

@property (nonatomic, retain) NSString* assetType;
@property (nonatomic, retain) NSString* idFromCMS;
@property (nonatomic, retain) NSString* language;
@property (nonatomic, retain) NSString* name;
@property (nonatomic, retain) NSString* title;
@property (nonatomic, retain) NSDate* expirationDate;
@property (nonatomic, retain) NSString* deploymentStatus;
@property (nonatomic, retain) NSString* installedVersion;
@property (nonatomic, assign) double sizeIncludingDependencies;

@property (nonatomic, retain) NSDate* creationDate;
@property (nonatomic, retain) NSDate* updateDate;

@property (nonatomic, retain) NSSet* brands;
@property (nonatomic, retain) PKSupplementalMedia* supplementalMedia;
@property (nonatomic, strong, readonly) PKPresentation* presentation;

@property (nonatomic, strong, readonly) NSString* pathToRoot;

+ (BOOL) loadPackagesAtPath:(NSString*)pathToPackages error:(NSError**)error;
+ (NSString*) pathToContentFolder;

@end

@interface PKPackage (CoreDataGeneratedAccessors)

- (void) addBrandsObject:(PKBrand*)value;
- (void) removeBrandsObject:(PKBrand*)value;
- (void) addBrands:(NSSet*)values;
- (void) removeBrands:(NSSet*)values;

@end

@interface PKPackage (PrimitiveAccessors)

- (NSString*)primitivePathToRoot;
- (void)setPrimitivePathToRoot:(NSString*)newPathToRoot;

@end

@interface NSManagedObjectContext (Package)

- (PKPackage*) findPackageWithIdentifier:(NSString*)identifier error:(NSError**)error;
- (PKPackage*) findPackageWithName:(NSString*)name;
- (PKPackage*) findPackageWithIdFromCMS:(NSInteger)idFromCMS;
- (PKPackage*) findPackageWithIdFromCMS:(NSInteger)idFromCMS orInsert:(void(^)(PKPackage* content))didInsert;
- (PKPackage*) findPackageWithName:(NSString*)name orInsert:(void(^)(PKPackage* content))didInsert;

@end
