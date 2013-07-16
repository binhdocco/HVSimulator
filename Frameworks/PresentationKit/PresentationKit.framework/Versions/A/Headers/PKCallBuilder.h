#import <PresentationKit/PKEvent.h>

@class PKSlide;
@class PKSlideModal;
@class PKPerson;

extern const CGFloat kDefaultMinimumTrackingTime;

@interface PKCallBuilder : NSObject

@property (nonatomic, strong) PKCall* currentCall;
@property (nonatomic, strong) NSOrderedSet* healthCareProviders;
@property (strong, nonatomic, readonly) NSOrderedSet* audience;
@property (nonatomic, assign) NSUInteger minimumTrackingTime;
@property (nonatomic, strong) NSString* activityId;

- (id) initWithRepresentative:(PKRepresentative*)representative;

- (void) clearOpenEventsWithEndDate:(NSDate*)endDate;
- (void) deleteOpenEvents;

- (PKEvent*) currentEvent;
- (void) endTopEvent;
- (void) flagTopEvent;

- (void) addPresentationToCurrentCall:(PKPresentation*)presentation;

- (void) addAudienceMember:(PKPerson*)audienceMember;
- (void) removeAudienceMember:(PKPerson*)audienceMember;
- (void) clearAudience;

- (void) createEventWithTypeSlide:(PKSlide*)slide andPresentation:(PKPresentation*)presentation;

- (void) createEventWithTypePopUPWithSlide:(PKSlide*)slide presentation:(PKPresentation*)presentation path:(NSString*)path message:(NSString*)message;
- (void) createEventWithTypePopUPWithParentEvent;
- (void) createEventWithTypePopUpForSlideModal:(PKSlideModal *)slideModal presentation:(PKPresentation *)presentation;

- (void) createEventWithTypeBriefcase:(PKPresentation*)presentation;
- (void) createEventWithTypeMap:(PKPresentation*)presentation;
- (void) createEventWithTypeOrientation:(PKPresentation*)presentation data:(NSString*)data;
- (void) createEventWithTypeSignature:(PKPresentation*)presentation;
- (void) createEventWithTypePausePresentation:(PKPresentation*)presentation;
- (void) createEventWithTypeDraw:(PKSlide*)slide presentation:(PKPresentation*)presentation data:(NSString*)data;
- (void) createEventWithTypeScreenLock:(PKSlide*)slide presentation:(PKPresentation*)presentation data:(NSString*)data;
- (void) createEventWithTypeSurvey:(PKSlide*)slide presentation:(PKPresentation*)presentation title:(NSString*)title contentKey:(NSString*)contentKey data:(NSString*)data;
- (void) createEventWithTypeSurvey:(PKSlide*)slide presentation:(PKPresentation*)presentation data:(NSString*)data;
- (void) createEventWithTypeCustom:(PKSlide*)slide presentation:(PKPresentation*)presentation title:(NSString*)title message:(NSString*)message data:(NSString*)data;

- (void) createEventWithTypePDFForSupplementalMedia:(PKSupplementalMedia*)mediaItem presentation:(PKPresentation*)presentation;
- (void) createEventWithTypePDFForSlide:(PKSlide*)slide presentation:(PKPresentation*)presentation title:(NSString*)title path:(NSString*)path message:(NSString*)message;
- (void) createEventWithTypePDFForSlideModal:(PKSlideModal*)slideModal presentation:(PKPresentation*)presentation;

- (void) createEventWithTypePDFPage:(NSNumber*)pageNumber;
- (void) createEventWithTypePDFBookmark:(NSString*)bookmark andPageNumber:(NSNumber*)pageNumber;

- (void) createEventWithTypeVideoForSlide:(PKSlide*)slide presentation:(PKPresentation*)presentation path:(NSString*)path message:(NSString*)message;
- (void) createEventWithTypeVideoForSlideModal:(PKSlideModal*)slideModal presentation:(PKPresentation*)presentation;
- (void) createEventWithTypeVideoForSupplementalMedia:(PKSupplementalMedia*)mediaItem presentation:(PKPresentation*)presentation;
- (void) createEventForVideoWithType:(EventType)type andData:(NSString*)data;

- (void) createEventWithTypeHTML:(PKSlide *)slide presentation:(PKPresentation *)presentation title:(NSString *)title path:(NSString*)path message:(NSString *)message;
- (void) createEventWithTypeHTMLForSupplementalMedia:(PKSupplementalMedia*)mediaItem presentation:(PKPresentation*)presentation;


@end