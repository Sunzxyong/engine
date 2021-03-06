// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#import <Cocoa/Cocoa.h>

#import "FLEOpenGLContextHandling.h"
#import "FLEPluginRegistrar.h"
#import "FLEReshapeListener.h"

#if defined(FLUTTER_FRAMEWORK)
#import "flutter/shell/platform/darwin/ios/framework/Headers/FlutterBinaryMessenger.h"
#import "flutter/shell/platform/darwin/ios/framework/Headers/FlutterMacros.h"
#else
#import "FlutterBinaryMessenger.h"
#import "FlutterMacros.h"
#endif

/**
 * Controls embedder plugins and communication with the underlying Flutter engine, managing a view
 * intended to handle key inputs and drawing protocols (see |view|).
 *
 * Can be launched headless (no managed view), at which point a Dart executable will be run on the
 * Flutter engine in non-interactive mode, or with a drawable Flutter canvas.
 */
FLUTTER_EXPORT
@interface FLEViewController
    : NSViewController <FlutterBinaryMessenger, FLEPluginRegistrar, FLEReshapeListener>

/**
 * The view this controller manages when launched in interactive mode (headless set to false). Must
 * be capable of handling text input events, and the OpenGL context handling protocols.
 */
@property(nullable) NSView<FLEOpenGLContextHandling>* view;

/**
 * Launches the Flutter engine with the provided configuration.
 *
 * @param assets The path to the flutter_assets folder for the Flutter application to be run.
 * @param arguments Arguments to pass to the Flutter engine. See
 *               https://github.com/flutter/engine/blob/master/shell/common/switches.h
 *               for details. Not all arguments will apply to embedding mode.
 *               Note: This API layer will likely abstract arguments in the future, instead of
 *               providing a direct passthrough.
 * @return YES if the engine launched successfully.
 */
- (BOOL)launchEngineWithAssetsPath:(nonnull NSURL*)assets
              commandLineArguments:(nullable NSArray<NSString*>*)arguments;

/**
 * Launches the Flutter engine in headless mode with the provided configuration. In headless mode,
 * this controller's view should not be displayed.
 *
 * See launcheEngineWithAssetsPath:commandLineArguments: for details.
 */
- (BOOL)launchHeadlessEngineWithAssetsPath:(nonnull NSURL*)assets
                      commandLineArguments:(nullable NSArray<NSString*>*)arguments;

/**
 * Returns the FLEPluginRegistrar that should be used to register the plugin with the given name.
 */
- (nonnull id<FLEPluginRegistrar>)registrarForPlugin:(nonnull NSString*)pluginName;

@end
