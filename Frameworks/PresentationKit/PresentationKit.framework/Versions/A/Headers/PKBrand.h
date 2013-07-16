#import <CoreData/CoreData.h>
@class PKRepresentative;
@class PKHealthCareProvider;
@class PKPresentation;

@interface PKBrand : NSManagedObject

@property (nonatomic, assign) NSInteger idFromCMS;
@property (nonatomic, retain) NSString* summary;
@property (nonatomic, retain) NSString* thumbnail;
@property (nonatomic, retain) NSString* title;
@property (nonatomic, retain) NSSet* healthCareProviders;
@property (nonatomic, retain) NSSet* packages;
@property (nonatomic, retain) NSSet* representatives;
@property (nonatomic, strong) NSOrderedSet* presentations;

+ (NSString*) brandTitleFromBrands:(NSSet*)brands;

@end

@interface PKBrand (CoreDataGeneratedAccessors)

- (void) addHealthCareProvidersObject:(PKHealthCareProvider*)value;
- (void) removeHealthCareProvidersObject:(PKHealthCareProvider*)value;
- (void) addHealthCareProviders:(NSSet*)healthCareProviders;
- (void) removeHealthCareProviders:(NSSet*)healthCareProviders;

- (void) addPresentationsObject:(PKPresentation*)value;
- (void) removePresentationsObject:(PKPresentation*)value;
- (void) addPresentations:(NSSet*)values;
- (void) removePresentations:(NSSet*)values;

- (void) addRepresentativesObject:(PKRepresentative*)value;
- (void) removeRepresentativesObject:(PKRepresentative*)value;
- (void) addRepresentatives:(NSSet*)values;
- (void) removeRepresentatives:(NSSet*)values;

@end


@interface NSManagedObjectContext (PKBrand)

- (PKBrand*) findBrandWithTitle:(NSString*)title;
- (PKBrand*) findBrandWithTitle:(NSString*)title orInsert:(void(^)(PKBrand* brand))didInsert;

@end