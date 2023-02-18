# Maintainer: b1f6c1c4 <b1f6c1c4@gmail.com>
pkgname=opendetex
pkgver=3.0.0
pkgrel=1
pkgdesc="Improved version of Detex - tool for extracting plain text from TeX and LaTeX sources"
arch=('x86_64')
url="https://github.com/b1f6c1c4/opendetex"
license=('custom')
depends=('git' 'gcc')
source=()
sha256sums=()

build() {
    flex -o "$srcdir/detex.c" "$srcdir/../detex.l" 
    CFLAGS="-std=c2x -Wall -Wextra -pedantic -Werror ${CFLAGS} -DVERSION=\"$pkgver\""
    gcc ${CFLAGS} -I "$srcdir/.." -o "$srcdir/detex" "$srcdir/detex.c"
    gcc ${CFLAGS} -o "$srcdir/detex-util" "$srcdir/../util.c"
    sed "/^ \/\* PLACEHOLDER FOR \.detexrc \*/q" "$srcdir/../detex.l" > "$srcdir/detex-1.l"
    sed "0,/^ \/\* PLACEHOLDER FOR \.detexrc \*/d" "$srcdir/../detex.l" > "$srcdir/detex-2.l"
}

package() {
    mkdir -p "$pkgdir/usr/bin/"
    mkdir -p "$pkgdir/usr/share/licenses/opendetex/"
    mkdir -p "$pkgdir/usr/share/opendetex/"
    mkdir -p "$pkgdir/var/cache/opendetex/"
    chmod a+rwxt "$pkgdir/var/cache/opendetex/"
    install -m 0755 "$srcdir/../detex-copy" "$pkgdir/usr/bin/"
    install -m 0755 "$srcdir/../detex-paste" "$pkgdir/usr/bin/"
    install -m 0755 "$srcdir/detex" "$pkgdir/usr/bin/detex-default"
    install -m 0755 "$srcdir/detex-util" "$pkgdir/usr/bin/"
    install -m 0644 "$srcdir/../COPYRIGHT" "$pkgdir/usr/share/licenses/opendetex/"
    install -m 0644 "$srcdir/detex-1.l" "$pkgdir/usr/share/opendetex/"
    install -m 0644 "$srcdir/detex-2.l" "$pkgdir/usr/share/opendetex/"
    install -m 0644 "$srcdir/../detex.h" "$pkgdir/usr/share/opendetex/"
}
