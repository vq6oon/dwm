#!/bin/bash

# download waycat, move its glyphs to the private use area and install it

set -e

Here=$(cd "$(dirname "$0")" && pwd)
Tmp=$(mktemp -d)

git clone --depth 1 https://github.com/CarloCattano/waycat "$Tmp/waycat"
cp "$Here/remap.py" "$Tmp/"

cd "$Tmp"
fontforge -lang=py -script remap.py

mkdir -p ~/.local/share/fonts
cp WaycatPUA.ttf ~/.local/share/fonts/
fc-cache -f

rm -rf "$Tmp"
echo "waycat font installed"