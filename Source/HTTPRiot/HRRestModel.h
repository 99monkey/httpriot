//
//  HRRestModel.h
//  HTTPRiot
//
//  Created by Justin Palmer on 1/28/09.
//  Copyright 2009 Alternateidea. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "HRConstants.h"
/**
 * You can either subclass this class or use it directly to make requests.
 * It's recommended that you subclass it and setup default properties in your 
 * classes <tt>initialize</tt> method.
 *
 * @code
 *  @implementation Person
 *  + (void)initialize
 *  {
 *     NSDictionary *params = [NSDictionary dictionaryWithObject:@"1234567" forKey:@"api_key"];
 *     [self setBaseURI:[NSURL URLWithString:@"http://localhost:1234/api"]];    
 *     [self setFormat:kHTTPFormatJSON];
 *     [self setDefaultParameters:params];
 *  }
 *
 *  -(void)personLoaded:(NSDictionary *)info
 *  {
 *      NSDictionary *person = [info valueForKey:@"results"];   
 *  }
 *  @end
 *
 *  // Would send a request to http://localhost:1234/api/people/1?api_key=1234567
 *  [Person getPath:@"/people/1" withOptions:nil target:self selector:@selector(personLoaded:)];
 * @endcode
 *
 * <h3>A note on default properties and subclassing</h3>
 * Each subclass has its own set of unique properties and these properties <em>are not</em>
 * inherited by any additional subclasses.
 */
@interface HRRestModel : NSObject {

}

/**
 * @name Setting default request options
 * Set the default options that can be used in every request made from the model 
 * that sets them.
 * @{ 
 */

/**
 * The base url to use in every request
 */
+ (NSURL *)baseURI;

/** 
 * Set the base URL to be used in every request.
 *
 * Instead of providing a URL for every request you can set the base
 * url here.  You can also provide a path and port if you wish.  This 
 * url is prepended to the path argument of the request methods.
 *
 * @param uri The base uri used in all request
 */
+ (void)setBaseURI:(NSURL *)uri;

/**
 * Default headers sent with every request
 */
+ (NSDictionary *)headers;

/**
 * Set the default headers sent with every request.
 * @param hdrs An NSDictionary of headers.  For example you can 
 * set this up.
 *
 * @code
 * NSDictionary *hdrs = [NSDictionary dictionaryWithObject:@"application/json" forKey:@"Accept"];
 * [self setHeaders:hdrs];
 * @endcode
 */
+ (void)setHeaders:(NSDictionary *)hdrs;

/**
 * Returns a dictionary containing the username and password used for basic auth.
 */
+ (NSDictionary *)basicAuth;

/**
 * Set the username and password used in requests that require basic authentication.
 *
 * The username and password privded here will be Base64 encoded and sent as an 
 * <code>Authorization</code> header.
 * @param username user name used to authenticate
 * @param password Password used to authenticate
 */
+ (void)setBasicAuthWithUsername:(NSString *)username password:(NSString *)password;

/**
 * Default params sent with every request.
 */
+ (NSDictionary *)defaultParams;

/**
 * Set the defaul params sent with every request.
 * If you need to send something with every request this is the perfect way to do it.
 * For GET request, these parameters will be appended to the query string.  For 
 * POST request these parameters are sent with the body.
 */
+ (void)setDefaultParams:(NSDictionary *)params;

/**
 * The format used to decode and encode request and responses.
 * Supported formats are JSON and XML.
 */
+ (HRDataFormat)format;

/**
 * Set the format used to decode and encode request and responses.
 */
+ (void)setFormat:(HRDataFormat)format;
//@}

/** 
 * @name Sending Requests
 * These methods allow you to send GET, POST, PUT and DELETE requetsts.
 *
 * <h3>Request Options</h3>
 * All requests can take numerous types of options passed as the second argument.
 * @li @b headers <tt>NSDictionary</tt> - The headers to send with the request
 * @li @b params <tt>NSDictionary</tt> - The query or body parameters sent with the request.
 * @li @b body <tt>NSData</tt>, <tt>NSString</tt> or <tt>NSDictionary</tt> - This option is used only during POST and PUT
 *     requests.  This option is eventually transformed into an NSData object before it is sent.
 *     If you supply the body as an NSDictionary it's turned to a query string &foo=bar&baz=boo and 
 *     then it's encoded as an NSData object.  If you supply an NSString, it's encoded as an NSData 
 *     object and sent.  
 * @{
 */
 
/**
 * Send a GET request
 * @param path The path to get.  If you haven't setup the baseURI option you'll need to provide a 
 *        full url. 
 * @param options The options for this request.
 * @param target The object on which the selector is invoked.
 * @param sel The selector run after the request is complete.  
 *        This selector will be passed a dictionary containing 4 objects:
 *        @li <tt>results</tt>: The decoded data recieved from the server
 *        @li <tt>response</tt>: The NSHTTPURLResponse object.
 *        @li <tt>error</tt>: The error if present or nil. 
 *        @li <tt>object</tt>: Any object that was passed along
 * @param obj Any object you want passed to the selector callback
 *
 */
