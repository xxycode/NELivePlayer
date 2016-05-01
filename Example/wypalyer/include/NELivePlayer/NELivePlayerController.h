/*
 *  NELivePlayerController.h
 *  NELivePlayer
 *
 *  Created by Netase on 15-9-21.
 *  Copyright (c) 2015年 Netease. All rights reserved.
 *
 *  This file is part of LivePlayer.
 *
 */

#import "NELivePlayer.h"

/*! \file */

/**
 *	@brief	log级别
 */
typedef enum NELPLogLevel
 {
    NELP_LOG_DEFAULT = 1, //!< log输出模式：输出详细

    NELP_LOG_VERBOSE = 2, //!< log输出模式：输出详细
    NELP_LOG_DEBUG   = 3, //!< log输出模式：输出调试信息
    NELP_LOG_INFO    = 4, //!< log输出模式：输出标准信息
    NELP_LOG_WARN    = 5, //!< log输出模式：输出警告
    NELP_LOG_ERROR   = 6, //!< log输出模式：输出错误
    NELP_LOG_FATAL   = 7, //!< log输出模式：一些错误信息，如头文件找不到，非法参数使用
    NELP_LOG_SILENT  = 8, //!< log输出模式：不输出
} NELPLogLevel;


@interface NELivePlayerController : NSObject <NELivePlayer>


/**
 *	@brief	初始化播放器，输入播放文件路径
 *
 *	@param 	aUrl 	播放文件的路径
 *
 *	@return	返回播放器实例
 */
- (id)initWithContentURL:(NSURL *)aUrl;

/**
 *	@brief	设置log级别
 *
 *	@param 	logLevel 	log级别
 *
 *	@return	无
 */
+ (void)setLogLevel:(NELPLogLevel)logLevel;

@end

