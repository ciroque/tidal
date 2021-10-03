//
// Created by swagner on 10/3/20.
//

#include "DisplayManager.h"
#include "graphLib.h"
#include "src/app/models/DisplayData.h"
//#define XTESTING

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
#ifdef XTESTING
    FILE *frameBuffer = fopen("/tmp/fb", "w");
#else
    FILE *frameBuffer = fopen("/dev/fb0", "w");
#endif
    if(!frameBuffer)
        throw("Could not open frameBuffer");
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
    horizontalLine(buffer, 0, 1024, 350, 0x0000FF);

    for(auto prediction : displayData.dailyPredictions | indexed()) {
	int channelPos = prediction.index() * channelWidth;	/*Current channel position*/
	int xoffset = channelPos + halfChannelWidth;	/*Middle of current channel*/
	auto day = prediction.value();	/*Easy accessor*/

	/*Line stuff*/
	verticalLine(buffer, channelPos, 0, 360, 0x0000FF);

	/*Moon rendering*/
	DrawMoonPhase(xoffset, 90, 50, M_PI * 2 * day.lunarData.phase);
	std::snprintf(stringBuf, sizeof(stringBuf), "%f", day.lunarData.visible);
	int strOff = strlen(stringBuf) * 5;	/*Half pixel length for string*/
	drawString(buffer, stringBuf, xoffset - strOff, 150, 0x0000FF);
	std::snprintf(stringBuf, sizeof(stringBuf), "%d/%d", day.date.tm_mon + 1, day.date.tm_mday);
	strOff = strlen(stringBuf) * 10;	/*Half pixel length for big string*/
	drawBigString(buffer, stringBuf, xoffset - strOff, 10, 0x0000FF);

	/*Tide rendering*/
	auto tideLevels = day.tideData.getTideLevels();
	float tidePointSpacing = (float)channelWidth / (float)tideLevels.size();
	float highTide = day.tideData.getHighestTideLevel().getValue();
	float lowTide = day.tideData.getLowestTideLevel().getValue();
	auto highTime = day.tideData.getHighestTideLevel().getTimestamp();
	auto lowTime = day.tideData.getLowestTideLevel().getTimestamp();
	for(auto tdat : tideLevels | indexed()) {
	    auto tideData = tdat.value();	/*Easy accessor*/
	    float level = tideData.getValue();
	    auto time = tideData.getTimestamp();
	    int ypoint = 340 - level * 10;	/*Y coord of tide level on-screen*/
	    int xpoint = channelPos + tidePointSpacing * tdat.index();	/*Same as above but for x*/
	    drawline(buffer, oldx, oldy, xpoint, ypoint, 0x8080FF);
	    oldx = xpoint; oldy = ypoint;	/*Update old coords*/
	    verticalLine(buffer, xpoint, 350, 360, 0x0000FF);	/*Hourly tick mark*/
	    if(level == highTide) {	/*High tide tick*/
	    	verticalLine(buffer, xpoint, 360, ypoint, 0x00FF00);
	    }else if(level == lowTide) {	/*Low tide tick*/
	    	verticalLine(buffer, xpoint, 360, ypoint, 0xFF0000);
	    }
	    if((prediction.index() == 0) && (time.tm_hour == displayData.hour))
		    curLevel = level;
	}
	/*Prints highest tide level and time*/
	std::snprintf(stringBuf, sizeof(stringBuf), "high @ %02d00:", highTime.tm_hour);
	drawString(buffer, stringBuf, channelPos + 5, 175, 0x0000FF);
	std::snprintf(stringBuf, sizeof(stringBuf), "%.3f feet", highTide);
	drawString(buffer, stringBuf, channelPos + 5, 185, 0x0000FF);

	/*Prints lowest tide level and time*/
	std::snprintf(stringBuf, sizeof(stringBuf), "low @ %02d00:", lowTime.tm_hour);
	drawString(buffer, stringBuf, channelPos + 5, 200, 0x0000FF);
	std::snprintf(stringBuf, sizeof(stringBuf), "%.3f feet", lowTide);
	drawString(buffer, stringBuf, channelPos + 5, 210, 0x0000FF);
    }

    /*Render current tide mark and print level*/
    auto curTideLevels = displayData.dailyPredictions.at(0).tideData.getTideLevels();
    float xoffset = (float)(displayData.hour * channelWidth) / curTideLevels.size();

    /*Draws yellow arrow pointing at current tide*/
    verticalLine(buffer, xoffset, 365, 380, 0xFFFF00);
    drawline(buffer, xoffset, 365, xoffset + 5, 370, 0xFFFF00);
    drawline(buffer, xoffset, 365, xoffset - 5, 370, 0xFFFF00);

    /*Prints current level*/
    std::snprintf(stringBuf, sizeof(stringBuf), "cur: %.3f\'", curLevel);
    int strOff = strlen(stringBuf) * 5;
    strOff = xoffset < strOff ? xoffset - 5 : strOff;
    drawString(buffer, stringBuf, xoffset - strOff, 385, 0x0000FF);

    drawBigString(buffer, "Mystic Rhythms", 2, 750, 0xFF00FF);

    CopyBuffer();
}

DisplayManager::DisplayManager() = default;
