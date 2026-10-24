# dwm rice

My personal [dwm](https://dwm.suckless.org/) setup with all patches already applied. No manual patching needed, just clone, build, and go.

<p align="center">
<img src="screenshots/dwm.jpg" alt="dwm screenshot" width="800">
</p>

## Patches

- [bar-height](https://dwm.suckless.org/patches/bar_height/)
- [fullgaps](https://dwm.suckless.org/patches/fullgaps/)
- [moveresize](https://dwm.suckless.org/patches/moveresize/)
- [noborderfloatingfix](https://dwm.suckless.org/patches/noborder/)
- [movestack](https://dwm.suckless.org/patches/movestack/)
- [pertag](https://dwm.suckless.org/patches/pertag/)
- [status2d](https://dwm.suckless.org/patches/status2d/)
- [warp](https://dwm.suckless.org/patches/warp/)
- [xrdb](https://dwm.suckless.org/patches/xrdb/)

The `patches/` folder is kept for reference and credit only. They are already applied to the source.

## Dependencies

    sudo apt install build-essential libx11-dev libxft-dev libxinerama-dev git fontforge python3-fontforge fonts-font-awesome

For the optional wallpaper theme (see below):

    sudo apt install xdotool pipx nitrogen inotify-tools

## Font

The layout symbol uses a cat glyph from [waycat](https://github.com/CarloCattano/waycat) by CarloCattano. The original font maps its frames to plain letters, which clashes with normal text in dwm, so the glyphs are moved to the private use area first. The font file is not included in this repo, the script below builds it from the original:

    ./fonts/install-waycat.sh

Check that it is installed:

    fc-list | grep -i waycat

Without the font, the layout symbol shows an empty box. To skip it, edit the `layouts[]` array in `config.h` and remove the `\uE000` glyphs.

## Installation

    git clone https://github.com/vq6oon/dwm.git
    cd dwm
    ./fonts/install-waycat.sh
    sudo make clean install

Then add this line to your `~/.xinitrc`:

    exec dwm

## Status bar

The status bar is a separate project: [sxstatus](https://github.com/vq6oon/sxstatus). It uses the same cat font for the animated CPU cat, so install the font first.

## Theme from wallpaper (optional)

Bar colors follow the wallpaper using [pywal](https://github.com/dylanaraps/pywal) and the xrdb patch. The status bar colors from [sxstatus](https://github.com/vq6oon/sxstatus) follow too.

    pipx install pywal
    ./pywal/install.sh

Pick a wallpaper in nitrogen, then run `theme` (or press `MODKEY+w`). It regenerates the colors from the wallpaper, reloads the bar and restarts sxstatus.

To update automatically whenever you apply a new wallpaper in nitrogen, and to keep the colors after login, add this to `~/.xsessionrc`:

    xrdb -merge ~/.cache/wal/dwm-xres
    ~/.local/bin/theme-watch &

If you start dwm with `startx`, put the same lines in `~/.xinitrc` before `exec dwm`, since `~/.xsessionrc` is only read by display managers.

To make kitty follow the wallpaper too, add this to `~/.config/kitty/kitty.conf` below the theme block:

    include ~/.cache/wal/colors-kitty.conf

Without pywal, dwm simply uses the colors set in `config.h`. Warning colors in the status bar (medium, low, mute) stay fixed on purpose, so they stay readable on any wallpaper.

## Emoji picker (optional)

Type emoji in any app with `MODKEY+e`, using [bemoji](https://github.com/marty-oehme/bemoji) and dmenu.

    sudo apt install xclip curl fonts-noto-color-emoji
    git clone https://github.com/marty-oehme/bemoji /tmp/bemoji
    install -m 755 /tmp/bemoji/bemoji ~/.local/bin/bemoji

The emoji list is downloaded on first run, so it needs an internet connection once.

### Launcher

| Keybind | Action |
| --- | --- |
| `Super + P` | Open launcher (dmenu) |

---

### Workspaces (Tags)

| Keybind | Action |
| --- | --- |
| `Super + 1~9` | Go to workspace 1~9 |
| `Super + Shift + 1~9` | Move window to workspace 1~9 |
| `Super + Tab` | Go to previously active workspace |
| `Super + 0` | View all windows from all workspaces |
| `Super + Shift + 0` | Assign window to all workspaces |

---

### Window actions

| Keybind | Action |
| --- | --- |
| `Super + J` / `K` | Focus next / previous window |
| `Super + Shift + J` / `K` | Move window down / up the stack |
| `Super + Return` | Promote focused window to master area |
| `Super + H` / `L` | Decrease / Increase master area size |
| `Super + I` / `O` | Increase / Decrease number of master windows |
| `Super + Arrows` | Move floating window |
| `Super + Shift + Arrows` | Resize floating window |
| `Super + Ctrl + Arrows` | Snap floating window edge |
| `Super + Shift + T` | Set Tiled layout |
| `Super + Shift + F` | Set Floating layout |
| `Super + Shift + M` | Set Monocle (Fullscreen) layout |
| `Super + Space` | Toggle between current and previous layout |
| `Super + Shift + Space` | Toggle floating mode for window |
| `Super + -` / `=` | Decrease / Increase gaps between windows |
| `Super + Shift + =` | Reset/remove gaps |
| `Super + Q` | Close window |

---

### Applications

| Keybind | Action |
| --- | --- |
| `Super + T` | Terminal (default: kitty) |
| `Super + B` | Browser (default: firefox) |
| `Super + C` | Editor (default: code) |
| `Super + E` | File explorer (default: thunar) |
| `Super + D` | Communication (discord) |
| `Super + M` | Music (spotify) |
| `Super + R` | OBS Studio |
| `Super + F` | Mouse driver (Fantech X9 Thor) |

---

### Utilities

| Keybind | Action |
| --- | --- |
| `Super + Print` | Screenshot (full screen) |
| `Super + Shift + Print` | Screenshot (region/crop) |
| `Super + Shift + F5` | Reload colors from X resources (pywal) |

---

### Hardware & Media

| Keybind | Action |
| --- | --- |
| `Super + F6` / `F5` | Volume up / Volume down |
| `Super + F3` | Mute volume |
| `Super + F9` / `F8` | Brightness up / Brightness down |
| `Super + N` | Open WiFi menu |
| `Super + Shift + N` | Toggle WiFi on/off |
| `Super + G` | Open Bluetooth menu |
| `Super + Shift + G` | Toggle Bluetooth on/off |

---

### System & Miscellaneous

| Keybind | Action |
| --- | --- |
| `Super + Shift + B` | Toggle top status bar visibility |
| `Super + Shift + R` | Reboot system |
| `Super + Shift + S` | Shutdown system |
| `Super + Shift + Q` | Quit dwm |

---

### Clipboard / Emoji

| Keybind | Action |
| --- | --- |
| `Super + V` | Open emoji picker (bemoji) |

## Credits

Based on [dwm](https://dwm.suckless.org/) by suckless.org. Original license is in `LICENSE`, original readme in `README.dwm`.

Cat font by [CarloCattano/waycat](https://github.com/CarloCattano/waycat).