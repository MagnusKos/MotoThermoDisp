#include "DisplayManager.h"

DisplayManager::DisplayManager(DISP_TYPE * const u8x8_ext, DataConnector * const dc) :
    u8x8_(u8x8_ext),
    dc_{dc},
    frameL_{dc},
    frameR_{dc},
    frameW_{dc}
{ 
    u8x8_->setFont(u8x8_font_amstrad_cpc_extended_r);
    dispSizeX_ = u8x8_->getCols();
    dispSizeY_ = u8x8_->getRows();

    FrameGeom initGeom {dispSizeX_, dispSizeY_, 0};

    frameL_.setGeometry(initGeom);
    frameL_.setContent(EMPTY);
    frameR_.setGeometry(initGeom);
    frameR_.setContent(ENGINE);
}

void DisplayManager::drawFrame_(Frame const &frame) {
    if (frame.getContentId() != EMPTY) {
        FrameOutputData frData;
        frData = frame.getFrameOutputData();

        void (U8X8::*drawStringFunc)(uint8_t, uint8_t, const char *);
        drawStringFunc = (frData.topLineScale == 1) ? &U8X8::drawString : &U8X8::draw1x2String; // Scale selection
        (u8x8_->*drawStringFunc)(frData.topLinePosX, frData.topLinePosY, frData.topLineText.c_str()); // Write a string
        drawStringFunc = (frData.botLineScale == 1) ? &U8X8::drawString : &U8X8::draw1x2String; // Scale selection
        (u8x8_->*drawStringFunc)(frData.botLinePosX, frData.botLinePosY, frData.botLineText.c_str()); // Write a string

    }
}

void DisplayManager::expandFrame_(Frame &frame) {
    frame.setGeometry(
        FrameGeom {
            dispSizeX_, dispSizeY_, 0
        }
    );
}

void DisplayManager::shrinkFrame_(Frame &frame) {
    frame.setGeometry(
        FrameGeom {
            static_cast<uint8_t>(dispSizeX_ / 2), dispSizeY_, 0
        }
    );
}

void DisplayManager::moveFrame_(Frame &frame, uint8_t dir) {
    FrameGeom geomCur = frame.getFrameGeometry();
    uint8_t hposNew = (dir == TORIGHT) ? dispSizeX_ / 2 - 1 : 0; // Too stupid, but hey, we have only two dirs in x-axis
    frame.setGeometry(
        FrameGeom {
            geomCur.width, geomCur.height, hposNew
        }
    );
}

void DisplayManager::draw() {
    u8x8_->clearDisplay();
    drawFrame_(frameL_);
    drawFrame_(frameR_);
    u8x8_->refreshDisplay();
 }

void DisplayManager::drawDirect(const char *s) {
    u8x8_->clearDisplay();
    u8x8_->draw1x2String(1, 1, s);
 }

void DisplayManager::switchLFrame() {
    frameL_.switchContent();
    if (frameR_.isEmpty())
        expandFrame_(frameL_);
    else {
        shrinkFrame_(frameL_);
        moveFrame_(frameL_, TOLEFT);
        shrinkFrame_(frameR_);
        moveFrame_(frameR_, TORIGHT);
    }
    if (frameL_.isEmpty())      // A gentleman's rule, in case of emptying the frame
        expandFrame_(frameR_);
}

void DisplayManager::switchRFrame() {
    frameR_.switchContent();
    if (frameL_.isEmpty())
        expandFrame_(frameR_);
    else {
        shrinkFrame_(frameR_);
        moveFrame_(frameR_, TORIGHT);
        shrinkFrame_(frameL_);
        moveFrame_(frameL_, TOLEFT);
    }
    if (frameR_.isEmpty())      // A gentleman's rule, in case of emptying the frame
        expandFrame_(frameL_);
 }