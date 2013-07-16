@class PKPresentation;
@class PKHealthCareProvider;

@interface PKRule : NSManagedObject

@property (nonatomic, strong) NSString* key;
@property (nonatomic, strong) NSString* operand;
@property (nonatomic, strong) NSString* value;
@property (nonatomic, strong) PKPresentation* presentation;

- (BOOL) evaluateForHcp:(PKHealthCareProvider*)hcp;

@end
