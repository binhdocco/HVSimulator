#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@class PKSupplementalMedia;
@class PKBriefcaseRecipient;
@class NSManagedObjectObservable;

@interface PKBriefcase : NSManagedObject

@property (nonatomic, retain) NSDate * created;
@property (nonatomic, retain) NSSet *supplementalMediaItems;
@property (nonatomic, retain) PKBriefcaseRecipient* briefcaseRecipient;
@end

@interface PKBriefcase (CoreDataGeneratedAccessors)

- (void)addSupplementalMediaItemsObject:(PKSupplementalMedia *)value;
- (void)removeSupplementalMediaItemsObject:(PKSupplementalMedia *)value;
- (void)addSupplementalMediaItems:(NSSet *)values;
- (void)removeSupplementalMediaItems:(NSSet *)values;

@end

@interface NSManagedObjectContext (PKBriefcase)

- (NSArray*) briefcasesWithPredicate:(NSPredicate*)predicate error:(NSError**)error;
- (NSUInteger) numberOfBriefcasesWithPredicate:(NSPredicate*)predicate error:(NSError**)error;
- (NSManagedObjectObservable*) briefcasesObservable;

@end

