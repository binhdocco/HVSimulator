@interface PKPresentationCrossBrand : PKPresentation

@property (nonatomic, strong) NSOrderedSet* crossBrandSections;

+ (PKPresentationCrossBrand*) presentationCrossBrandFromFlow:(PKFlow*)flow;

@end
