#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
#import <PresentationKit/PKManagedObject.h>

@class PKBrand;

@interface PKRepresentative : PKManagedObject

@property (nonatomic, retain) NSString * email;
@property (nonatomic, retain) NSString * firstname;
@property (nonatomic, retain) NSString * lastname;
@property (nonatomic, retain) NSString * prid;
@property (nonatomic, assign) BOOL postCallEnabled;
@property (nonatomic, assign) BOOL crossBrandEditingEnabled;
@property (nonatomic, assign) BOOL presentationReOrderingEnabled;
@property (nonatomic, assign) BOOL shouldExcludeTimeFromTracking;
@property (nonatomic, assign) BOOL shouldExcludeHCPFromTracking;
@property (nonatomic, assign) BOOL trackingIsEnabled;
@property (nonatomic, assign) BOOL trackingCountryEnabled;
@property (nonatomic, assign) BOOL customConfigurationEnabled;
@property (nonatomic, retain) NSSet *brands;
@property (nonatomic, strong) NSOrderedSet* calls;

+ (PKRepresentative*) findRepresentativeWithIdFromCMS:(NSString*)idFromCMS orInsert:(void(^)(PKRepresentative* rep))didInsert;
+ (PKRepresentative*) findRepresentativeWithMostRecentCall;

@end

@interface PKRepresentative (CoreDataGeneratedAccessors)

- (void)addBrandsObject:(PKBrand *)value;
- (void)removeBrandsObject:(PKBrand *)value;
- (void)addBrands:(NSSet *)values;
- (void)removeBrands:(NSSet *)values;

@end


@interface NSManagedObjectContext (PKRepresentative)
- (PKRepresentative*) findRepresentativeWithIdFromCMS:(NSString*)idFromCMS;
- (PKRepresentative*) findRepresentativeWithIdFromCMS:(NSString*)idFromCMS orInsert:(void(^)(PKRepresentative* rep))didInsert;
@end