+ (NSOperation *)getPath:(NSString *)path withOptions:(NSDictionary *)options target:(id)target selector:(SEL)sel object:(id)obj;
/**
 * @see getPath:withOptions:target:selector:object
 */
+ (NSOperation *)getPath:(NSString *)path withOptions:(NSDictionary *)options target:(id)target selector:(SEL)sel;
/**
 * @see getPath:withOptions:target:selector:object
 */
+ (NSOperation *)getPath:(NSString *)path target:(id)target selector:(SEL)sel object:(id)obj;
/**
 * @see getPath:withOptions:target:selector:object
 */
+ (NSOperation *)getPath:(NSString *)path target:(id)target selector:(SEL)sel;

/**
 * Send a POST request
 * @param path The path to POST to.  If you haven't setup the baseURI option you'll need to provide a 
 *        full url. 
 * @param options The options for this request.
 *
 * <strong>Note:</strong>  There are two important options you can set on post request.  Setting the 
 * <tt>params</tt> option will cause the request to be posted as <tt>application/x-www-form-urlencoded</tt> data.
 * If you'd like to post raw data like JSON or XML you'll need to set the <tt>body</tt> option.  Setting the <tt>body</tt>
 * option will cause the <tt>params</tt> option to be ignored.
 * 
 * @param target The object on which the selector is invoked.
 * @param sel The selector run after the request is complete.  
 *        This selector with be passed a dictionary containing 3 objects:
 *        @li <tt>results</tt>: The decoded data recieved from the server
 *        @li <tt>response</tt>: The NSHTTPURLResponse object.
 *        @li <tt>error</tt>: The error if present or nil.
 *
 */
+ (NSOperation *)postPath:(NSString *)path withOptions:(NSDictionary *)options target:(id)target selector:(SEL)sel;

/**
 * @see postPath:withOptions:target:selector:
 */
+ (NSOperation *)postPath:(NSString *)path target:(id)target selector:(SEL)sel;

/**
 * Send a PUT request
 * @param path The path to PUT to.  If you haven't setup the baseURI option you'll need to provide a 
 *        full url. 
 * @param options The options for this request.
 *
 * <strong>Note:</strong>  All data found in the <tt>body</tt> option will be PUT.  Setting the <tt>body</tt>
 * option will cause the <tt>params</tt> option to be ignored.
 * 
 * @param target The object on which the selector is invoked.
 * @param sel The selector run after the request is complete.  
 *        This selector with be passed a dictionary containing 3 objects:
 *        @li <tt>results</tt>: The decoded data recieved from the server
 *        @li <tt>response</tt>: The NSHTTPURLResponse object.
 *        @li <tt>error</tt>: The error if present or nil. 
 * @param obj An object to pass with the info dictionary to the callback
 *
 */
+ (NSOperation *)putPath:(NSString *)path withOptions:(NSDictionary *)options target:(id)target selector:(SEL)sel object:(id)obj;

/**
 * @see putPath:withOptions:target:selector:object
 */
+ (NSOperation *)putPath:(NSString *)path withOptions:(NSDictionary *)options target:(id)target selector:(SEL)sel;

/**
 * @see putPath:withOptions:target:selector:object
 */
+ (NSOperation *)putPath:(NSString *)path target:(id)target selector:(SEL)sel object:(id)obj;

/**
 * @see putPath:withOptions:target:selector:object
 */
+ (NSOperation *)putPath:(NSString *)path target:(id)target selector:(SEL)sel;

/**
 * Send a DELETE request
 * @param path The path to DELETE.  If you haven't setup the baseURI option you'll need to provide a 
 *        full url. 
 * @param options The options for this request.
 * @param target The object on which the selector is invoked.
 * @param sel The selector run after the request is complete.  
 *        This selector with be passed a dictionary containing 3 objects:
 *        @li <tt>results</tt>: The decoded data recieved from the server
 *        @li <tt>response</tt>: The NSHTTPURLResponse object.
 *        @li <tt>error</tt>: The error if present or nil. 
 * @param obj An object to pass with the info dictionary to the callback
 *
 */
+ (NSOperation *)deletePath:(NSString *)path withOptions:(NSDictionary *)options target:(id)target selector:(SEL)sel object:(id)obj;

/**
 * @see deletePath:withOptions:target:selector:object
 */
+ (NSOperation *)deletePath:(NSString *)path withOptions:(NSDictionary *)options target:(id)target selector:(SEL)sel;

/**
 * @see deletePath:withOptions:target:selector:object
 */
+ (NSOperation *)deletePath:(NSString *)path target:(id)target selector:(SEL)sel object:(id)obj;

/**
 * @see deletePath:withOptions:target:selector
 */
+ (NSOperation *)deletePath:(NSString *)path target:(id)target selector:(SEL)sel;
//@}
@end