# Translate strings Makefile
progversion=`awk -F '"' '/define PROGVERSION/ {print $2}' ../src/main.h`
sfmversion="sfm-${progversion}"

rm -rf sfm-*
mkdir -p dist ${sfmversion}
rsync -a --exclude='build/' --exclude='.git*' ../ ${sfmversion}
tar cvfz ${sfmversion}.tar.gz ${sfmversion}


