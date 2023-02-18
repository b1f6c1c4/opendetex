#!/bin/bash

grep '^pkgver' PKGBUILD
grep '^Version:' control
echo 'Is this correct????'
read -p "Press enter to continue"

set -euxo pipefail

docker build -t detex-releaser --pull - <<EOF
FROM debian:unstable
RUN apt update && apt install -y alien && apt clean
EOF

rm -f opendetex-*.pkg.tar.zst opendetex.deb opendetex.rpm

makepkg

ln -sf opendetex-*.pkg.tar.zst opendetex.pkg.tar.zst

rm -rf opendetex
cp -r --preserve=mode pkg/opendetex .
mkdir opendetex/DEBIAN
cp control opendetex/DEBIAN/
rm opendetex/.{BUILDINFO,MTREE,PKGINFO}

docker run --rm -it \
    -v "$PWD:/mnt" --workdir /mnt \
    --user "$UID:$(id -g)" detex-releaser \
    dpkg-deb --root-owner-group --build opendetex

docker run --rm -it \
    -v "$PWD:/mnt" --workdir /mnt \
    detex-releaser \
    sh -c '
        set -e
        alien -r opendetex.deb
        mv opendetex-*.rpm opendetex.rpm
        cp -p --attributes-only opendetex.deb opendetex.rpm'
