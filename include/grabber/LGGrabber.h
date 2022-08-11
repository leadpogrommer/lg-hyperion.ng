#pragma once

#include <QObject>

// Hyperion-utils includes
#include <utils/ColorRgb.h>
#include "utils/Image.h"
//#include <hyperion/Grabber.h>



class LGGrabber : public QObject
{
    Q_OBJECT
public:
    LGGrabber();
    ~LGGrabber();

public slots:
    void run();
    void forceClose();
signals:
    bool setGlobalInputImage(int priority, const Image<ColorRgb>& image, int timeout_ms, bool clearEffect = false);

private:
    bool running;


};
