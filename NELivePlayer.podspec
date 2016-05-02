

Pod::Spec.new do |s|


  s.name         = "NELivePlayer"
  s.version      = "0.0.4"
  s.summary      = "NELivePlayer, can play rtmp hls"

  s.description  = <<-DESC
                    网易直播云播放器SDK 支持rtmp hls 播放，低延迟，高可定制
                   DESC
  s.homepage     = "http://dev.netease.im/docs?doc=iOS_LivePlayer"
  s.license      = { :type => 'Apache License, Version 2.0', :text => <<-LICENSE
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
    LICENSE
  }
  s.author             = { "Xiaoxueyuan" => "xxyc15@me.com" }
 s.platform     = :ios, "7.0"
  s.source       = { :git => "https://github.com/xxycode/NELivePlayer.git", :tag => "0.0.4" }
  s.source_files  =  "Pod/NELivePlayer/include/**/*.h"
  s.requires_arc = true
  s.public_header_files = "Pod/NELivePlayer/include/**/*.h"
  s.frameworks = ["CoreAudio", "CoreMedia", "AVFoundation", "VideoToolBox", "AudioToolBox", "OpenGLES", "Foundation", "QuartzCore", "CoreGraphics", "CFNetwork", "CoreTelephony","SystemConfiguration"]

  s.libraries = "iconv", "z", "bz2" ,"stdc++"

  s.default_subspec = "precompiled"

  s.subspec "precompiled" do |ss|
    ss.preserve_paths         = "Pod/NELivePlayer/include/**/*.h"
    ss.vendored_libraries   = "Pod/NELivePlayer/libs/*.a"
    ss.xcconfig = { 'HEADER_SEARCH_PATHS' => "${PODS_ROOT}/#{s.name}/" }
  end

end
