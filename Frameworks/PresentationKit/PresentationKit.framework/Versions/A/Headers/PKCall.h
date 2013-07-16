@class PKRepresentative;

@interface PKCall : NSManagedObject

@property (nonatomic, strong) NSDate* startTime;
@property (nonatomic, strong) NSDate* endTime;
@property (nonatomic, strong) NSOrderedSet* events;
@property (nonatomic, getter = isCompleted) BOOL completed;
@property (nonatomic, strong) NSOrderedSet* presentations;
@property (nonatomic, strong) PKRepresentative* representative;
@property (nonatomic, getter = isSent) BOOL sent;
@property (nonatomic, strong) NSSet* possibleAudience;
@property (nonatomic, strong) NSString* activityId;
@property (nonatomic, strong) NSDictionary* callData;

- (NSOrderedSet*) audience;
- (NSArray*) eventsSortedByStartTimeWithError:(NSError**)error;

@end

@interface PKCall (CoreDataGeneratedAccessors)

- (void) addPossibleAudienceObject:(PKHealthCareProvider*)value;
- (void) removePossibleAudienceObject:(PKHealthCareProvider*)value;
- (void) addPossibleAudience:(NSSet*)values;
- (void) removePossibleAudience:(NSSet*)values;

@end

@interface NSManagedObjectContext (PKCall)

- (NSManagedObjectObservable*) unfinishedCallsObservable;
- (NSManagedObjectObservable*) completedCallsObservable;

@end
