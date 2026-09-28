# TrafShow 5.3

This directory contains the TrafShow source code, a tool for real-time
network traffic visualization.

This is a release of the original TrafShow 5.2.3, updated to build and run on
modern macOS (Darwin/arm64), with working IPv6 support, reverse-DNS hostname
display, and a configurable color theme. See [CHANGELOG.md](CHANGELOG.md)
for the full list of changes made in this release, and [CHANGES](CHANGES) for
the original upstream project history.

## Brief description

TrafShow is a simple interactive program that gathers network traffic from
all libpcap-capable interfaces, accumulates it in an in-memory cache, and
displays it in a curses window as a line-narrowed list of network flows
sorted by throughput. The display updates near real time, asynchronously
from data collection — a live show of traffic flows. Any kind of network
traffic is mixed together on the one live-show screen: Ethernet, IP, etc.

IP traffic can be aggregated by netmask prefix bits and service ports to
reorganize a heap of trivial flows into tree-like hierarchies suitable for
human perception. You can glance over the list of resulting flows, select
one, and drill into the traffic hierarchy to inspect the packets of each
flow in a variety of presentations: raw-hex, ASCII, time-stamp.

Aggregation happens automatically once the number of flows exceeds a
reasonable amount. Just a few seconds after launch may be required to adapt
to your traffic volume.

TrafShow also listens on a UDP port (as a server) for Cisco Netflow feeders
and displays the collected data the same way as live-captured traffic. The
following Netflow versions are currently supported: V1, V5, V7.

## Features in this release

- **IPv6**: fully supported end to end — packet parsing, color-rule address
  matching, and reverse DNS all handle IPv6 the same as IPv4.
  `configure` detects IPv6 support automatically and defines `INET6`; no
  manual configuration is needed.
- **Reverse DNS**: source/destination addresses in the live session table
  are resolved to hostnames asynchronously (a numeric placeholder is shown
  immediately, updated in place once the PTR lookup completes), for both
  IPv4 and IPv6, with automatic failover to a secondary nameserver.
- **Color theme**: the session-list header, footer, and help-menu popup are
  colored, and traffic is colored by well-known service (ssh, http/https,
  dns, mail, ftp/tftp/nfs, netbios, snmp/bootp, icmp, ...) first, falling
  back to LAN (bright blue) vs. WAN (bright cyan) address-based coloring
  for anything else. See the `header`/`footer`/`help` directives in
  `.trafshow` to customize it.

## Usage

This program is useful for locating suspicious traffic on the network
quickly on demand, or for evaluating real-time traffic bandwidth
utilization, in a simple and convenient environment. It is **not** intended
for collecting and analyzing network traffic over a long period of time,
nor for billing.

Please see the `trafshow(1)` man page for further information.

## Requirements

TrafShow uses libpcap to gather network traffic, a system-independent
interface for user-level packet capture. Note that most systems ship
libpcap, but usually an older version — the minimum required version is
0.7, newest always preferred. The original distribution of the library is
at <http://www.tcpdump.org>.

TrafShow can use various curses libraries, a terminal-independent set of
screen functions with optimal cursor motion. Not all curses libraries
support color functions properly — Slang or Ncurses is preferred because
it supports color correctly. Most systems ship ncurses, which is enough.

Once libpcap and libncurses (or slang) are built and installed, build
TrafShow using the procedure in the [INSTALL](INSTALL) file.

## Color configuration

TrafShow reads color rules from a config file at startup: `-c <file>` if
given, otherwise `$HOME/.trafshow`, otherwise `/etc/trafshow`. The
`.trafshow` file in this source tree is only a *sample* — copy it to one of
those paths (most commonly `$HOME/.trafshow`) for it to take effect, and
copy it there again after pulling in changes, since it isn't read from the
source tree automatically.

See the `COLORS` section of the `trafshow(1)` man page for the full config
file syntax.

## Distribution and support

Because the program is freely distributed software, it can be found around
the world with or without modifications. The original distribution of the
program is available at
`ftp://ftp.nsk.su/pub/RinetSoft/trafshow-X.Y.tgz`, where X is the main
version and Y is the current release.

There is no special support available right now. Problems, bugs, questions,
and desirable enhancements for the original upstream project should be sent
to `trafshow@risp.ru`.

Please see the `trafshow(1)` man page for the authors and acknowledgements.

## License

This release is licensed under the GNU General Public License v3.0 or later.
See [LICENSE](LICENSE) for the full text. The original copyright notices
of the upstream authors (Rinet Corp., Novosibirsk, Russia) are retained in
the individual source file headers.

Earlier releases of TrafShow (up through the point this release diverged) were
distributed under a permissive BSD-style license from the original
authors; that license still applies to those earlier releases as
originally published. This repository, from this point forward, is GPLv3.
