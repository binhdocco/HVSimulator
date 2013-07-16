@class PKPackage;
@class PKPresentation;
@class PKBriefcase;

extern NSString* const kPKSupplementalMediaTypeDocument;
extern NSString* const kPKSupplementalMediaTypeHtml;
extern NSString* const kPKSupplementalMediaTypeVideo;

@interface PKSupplementalMedia : NSManagedObject

@property (nonatomic, retain) NSString* type;
@property (nonatomic, retain) NSString* contentFile;
@property (nonatomic, retain) NSString* thumbnailFile;
@property (nonatomic, retain) NSString* rootDirectory;
@property (nonatomic, retain) NSString* contentDescription;
@property (nonatomic, retain) NSString* title;
@property (nonatomic, retain) NSString* contentKey;
@property (nonatomic, retain) PKPackage* package;
@property (nonatomic, retain) NSSet* briefcases;
@property (nonatomic, retain) NSSet* presentations;

+(NSOrderedSet*)mediaItemsWithNoPackageInManagedContext:(NSManagedObjectContext*)context;

@end

@interface PKSupplementalMedia (CoreDataGeneratedAccessors)

- (void)addBriefcasesObject:(PKBriefcase *)value;
- (void)removeBriefcasesObject:(PKBriefcase *)value;
- (void)addBriefcases:(NSSet *)values;
- (void)removeBriefcases:(NSSet *)values;

@end