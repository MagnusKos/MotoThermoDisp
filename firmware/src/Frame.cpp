#include "Frame.h"

Frame::Frame(DataConnector *dc):
    geometry_{},
    contentId_{ENGINE},
    dc_{dc},
    valuePtr_{nullptr},
    prefix_{&framePrefix[ENGINE]},
    postfix_{&framePostfix[ENGINE]}
    { }

void Frame::updateStringLines_() {
    prefix_ = &framePrefix[contentId_];
    postfix_ = &framePostfix[contentId_];
}

void Frame::setContent(uint8_t contentId) {
    if (0 <= contentId && contentId < FrameContentId_size) {
        contentId_ = contentId;
        if (dc_ != nullptr)
            dc_->reconnect(this, valuePtr_);    // Change valuePtr with a help of the helper object
        updateStringLines_();
    }
}

uint8_t Frame::switchContent() {
    contentId_ = (contentId_ + 1) & 0x03; // Rotation is in range [0..3], so let's use some bit magic
    if (dc_ != nullptr)
            dc_->reconnect(this, valuePtr_);    // Change valuePtr with a help of the helper object
    updateStringLines_();
    return contentId_;
}

void Frame::setGeometry(FrameGeom const &geometry) {
    geometry_ = geometry;       // Ye good ol' structure copying
}

uint8_t Frame::getContentId() const {
    return contentId_;
}

FrameGeom Frame::getFrameGeometry() const {
    return geometry_;
}

bool Frame::isEmpty() const {
    return (contentId_ == EMPTY);
}

FrameOutputData Frame::getFrameOutputData() const {
    String valueStr;
    if (valuePtr_ == nullptr)
        valueStr = "";                                 // Just show nothing, useful with warning frames
    else
        valueStr = String(*valuePtr_, 1);              // Get a floating point value truncated to 1 digit after a comma
    
    valueStr += *postfix_;
    return FrameOutputData {
        *prefix_,                                       // Top line string
        valueStr,                                       // Bot line string
        static_cast<uint8_t>(contentId_ <= 2 ? 1 : 2),  // VScale of the top line
        static_cast<uint8_t>(contentId_ > 2 ? 1 : 2),   // VScale of the bot line
        static_cast<uint8_t>(geometry_.hpos + (geometry_.width - prefix_->length()) / 2), // Top line xpos, center placement
        0,                                              // Top line ypos
        static_cast<uint8_t>(geometry_.hpos + (geometry_.width - valueStr.length()) / 2), // Bot line xpos, center placement
        2                                               // Bot line ypos
    };
}