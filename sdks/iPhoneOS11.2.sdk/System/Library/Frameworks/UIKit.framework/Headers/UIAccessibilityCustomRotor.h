//
//  UIAccessibilityCustomRotor.h
//  UIKit
//
//  Copyright (c) 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UITextInput.h>

/*
 UIAccessibilityCustomRotor
 
 Assistive technologies, like VoiceOver, use a context sensitive function to provide more power
 and flexibility to perform actions and searches. This is called "The Rotor."
 
 An element (or an element in the ancestor hierarchy) can expose an array of custom rotors
 that a user can activate to search for other instances of like minded elements. This can also
 be applied to ranges within elements.
 
 As an example, in a magazine app, a custom rotor can be created to allow the user to find the next link or heading within an article.
 Alternatively, in a document editor, the next misspelled word can be found by returning the next range that contains a misspelled word.
 */

NS_ASSUME_NONNULL_BEGIN

@class UIAccessibilityCustomRotor, UIAccessibilityCustomRotorItemResult, UIAccessibilityCustomRotorSearchPredicate;

typedef NS_ENUM(NSInteger, UIAccessibilityCustomRotorDirection) {
    UIAccessibilityCustomRotorDirectionPrevious NS_ENUM_AVAILABLE_IOS(10_0),
    UIAccessibilityCustomRotorDirectionNext NS_ENUM_AVAILABLE_IOS(10_0),
};

/*
 UIAccessibilityCustomSystemRotorType should be used when you want to allow searching for one of the following types.
 This will allow VoiceOver to use appropriate gestures and keyboard commands for these specific search types.
 */
typedef NS_ENUM(NSInteger, UIAccessibilityCustomSystemRotorType) {
    UIAccessibilityCustomSystemRotorTypeNone = 0,
    UIAccessibilityCustomSystemRotorTypeLink,
    UIAccessibilityCustomSystemRotorTypeVisitedLink,
    UIAccessibilityCustomSystemRotorTypeHeading,
    UIAccessibilityCustomSystemRotorTypeHeadingLevel1,
    UIAccessibilityCustomSystemRotorTypeHeadingLevel2,
    UIAccessibilityCustomSystemRotorTypeHeadingLevel3,
    UIAccessibilityCustomSystemRotorTypeHeadingLevel4,
    UIAccessibilityCustomSystemRotorTypeHeadingLevel5,
    UIAccessibilityCustomSystemRotorTypeHeadingLevel6,
    UIAccessibilityCustomSystemRotorTypeBoldText,
    UIAccessibilityCustomSystemRotorTypeItalicText,
    UIAccessibilityCustomSystemRotorTypeUnderlineText,
    UIAccessibilityCustomSystemRotorTypeMisspelledWord,
    UIAccessibilityCustomSystemRotorTypeImage,
    UIAccessibilityCustomSystemRotorTypeTextField,
    UIAccessibilityCustomSystemRotorTypeTable,
    UIAccessibilityCustomSystemRotorTypeList,
    UIAccessibilityCustomSystemRotorTypeLandmark,
} NS_AVAILABLE_IOS(11_0);

typedef UIAccessibilityCustomRotorItemResult *_Nullable(^UIAccessibilityCustomRotorSearch)(UIAccessibilityCustomRotorSearchPredicate *predicate);

// Create the array of UIAccessibilityCustomRotors and set it on the target element or ancestor element to which it applies.
@interface NSObject (UIAccessibilityCustomRotor)
@property (nonatomic, retain, nullable) NSArray<UIAccessibilityCustomRotor *> *accessibilityCustomRotors NS_AVAILABLE_IOS(10_0);
@end

// UIAccessibilityCustomRotorSearchPredicate is a container for search parameters.
// It should be examined to determine the next matching UIAccessibilityCustomRotorItemResult.
NS_CLASS_AVAILABLE_IOS(10_0) @interface UIAccessibilityCustomRotorSearchPredicate : NSObject
@property (nonatomic, retain) UIAccessibilityCustomRotorItemResult *currentItem;
@property (nonatomic) UIAccessibilityCustomRotorDirection searchDirection;
@end

NS_CLASS_AVAILABLE_IOS(10_0) @interface UIAccessibilityCustomRotor : NSObject

- (instancetype)initWithName:(NSString *)name itemSearchBlock:(UIAccessibilityCustomRotorSearch)itemSearchBlock;
- (instancetype)initWithAttributedName:(NSAttributedString *)attributedName itemSearchBlock:(UIAccessibilityCustomRotorSearch)itemSearchBlock API_AVAILABLE(ios(11.0), tvos(11.0));
- (instancetype)initWithSystemType:(UIAccessibilityCustomSystemRotorType)type itemSearchBlock:(UIAccessibilityCustomRotorSearch)itemSearchBlock NS_AVAILABLE_IOS(11_0);

// The localized name the assistive technology will use to describe the custom rotor.
@property (nonatomic, copy) NSString *name;

// Underlying attributed version of the "name" property. Setting this property will change the
// value of the "name" property and vice-versa.
@property (nonatomic, copy) NSAttributedString *attributedName API_AVAILABLE(ios(11.0), tvos(11.0));

// A block that takes a UIAccessibilityCustomRotorItemResult and the search direction and returns the next/previous instance of that rotor item.
// If the currentItem is nil, that implies the first/last item should be returned.
@property (nonatomic, copy) UIAccessibilityCustomRotorSearch itemSearchBlock;

// The system rotor type that was optionally used during initialization.
// default = UIAccessibilityCustomSystemRotorTypeNone
@property (nonatomic, readonly) UIAccessibilityCustomSystemRotorType systemRotorType NS_AVAILABLE_IOS(11_0);

@end


NS_CLASS_AVAILABLE_IOS(10_0) @interface UIAccessibilityCustomRotorItemResult : NSObject

- (instancetype)initWithTargetElement:(id<NSObject>)targetElement targetRange:(nullable UITextRange *)targetRange;

// A UIAccessibilityCustomRotorItemResult references a real element that will be messaged for other accessibility properties.
@property (nonatomic, weak) id<NSObject> targetElement;

// Optionally, a target range can be used to search within an element (like a UITextView).
// If targetRange is nil, the search should begin from the start/end of the element depending on the search direction.
@property (nullable, nonatomic, retain) UITextRange *targetRange;

@end

NS_ASSUME_NONNULL_END