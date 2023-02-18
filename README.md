# OpenDetex

> OpenDetex is a program to remove TeX constructs from a text file.  It recognizes
> the `\input` command.  It is capable of generating proofreader-ready text.

## Usage

1. Install OpenDetex:

    1. Download [pkg.tar.zst File](https://github.com/b1f6c1c4/opendetex/releases/latest/download/opendetex.pkg.tar.zst)
    1. `sudo pacman -U <path-to-pkg.tar.zst>`

1. Inside your project, create a file named `.detexrc` describing additional lexer rules:

    ```lex
    <Normal>"\\mymacroa"   { printf("some substitude words"); }
    <Normal>"\\mymacrob"   { printf("other substitude words"); }
    ```

1. Detex and copy your entire LaTeX document, including `\input`'d, into clipboard:

    ```bash
    detex-copy main.tex
    ```

1. Paste your entire document into your favorite grammar checker
1. Copy the entire document from your favorite grammar checker
1. Obtain a list of changes based on your clipboard information:

    ```bash
    detex-paste main.tex
    ```

## Legal, Copyright, history

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
