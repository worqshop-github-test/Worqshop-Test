//
//  MOOMaskedIconView.h
//  MOOMaskedIconView
//
//  Created by Peyton Randolph on 2/6/12.
//

#import <UIKit/UIKit.h>

//
//  ARC Helper
//
//  Version 1.2.1
//
//  Created by Nick Lockwood on 05/01/2012.
//  Copyright 2012 Charcoal Design
//
//  Distributed under the permissive zlib license
//  Get the latest version from here:
//
//  https://gist.github.com/1563325
//

#ifndef AH_RETAIN
#if __has_feature(objc_arc)
#define AH_RETAIN(x) (x)
#define AH_RELEASE(x)
#define AH_AUTORELEASE(x) (x)
#define AH_SUPER_DEALLOC
#else
#warning "Compiling MOOMaskedIconView without ARC is beta and may not work. Use at your own risk"
#define __AH_WEAK
#define AH_WEAK assign
#define AH_RETAIN(x) [(x) retain]
#define AH_RELEASE(x) [(x) release]
#define AH_AUTORELEASE(x) [(x) autorelease]
#define AH_SUPER_DEALLOC [super dealloc]
#endif
#endif

//  Weak reference support

#ifndef AH_WEAK
#if defined __IPHONE_OS_VERSION_MIN_REQUIRED
#if __IPHONE_OS_VERSION_MIN_REQUIRED >= __IPHONE_5_0
#define __AH_WEAK __weak
#define AH_WEAK weak
#else
#define __AH_WEAK __unsafe_unretained
#define AH_WEAK unsafe_unretained
#endif
#elif defined __MAC_OS_X_VERSION_MIN_REQUIRED
#if __MAC_OS_X_VERSION_MIN_REQUIRED >= __MAC_10_7
#define __AH_WEAK __weak
#define AH_WEAK weak
#else
#define __AH_WEAK __unsafe_unretained
#define AH_WEAK unsafe_unretained
#endif
#endif
#endif

//  ARC Helper ends

typedef void (^DrawingBlock)(CGContextRef context);

@interface MOOMaskedIconView : UIView <NSCopying>
{
    BOOL _highlighted;

    UIColor *_color;
    UIColor *_highlightedColor;
    UIColor *_gradientStartColor;
    UIColor *_gradientEndColor;
    UIImage *_overlay;
    CGBlendMode _overlayBlendMode;

    DrawingBlock _drawingBlock;
    CGImageRef _mask;
    CGGradientRef _gradient;
}

/* @name Properties */

/*
 * Whether the icon view is in its highlighted state.
 */
@property (nonatomic, assign, getter = isHighlighted) BOOL highlighted;

/*
 * Fill color painted when the icon view is unhighlighted.
 *
 * When gradientStartColor and gradientEndColor are both non-nil,
 * the view ignores fill color and draws a gradient.
 *
 * @see highlightedColor
 */
@property (nonatomic, strong) UIColor *color;

/*
 * Fill color painted when the icon view is highlighted.
 *
 * When gradientStartColor and gradientEndColor are both non-nil,
 * the view ignores fill color and draws a gradient.
 *
 * @see color
 */
@property (nonatomic, strong) UIColor *highlightedColor;

/*
 * The color filled at the gradient's start location
 *
 * When gradientStartColor and gradientEndColor are both non-nil,
 * the view ignores fill color and draws a gradient.
 *
 * @see gradientEndColor
 */
@property (nonatomic, strong) UIColor *gradientStartColor;

/*
 * The color filled at the gradient's end location
 *
 * When gradientStartColor and gradientEndColor are both non-nil,
 * the view ignores fill color and draws a gradient.
 *
 * @see gradientStartColor
 */
@property (nonatomic, strong) UIColor *gradientEndColor;

/*
 * An image composited over the icon after drawing's done.
 *
 * @see overlayBlendMode
 */
@property (nonatomic, strong) UIImage *overlay;

/*
 * The blend mode under which the overlay is drawn. Defaults to kCGBlendModeNormal. For a list of options see "CGBlendMode"
 *
 * @see overlay
 */
@property (nonatomic, assign) CGBlendMode overlayBlendMode;

/*
 * A block called with the current context at the end of every drawing. Has signature `void (^DrawingBlock)(CGContextRef context)`.
 *
 * Useful for custom drawing.
 */
@property (nonatomic, strong) DrawingBlock drawingBlock;

/*
 * The current CGImage mask held by the view. Read-only.
 *
 * @see Configuration methods
 */
@property (nonatomic, assign, readonly) CGImageRef mask;

/* @name Initialization methods */
- (id)initWithImage:(UIImage *)image;
- (id)initWithImage:(UIImage *)image size:(CGSize)size;
- (id)initWithImageNamed:(NSString *)imageName;
- (id)initWithImageNamed:(NSString *)imageName size:(CGSize)size;
- (id)initWithPDFNamed:(NSString *)pdfName;
- (id)initWithPDFNamed:(NSString *)pdfName size:(CGSize)size;
- (id)initWithResourceNamed:(NSString *)resourceName;
- (id)initWithResourceNamed:(NSString *)resourceName size:(CGSize)size;

/* @name Configuration methods */
- (void)configureWithImage:(UIImage *)image;
- (void)configureWithImage:(UIImage *)image size:(CGSize)size;
- (void)configureWithImageNamed:(NSString *)imageName;
- (void)configureWithImageNamed:(NSString *)imageName size:(CGSize)size;
- (void)configureWithPDFNamed:(NSString *)pdfName;
- (void)configureWithPDFNamed:(NSString *)pdfName size:(CGSize)size;
- (void)configureWithResourceNamed:(NSString *)resourceName;
- (void)configureWithResourceNamed:(NSString *)resourceName size:(CGSize)size;

/* @name Rendering */

/*
 * Render the icon unhighlighted to a UIImage.
 *
 * Useful for passing the icon to other views, e.g. UIButton.
 *
 * @see renderHighlightedImage
 */
- (UIImage *)renderImage;

/*
 * Render the icon highlighted to a UIImage.
 *
 * Useful for passing the icon to other views, e.g. UIButton.
 *
 * @see renderImage
 */
- (UIImage *)renderHighlightedImage;

@end
