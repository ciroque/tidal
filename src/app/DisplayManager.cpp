//
// Created by swagner on 10/3/20.
//

#include "DisplayManager.h"
#include "graphLib.h"
#include "src/app/models/DisplayData.h"
#include "FrameBufferOpenException.h"
#define XTESTING

using namespace boost::adaptors;

static inline float CircEquat(float rsqr, float x)
{
	return sqrt(rsqr - (x * x));
}

void DisplayManager::DrawMoonPhase(float centerx, float centery, float radius, float phase)
{
    radius *= SCALEFACTOR;
    float rsquared = radius * radius;
    float a = tan(phase) * radius;
    float b = sqrt(rsquared + (a * a));
    b *= b;
    float sign = (a >= 0) ? 1.0f : -1.0f;
    float side = fmod(phase, 2 * M_PI) > M_PI ? -1 : 1;
    for(int i = -radius; i < radius; i++){
        float edgex = CircEquat(rsquared, i) * side;
        float midx = CircEquat(b, i) * sign - a;
        drawline(superSample, SUPERAD + midx, SUPERAD + i, SUPERAD + edgex, SUPERAD + i, 0xE0E0E0);
    }
    scaleBitmap(normalSample, superSample);
    LGL_cls(superSample);
    copyBitmap(buffer, normalSample, centerx - MOONRAD, centery - MOONRAD);
}

void DisplayManager::CopyBuffer()
{
    const std::string FrameBufferName = "/dev/fb0";

#ifdef XTESTING
    FILE *frameBuffer = fopen("/tmp/fb", "w");
#else
    FILE *frameBuffer = fopen(FrameBufferName.c_str(), "w");
#endif
    if(frameBuffer == nullptr) {
        throw FrameBufferOpenException(FrameBufferName);
    }

    fwrite(buffer->fb, sizeof(int), buffer->size, frameBuffer);
    fclose(frameBuffer);
}

void DisplayManager::Render(DisplayData displayData) {
    LGL_cls(buffer);
    static int daysToDisplay = displayData.dailyPredictions.size();	/*How many channels do we need on-screen*/
    static int channelWidth = buffer->width / daysToDisplay;
    static int halfChannelWidth = channelWidth / 2;	/*Middle of the channel*/
    int oldx = -10, oldy = 200;	/*Used for rendering tide level lines*/
    char stringBuf[64];	/*Buffer for writing strings to*/
    float curLevel;	/*Current tide level*/

    /*Background rendering*/
    horizontalLine(buffer, 0, 1024, 170, 0x0000FF);
    horizontalLine(buffer, 0, 1024, 222, 0x0000FF);
    horizontalLine(buffer, 0, 1024, 350, 0x0000FF);

    for(auto prediction : displayData.dailyPredictions | indexed()) {
	int channelPos = prediction.index() * channelWidth;	/*Current channel position*/
	int xoffset = channelPos + halfChannelWidth;	/*Middle of current channel*/
	auto day = prediction.value();	/*Easy accessor*/

	/*Line stuff*/
	verticalLine(buffer, channelPos, 0, 360, 0x0000FF);

	/*Moon rendering*/
	DrawMoonPhase(xoffset, 90, 50, M_PI * 2 * day.GetLunarData().phase);
	std::snprintf(stringBuf, sizeof(stringBuf), "%.2f%%", day.GetLunarData().visible * 100.0f);
	int strOff = strlen(stringBuf) * 5;	/*Half pixel length for string*/
	drawString(buffer, stringBuf, xoffset - strOff, 150, 0x0000FF);
	std::snprintf(stringBuf, sizeof(stringBuf), "%d/%d", day.GetDate().tm_mon + 1, day.GetDate().tm_mday);
	strOff = strlen(stringBuf) * 10;	/*Half pixel length for big string*/
	drawBigString(buffer, stringBuf, xoffset - strOff, 10, 0x0000FF);

	/*Tide rendering*/
	auto tideLevels = day.GetTideData().getTideLevels();
	float tidePointSpacing = (float)channelWidth / (float)tideLevels.size();
	float highTide = day.GetTideData().getHighestTideLevel().getValue();
	float lowTide = day.GetTideData().getLowestTideLevel().getValue();
	auto highTime = day.GetTideData().getHighestTideLevel().getTimestamp();
	auto lowTime = day.GetTideData().getLowestTideLevel().getTimestamp();
	for(auto tdat : tideLevels | indexed()) {
	    auto tideData = tdat.value();	/*Easy accessor*/
	    float level = tideData.getValue();
	    auto time = tideData.getTimestamp();
	    int ypoint = 340 - level * 10;	/*Y coord of tide level on-screen*/
	    int xpoint = channelPos + tidePointSpacing * tdat.index();	/*Same as above but for x*/
	    drawline(buffer, oldx, oldy, xpoint, ypoint, 0x8080FF);
	    oldx = xpoint; oldy = ypoint;	/*Update old coords*/
	    if(time.tm_hour == 6  |
	       time.tm_hour == 12 |
	       time.tm_hour == 18)
		    verticalLine(buffer, xpoint, 350, 222, 0x000060);
	    int bottom = (time.tm_hour % 6) == 0 ? 370 : 360;
	    verticalLine(buffer, xpoint, 350, bottom, 0x0000FF);	/*Hourly tick mark*/
	    if(level == highTide) {	/*High tide tick*/
		verticalLine(buffer, xpoint, bottom, ypoint, 0x00FF00);
	    }else if(level == lowTide) {	/*Low tide tick*/
		verticalLine(buffer, xpoint, bottom, ypoint, 0xFF0000);
	    }
	    if((prediction.index() == 0) && (time.tm_hour == displayData.hour))
		    curLevel = level;
	}
	/*Prints highest tide level and time*/
	drawString(buffer, "high:", channelPos + 5, 175, 0x0000FF);
	std::snprintf(stringBuf, sizeof(stringBuf), "%.3f' @ %02d00", highTide, highTime.tm_hour);
	drawString(buffer, stringBuf, channelPos + 5, 185, 0x0000FF);

	/*Prints lowest tide level and time*/
	drawString(buffer, "low:", channelPos + 5, 200, 0x0000FF);
	std::snprintf(stringBuf, sizeof(stringBuf), "%.3f' @ %02d00", lowTide, lowTime.tm_hour);
	drawString(buffer, stringBuf, channelPos + 5, 210, 0x0000FF);
    }

    /*Render current tide mark and print level*/
    auto curTideLevels = displayData.dailyPredictions.at(0).GetTideData().getTideLevels();
    float xoffset = (float)(displayData.hour * channelWidth) / curTideLevels.size();

    /*Draws yellow arrow pointing at current tide*/
    verticalLine(buffer, xoffset, 375, 390, 0xFFFF00);
    drawline(buffer, xoffset, 375, xoffset + 5, 380, 0xFFFF00);
    drawline(buffer, xoffset, 375, xoffset - 5, 380, 0xFFFF00);

    /*Prints current level*/
    std::snprintf(stringBuf, sizeof(stringBuf), "cur: %.3f\'", curLevel);
    int strOff = strlen(stringBuf) * 5;
    strOff = xoffset < strOff ? xoffset - 5 : strOff;
    drawString(buffer, stringBuf, xoffset - strOff, 395, 0x0000FF);

    drawBigString(buffer, "Mystic Rhythms", 2, 750, 0xFF00FF);

    CopyBuffer();
}

DisplayManager::DisplayManager() = default;
