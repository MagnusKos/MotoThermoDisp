#include "Frame.h"

Frame::Frame():
    geometry_{},
    contentId_{ENGINE},
    valuePtr_{nullptr},
    prefix_{&framePrefix[ENGINE]},
    postfix_{&framePostfix[ENGINE]}
    { }

void Frame::attachValuePtr(float const *valuePtr) {
    if (valuePtr != nullptr)
        valuePtr_ = valuePtr;
}

void Frame::updateStringLines() {
    prefix_ = &framePrefix[contentId_];
    postfix_ = &framePostfix[contentId_];
}

void Frame::setContent(uint8_t contentId) {
    if (0 <= contentId && contentId < frameType_size) {
        contentId_ = contentId;
        updateStringLines();
    }
}

uint8_t Frame::rotateContent() {
    contentId_ = (contentId_ + 1) & 0x03; // Rotation is in range [0..3], so let's use some bit magic
    updateStringLines();
    return contentId_;
}

void Frame::setGeometry(const FrameGeom &geometry) {
    geometry_ = geometry;       // Ye good ol' structure copying
}

uint8_t Frame::getContentId() const {
    return contentId_;
}

bool Frame::isEmpty() const {
    return (contentId_ == EMPTY);
}

FrameOutputData Frame::getFrameOutputData() const {
    String valueStr = String((valuePtr_ == nullptr) ? -42.0 : *valuePtr_, 1); // An ugly way to put a placeholder
    valueStr += *postfix_;
    return FrameOutputData {
        *prefix_,                                       // Top line string
        valueStr,                           // Bot line string
        static_cast<uint8_t>(contentId_ <= 2 ? 1 : 2),  // VScale of the top line
        static_cast<uint8_t>(contentId_ > 2 ? 1 : 2),   // VScale of the bot line
        static_cast<uint8_t>(geometry_.hpos + (geometry_.width - prefix_->length()) / 2), // Top line xpos, center placement
        0,                                              // Top line ypos
        static_cast<uint8_t>(geometry_.hpos + (geometry_.width - valueStr.length()) / 2), // Bot line xpos, center placement
        2                                               // Bot line ypos
    };
}