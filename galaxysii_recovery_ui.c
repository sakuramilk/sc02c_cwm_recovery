/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <unistd.h>
#include <linux/input.h>

#include "recovery_ui.h"
#include "common.h"
#include "extendedcommands.h"

char* MENU_HEADERS[] = { NULL };

char* MENU_ITEMS[] = { "reboot system now",
#ifdef RECOVERY_MULTI_BOOT
                        "select boot rom",
#endif
                       "apply update from sdcard",
                       "wipe data/factory reset",
                       "wipe cache partition",
                       "install zip from sdcard",
                       "backup and restore",
                       "mounts and storage",
                       "advanced",
                       "power off",
                       NULL };

int device_recovery_start() {
    return 0;
}

int device_toggle_display(volatile char* key_pressed, int key_code) {
    return ( (get_allow_toggle_display()) && (key_code == KEY_POWER) );
}

int device_reboot_now(volatile char* key_pressed, int key_code) {
    return 0;
}

int device_handle_key(int key_code, int visible) {

    //LOGE("device_handle_key key_code=%d, visible=%d\n", key_code, visible);

    if (visible) {
        switch (key_code) {
            case KEY_VOLUMEDOWN:
                return HIGHLIGHT_DOWN;
            case KEY_VOLUMEUP:
                return HIGHLIGHT_UP;
            case KEY_HOME:
                return SELECT_ITEM;
            case KEY_BACK:
                return GO_BACK;
            case KEY_POWER:
                break;
        }
    }

    return NO_ACTION;
}

int device_perform_action(int which) {
    return which;
}

int device_wipe_data() {
    __system("rm -rf /data/*");
    __system("rm -rf /data/.*");
    return 0;
}

int restore_preinstall()
{
#ifndef RECOVERY_MULTI_BOOT
    __system("mount -t ext4 /dev/block/mmcblk0p10 /data");
#if 0
    mkdir("/data/system", 0775);
    mkdir("/data/system/dropbox", 0700);
   mkdir("/data/system/registered_services", 0771);
    mkdir("/data/system/sync", 0700);
    mkdir("/data/system/throttle", 0700);
    mkdir("/data/system/usagestats", 0700);

    chown("/data/system", 1000, 1000);
    chown("/data/system/dropbox", 1000, 1000);
    chown("/data/system/registered_services", 1000, 1000);
    chown("/data/system/sync", 1000, 1000);
    chown("/data/system/throttle", 1000, 1000);
    chown("/data/system/usagestats", 1000, 1000);
#endif

    _system("mount -t ext4 /dev/block/mmcblk0p12 /preload");
    usleep(3000);
    mkdir("/data/app", 0771);
    chown("/data/app", 1000, 1000);	
    __system("cp /preload/app/* /data/app/");
    __system("chmod 644 /data/app/*");
    __system("chown system.system /data/app/*");
    
    __system("cp /preload/pre_video/Color_SuperAMOLEDPlus-30mb.mp4 /sdcard/");
	__system("chmod 644 /sdcard/Color_SuperAMOLEDPlus-30mb.mp4");
    __system("chown system.system /sdcard/Color_SuperAMOLEDPlus-30mb.mp4");
    __system("umount /preload");

    __system("umount /data");
#endif
    return 0;
}
