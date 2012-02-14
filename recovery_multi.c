/*
 * Copyright (C) 2007 The Android Open Source Project
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
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "libcrecovery/common.h"

int multi_mount(const char* device, const char* mount_point, const char* fs_type, const char* fs_options)
{
#ifdef RECOVERY_MULTI_BOOT
    char mount_cmd[PATH_MAX];

    if (strcmp(mount_point, "/system") == 0) {
        sprintf(mount_cmd, "mount %s", "/system");
        return __system(mount_cmd);
    } else if (strcmp(mount_point, "/data") == 0) {
        sprintf(mount_cmd, "mount %s", "/data_dev");
        return __system(mount_cmd);
    } else {
        int ret = 0;
        if (fs_options == NULL) {
            ret = mount(device, mount_point, fs_type,
                           MS_NOATIME | MS_NODEV | MS_NODIRATIME, "");
        }
        else {
            char mount_cmd[PATH_MAX];
            sprintf(mount_cmd, "mount -t %s -o %s %s %s", fs_type, fs_options, device, mount_point);
            ret = __system(mount_cmd);
        }
        return ret;
    }
#else
    return -1;
#endif
}

int multi_format(const char* location) {
#ifdef RECOVERY_MULTI_BOOT
    printf("multi_format location=%s\n", location);
    if (strcmp(location, "/dev/block/mmcblk0p9") == 0) {
        char* value = getenv("SYSTEM_DEVICE");
        if (value && strlen(value) > 0) {
            char cmd[PATH_MAX];
            sprintf(cmd, "mke2fs -T ext4 -F %s", value);
            return __system(cmd);
        }
    }
#endif
    return -1;
}

