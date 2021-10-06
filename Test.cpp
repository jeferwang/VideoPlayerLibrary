#include <string>
#include <iostream>
#include "VPLib.h"
#include "Logger/ConsoleLogWriter.h"
#include "lodepng.h"

int main() {
    // add a LoggerWriter
    auto ConsoleWriter = new VP::Logger::ConsoleLogWriter();
    VP::Logger::Log::RegisterLogger(ConsoleWriter);

    // init VideoPlayer
    std::string Url = "D:/Projects/XDance1.0/Client/Assets/Resources/DanceVideos/jiuzuidehudiezuo/jiuzuidehudiezuo.mp4";
    VP::Player P;
    P.Init(Url.c_str());
    P.SetFrameUpdateCallback([&P](void *ImageData, int32_t FrameIndex, int64_t FramePTS, int32_t Width, int32_t Height, int32_t LineSize) {
        char FileName[256] = {'\0'};
        std::snprintf(FileName, 256, "D:/Projects/VPLib/Frame/%d.png", FrameIndex);
        unsigned error = lodepng_encode32_file(FileName, (uint8_t *) ImageData, P.GetWidth(), P.GetHeight());
        VP::Logger::Log::Write(VP::Logger::LogLevel::Info, "lodepng_encode32_file error=%d", error);
    });
    P.Play();

    std::this_thread::sleep_for(std::chrono::duration<double>(10));

    return 0;
}