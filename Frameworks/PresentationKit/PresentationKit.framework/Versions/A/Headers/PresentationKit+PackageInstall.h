#import "PresentationKit+Private.h"

extern NSString* const kPackageDescriptionKey;
extern NSString* const kPresentationDependenciesKey;

extern NSString* const kPKPackageAssetTypeKey;
extern NSString* const kPKPackageLanguageKey;
extern NSString* const kPKPackageNameKey;
extern NSString* const kPKPackageTitleKey;
extern NSString* const kPKPackageExprationDateKey;
extern NSString* const kPKPackageDeploymentStatusKey;
extern NSString* const kPKPackageVersionKey;
extern NSString* const kPKPackageSingleBrandKey;
extern NSString* const kPKPackageMultipleBrandsKey;

extern NSString* const kOperandEquals;
extern NSString* const kOperandNotEquals;
extern NSString* const kOperandContains;
extern NSString* const kOperandDoesNotContain;


@interface PresentationKit (PackageInstall)

+ (BOOL) installPresentationWithBundle:(NSBundle*)presentationBundle packageId:(NSString*)packageId size:(NSUInteger)sizeInBytes dependencies:(NSDictionary*)dependenciesByName briefcases:(NSDictionary*)briefcasesByName error:(NSError**)error;
- (void) uninstallPackage:(PKPackage*)package;
- (void) uninstallPackages:(NSSet*)packages;

@end
