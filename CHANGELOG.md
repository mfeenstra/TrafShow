# Changelog

Changes made to this trafshow 5.3 checkout since it was first compiled on
macOS. For the original upstream project history, see `CHANGES`.

## Build: get 5.3 compiling on modern macOS (arm64)

- Updated `config.guess`/`config.sub` so `configure` recognizes current
  Darwin/arm64.
- Renamed a local `pcap_init` that clashed with a symbol libpcap now exports
  itself.
- Defined `BIND_8_COMPAT` for the legacy resolver macros the code expects.
- Switched from the removed `pcap_version` global to `pcap_lib_version()`.
- Added a `.gitignore` and untracked the configure-generated
  `Makefile`/`config.h`/`config.log`/`config.status`, object files, and the
  `trafshow` binary itself, which had accidentally been committed in the
  initial baseline.

## IPv6 support

`trafshow` already had a fair amount of IPv6 plumbing (`parse_ip.c`,
`addrtoname.c`, `show_stat.c`, `show_dump.c`, `netstat.h`, ...), all gated
behind an `INET6` macro that nothing ever actually defined, so none of it was
compiled in and IPv6 traffic was silently dropped as "unknown IP version".

- `configure.in` now detects IPv6 support (`sockaddr_in6`/`in6_addr`/
  `inet_pton`) and defines `INET6` accordingly; `configure` was regenerated.
- `configure.in` also strips any `-std=gnuNN` a newer `AC_PROG_CC` injects —
  this codebase is K&R-style C throughout, and C23 dropped K&R function
  definitions entirely, so a strict `-std=gnu23` broke the build outright.
- `colormask.c`: address/mask matching for color rules only ever read the
  4-byte IPv4 union member with a 32-bit-only netmask, regardless of the
  packet's or rule's actual IP version. Replaced with a version-aware,
  byte-length-generic comparison (`addr_bits_equal`/`addr_is_unspec`) that
  works for both 32-bit and 128-bit addresses at arbitrary prefix lengths,
  and fixed a related bug where an IPv6 rule address with a zero first 4
  bytes (e.g. `::1`) was misread as an unspecified/wildcard address.
- `addrtoname.c` / `domain_resolver.[ch]`: `getname6()` reverse-resolved
  IPv6 addresses with a *synchronous* `gethostbyaddr()` call, unlike
  `getname()`'s asynchronous resolution — since address formatting runs on
  the same thread that drives curses rendering, this froze the whole UI for
  as long as each PTR lookup took. Extended the async nameserver engine with
  a `DomainName6` query type (reversed-nibble `ip6.arpa` PTR lookups) and
  `domain_resolve_name6()`, and rewrote `getname6()` to resolve in the
  background and update the display once the name comes back, the same way
  `getname()` already did.

## Reverse DNS hostname display in the live session table

Two further bugs kept reverse DNS from actually working end-to-end even
after IPv6 was enabled:

- `domain_resolver_init()` parsed `/etc/resolv.conf` nameserver lines with
  `inet_addr()`, which can't parse an IPv6 literal — an IPv6-only or
  IPv6-first nameserver silently became `255.255.255.255`, so every query
  went nowhere. It now parses each line as IPv4 or IPv6 into a
  `sockaddr_storage`.
- `session.c`'s generic UDP session layer was IPv4-only: `session_open()`/
  `session_start()` copied/connected a fixed `sizeof(struct sockaddr)` (16
  bytes, truncating a 28-byte `sockaddr_in6`), and `session_read()`'s
  `recvfrom()` used a 16-byte local buffer with a sanity check that rejected
  anything IPv6-sized. Both are now family-aware.
- `nameserver_error()` parsed a secondary nameserver from `resolv.conf` but
  never used it — on timeout it just kept retrying the same (possibly dead)
  primary forever and gave up silently. It now fails over to the secondary
  nameserver once, opening a fresh transport session against it with the
  same pending request, so a dead primary no longer means reverse DNS never
  resolves.

## UI color theming

- Extended the existing `colormask` rc-file mechanism (`.trafshow` /
  `/etc/trafshow` / `~/.trafshow`, previously only used for per-connection
  address/port coloring) with three new directives — `header`, `footer`,
  and `help` — that color the session-list column-title header, the
  session-list summary footer, and the help-menu popup.
- Recolored the shipped `.trafshow` sample config: LAN traffic (RFC1918 +
  loopback + link-local, both IPv4 and IPv6) is bright blue, everything
  else (WAN/public) is bright cyan via a catch-all rule; header is bright
  red, footer is bright yellow, help is bright yellow-on-blue.
- Layered the original well-known-service colors (ssh, http/https, dns,
  mail, ftp/tftp/nfs, netbios, snmp/bootp, icmp, ...) back on top of the
  LAN/WAN scheme. Rules are matched top-to-bottom and the first match wins,
  so service rules are listed first (e.g. ssh shows magenta, http shows
  blue) and a connection only falls back to the plain LAN/WAN color when no
  specific service rule applies.

## Documentation

- Converted the plain-text `README` to Markdown (`README.md`) and updated
  it to describe this release's IPv6, reverse-DNS, and color-theme features.
- Added `CHANGELOG.md` (this file) and `BUILD.md`, a step-by-step
  configure/make/run walkthrough for new users, verified against a clean
  worktree with no pre-existing build artifacts.

## Licensing

- Relicensed this release under the GNU General Public License v3.0 or later:
  added a top-level `LICENSE` file with the full GPLv3 text, and replaced
  the permissive BSD-style notice in every project-owned source file
  header (the `Redistribution and use in source forms...` boilerplate)
  with a GPLv3 notice, preserving each file's original copyright line.
  Third-party vendored files with their own distinct license/attribution
  (`addrtoname.c`/`.h`, `hashtab.*`, `lookupa.*`, `recycle.*`, `snprintf.*`,
  `strcasecmp.c`, `strftime.c`, `ethertype.h`, `sll.h`, `standard.h`) were
  left untouched, since their copyright belongs to other authors.
  Earlier releases of TrafShow remain available under their original
  BSD-style license as previously published; only this release, from this
  point forward, is GPLv3.

## Notes for future changes

- `.trafshow` in this source tree is only a *sample*. At runtime trafshow
  reads `-c <file>`, then `$HOME/.trafshow`, then `/etc/trafshow` — editing
  the repo's copy has no effect until it's copied to one of those paths.
- After pulling in source changes, the `trafshow` binary needs an explicit
  rebuild (`make trafshow`) — `make` has occasionally reported "up to date"
  against a binary that predated a fast-forward merge, so when in doubt
  `touch` the changed sources first.
