# OpenDetex

> OpenDetex is a program to remove TeX constructs from a text file.  It recognizes
> the `\input` command.  It is capable of generating proofreader-ready text.
> Our results are much, much better than the original `detex` program commonly found in TeX Live.

## Install

- For `pacman`-based system: (Arch Linux, Manjaro, etc.)
    1. Download [pkg.tar.zst File](https://github.com/b1f6c1c4/opendetex/releases/latest/download/opendetex.pkg.tar.zst)
    1. `sudo pacman -U <path-to-pkg.tar.zst>`
- For `apt/deb`-based system: (Debian, Ubuntu, etc.)
    1. Download [deb File](https://github.com/b1f6c1c4/opendetex/releases/latest/download/opendetex.deb)
    1. `sudo apt update`
    1. `sudo apt install <path-to-deb>`
- For `rpm/dnf`-based system: (Fedora, RHEL, etc.)
    1. Download [rpm File](https://github.com/b1f6c1c4/opendetex/releases/latest/download/opendetex.rpm)
    1. `sudo dnf install <path-to-rpm>`

## Configure

We understand that TeX/LaTeX users use custom-defined macros to simplify their writing.
To properly detex such macros,
just create a file named `.detexrc` describing additional lexer rules:

```lex
<Normal>"\\mymacroa"   { printf("some substitude words"); }
<Normal>"\\mymacrob"   { printf("other substitude words"); }
```

Checkout [`detex.l`](/detex.l#L308) for more examples.

## Standalone use

```bash
DISPLAY= detex-copy main.tex
```

## Use with a grammar checker (requires X11 and `xclip`)

1. Detex and copy your entire LaTeX document, including `\input`'d, into clipboard:

    ```bash
    detex-copy main.tex
    ```

1. Paste your entire document into your favorite grammar checker
1. Edit using your favorite grammar checker
1. Copy the entire document from your favorite grammar checker
1. Obtain a list of changes based on your clipboard information:

    ```bash
    detex-paste main.tex
    ```

1. (TODO) automatically integrate changes back to your TeX files

## Legal, copyright, history

This software package is distributed under the NCSA/University of
Illinois Open Source License.

OpenDetex was created by b1f6c1c4 from version 3.0, obtained from
Piotr Kubowicz from version 2.8 of Detex
program by Daniel Trinkle, obtained from
http://www.cs.purdue.edu/homes/trinkle/detex/

Currently home of OpenDetex is GitHub:
https://github.com/b1f6c1c4/opendetex
You can check for latest version, submit bug reports or patches, or
ask for becoming team member there.
