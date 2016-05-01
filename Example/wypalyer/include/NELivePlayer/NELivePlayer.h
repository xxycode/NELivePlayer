/*
 *  NELivePlayer.h
 *  NELivePlayer
 *
 *  Created by Netase on 15-9-21.
 *  Copyright (c) 2015年 Netease. All rights reserved.
 *
 * This file is part of LivePlayer.
 *
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>

/*! \file */

/**
 * @brief 视频流类型
 */
typedef enum NELPBufferStrategy{
    NELPLowDelay,    //!< 网络直播低延时，适用于视频直播，延时低
    NELPAntiJitter,  //!< 网络点播抗抖动，适用于视频点播和本地视频，抗抖动性强
}NELPBufferStrategy;

/**
 * @brief 显示模式
 */
typedef enum NELPMovieScalingMode {
    NELPMovieScalingModeNone,       //!< 无缩放
    NELPMovieScalingModeAspectFit,  //!< 等比例缩放，某一边会有黑边填充
    NELPMovieScalingModeAspectFill, //!< 等比例缩放，某一边可能会被裁减
    NELPMovieScalingModeFill        //!< 全屏显示，画面宽高比可能与视频原始宽高比不一致
}NELPMovieScalingMode;
/**
 * @brief 播放状态
 */
typedef enum NELPMoviePlaybackState {
    NELPMoviePlaybackStateStopped, //!< 停止状态
    NELPMoviePlaybackStatePlaying, //!< 播放状态
    NELPMoviePlaybackStatePaused,  //!< 暂停状态，可调play继续播放
    NELPMoviePlaybackStateSeeking  //!< Seek状态
}NELPMoviePlaybackState;

/**
 * @brief 加载状态
 */
typedef enum NELPMovieLoadState {
    NELPMovieLoadStatePlayable       = 1 << 0, //!< 在该状态下，播放器初始化完成，可以播放，若shouldAutoplay 设置成YES，播放器初始化完成后会自动播放；
    NELPMovieLoadStatePlaythroughOK  = 1 << 1, //!< 在该状态下，在网络不好的情况下缓冲完成，可以播放
    NELPMovieLoadStateStalled        = 1 << 2, //!< 在播放过程中网络不好需要缓冲数据的时候播放会自动暂停
}NELPMovieLoadState;

/**
 * @brief 播放结束的原因
 */
typedef enum NELPMovieFinishReason {
    NELPMovieFinishReasonPlaybackEnded, //!< 正常播放结束
    NELPMovieFinishReasonPlaybackError, //!< 播放发生错误导致结束
    NELPMovieFinishReasonUserExited,    //!< 人为退出
}NELPMovieFinishReason;

/**
 * @brief 视频信息
 */
typedef struct NELPVideoInfo {
    const char *codec_type;  //!< 视频编码器类型 如: h264
    NSInteger width;   //!< 视频宽度
    NSInteger height;  //!< 视频高度
    CGFloat fps;       //!< 视频的帧率
    NSInteger bitrate; //!< 码率 (单位: kb/s)
}NELPVideoInfo;

/**
 * @brief 音频信息
 */
typedef struct NELPAudioInfo {
    const char *codec_type;        //!< 音频编码器类型 如: aac
    NSInteger sample_rate;   //!< 音频的采样率
    NSInteger bitrate;       //!< 码率 (单位: kb/s)
    NSInteger numOfChannels; //!< 音频的通道数
}NELPAudioInfo;

@protocol NELivePlayer;


#pragma mark NELPMediaPlayback

@protocol NELivePlayer <NSObject>


/**
 * @brief  设置缓冲策略，在播放器初始化后，prepareToPlay之前调用
 *
 * @discussion 缓冲策略有直播低延时模式和点播抗抖动模式，如果是直播，建议采用低延时模式，如果是点播或本地视频，建议采用抗抖动模式
 *
 * @return 无
 */
- (void)SetBufferStrategy:(NELPBufferStrategy)bufferStrategy;

/**
 *	@brief	设置数据源，初始化视频文件为播放做准备，在播放前调用
 *
 *  @discussion 当prepareToPlay完成时,若shouldAutoplay 为YES，则会自动调用play进行播放，若shouldAutoplay为 NO，则需手动播放
 *
 *	@return	无
 */
- (void)prepareToPlay;

/**
 *	@brief	开始播放
 *
 *  @discussion
 *  如果当前正在播放，则调用该方法将无效果\\\n
 *  此时播放器状态为: NELPMoviePlaybackStatePlaying
 *
 *	@return	无
 */
- (void)play;

/**
 *	@brief	暂停播放
 *
 *  @discussion
 *  调用play方法继续播放。如果当前播放已经暂停，则调用该方法将无效果。\\\n
 *  此时播放器状态为: NELPMoviePlaybackStatePaused
 *
 *	@return	无
 */
- (void)pause;

/**
 *	@brief	停止播放
 *
 *  @discussion
 *  此时播放器状态为:NELPMoviePlaybackStateStopped
 *
 *	@return	无
 */
