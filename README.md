# dwm rice

dwm dengan patch yang sudah ter-apply, jadi tidak perlu patch manual.

![screenshot](screenshots/dwm.png)

## Patch
- bar-height
- fullgaps
- moveresize
- noborderfloatingfix

Folder `patches/` hanya referensi dan kredit.

## Dependensi
    sudo apt install build-essential libx11-dev libxft-dev libxinerama-dev

Font: (isi font yang kamu pakai)

## Install
    git clone https://github.com/vq6oon/dwm.git
    cd dwm
    sudo make clean install

Tambahkan `exec dwm` di `~/.xinitrc`.

## Kredit
Berdasarkan [dwm](https://dwm.suckless.org/) dari suckless.org. Lisensi asli ada di `LICENSE`.
