#import <Foundation/Foundation.h>

@interface NSOrderedSet (Sorting)

- (NSUInteger)indexOfObject:(id)object inSortedRange:(NSRange)range options:(NSBinarySearchingOptions)opts usingSortDescriptors:(NSArray*)sortDescriptors;

@end
