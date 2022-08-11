#include <grabber/LGGrabber.h>
#include <QSemaphore>
#include "api.h"
#include "log.h"


//static
static int img_width;
static int img_height;
static uint8_t* img_data;
static QSemaphore* lock;

void LGGrabber::run() {
    lock = new QSemaphore(1);
    lock->acquire(1);
    log_init();
    log_set_level(LogLevel::Debug);
    cap_backend_config_t config = {0, 0, 360, 180, 0, 0, 0};

    capture_preinit(&config, [](int width, int height, uint8_t* rgb_data)->int{
        img_width = width;
        img_height = height;
        img_data = rgb_data;
        lock->release(1);
        return 0;
    });

    capture_init();

    capture_start();

    while (running){
        lock->acquire(1);
//        std::cout<< "Lock available: " << lock->available() << std::endl;
        Image<ColorRgb> img(img_width, img_height);
//        new ImageData<ColorRgb>()
        memmove(img.memptr(), img_data, img_width*img_height*3);
        emit setGlobalInputImage(1, img, 1000);
    }

    capture_terminate();
    capture_cleanup();
}

void LGGrabber::forceClose() {
    running = false;
}

LGGrabber::LGGrabber() {}

LGGrabber::~LGGrabber() noexcept {}