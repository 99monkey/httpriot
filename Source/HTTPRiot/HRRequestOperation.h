//
//  HRRequestOperation.h
//  HTTPRiot
//
//  Created by Justin Palmer on 1/30/09.
//  Copyright 2009 Alternateidea. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "HRConstants.h"

/**
 * The object which all requests are routed through.  You shouldn't need to use 
 * this class directly, but instead use HRRestModel which wraps the method 
 * of this class neatly.
 */
@interface HRRequestOperation : NSOperation {
    NSURLConnection *_connection;
    NSMutableData   *_responseData;
    CGFloat         timeout;
    HRRequestMethod httpMethod;
    NSString        *path;
    NSDictionary    *options;
    id              formatter;
    
    /// The target which the didEneSelector is invoked
    id target;
    
    /// The selector invoked after a request completes or returns an error
    SEL didEndSelector;
    
    /// An object to be added to the dictionary passed to didEndSelector
    id obj;
    
    BOOL _isFinished;
    BOOL _isExecuting;
}
 
/// The lenght of time in seconds before the request times out.
/**
 * Sets the length of time in seconds before a request will timeout.
 * This defaults to <tt>30.0</tt>.
 */
@property (nonatomic, assign) CGFloat timeout;

/// The REST method to use when performing a request
/**
 * This defaults to HRRequestMethodGet.  Valid options are ::HRRequestMethod.
 */
@property (nonatomic, readonly, assign) HRRequestMethod httpMethod;

/// The relative path or url string used in a request
/**
 If you provide a relative path here, you must set the baseURI option.
 If given a full url this will overide the baseURI option.
 */
@property (nonatomic, readonly, copy) NSString *path;

/// An NSDictionary containing all the options for a request.
/**
 This needs documented
 */
@property (nonatomic, readonly, retain) NSDictionary *options;

/// The formatter used to decode the response body.
/**
 Currently, only JSON is supported.
 */
@property (nonatomic, readonly, retain) id formatter;

/**
 * Returns an NSDictionary, NSArray decoded from the server
 */
+ (NSOperation*)requestWithMethod:(HRRequestMethod)method
                             path:(NSString*)urlPath
                          options:(NSDictionary*)requestOptions
                           target:(id)target
                         selector:(SEL)sel
                           object:(id)obj;
@end