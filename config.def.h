/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = {
  "Inconsolata Nerd Font Mono:style=Regular:pixelsize=15:antialias=true:autohint=true",
  "Font Awesome 5 Free:style=Regular:pixelsize=15:antialias=true:autohint=true",
};

static const char dmenufont[]       = "Inconsolata:size=13";

static const char col_gray1[]       = "#111";       /* backgruond color */
static const char col_gray2[]       = "#444";       /* inactive window border color */
static const char col_gray3[]       = "#e6e6e6";    /* font color */
static const char col_gray4[]       = "#78c";       /* current tag and current window font color */
static const char col_cyan[]        = "#111";       /* top bar second color and active window border color */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray4 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                                     instance    title       tags mask     isfloating   monitor */
	{ "Chromium-browser-ungoogled-chromium",     NULL,       NULL,       1,            0,           -1 },
	{ "KeePassXC",                               NULL,       NULL,       1 << 6,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,                      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,                 spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,                      togglebar,      {0} },
	{ MODKEY,                       XK_j,                      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return,                 zoom,           {0} },
	{ Mod1Mask,                     XK_Tab,                    view,           {0} },
	{ MODKEY,                       XK_q,                      killclient,     {0} },
	{ MODKEY,                       XK_t,                      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                  togglefloating, {0} },
	{ MODKEY,                       XK_0,                      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                 tagmon,         {.i = +1 } },
	{ ControlMask|Mod1Mask,         XK_l,                      shiftview,      {.i = +1 } },
	{ ControlMask|Mod1Mask,         XK_h,                      shiftview,      {.i = -1 } },
	{ 0,                            XK_Print,                  spawn,          SHCMD("import png:- | xclip -selection clipboard -t image/png") },
	{ ShiftMask,                    XK_Print,                  spawn,          SHCMD("import ~/Images/Screenshots/$(date +%Y-%m-%d-%H:%M:%S).png") },
	{ ControlMask,                  XK_Print,                  spawn,          SHCMD("printupload") },
        { 0,                            XF86XK_AudioRaiseVolume,   spawn,          SHCMD("amixer set Master 5%+ | pkill -RTMIN+11 dwmblocks") },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,	   SHCMD("amixer set Master 5%- | pkill -RTMIN+11 dwmblocks") },
	{ 0,                            XF86XK_AudioMute,	   spawn,          SHCMD("amixer set Master toggle | pkill -RTMIN+11 dwmblocks") },
	{ 0,                            XF86XK_AudioPrev,          spawn,          SHCMD("mpc prev | pkill -RTMIN+10 dwmblocks") },
	{ 0,                            XF86XK_AudioNext,          spawn,          SHCMD("mpc next | pkill -RTMIN+10 dwmblocks") },
	{ 0,                            XF86XK_AudioStop,          spawn,          SHCMD("mpc stop | pkill -RTMIN+10 dwmblocks") },
	{ 0,                            XF86XK_AudioPlay,          spawn,          SHCMD("mpc toggle | pkill -RTMIN+10 dwmblocks") },
	{ MODKEY,		        XK_u,                      spawn,	   SHCMD("emojilist") },
	{ MODKEY,		        XK_y,                      spawn,	   SHCMD("st -e neomutt") },
	{ MODKEY,		        XK_g,                      spawn,	   SHCMD("st -e vifmrun") },
	{ MODKEY,		        XK_n,                      spawn,	   SHCMD("st -e ncmpcpp") },
	{ MODKEY,		        XK_e,                      spawn,	   SHCMD("st -f 'Inconsolata Nerd Font:style=Regular:pixelsize=18:antialias=true:autohint=true' -e calcurse") },
	{ MODKEY,		        XK_c,                      spawn,	   SHCMD("st -e ssh -i ~/.ssh/homeserver_key felipe@homeserver -t tmux a -t weechat") },
	{ MODKEY,		        XK_w,                      spawn,	   SHCMD("st -e nvim ~/Documents/notes/index.md") },
	{ MODKEY,		        XK_F1,                     spawn,	   SHCMD("sshfs-manager phone /home/$USER/Documents/remote-devices/phone /storage/emulated/0/ 'Phone SSHFS'") },
	{ MODKEY,		        XK_F2,                     spawn,	   SHCMD("sshfs-manager homeserver /home/$USER/Documents/remote-devices/homeserver / 'Homeserver SSHFS'") },
	{ MODKEY,		        XK_F3,                     spawn,	   SHCMD("sshfs-manager vps /home/$USER/Documents/remote-devices/vps /home/felipe 'VPS SSHFS'") },
	{ MODKEY|ShiftMask,		XK_i,                      spawn,	   SHCMD("/opt/KeepassXC/KeePassXC-2.5.4-x86_64.AppImage") },
	{ MODKEY|ShiftMask,		XK_b,                      spawn,	   SHCMD("blogenv") },
	{ MODKEY|ShiftMask,		XK_x,                      spawn,	   SHCMD("slock") },
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
static Button buttons[] = {
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

