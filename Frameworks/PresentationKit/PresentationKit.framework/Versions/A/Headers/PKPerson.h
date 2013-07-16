#import <PresentationKit/PKManagedObject.h>

@interface PKPerson : NSManagedObject

@property (nonatomic, retain) NSString* firstName;
@property (nonatomic, retain) NSString* lastName;
@property (nonatomic, retain) NSString* suffix;
@property (nonatomic, retain) NSString* email;
@property (nonatomic, retain) NSString* profession;

@property (nonatomic, retain) PKPerson* superior;
@property (nonatomic, retain) NSSet* events;
@property (nonatomic, strong, readonly) NSString* fullName;

@end

@interface PKPerson (CoreDataGeneratedAccessors)

- (void)addEventsObject:(PKEvent *)value;
- (void)removeEventsObject:(PKEvent *)value;
- (void)addEvents:(NSSet *)values;
- (void)removeEvents:(NSSet *)values;

@end

@interface NSManagedObjectContext (PKPerson)

- (PKPerson*) findPersonWithFirstName:(NSString*)firstName lastName:(NSString*)lastName;
- (PKPerson*) findPersonWithFirstName:(NSString*)firstName lastName:(NSString*)lastName suffix:(NSString*)suffix orInsert:(void(^)(PKPerson* personObject))didInsert;

@end
