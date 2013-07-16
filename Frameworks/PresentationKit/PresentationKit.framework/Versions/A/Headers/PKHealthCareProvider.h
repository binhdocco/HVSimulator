#import <PresentationKit/PKBriefcaseRecipient.h>

@class PKBrand;
@class PKPerson;

@interface PKHealthCareProvider : PKBriefcaseRecipient

@property (nonatomic, retain) NSString* accountId;
@property (nonatomic, retain) NSString* address1;
@property (nonatomic, retain) NSString* address2;
@property (nonatomic, retain) NSString* city;
@property (nonatomic, retain) NSString* date;
@property (nonatomic, retain) NSString* hcpId;
@property (nonatomic, retain) NSString* phone1;
@property (nonatomic, retain) NSString* phone2;
@property (nonatomic, retain) NSString* prefix;
@property (nonatomic, retain) NSString* region;
@property (nonatomic, assign) BOOL specialist;
@property (nonatomic, retain) NSString* speciality;
@property (nonatomic, retain) NSString* state;
@property (nonatomic, retain) NSString* suffix;
@property (nonatomic, retain) NSString* website;
@property (nonatomic, retain) NSString* zip;
@property (nonatomic, retain) NSSet* brands;
@property (nonatomic, retain) NSMutableDictionary* parameters;
@property (nonatomic, assign) NSOrderedSet* ratings;
@property (nonatomic, retain) NSSet *subordinates;
@property (nonatomic, strong) NSSet* possibleCalls;

+ (PKHealthCareProvider*) findHealthCareProviderWithHcpId:(NSString*)hcpId orInsert:(void(^)(PKHealthCareProvider* hcp))didInsert;
+ (PKHealthCareProvider*) findHealthCareProviderWithAccountId:(NSString*)accountId orInsert:(void(^)(PKHealthCareProvider* hcp))didInsert;
- (void) removeRatingsObject:(PKEventRating*)value;

- (void) setPersistentIdData:(NSDictionary*)idDataDictionary;
- (NSString*) persistentIdDataValueForKey:(NSString*)key;

@end

@interface PKHealthCareProvider (CoreDataGeneratedAccessors)

- (void) addBrandsObject:(PKBrand*)value;
- (void) removeBrandsObject:(PKBrand*)value;
- (void) addBrands:(NSSet*)values;
- (void) removeBrands:(NSSet*)values;

- (NSSet*) events;
- (void) addSubordinatesObject:(PKPerson*)value;
- (void) removeSubordinatesObject:(PKPerson*)value;
- (void) addSubordinates:(NSSet*)values;
- (void) removeSubordinates:(NSSet*)values;

- (NSString*)sectionInitial;

@end


@interface NSManagedObjectContext (HealthCareProvider)

- (PKHealthCareProvider*) findHealthCareProviderWithHcpId:(NSString*)hcpId;
- (PKHealthCareProvider*) findHealthCareProviderWithHcpId:(NSString*)hcpId orInsert:(void(^)(PKHealthCareProvider* hcp))didInsert;
- (PKHealthCareProvider*) findHealthCareProviderWithAccountId:(NSString*)accountId;
- (PKHealthCareProvider*) findHealthCareProviderWithAccountId:(NSString*)accountId orInsert:(void(^)(PKHealthCareProvider* hcp))didInsert;
- (NSManagedObjectObservable*) healthCareProviderObservable;

@end
