### Dynamic Window Manager

___
![](https://i.imgur.com/wHjGKl3.png)
___

### This fork has the following pacthed features:

* Removed window title ([notitle](https://dwm.suckless.org/patches/notitle))
* Fullscreen mode ([fullscreen](https://dwm.suckless.org/patches/fullscreen))
* Prevents empty tags from being shown ([hide_vacant_tags](https://dwm.suckless.org/patches/hide_vacant_tags))
* Keeps layouts per tag ([pertag](https://dwm.suckless.org/patches/pertag))
* Had some code changed to work with my build of [dwmblocks](https://github.com/cfelipe/dwmblocks).

### Requirements

In order to build dwm you need the Xlib header files.


### Installation

`sudo make install`


### Running dwm

Add the following line to your .xinitrc to start dwm using startx:

`exec dwm`
