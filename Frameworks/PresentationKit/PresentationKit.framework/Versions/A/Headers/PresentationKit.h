#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
#import <UIKit/UIKit.h>

#import <PresentationKit/NSManagedObject+Model.h>
#import <PresentationKit/NSManagedObjectObservable.h>

#import <PresentationKit/PKBrand.h>
#import <PresentationKit/PKBriefcase.h>
#import <PresentationKit/PKCall.h>
#import <PresentationKit/PKCallBuilder.h>
#import <PresentationKit/PKEvent.h>
#import <PresentationKit/PKEventRating.h>
#import <PresentationKit/PKFlow.h>
#import <PresentationKit/PKFlowSlide.h>
#import <PresentationKit/PKHealthCareProvider.h>
#import <PresentationKit/PKBriefcaseRecipient.h>
#import <PresentationKit/PKPackage.h>
#import <PresentationKit/PKPerson.h>
#import <PresentationKit/PKPresentation.h>
#import <PresentationKit/PKPresentationCrossBrand.h>
#import <PresentationKit/PKHelpPresentation.h>
#import <PresentationKit/PKRule.h>
#import <PresentationKit/PKRepresentative.h>
#import <PresentationKit/PKSection.h>
#import <PresentationKit/PKSlide.h>
#import <PresentationKit/PKSlideModal.h>
#import <PresentationKit/PKSupplementalMedia.h>

#import <PresentationKit/UIView+Nib.h>
#import <PresentationKit/NSBundle+Presentation.h>
#import <PresentationKit/PresentationKit+PackageInstall.h>
#import <PresentationKit/PresentationKit+ShareCrossBrandPresentation.h>

#import <PresentationKit/PKPresentationViewController.h>

extern NSString* const PresentationKitErrorDomain;

enum {
    kPresentationKitInstallationError,
};

extern NSString* const PKPackageNameKey;
extern NSString* const PKPresentationKitDidDeleteDataNotification;