- (void)stop;

/**
 *	@brief	停止播放，并释放播放器相关资源
 *
 *  @discussion
 *  在播放器退出时，需要调用该方法用于释放资源。\\\n
 *  若在播放过程中需要切换URL，首先需要调用该方法停止播放，然后调用removeFromSuperview 将view移除，再初始化，prepareToPlay，最后调用play方法。
 *
 *	@return	无
 */
- (void)shutdown;

/**
 *	@brief	设置播放器切入后台后的播放状态
 *
 *  @discussion
 *  若设置后台暂停，则在切入后台后播放器处于暂停状态，回到前台需要手动播放\\\n
 *  若设置后台继续播放，则在切入后台后音频继续播放，回到前台后音视频正常播放
 *
 *	@param 	pause 	YES：后台暂停 NO：继续播放
 *
 *	@return	无
 */
- (void)setPauseInBackground:(BOOL)pause;

/**
 *	@brief	设置显示模式.
 *
 *  @param  aScalingMode 显示模式.
 *
 *  @discussion 共有以下4种显示模式，详见 NELPMovieScalingMode \\\n
 *  NELPMovieScalingModeNone,       //!< 无缩放  \\\n
 *  NELPMovieScalingModeAspectFit,  //!< 等比例缩放，某一边会有黑边填充  \\\n
 *  NELPMovieScalingModeAspectFill, //!< 等比例缩放，某一边可能会被裁减  \\\n
 *  NELPMovieScalingModeFill        //!< 全屏显示，画面宽高比可能与视频原始宽高比不一致
 *
 *	@return	无.
 */
- (void)setScalingMode: (NELPMovieScalingMode) aScalingMode;

/**
 *	@brief	播放过程中实时开启和关闭音频输出
 *
 *	@param 	isMute 	YES：开启音频输出 NO：关闭音频输出
 *
 *	@return	无
 */
- (void)setMute :(BOOL)isMute;

/**
 *	@brief	设置是否开启硬件解码，仅IOS 8.0以上支持，默认开启，如果开启失败会自动切换到软件解码
 *
 *  @param 	isOpen 	YES：开启硬件解码 NO：关闭硬件解码
 *
 *	@return	无
 */
- (void)setHardwareDecoder :(BOOL)isOpen;

/**
 *	@brief	截图
 *
 *	@return	截图结果，以UIImage格式保存
 */
- (UIImage *)getSnapshot;

/**
 *	@brief	获取视频信息
 *
 *	@param 	videoInfo 	保存音频信息
 *
 *  @discussion
 *  调用prepareToPlay方法后，播放器发出NELivePlayerDidPreparedToPlayNotification通知后，调用该方法才能获取到有效的视频信息。
 *
 *	@return	无
 */
- (void)getVideoInfo :(NELPVideoInfo *)videoInfo;

/**
 *	@brief	获取音频信息
 *
 *	@param 	audioInfo 	保存音频信息
 *
 *  @discussion
 *  调用prepareToPlay方法后，播放器发出NELivePlayerDidPreparedToPlayNotification通知后，调用该方法才能获取到有效的音频信息。
 *
 *	@return	无
 */
- (void)getAudioInfo :(NELPAudioInfo *)audioInfo;

/**
 *	@brief	获取当前解码库版本号
 *
 *	@return	解码库版本号
 */
- (NSString *)getSDKVersion;




/**
 *	@brief	用于显示的view (只读)
 *
 *  @discussion 该view中不包含播放控制组件，只用于显示视频图像
 */
@property(nonatomic, readonly)  UIView *view;

/**
 * @brief 当前视频文件是否完成初始化（只读）
 *
 * @discussion
 *
 * 调用prepareToPlay方法后，如果播放器完成视频文件的初始化，会发送NELivePlayerDidPreparedToPlayNotification通知，并将isPreparedToPlay置为YES。
 *
 * @see prepareToPlay
 */
@property(nonatomic, readonly)  BOOL isPreparedToPlay;

/**
 *	@brief	设置播放器初始化视频文件完成后是否自动播放，默认自动播放
 *
 *  @param 	shouldAutoplay 	YES：自动播放 NO：手动播放
 *
 *  @discussion 当设置为YES后，则在调用prepareToPlay初始化视频文件完成后会自动调用play方法进行播放
 *
 *	@return	无
 */
@property(nonatomic)            BOOL shouldAutoplay;

/**
 *	@brief	设置当前播放时间点(用于seek操作)以及获取当前播放的时间点
 *
 *	@param 	aCurrentPlaybackTime 	当前要播放的时间点(单位：秒)
 *
 *  @discussion
 *  需要在播放器发送NELivePlayerDidPreparedToPlayNotification通知后，才能调用该set方法设置到某一时间点播放，\\\n
 *  此时isPreparedToPlay的值为 YES
 *
 *	@return	get操作返回的是当前播放的时间点
 *
 *  @see isPreparedToPlay
 */
