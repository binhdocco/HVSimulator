
@interface PresentationKit : NSObject

@property (readonly, strong, nonatomic) NSPersistentStoreCoordinator* persistentStoreCoordinator;
@property (readonly, strong, nonatomic) NSManagedObjectContext* managedObjectContext;
@property (readonly, strong, nonatomic) NSManagedObjectModel* managedObjectModel;

+ (PresentationKit*) sharedInstance;
+ (NSManagedObjectContext*) distinctManagedObjectContext;

- (BOOL) saveManagedObjectContext:(NSManagedObjectContext*)context error:(NSError**)error;
- (BOOL) savePKManagedObjectContextWithError:(NSError**)error;

- (void) performOperationOnSharedContext:(void(^)(NSManagedObjectContext*))operationBlock;
- (void) performOperationOnDistinctContext:(void(^)(NSManagedObjectContext*))operationBlock;

- (NSString*) pathForPackageWithName:(NSString*)packageName;
- (NSString*) pathForPackageWithName:(NSString*)packageName inManagedObjectContext:(NSManagedObjectContext*)context;

+ (NSString*) pathToResourceForPackageURL:(NSURL*)URL;
+ (NSString*) pathToResourceForPackageURL:(NSURL*)URL inManagedObjectContext:(NSManagedObjectContext*)context;

- (void) deleteManagedObjectModel;

- (void) registerSystemBridgePluginWithKey:(NSString*)key executionBlock:(NSDictionary*(^)(NSURL*, NSDictionary*))executionBlock;
- (NSDictionary*(^)(NSURL*, NSDictionary*)) blockForPluginWithKey:(NSString*)key;

@end

extern NSString* const kCFBundlePackageTypeKey;
