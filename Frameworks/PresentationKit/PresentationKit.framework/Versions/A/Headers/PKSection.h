@class PKPresentation;

@interface PKSection : NSManagedObject

@property (nonatomic, strong) NSSet* crossBrandPresentations;
@property (nonatomic, strong) NSString* name;
@property (nonatomic, strong) NSArray* slides;
@property (nonatomic, strong) PKPresentation* originalPresentation;

@end
