
@class PKFlow;
@class PKSection;
@class PKSlide;
@class PKSlideModal;
@class PKPackage;
@class PKHealthCareProvider;

extern NSString* const kPresentationDeploymentStatusTraining;
extern NSString* const kPresentationDeploymentStatusReview;
extern NSString* const kPresentationDeploymentStatusDraft;
extern NSString* const kPresentationDeploymentStatusProduction;
extern NSString* const kPresentationDeploymentStatusAssessment;

extern NSString* const kPresentationDefaultFlowName;

@interface PKPresentation : NSManagedObject

+ (PKPresentation*) presentationWithName:(NSString*)name;
+ (NSPredicate*) excludeHelpPresentationsPredicate;
+ (NSPredicate*) excludeExpiredPresentationsPredicate;
+ (BOOL) isValidDeploymentStatus:(NSString*)deploymentStatus;
+ (BOOL) isValidAssessmentType:(NSString*)assessmentType;

@property (nonatomic, strong) NSDate* expirationDate;
@property (nonatomic, strong) NSString* title;
@property (nonatomic, strong) NSString* deploymentStatus;
@property (nonatomic, strong) NSString* assessmentType;
@property (nonatomic, strong) NSString* language;
@property (nonatomic, strong) NSString* region;
@property (nonatomic, strong) NSString* contentKey;
@property (nonatomic, strong) NSString* summary;
@property (nonatomic, strong) NSString* pathToRoot;
@property (nonatomic, strong) NSOrderedSet* sections;
@property (nonatomic, strong) NSOrderedSet* flows;
@property (nonatomic, strong) NSOrderedSet* supplementalMediaItems;
@property (nonatomic, strong) NSOrderedSet* calls;
@property (nonatomic, strong) NSOrderedSet* slideModals;
@property (nonatomic, strong) NSSet* brands;
@property (nonatomic) NSInteger viewerIndex;
@property (nonatomic, strong) NSSet* rules;

@property (nonatomic, readonly) NSString* coverFile;
@property (nonatomic, readonly) NSString* configFile;
@property (nonatomic, readonly) NSArray* alternateConfigFiles;

@property (nonatomic, readonly) NSDictionary* menuDescriptor;
@property (nonatomic, readonly) NSBundle* menuBundle;

@property (nonatomic, readonly) NSUInteger supportedOrientations;

@property (nonatomic, strong) PKPackage* package;
@property (nonatomic, readonly) PKFlow* defaultFlow;
@property (nonatomic, readonly) UIImage* thumbnailImage;
@property (nonatomic) BOOL screenLockEnabled;
@property (nonatomic) BOOL drawingEnabled;
@property (nonatomic) BOOL exitOnDoubleTap;
@property (nonatomic) BOOL isCrossBrand;
@property (nonatomic) BOOL validTypeForDisplay;

@property (nonatomic, strong, readonly) NSString* displayedBrandTitle;

- (NSString*) pathToConfigurationFileDirectory;
- (NSString*) pathToHtmlDirectory;
- (NSString*) pathToConfigurationFile;
- (NSArray*) configurationFiles;

- (PKSection*) sectionWithName:(NSString*)name;
- (PKSlide*) slideWithIdentifier:(NSString*)identifier;
- (PKSlideModal*) slideModalWithIdentifier:(NSString*)identifier;
- (NSArray*) slides;
- (PKFlow*) flowWithName:(NSString*)name;

- (void) setPersistenValue:(NSString*)value forKey:(NSString*)key;
- (NSString*) persistentValueForKey:(NSString*)key;
- (NSArray*) fonts;
- (BOOL) isValidForHCP:(PKHealthCareProvider*)hcp;


+ (NSArray*) allIDs;

@end

@interface PKPresentation (PrimitiveAccessors)

- (NSString*)primitivePathToRoot;
- (void)setPrimitivePathToRoot:(NSString*)newPathToRoot;

@end

@interface PKPresentation (CoreDataGeneratedAccessors)

- (void)insertObject:(PKFlow *)value inFlowsAtIndex:(NSUInteger)idx;
- (void)removeObjectFromFlowsAtIndex:(NSUInteger)idx;
- (void)insertFlows:(NSArray *)value atIndexes:(NSIndexSet *)indexes;
- (void)removeFlowsAtIndexes:(NSIndexSet *)indexes;
- (void)replaceObjectInFlowsAtIndex:(NSUInteger)idx withObject:(PKFlow *)value;
- (void)replaceFlowsAtIndexes:(NSIndexSet *)indexes withSlides:(NSArray *)values;
- (void)addFlowsObject:(PKFlow *)value;
- (void)removeFlowsObject:(PKFlow *)value;
- (void)addFlows:(NSOrderedSet *)values;
- (void)removeFlows:(NSOrderedSet *)values;

- (void) addSectionsObject:(PKSection*)value;
- (BOOL) isBuiltIn;

@end

@interface NSManagedObjectContext (PKPresentation)

- (NSManagedObjectObservable*) presentationObservable;
- (NSArray*) findPresentationsWithBrand:(PKBrand*)brand;
- (PKPresentation*) presentationWithPredicate:(NSPredicate*)predicate;
- (NSArray*) presentationsWithPredicate:(NSPredicate*)predicate andSortDescriptors:(NSArray*)sortDescriptors;
- (NSUInteger) numberOfPresentationsWithPredicate:(NSPredicate*)predicate error:(NSError**)error;

@end
