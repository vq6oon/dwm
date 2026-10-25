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

Build:

    sudo apt install build-essential libx11-dev libxft-dev libxinerama-dev git fontforge python3-fontforge fonts-font-awesome

Programs used by the keybindings (install what you need, or change them in `config.h`):

    sudo apt install dmenu kitty thunar scrot maim xclip brightnessctl alsa-utils network-manager bluez rfkill power-profiles-daemon picom

Firefox, VS Code, Discord, Spotify and OBS are launched by name, so install them separately or edit `config.h`.

The optional extras at the bottom list their own dependencies.

## Font

The layout symbols are cat glyphs from [waycat](https://github.com/CarloCattano/waycat) by CarloCattano. Each layout gets a different frame: running cats for tile and floating, a sleeping cat for monocle. The original font maps its frames to plain letters, which clashes with normal text in dwm, so the glyphs are moved to the private use area first. The font file is not included in this repo, the script below builds it from the original:

    ./fonts/install-waycat.sh

Check that it is installed:

    fc-list | grep -i waycat

Without the font, the layout symbols show an empty box. To skip it, edit the `layouts[]` array in `config.h` and remove the `\uE000`, `\uE002` and `\uE010` glyphs.

## Installation

    git clone https://github.com/vq6oon/dwm.git
    cd dwm
    ./fonts/install-waycat.sh
    sudo make clean install

Create the folder used by the screenshot keys:

    mkdir -p ~/Pictures/Screenshots

Then start dwm. With `startx`, add this line to `~/.xinitrc`:

    exec dwm

With a display manager, add a session entry at `/usr/share/xsessions/dwm.desktop`:

    [Desktop Entry]
    Name=dwm
    Comment=dynamic window manager
    Exec=dwm
    Type=Application

Programs that should start at login (status bar, wallpaper, compositor) go in `~/.xsessionrc` for a display manager, or in `~/.xinitrc` before `exec dwm` for `startx`.

## Status bar

The status bar is a separate project: [sxstatus](https://github.com/vq6oon/sxstatus). The wifi and bluetooth keys below call its dmenu menus, so clone it to `~/.config/sxstatus`. Its icons come from Font Awesome, which is already in `fonts[]` in `config.h`.

## Keybindings

`Super` is the modifier (`MODKEY` in `config.h`).

### Applications

| Keybind | Action |
| --- | --- |
| `Super + P` | Launcher (dmenu) |
| `Super + T` | Terminal (kitty) |
| `Super + B` | Browser (firefox) |
| `Super + C` | Editor (code) |
| `Super + E` | File manager (thunar) |
| `Super + D` | Discord |
| `Super + M` | Spotify |
| `Super + R` | OBS Studio |
| `Super + V` | Emoji picker (see below) |
| `Super + F` | Mouse driver (Fantech X9 Thor, personal, change or remove in `config.h`) |

### Workspaces

Each workspace remembers its own layout, master size and master count (pertag).

| Keybind | Action |
| --- | --- |
| `Super + 1~9` | Go to workspace 1~9 |
| `Super + Shift + 1~9` | Move window to workspace 1~9 |
| `Super + Ctrl + 1~9` | Show workspace 1~9 in addition to the current one |
| `Super + Ctrl + Shift + 1~9` | Toggle window on workspace 1~9 |
| `Super + Tab` | Go to previously active workspace |
| `Super + 0` | View all workspaces |
| `Super + Shift + 0` | Show window on all workspaces |

### Windows

| Keybind | Action |
| --- | --- |
| `Super + J` / `K` | Focus next / previous window |
| `Super + Shift + J` / `K` | Move window down / up the stack |
| `Super + Return` | Promote focused window to master area |
| `Super + H` / `L` | Decrease / increase master area size |
| `Super + I` / `O` | Increase / decrease number of master windows |
| `Super + Q` | Close window |
| `Super + Shift + T` | Tiled layout |
| `Super + Shift + F` | Floating layout |
| `Super + Shift + M` | Monocle (fullscreen) layout |
| `Super + Space` | Toggle between current and previous layout |
| `Super + Shift + Space` | Toggle floating mode for window |
| `Super + -` / `=` | Decrease / increase gaps |
| `Super + Shift + =` | Reset gaps |
| `Super + Arrows` | Move floating window |
| `Super + Shift + Arrows` | Resize floating window |
| `Super + Ctrl + Arrows` | Move floating window to screen edge |
| `Super + Ctrl + Shift + Arrows` | Stretch floating window to screen edge |

### Monitors

| Keybind | Action |
| --- | --- |
| `Super + ,` / `.` | Focus previous / next monitor |
| `Super + Shift + ,` / `.` | Send window to previous / next monitor |

### Screenshots

Screenshots go to `~/Pictures/Screenshots`.

| Keybind | Action |
| --- | --- |
| `Super + Print` | Screenshot, full screen |
| `Super + Shift + Print` | Screenshot, select region (saved and copied to clipboard) |

### Hardware and network

| Keybind | Action |
| --- | --- |
| `Super + F6` / `F5` | Volume up / down |
| `Super + F3` | Toggle mute |
| `Super + F9` / `F8` | Brightness up / down |
| `Super + N` | Wifi menu |
| `Super + Shift + N` | Toggle wifi |
| `Super + G` | Bluetooth menu |
| `Super + Shift + G` | Toggle bluetooth |

### System

There is no confirmation for reboot and shutdown.

| Keybind | Action |
| --- | --- |
| `Super + Shift + P` | Power profile menu (needs power-profiles-daemon) |
| `Super + Ctrl + P` | Picom mode menu: blur + opacity + vsync, opacity + vsync, vsync only, off |
| `Super + Shift + B` | Toggle status bar |
| `Super + Shift + F5` | Reload bar colors from X resources |
| `Super + Shift + R` | Reboot |
| `Super + Shift + S` | Shutdown |
| `Super + Shift + Q` | Quit dwm |

## Theme from wallpaper (optional)

Bar colors follow the wallpaper using [pywal](https://github.com/dylanaraps/pywal) and the xrdb patch. The status bar from [sxstatus](https://github.com/vq6oon/sxstatus), notifications and kitty follow too.

    sudo apt install xdotool pipx nitrogen inotify-tools dunst libnotify-bin adwaita-icon-theme
    pipx install pywal
    ./pywal/install.sh

Add this to `~/.xsessionrc`, with the `xrdb` line before the status bar starts:

    xrdb -merge ~/.cache/wal/dwm-xres
    nitrogen --restore &
    dunst &
    ~/.local/bin/theme-watch &

Then pick a wallpaper in nitrogen and click Apply. `theme-watch` notices the change and runs `theme`, which regenerates the colors, reloads the dwm bar, restarts sxstatus and recolors notifications and kitty. You can also run `theme` yourself, or `theme /path/to/image`. `Super + Shift + F5` reloads the bar colors from X resources by hand.

The status bar text uses the same foreground color as the dwm bar. Notification borders use an accent picked from the wallpaper and lightened until it is readable.

To make kitty follow the wallpaper too, add this at the end of `~/.config/kitty/kitty.conf`, below the theme block:

    include ~/.cache/wal/colors-kitty.conf

If you ever picked a theme with `kitten themes`, remove `~/.config/kitty/dark-theme.auto.conf`, because it overrides these colors in new windows.

Without pywal, dwm simply uses the colors set in `config.h`.

## Emoji picker (optional)

Type emoji in any app with `Super + V`, using [bemoji](https://github.com/marty-oehme/bemoji) and dmenu.

    sudo apt install xclip xdotool curl fonts-noto-color-emoji
    git clone https://github.com/marty-oehme/bemoji /tmp/bemoji
    install -m 755 /tmp/bemoji/bemoji ~/.local/bin/bemoji

The emoji list is downloaded on first run, so it needs an internet connection once.

## Transparency and blur (optional)

Opacity and blur come from [picom](https://github.com/yshui/picom), not from dwm. Three ready-made configs live in `picom/`, each one heavier than the last:

| Mode | What it does |
| --- | --- |
| `vsync` | vsync only, no transparency |
| `opacity` | vsync and 0.9 window opacity |
| `blur` | opacity, vsync and dual kawase blur (heaviest) |

    sudo apt install picom
    mkdir -p ~/.config/picom
    cp picom/*.conf ~/.config/picom/

`Super + Ctrl + P` opens a menu to switch between the modes or turn picom off, and the choice is remembered for the next login. The menu comes from [sxstatus](https://github.com/vq6oon/sxstatus). To start the last chosen mode at login, add this to `~/.xsessionrc`:

    ~/.config/sxstatus/menus/picom_menu restore &

Blur is heavy on the GPU and can cause stutter and audio crackle while screen sharing or mirroring a phone with scrcpy. Use the `vsync` mode or turn picom off while streaming.

## Configuration

All settings live in `config.h` (`config.def.h` is kept in sync). Edit it, then rebuild with `sudo make clean install` and restart dwm.

## Credits

Based on [dwm](https://dwm.suckless.org/) by suckless.org. Original license is in `LICENSE`, original readme in `README.dwm`.

Cat font by [CarloCattano/waycat](https://github.com/CarloCattano/waycat). Wallpaper colors by [pywal](https://github.com/dylanaraps/pywal). Emoji picker by [bemoji](https://github.com/marty-oehme/bemoji).