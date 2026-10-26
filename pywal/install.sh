#!/bin/bash

# install the theme scripts and pywal templates

Dir=$(dirname "$(readlink -f "$0")")

mkdir -p ~/.local/bin ~/.config/wal/templates
install -m 755 "$Dir/theme" ~/.local/bin/theme
install -m 755 "$Dir/theme-watch" ~/.local/bin/theme-watch
install -m 755 "$Dir/theme-dunst" ~/.local/bin/theme-dunst
install -m 755 "$Dir/theme-accent" ~/.local/bin/theme-accent
install -m 755 "$Dir/theme-neutral" ~/.local/bin/theme-neutral
install -m 755 "$Dir/theme-accent" ~/.local/bin/theme-accent
install -m 755 "$Dir/theme-neutral" ~/.local/bin/theme-neutral
cp "$Dir"/templates/* ~/.config/wal/templates/

echo "done. pick a wallpaper in nitrogen and run: theme"
echo "for automatic updates, add this to ~/.xsessionrc: ~/.local/bin/theme-watch &"
