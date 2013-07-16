
typedef enum {
    kEventTypePDF,
    kEventTypePDFPage,
    kEventTypePDFBookmark,
    kEventTypeSlide,
    kEventTypeVideo,
    kEventTypeVideoPlay,
    kEventTypeVideoPause,
    kEventTypeVideoStop,
    kEventTypeVideoSeek,
    kEventTypePopup,
    kEventTypeBriefcase,
    kEventTypeMap,
    kEventTypeHTML,
    kEventTypePausePresentation,
    kEventTypeDraw,
    kEventTypeScreenLock,
    kEventTypeSurvey,
    kEventTypeOrientationChange,
	kEventTypeCustom,
	kEventTypeSampleSignature,
} EventType;

@class PKCall;
@class PKHealthCareProvider;
@class PKSlide;
@class NSManagedObjectObservable;
@class PKPerson;

@interface PKEvent : NSManagedObject

@property (nonatomic) EventType type;

@property (strong, nonatomic) NSString* notes;
@property (strong, nonatomic) NSString* title;
@property (strong, nonatomic) NSString* contentKey;
@property (strong, nonatomic) NSString* data;
@property (strong, nonatomic) NSString* parentID;

@property (strong, nonatomic) NSDate* startTime;
@property (strong, nonatomic) NSDate* endTime;
@property (assign, nonatomic, readonly) BOOL flag;
@property (nonatomic, strong) NSOrderedSet* ratings;
@property (nonatomic, retain) NSOrderedSet* audience;

@property (strong, nonatomic) PKCall* call;
@property (strong, nonatomic) PKSlide* slide;
@property (nonatomic) BOOL validForPostCall;

@property (nonatomic, retain) NSSet *brands;

@property (readonly, nonatomic) UIImage* thumbnailImage;
@property (strong, nonatomic, readonly) NSString* eventTypeDisplayTitle;

- (NSArray*) healthCareProviders;
- (void) removeHealthCareProvider:(PKHealthCareProvider*)healthCareProvider;
- (void) addHealthCareProviders:(NSOrderedSet*)hcpToAdd;

- (BOOL) setFlagged:(BOOL)flagged;

@end

@interface PKEvent (CoreDataGeneratedAccessors)

- (void)insertObject:(PKPerson *)value inAudienceAtIndex:(NSUInteger)idx;
- (void)removeObjectFromAudienceAtIndex:(NSUInteger)idx;
- (void)insertAudience:(NSArray *)value atIndexes:(NSIndexSet *)indexes;
- (void)removeAudienceAtIndexes:(NSIndexSet *)indexes;
- (void)replaceObjectInAudienceAtIndex:(NSUInteger)idx withObject:(PKPerson *)value;
- (void)replaceAudienceAtIndexes:(NSIndexSet *)indexes withAudience:(NSArray *)values;
- (void)addAudienceObject:(PKPerson *)value;
- (void)removeAudienceObject:(PKPerson *)value;
- (void)addAudience:(NSOrderedSet *)values;
- (void)removeAudience:(NSOrderedSet *)values;

- (void) addBrandsObject:(PKBrand*)value;
- (void) removeBrandsObject:(PKBrand*)value;
- (void) addBrands:(NSSet*)values;
- (void) removeBrands:(NSSet*)values;

@end

@interface NSManagedObjectContext (PKEvent)

- (NSUInteger)numberOfEventsWithPredicate:(NSPredicate*)predicate;

@end
