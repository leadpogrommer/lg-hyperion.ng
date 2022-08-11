#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
int capture_preinit(cap_backend_config_t *backend_config, cap_imagedata_callback_t callback);
int capture_init();
int capture_terminate();
int capture_cleanup();
int capture_start();
void capture_frame();


#ifdef __cplusplus
} // closing brace for extern "C"

#endif