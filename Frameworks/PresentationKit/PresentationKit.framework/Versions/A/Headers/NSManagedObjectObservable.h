
@interface NSManagedObjectObservable : NSObject

@property (nonatomic, strong, readonly) NSArray* contents;

- (id) initWithManagedObjectContext:(NSManagedObjectContext*)context fetchRequest:(NSFetchRequest*)request sectionNameKeyPath:(NSString*)sectionNameKeyPath;
- (id) initWithManagedObjectContext:(NSManagedObjectContext*)context fetchRequest:(NSFetchRequest*)request;

- (void) setPredicate:(NSPredicate*)predicate;
- (NSArray*) sectionIndexTitles;
- (NSArray*) sections;
- (id) objectAtIndexPath:(NSIndexPath*)indexPath;
- (NSIndexPath*) indexPathForObject:(id)object;

@end

extern NSString* const NSManagedObjectObservableObservationKey;
