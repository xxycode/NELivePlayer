//
//  ViewController.m
//  wypalyer
//
//  Created by Xiaoxueyuan on 16/4/30.
//  Copyright © 2016年 Xiaoxueyuan. All rights reserved.
//

#import "ViewController.h"
#import "NELivePlayerController.h"

@interface ViewController ()

@property (nonatomic, strong) NELivePlayerController *player;

@property (nonatomic, strong) NELivePlayerController *player2;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.player = [[NELivePlayerController alloc] initWithContentURL:[NSURL URLWithString:@"rtmp://pili-live-rtmp.test.xxycode.com/test_xiaoyang/5723aae6eb6f92347407f6c1"]];
    [self.player SetBufferStrategy:NELPLowDelay];
    [self.player setHardwareDecoder:YES];
    [self.player setScalingMode:NELPMovieScalingModeFill];
    [self.player setPauseInBackground:NO];
    CGFloat width = [UIScreen mainScreen].bounds.size.width;
    self.player.view.frame = CGRectMake(0, 0, width, width * 0.75);
    [self.view addSubview:self.player.view];
    [self.player setShouldAutoplay:YES];
    [self.player prepareToPlay];
    
    
//    self.player2 = [[NELivePlayerController alloc] initWithContentURL:[NSURL URLWithString:@"rtmp://live.hkstv.hk.lxdns.com/live/hks"]];
//    [self.player2 SetBufferStrategy:NELPLowDelay];
//    [self.player2 setHardwareDecoder:YES];
//    [self.player2 setScalingMode:NELPMovieScalingModeFill];
//    [self.player2 prepareToPlay];
//    [self.player2 setPauseInBackground:NO];
//    self.player2.view.frame = CGRectMake(0, 500, 400, 300);
//    [self.view addSubview:self.player2.view];
//    [self.player2 setShouldAutoplay:YES];
    [[UIApplication sharedApplication] beginReceivingRemoteControlEvents];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
