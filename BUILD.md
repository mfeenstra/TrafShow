# Building TrafShow

This walks a new user through building and running this 5.3 version of
TrafShow from source. It's been verified on macOS (Darwin/arm64); the same
steps should work on any Unix with libpcap and a curses library.

## 1. Prerequisites

- **A C compiler and make** — on macOS, install the Xcode Command Line
  Tools if you haven't already:

  ```sh
  xcode-select --install
  ```

- **libpcap** — macOS ships this by default. On Linux, install your
  distribution's `libpcap-dev`/`libpcap-devel` package if `configure` can't
  find it.
- **A curses library** — macOS ships ncurses by default, which is enough.
  `configure` will detect whichever curses library is available and prefers
  one that supports color (Slang or Ncurses).

You do **not** need to do anything special for IPv6 — `configure` detects
IPv6 support automatically.

## 2. Configure

From the source directory:

```sh
./configure
```

This generates `Makefile` from `Makefile.in` and `config.h` from
`config.h.in` based on what your system supports. If something unusual is
needed (an alternate compiler, extra libraries), pass it as an environment
variable, e.g.:

```sh
CC=clang CFLAGS=-O2 ./configure
```

By default, `--prefix` for a later `make install` is `/usr/local`; pass
`--prefix=/usr` (or edit `BINDEST`/`MANDEST` in `Makefile.in`) to change
that.

## 3. Build

```sh
make
```

Ignore warnings about K&R-style function definitions (`-Wdeprecated-non-prototype`)
— this is old-style C throughout and they're expected. There should be no
errors. This produces a `trafshow` binary in the current directory.

**If you pull in new changes later** (e.g. after a `git merge`), rebuild
with `make trafshow`. If `make` reports the binary as "up to date" even
though source files changed, `touch` the changed `.c`/`.h` files first —
this has happened a couple of times when a fast-forward merge landed files
with timestamps `make` didn't consider newer than the existing build.

## 4. Set up the color config (optional but recommended)

TrafShow reads color rules from a config file at startup: `-c <file>` if
given, otherwise `$HOME/.trafshow`, otherwise `/etc/trafshow`. The
`.trafshow` file in this source tree is a **sample** — it has no effect
until it's copied to one of those paths:

```sh
cp .trafshow ~/.trafshow
```

Without this, TrafShow still runs, but every rule (LAN/WAN coloring,
service coloring, header/footer/help colors) is simply absent — plain
`use_colors` mode with no rules loaded.

## 5. Run it

Packet capture requires access to the system's capture devices, so run
with `sudo`:

```sh
sudo ./trafshow
```

Some useful flags (see `trafshow(1)` for the full list):

- `-i <name>` — listen on one specific interface instead of all of them.
- `-n` — show numeric addresses/ports instead of resolving names (can be
  toggled live with `N`).
- `-c <file>` — use a specific color config file instead of the default
  lookup.

Once it's running, press `h` for the in-app help menu, and `q`/`Esc` to
quit.

## 6. Installing system-wide (optional)

```sh
sudo make install
```

This installs the `trafshow` binary and man page under your configured
prefix, and copies `.trafshow` to `/etc/trafshow` if nothing is there yet
(existing files are never overwritten). Note the install rule uses
`-o bin -g bin`; if your system has no `bin` user/group (common on a
default macOS install), either add one or just run `trafshow` straight out
of the build directory as shown above — that's the simpler path for
day-to-day use and is all you need to try out this release.

## Next steps

- [README.md](README.md) — what TrafShow does and what's new in this release.
- [CHANGELOG.md](CHANGELOG.md) — everything changed in this release since the
  original 5.2.3 baseline.
- `trafshow(1)` man page — full command-line options and the `.trafshow`
  color config file syntax.
