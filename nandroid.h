#ifndef NANDROID_H
#define NANDROID_H

int nandroid_main(int argc, char** argv);
int nandroid_backup(const char* backup_path);
int nandroid_restore(const char* backup_path, int restore_boot, int restore_system0, int restore_system1,
                     int restore_xdata, int restore_cache, int restore_sdext, int restore_wimax);

#endif