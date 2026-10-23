cat > pywal/install.sh << 'EOF'
#!/bin/bash

# install the theme script and pywal templates

Dir=$(dirname "$(readlink -f "$0")")

mkdir -p ~/.local/bin ~/.config/wal/templates
install -m 755 "$Dir/theme" ~/.local/bin/theme
cp "$Dir"/templates/* ~/.config/wal/templates/

echo "done, pick a wallpaper in nitrogen and run: theme"
EOF
chmod +x pywal/install.sh pywal/theme
