
@interface NSManagedObject (Model)

+ (NSFetchRequest*) fetchRequest;
+ (NSFetchRequest*) fetchRequestWithPredicate:(NSPredicate*)predicate;

+ (id) findObjectWithPredicate:(NSPredicate*)predicate inManagedObjectContext:(NSManagedObjectContext*)managedObjectContext;
+ (id) findObjectsWithPredicate:(NSPredicate*)predicate inManagedObjectContext:(NSManagedObjectContext*)managedObjectContext;

+ (id) insertNewObjectInManagedObjectContext:(NSManagedObjectContext*)managedObjectContext;

@end
