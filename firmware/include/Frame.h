#pragma once

#include <Arduino.h>

#include "DataConnector.h"

class DataConnector;

const String framePrefix[] = {
    "Engine",
    "Air",
    "Battery",
    "",
    "OVERHEAT",
    "BATTERY",
    "READY!",
    MSG_GREET
};

const String framePostfix[] = {
    "C",
    "C",
    "V",
    "",
    "",
    "",
    "",
    ""
};

enum FrameContentId {
    ENGINE,
    AIR,
    BATTERY,
    EMPTY,
    OVERHEAT,
    BATT_PROBLEM,
    RTG,
    GREETING
};
 const uint8_t FrameContentId_size = 8;

 struct FrameGeom {   // Symbols (8x8 squares), not pixels
    uint8_t width, height, hpos;   
};

 struct FrameOutputData {   // Symbols (8x8 squares), not pixels
    String topLineText, botLineText;
    uint8_t topLineScale, botLineScale;
    uint8_t topLinePosX, topLinePosY, botLinePosX, botLinePosY;    
};

class Frame {
    public:
        Frame(DataConnector *dc=nullptr);

        void setContent(uint8_t contentId);             // Change string lines by integer id
        uint8_t switchContent();                        // Change string lines iteratively, return selected id
        void setGeometry(FrameGeom const &geometry);    // Set frame's position and size

        FrameOutputData getFrameOutputData() const;     // Return data that is used to draw the contents with u8x8
        FrameGeom getFrameGeometry() const;
        uint8_t getContentId() const;                   // Returns current content id
        bool isEmpty() const;                           // Checks if current content == EMPTY

        void directDraw();                              //ToDo (or not)

    private:
        FrameGeom geometry_;
        uint8_t contentId_;
        DataConnector *dc_;      // This thing will change value pointer and text info
        float const *valuePtr_;  // We don't want to be able to modify this thing, only to change the address
        String const *prefix_;
        String const *postfix_;

        void updateStringLines_();
};