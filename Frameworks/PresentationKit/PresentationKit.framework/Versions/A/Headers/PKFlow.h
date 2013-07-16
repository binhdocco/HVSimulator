#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@class PKPresentation, PKFlowSlide;

@interface PKFlow : NSManagedObject

@property (nonatomic, retain) NSString * name;
@property (nonatomic, retain) PKPresentation *presentation;
@property (nonatomic, retain) NSOrderedSet *flowSlides;
@property (nonatomic) BOOL isBuiltIn;

- (NSArray*) slides;
- (NSArray*) sections;
- (NSArray*) divergentSections;

@end

@interface PKFlow (CoreDataGeneratedAccessors)

- (void)insertObject:(PKFlowSlide *)value inSlidesAtIndex:(NSUInteger)idx;
- (void)removeObjectFromSlidesAtIndex:(NSUInteger)idx;
- (void)insertSlides:(NSArray *)value atIndexes:(NSIndexSet *)indexes;
- (void)removeSlidesAtIndexes:(NSIndexSet *)indexes;
- (void)replaceObjectInSlidesAtIndex:(NSUInteger)idx withObject:(PKFlowSlide *)value;
- (void)replaceSlidesAtIndexes:(NSIndexSet *)indexes withSlides:(NSArray *)values;
- (void)addSlidesObject:(PKFlowSlide *)value;
- (void)removeSlidesObject:(PKFlowSlide *)value;
- (void)addSlides:(NSOrderedSet *)values;
- (void)removeSlides:(NSOrderedSet *)values;

@end
