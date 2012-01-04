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

#include <linux/input.h>

#include "recovery_ui.h"
#include "common.h"
#include "extendedcommands.h"

char* MENU_HEADERS[] = { NULL };

char* MENU_ITEMS[] = { "reboot system now",
                       "select boot rom",
                       "install zip from sdcard",
                       "factory reset",
                       "wipe data partition",
                       "wipe cache partition",
                       "backup and restore",
                       "mounts and storage",
                       "advanced",
                       NULL };

void device_ui_init(UIParameters* ui_parameters) {
}

int device_recovery_start() {
    return 0;
}

int device_reboot_now(volatile char* key_pressed, int key_code) {
    return 0;
}

int device_perform_action(int which) {
    return which;
}

extern int erase_volume(const char *volume);
int device_wipe_data(int userdata_type) {
#ifdef DUALBOOT
    __system("mount -t ext4 /dev/block/mmcblk0p10 /xdata");
    if (userdata_type & USERDATA0) {
        __system("rm -rf /xdata/data0/*");
        __system("rm -rf /xdata/data0/.*");
    }

    if (userdata_type & USERDATA1) {
        __system("rm -rf /xdata/data1/*");
        __system("rm -rf /xdata/data1/.*");
    }
    __system("umount /xdata");
#else
    erase_volume("/data");
#endif
    return 0;
}

int fix_userdata(int userdata_type)
{
#if 0
    __system("mount -t ext4 /dev/block/mmcblk0p10 /data");
    usleep(3000);
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
    
    if (userdata_type)
    {
        __system("mount -t ext4 /dev/block/mmcblk0p12 /preload");
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
    }

    __system("umount /data");
#endif
    return 0;
}
