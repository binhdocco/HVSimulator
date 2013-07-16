#import <CoreData/CoreData.h>
@class PKHealthCareProvider, PKEvent;

@interface PKEventRating : NSManagedObject

@property (nonatomic) NSInteger rating;
@property (nonatomic, strong) PKHealthCareProvider* healthCareProvider;
@property (nonatomic, strong) PKEvent* event;

@end
