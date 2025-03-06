#pragma once

#include <Arduino.h>

const String framePrefix[] = {
    "Engine",
    "Air",
    "Battery",
    "",
    "OVERHEAT",
    "BATTERY",
    "READY!",
    "M1NSK"
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
 const uint8_t frameType_size = 8;

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
        Frame();

        void attachValuePtr(float const *valuePtr);     // Add pointer to dynamic value that will be displayed
        void setContent(uint8_t contentId);             // Change string lines by integer id
        uint8_t rotateContent();                        // Change string lines iteratively, return selected id
        void setGeometry(const FrameGeom &geometry);    // Set frame's position and size

        FrameOutputData getFrameOutputData() const;     // Return data that is used to draw the contents with u8x8
        uint8_t getContentId() const;                   // Returns current content id
        bool isEmpty() const;                           // Checks if current content == EMPTY

        void directDraw();                              //ToDo (or not)

    private:
        FrameGeom geometry_;
        uint8_t contentId_;
        float const *valuePtr_;  // We don't want to be able to modify this thing
        String const *prefix_;
        String const *postfix_;

        void updateStringLines();
};