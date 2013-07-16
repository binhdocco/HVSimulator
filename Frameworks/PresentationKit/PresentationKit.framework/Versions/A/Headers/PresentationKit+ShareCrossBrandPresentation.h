@interface PresentationKit (ShareCrossBrandPresentation)

+ (BOOL) installCrossBrandPresentationFromJSON:(NSData*)json error:(NSError**)errorToReturn;
+ (NSData*) JSONFromCrossBrandPresentation:(PKPresentationCrossBrand*)presentation;

@end
