 Kernel release package version instruction
=====================================================
#
#      yuenar2@gmail.com
#        2015.02.28
#
USE zImage NOTE:

1、This package make out zImage only, you have to get ramdisk and add kernel cmdline to generate a total boot.img before replace your phone's bootimage. 2、If your phone already enable secboot feature, please decrypt or unlock the secboot feature first. 3、Please make sure your phone software version is same with this release package, if not, please download the match version first.

This kernel package is released for the phone software version P6S-U06V100R001C17B606+

    How to Build

        get Toolchain From android git server , codesourcery and etc ..
            arm-linux-androideabi-4.6

        edit Makefile edit "CROSS_COMPILE" to right toolchain path(You downloaded). EX) CROSS_COMPILE= $(android platform directory you download)/android/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi- Ex) CROSS_COMPILE=/usr/local/toolchain/arm-linux-androideabi-4.6/bin/arm-linux-androideabi- // check the location of toolchain or Ex) export CROSS_COMPILE=arm-linux-androideabi- Ex) export PATH=$PATH:/arm-linux-androideabi-4.6/bin

        $ make ARCH=arm hisi_k3v2oem1_defconfig $ make ARCH=arm zImage  //Note don't make menuconfig instead of hisi_hi6620oem_defconfig or you will fail!

    Output files
        Kernel : arch/arm/boot/zImage
        module : drivers//.ko

    How to Clean $ make ARCH=arm distclean

