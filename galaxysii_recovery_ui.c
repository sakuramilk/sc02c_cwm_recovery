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
                       "select boot rom",
                       "apply update from sdcard",
                       "factory reset",
                       "wipe data partition",
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

int device_wipe_data(int userdata_type) {
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
    return 0;
}

int fix_userdata(int userdata_type) {
    __system("mount -t ext4 /dev/block/mmcblk0p10 /xdata");

    if (userdata_type & USERDATA0) {
        mkdir("/xdata/data0/system", 0775);
        mkdir("/xdata/data0/system/dropbox", 0700);
        mkdir("/xdata/data0/system/registered_services", 0771);
        mkdir("/xdata/data0/system/sync", 0700);
        mkdir("/xdata/data0/system/throttle", 0700);
        mkdir("/xdata/data0/system/usagestats", 0700);

        chown("/xdata/data0/system", 1000, 1000);
        chown("/xdata/data0/system/dropbox", 1000, 1000);
        chown("/xdata/data0/system/registered_services", 1000, 1000);
        chown("/xdata/data0/system/sync", 1000, 1000);
        chown("/xdata/data0/system/throttle", 1000, 1000);
        chown("/xdata/data0/system/usagestats", 1000, 1000);
    }

    if (userdata_type & USERDATA1) {
        mkdir("/xdata/data1/system", 0775);
        mkdir("/xdata/data1/system/dropbox", 0700);
        mkdir("/xdata/data1/system/registered_services", 0771);
        mkdir("/xdata/data1/system/sync", 0700);
        mkdir("/xdata/data1/system/throttle", 0700);
        mkdir("/xdata/data1/system/usagestats", 0700);

        chown("/xdata/data1/system", 1000, 1000);
        chown("/xdata/data1/system/dropbox", 1000, 1000);
        chown("/xdata/data1/system/registered_services", 1000, 1000);
        chown("/xdata/data1/system/sync", 1000, 1000);
        chown("/xdata/data1/system/throttle", 1000, 1000);
        chown("/xdata/data1/system/usagestats", 1000, 1000);
    }

    __system("umount /xdata");
    return 0;
}
