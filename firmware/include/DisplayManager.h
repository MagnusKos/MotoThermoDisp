#pragma once

#include <U8x8lib.h>

#include "config.h"
#include "pins.h"
#include "Frame.h"
#include "DataConnector.h"

class DataConnector;

enum MoveDir {
    TOLEFT,
    TORIGHT
};

class DisplayManager {
    public:
        DisplayManager(DISP_TYPE * const u8x8_ext, DataConnector * const dc);

        void switchLFrame();
        void switchRFrame();
        void showWarning(uint8_t warningId);

        void draw();
        void drawDirect(const char *s);
    private:
        DISP_TYPE * const u8x8_; // Needs inspection, i'd like to create this thing inside the class
        DataConnector * const dc_;
        uint8_t dispSizeX_, dispSizeY_;
        Frame frameL_, frameR_, frameW_; // Three frames: Left, Right, Warning (invisible)

        void drawFrame_(const Frame &frame);        // Puts frame's data on the display
        void expandFrame_(Frame &frame);            // Expand the frame in x-direction
        void shrinkFrame_(Frame &frame);            // Resize the frame in half in x-direction
        void moveFrame_(Frame &frame, uint8_t dir); // Absolute positioning

};