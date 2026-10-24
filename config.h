/* See LICENSE file for copyright and license details. */

/* include */
#include <X11/XF86keysym.h>
#include "movestack.c"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 0;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "monospace:size=10", "FontAwesome:size=10", "Waycat:size=14" };
static const char dmenufont[]       = "monospace:size=10";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
        /* xprop(1):
         *      WM_CLASS(STRING) = instance, class
         *      WM_NAME(STRING) = title
         */
        /* class      instance    title       tags mask     isfloating   monitor */
        { "Gimp",     NULL,       NULL,       0,            1,           -1 },
        { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
        { "org-tlauncher-tlauncher-rmo-TLauncher", NULL,    NULL,  0,         1,          -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 60;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
        /* symbol          arrange function */
        { "[]= \uE000",    tile },    /* first entry is default */
        { "><> \uE002",    NULL },    /* no layout function means floating behavior */
        { "[M] \uE010",    monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
        { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
        { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
        { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *code[] = { "code", NULL };
static const char *discord[] = { "discord", NULL };
static const char *spotify[] = { "spotify", NULL };
static const char *browser[] = { "firefox", NULL };
static const char *obs[] = { "obs", NULL };
static const char *restart[] = { "systemctl", "reboot", NULL };
static const char *shutdown[] = { "systemctl", "poweroff", NULL };
static const char *files[] = { "thunar", NULL };
static const char *wifimenu[]   = { "/bin/sh", "-c", "$HOME/.config/sxstatus/menus/wifi_menu", NULL };
static const char *btmenu[]     = { "/bin/sh", "-c", "$HOME/.config/sxstatus/menus/bt_menu", NULL };
static const char *wifitoggle[] = { "/bin/sh", "-c", "if [ \"$(nmcli radio wifi)\" = enabled ]; then nmcli radio wifi off; else nmcli radio wifi on; fi", NULL };
static const char *bttoggle[]   = { "/bin/sh", "-c", "if bluetoothctl show | grep -q 'Powered: yes'; then bluetoothctl power off; else rfkill unblock bluetooth; bluetoothctl power on; fi", NULL };
static const char *emoji[] = { "/bin/sh", "-c", "$HOME/.local/bin/bemoji -t", NULL };
static const char *screenshot[] = { "/bin/sh", "-c", "scrot \"$HOME/Pictures/Screenshots/%Y-%m-%d-%T-screenshot.jpg\"", NULL };
static const char *shotcrop[]   = { "/bin/sh", "-c", "mkdir -p $HOME/Pictures/Screenshots && maim -s | tee \"$HOME/Pictures/Screenshots/$(date +%Y-%m-%d-%H%M%S)-crop.png\" | xclip -selection clipboard -t image/png", NULL };
static const char *mousetweak[] = { "/bin/sh", "-c", "python3 \"$HOME/.FantechX9ThorDriver/driver_frontend.py\"", NULL };
static const char *volup[] = { "amixer", "set", "Master", "5%+", NULL };
static const char *voldown[] = { "amixer", "set", "Master", "5%-", NULL };
static const char *voltoggle[] = { "amixer", "set", "Master", "toggle", NULL };
static const char *brightup[] = { "brightnessctl", "set", "+5%", NULL };
static const char *brightdown[] = { "brightnessctl", "set", "5%-", NULL };

static const Key keys[] = {
        /* modifier                     key        function        argument */
        { MODKEY,                       XK_n,      spawn,          {.v = wifimenu } },
        { MODKEY|ShiftMask,             XK_n,      spawn,          {.v = wifitoggle } },
        { MODKEY,                       XK_g,      spawn,          {.v = btmenu } },
        { MODKEY|ShiftMask,             XK_g,      spawn,          {.v = bttoggle } },
        { MODKEY,                       XK_e,      spawn,          {.v = files } },
        { MODKEY,                       XK_v,      spawn,          {.v = emoji } },
        { MODKEY|ShiftMask,             XK_F5,     xrdb,           {.v = NULL } },
        { MODKEY,                       XK_r,      spawn,          {.v = obs} },
        { MODKEY,                       XK_d,      spawn,          {.v = discord} },
        { MODKEY,                       XK_m,      spawn,          {.v = spotify} },
        { MODKEY,                       XK_b,      spawn,          {.v = browser} },
        { MODKEY,                       XK_c,      spawn,          {.v = code} },
        { MODKEY|ShiftMask,             XK_r,      spawn,          {.v = restart} },
        { MODKEY|ShiftMask,             XK_s,      spawn,          {.v = shutdown} },
        { MODKEY,                       XK_f,      spawn,          {.v = mousetweak} },
        { MODKEY,                       XK_F9,     spawn,          {.v = brightup} },
        { MODKEY,                       XK_F8,     spawn,          {.v = brightdown} },
        { MODKEY,                       XK_Print,  spawn,          {.v = screenshot } },
        { MODKEY|ShiftMask,             XK_Print,  spawn,          {.v = shotcrop } },
        { MODKEY,                       XK_F6,     spawn,          {.v = volup } },
        { MODKEY,                       XK_F5,     spawn,          {.v = voldown } },
        { MODKEY,                       XK_F3,     spawn,          {.v = voltoggle } },
        { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
        { MODKEY,                       XK_t,      spawn,          {.v = termcmd } },
        { MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
        { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
        { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
        { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
        { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
        { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
        { MODKEY,                       XK_Return, zoom,           {0} },
        { MODKEY,                       XK_Tab,    view,           {0} },
        { MODKEY,                       XK_q,      killclient,     {0} },
        { MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
        { MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
        { MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_space,  setlayout,      {0} },
        { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
        { MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
        { MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
        { MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
        { MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
        { MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
        { MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
        { MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
        { MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
        { MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
        { MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
        { MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
        { MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
        { MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
        { MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
        { MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
        { MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
        { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
        { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        { MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
        { MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
        { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
        TAGKEYS(                        XK_1,                      0)
        TAGKEYS(                        XK_2,                      1)
        TAGKEYS(                        XK_3,                      2)
        TAGKEYS(                        XK_4,                      3)
        TAGKEYS(                        XK_5,                      4)
        TAGKEYS(                        XK_6,                      5)
        TAGKEYS(                        XK_7,                      6)
        TAGKEYS(                        XK_8,                      7)
        TAGKEYS(                        XK_9,                      8)
        { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
        /* click                event mask      button          function        argument */
        { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
        { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
        { ClkWinTitle,          0,              Button2,        zoom,           {0} },
        { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
        { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
        { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
        { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
        { ClkTagBar,            0,              Button1,        view,           {0} },
        { ClkTagBar,            0,              Button3,        toggleview,     {0} },
        { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
        { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

