#include "../../lvgl/lvgl.h"

// 图像数组
const char * images[] = {
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01000.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01001.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01002.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01003.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01004.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01005.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01006.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01007.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01008.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01009.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01010.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01011.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01012.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01013.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01014.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01015.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01016.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01017.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01018.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01019.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01020.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01021.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01022.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01023.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01024.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01025.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01026.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01027.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01028.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01029.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01030.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01031.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01032.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01033.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01034.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01035.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01036.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01037.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01038.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01039.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01040.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01041.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01042.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01043.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01044.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01045.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01046.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01047.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01048.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01049.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01050.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01051.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01052.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01053.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01054.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01055.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01056.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01057.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01058.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01059.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01060.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01061.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01062.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01063.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01064.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01065.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01066.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01067.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01068.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01069.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01070.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01071.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01072.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01073.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01074.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01075.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01076.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01077.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01078.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01079.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01080.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01081.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01082.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01083.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01084.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01085.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01086.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01087.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01088.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01089.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01090.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01091.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01092.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01093.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01094.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01095.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01096.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01097.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01098.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01099.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01100.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01101.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01102.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01103.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01104.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01105.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01106.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01107.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01108.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01109.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01110.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01111.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01112.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01113.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01114.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01115.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01116.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01117.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01118.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01119.png",
    "S:/mnt/nfs/VMshare/9_19_/YueQian-phase2-project1/project/lv_port_linux_frame_buffer-release-v8.2/res/pic/boot_anima/open1/01120.png",
    // 添加更多帧
};

static lv_obj_t * img;
static uint8_t img_index = 0;
static lv_timer_t * anim_timer;

// 动画回调函数index
void anim_callback(lv_timer_t * timer)
{
    // 更新图像源
    lv_img_set_src(img, images[img_index]);
    img_index++;

    // 检查是否达到最后一帧
    if(img_index >= (sizeof(images) / sizeof(images[0]))) {
        lv_timer_del(anim_timer);
        anim_timer = NULL;
        // 动画结束后执行的逻辑
        lv_obj_del(img); // 删除图像对象
        // 这里可以添加后续操作，例如显示主界面等
        lv_scr_load(lv_scr_act()); // 重新加载当前屏幕
    }
}

void create_animation(lv_obj_t *parent) {
    img = lv_img_create(parent);
    lv_obj_set_pos(img, 50, 50);
    lv_obj_set_size(img, 100, 100);

    anim_timer = lv_timer_create(anim_callback, 100, NULL); // 每100毫秒更新一次
}

void start_animation(lv_obj_t *parent) {
    img_index = 0; // 重置帧计数
    create_animation(parent);
}
