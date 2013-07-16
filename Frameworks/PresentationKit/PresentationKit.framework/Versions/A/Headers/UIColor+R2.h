

@interface UIColor (R2)

+ (UIColor*) colorWithName:(NSString*)name;
+ (UIColor*) colorWithHexString:(NSString*)string;

- (UIColor*) colorConvertedToGray;
- (NSString*) hexString; // does not include a "#" prefix

@end
