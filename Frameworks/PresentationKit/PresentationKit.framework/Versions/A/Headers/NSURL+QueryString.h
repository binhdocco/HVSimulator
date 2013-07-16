#import <Foundation/Foundation.h>

@interface NSURL (QueryString)

- (NSDictionary*) dictonaryFromQueryString;
- (NSURL*) URLWithoutQueryParameters;

@end
