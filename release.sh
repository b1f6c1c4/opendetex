#!/bin/bash

grep '^pkgver' PKGBUILD
grep '^Version:' control
echo 'Is this correct????'
read -p "Press enter to continue"

set -euxo pipefail

rm -f opendetex-*.pkg.tar.zst opendetex.deb

makepkg

ln -sf opendetex-*.pkg.tar.zst opendetex.pkg.tar.zst

rm -rf opendetex
cp -r --preserve=mode pkg/opendetex .
mkdir opendetex/DEBIAN
cp control opendetex/DEBIAN/
rm opendetex/.{BUILDINFO,MTREE,PKGINFO}

docker run --pull always --rm -it \
    -v "$PWD:/mnt" --workdir /mnt \
    --user "$UID:$(id -g)" debian:stable \
    dpkg-deb --root-owner-group --build opendetex
