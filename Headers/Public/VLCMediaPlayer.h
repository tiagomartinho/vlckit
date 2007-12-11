/*****************************************************************************
 * VLCMediaPlayer.h: VLC.framework VLCMediaPlayer header
 *****************************************************************************
 * Copyright (C) 2007 Pierre d'Herbemont
 * Copyright (C) 2007 the VideoLAN team
 * $Id$
 *
 * Authors: Pierre d'Herbemont <pdherbemont # videolan.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#import <Cocoa/Cocoa.h>
#import "VLCMedia.h"

/* Notification Messages */
extern NSString * VLCMediaPlayerTimeChanged;
extern NSString * VLCMediaPlayerStateChanged;

// TODO: Documentation
typedef enum VLCMediaPlayerState
{
    VLCMediaPlayerStateStopped,        //< Player has stopped
    VLCMediaPlayerStateOpening,        //< Stream is opening
    VLCMediaPlayerStateBuffering,      //< Stream is buffering
    VLCMediaPlayerStateEnded,          //< Stream has ended
    VLCMediaPlayerStateError,          //< Player has generated an error
    VLCMediaPlayerStatePlaying,        //< Stream is playing
    VLCMediaPlayerStatePaused          //< Stream is paused
} VLCMediaPlayerState;

extern NSString *VLCMediaPlayerStateToString(VLCMediaPlayerState state);

/**
 * Formal protocol declaration for playback delegates.  Allows playback messages
 * to be trapped by delegated objects.
 */
@protocol VLCMediaPlayerDelegate
- (void)mediaPlayerTimeChanged:(NSNotification *)aNotification;
- (void)mediaPlayerStateChanged:(NSNotification *)aNotification;
@end

// TODO: Should we use medialist_player or our own flavor of media player?
@interface VLCMediaPlayer : NSObject 
{
    id delegate;            //< Object delegate
    VLCVideoView *videoView;//< NSView instance where media is rendered to

    void *instance;            //  Internal
    VLCMedia *media;        //< Current media being played
}

/* Initializers */
- (id)initWithVideoView:(VLCVideoView *)aVideoView;

/* Properties */
- (void)setDelegate:(id)value;
- (id)delegate;

/* Video View Options */
// TODO: Should be it's own object?

// TODO: use VLCVideoView instead of NSView
- (void)setVideoView:(VLCVideoView *)value;
- (VLCVideoView *)videoView;

- (void)setFullscreen:(BOOL)value;
- (BOOL)fullscreen;

- (void)setVideoAspectRatio:(char *)value;
- (char *)videoAspectRatio;
- (void)setVideoSubTitles:(int)value;
- (int)videoSubTitles;

- (void)setVideoCropGeometry:(char *)value;
- (char *)videoCropGeometry;

- (void)setVideoTeleText:(int)value;
- (int)videoTeleText;

- (void)setRate:(int)value;
- (int)rate;

/* Video Information */
- (NSSize)videoSize;
- (BOOL)hasVideoOut;
- (float)framesPerSecond;

/**
 * Sets the current position (or time) of the feed.
 * \param value New time to set the current position to.  If time is [VLCTime nullTime], 0 is assumed.
 */
- (void)setTime:(VLCTime *)value;

/** 
 * Returns the current position (or time) of the feed.
 * \return VLCTIme object with current time.
 */
- (VLCTime *)time;

- (void)setChapter:(int)value;
- (int)chapter;
- (int)countOfChapters;

/* Audio Options */
- (void)setAudioTrack:(int)value;
- (int)audioTrack;
- (int)countOfAudioTracks;

- (void)setAudioChannel:(int)value;
- (int)audioChannel;

/* Media Options */
- (void)setMedia:(VLCMedia *)value;
- (VLCMedia *)media;

/* Playback Operations */
/**
 * Plays a media resource using the currently selected media controller (or 
 * default controller.  If feed was paused then the feed resumes at the position 
 * it was paused in.
 * \return A Boolean determining whether the stream was played or not.
 */
- (BOOL)play;

/**
 * Toggle's the pause state of the feed.
 */
- (void)pause;

/**
 * Fast forwards through the feed at the standard 1x rate.
 */
//- (void)fastForward;

/**
 * Fast forwards through the feed at the rate specified.
 * \param rate Rate at which the feed should be fast forwarded.
 */
//- (void)fastForwardAtRate:(int)rate;

/**
 * Rewinds through the feed at the standard 1x rate.
 */
//- (void)rewind;

/**
 * Rewinds through the feed at the rate specified.
 * \param rate Rate at which the feed should be fast rewound.
 */
//- (void)rewindAtRate:(int)rate;

/* Playback Information */
/**
 * Playback state flag identifying that the stream is currently playing.
 * \return TRUE if the feed is playing, FALSE if otherwise.
 */
- (BOOL)isPlaying;

/**
 * Playback state flag identifying wheather the stream will play.
 * \return TRUE if the feed is ready for playback, FALSE if otherwise.
 */
- (BOOL)willPlay;

/**
 * Playback's current state.
 * \see VLCMediaState
 */
- (VLCMediaPlayerState)state;
@end