@property(nonatomic)            NSTimeInterval currentPlaybackTime;

/**
 *	@brief	获取多媒体文件总时长(单位: 秒) (只读)
 *
 *  @discussion
 *  调用prepareToPlay方法后，不能立即获得duration值。只有在播放器发送NELivePlayerDidPreparedToPlayNotification通知后，获取的duration值才有效，\\\n
 *  这也意味着isPreparedToPlay值为YES时，duration值才有效。\\\n
 *
 *  如果播放的是直播视频，则duration值为0。
 *
 *	@return	多媒体文件总时长(单位: 秒)
 *
 *  @see isPreparedToPlay
 */
@property(nonatomic, readonly)  NSTimeInterval duration;

/**
 *	@brief	获取当前可播放的视频时长(单位：秒) (只读)
 *
 *  @discussion 当播放网络视频时，该值表示已经缓冲的视频的最大时长，若此时网络端开，则只能播放到该时刻为止。
 *
 *	@return	当前缓冲时长(单位：秒)
 */
@property(nonatomic, readonly)  NSTimeInterval playableDuration;

/**
 *	@brief	获取当前播放状态 (只读)
 *
 *  @discussion 共有以下5种状态，详见 NELPMoviePlaybackState。
 *
 *  NELPMoviePlaybackStateStopped, // 停止状态 \\\n
 *  NELPMoviePlaybackStatePlaying, // 播放状态 \\\n
 *  NELPMoviePlaybackStatePaused,  // 暂停状态，可调play继续播放 \\\n
 *  NELPMoviePlaybackStateSeeking  // Seek状态 \\\n
 *
 *  播放状态的变换如下：\\\n
 *
 *  播放器调用initWithContentURL方法后处于NELPMoviePlaybackStateStopped状态，\\\n
 *  调用prepareToPlay方法，如果完成对视频文件的初始化则进入NELPMoviePlaybackStatePlaying状态；\\\n
 *  当调用setCurrentPlaybackTime方法时转成NELPMoviePlaybackStateSeeking状态，\\\n
 *  调用pause方法转NELPMoviePlaybackStatePaused状态，调用stop方法转到NELPMoviePlaybackStateStopped状态。
 *
 *	@return	当前播放状态
 */
@property(nonatomic, readonly)  NELPMoviePlaybackState playbackState;

/**
 *	@brief	获取当前加载状态 (只读)
 *
 *  @discussion 共有以下4种加载状态，详见 NELPMovieLoadState
 *
 *  NELPMovieLoadStatePlayable       = 1 << 0, // 在该状态下，播放器初始化完成，可以播放，若shouldAutoplay 设置成YES，播放器初始化完成后会自动播放 \\\n
 *  NELPMovieLoadStatePlaythroughOK  = 1 << 1, // 在该状态下，在网络不好的情况下缓冲完成，可以播放 \\\n
 *  NELPMovieLoadStateStalled        = 1 << 2, // 在播放过程中网络不好需要缓冲数据的时候播放会自动暂停 \\n
 *
 *  加载状态的变换如下：\\\n
 *  调用prepareToPlay方法，当视频文件初始化完成后，播放器会收到NELivePlayerLoadStateChangedNotification通知，此时的加载状态为 NELPMovieLoadStatePlayable \\\n
 *  当播放器需要缓冲的时候，缓冲开始时，播放会暂停，此时播放器会收到NELivePlayerLoadStateChangedNotification通知，此时的加载状态为 NEPMovieLoadStateStalled \\\n
 *  当缓冲结束时，播放会继续，此时播放器会收到NELivePlayerLoadStateChangedNotification通知，此时的加载状态为 NELPMovieLoadStatePlaythroughOK
 *
 *	@return	当前加载状态
 */
@property(nonatomic, readonly)  NELPMovieLoadState loadState;


#pragma mark Notifications

#ifdef __cplusplus
#define NELP_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define NELP_EXTERN extern __attribute__((visibility ("default")))
#endif

///调用prepareToPlay后，播放器初始化视频文件完成后的消息通知
NELP_EXTERN NSString *const NELivePlayerDidPreparedToPlayNotification;
///播放器加载状态发生改变时的消息通知
NELP_EXTERN NSString *const NELivePlayerLoadStateChangedNotification;
///播放器播放完成或播放发生错误时的消息通知
NELP_EXTERN NSString *const NELivePlayerPlaybackFinishedNotification;
///播放器播放状态发生改变时的消息通知
NELP_EXTERN NSString *const NELivePlayerPlaybackStateChangedNotification;
///播放器解码器打开后的消息通知，指示硬件解码是否开启
NELP_EXTERN NSString *const NELivePlayerHardwareDecoderOpenNotification;
///播放器第一帧视频显示时的消息通知
NELP_EXTERN NSString *const NELivePlayerFirstVideoDisplayedNotification;
///播放器资源释放完成时的消息通知
NELP_EXTERN NSString *const NELivePlayerReleaseSueecssNotification;

@end

