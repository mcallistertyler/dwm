/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx	= 6;		/* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *alttrayname      = "tray";    /* Polybar tray instance name */
static const char *altbarcmd        = "$HOME/bar.sh"; /* Alternate bar launch command */
static const char *fonts[]	    = { "JF Dot M+ 10:size=11" }; 
static const char dmenufont[]       = "monospace:size=8";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_pastelpink[]  = "#ffcccc";
static const char col_pastelblue[] = "#88ddf0";
static const char col_polybarpurple[] = "#1A1A2E";
static const char col_black[]	    = "#000000";
static const unsigned int baralpha = 0xc8;
static const unsigned int borderalpha = 0xc8;
//static const unsigned int borderalpha = OPAQUE;
//static const char *colors[][3]      = {
	/*               fg         bg         border   */
//	[SchemeNorm] = { col_black, col_pastelpink, col_pastelblue },
//	[SchemeSel]  = { col_black, col_pastelblue,  col_pastelpink },
//};

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_pastelblue, col_gray1, col_gray2 },
	[SchemeSel]  = { col_black, col_pastelpink,  col_pastelblue },
};

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* Fn keys */
#define XF86MonBrightnessDown	0x1008ff03
#define XF86MonBrightnessUp	0x1008ff02
#define XF86AudioMute		0x1008ff12
#define XF86AudioRaiseVolume	0x1008ff13
#define XF86AudioLowerVolume	0x1008ff11

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
#include "fibonacci.c"
#include "cmaster.c"
#include "layouts.c"

static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "tile",		tile },    /* first entry is default */
	{ "float",		NULL },    /* no layout function means floating behavior */
	{ "zoom",		monocle },
	{ "spiral",		spiral },
	{ "dwindle",		dwindle },
	{ "cmaster",		centeredmaster },
	{ "cfmaster",		centeredfloatingmaster },
	{ "grid",		grid },
	{ NULL,			NULL },
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
#include "push.c"
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *dmenucmd[] = { "rofi", "-show", "run", "-display-run", ">>> ", NULL};
static const char *termcmd[]  = { "alacritty", NULL };
// Not currently working, needs a super cool "im definitely not a cunt" terminal like st
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

/* Brightness */
static const char *cmdbrightnessup[] = { "brightnessctl", "set", "+10", NULL };
static const char *cmdbrightnessdown[] = { "brightnessctl", "set", "-10", NULL };

/* Volume */
static const char *cmdvolumeup[] = { "amixer", "set", "Master", "5%+" , NULL };
static const char *cmdvolumedown[] = { "amixer", "set", "Master", "5%-" , NULL };
static const char *cmdvolumetoggle[] = { "amixer", "set", "Master", "toggle", NULL };

/* Screen locking */
static const char *cmdlock[] = { "i3lock-fancy-rapid", "5", "10", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,						XK_f,	   togglescratch,  {.v = scratchpadcmd }},
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,				XK_Left,   pushdown,       	{0} },
	{ MODKEY|ShiftMask,				XK_Right,  pushup,       	{0} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,						XK_q,	   setlayout,      {.v = &layouts[3]} },
	{ MODKEY,						XK_w,	   setlayout,	   {.v = &layouts[4]} },
	{ MODKEY,						XK_e,	   setlayout,	   {.v = &layouts[5]} },
	{ MODKEY,						XK_r,	   setlayout,	   {.v = &layouts[6]} },
	{ MODKEY,						XK_y,	   setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ShiftMask,			    XK_f,	   cyclelayout,    {.i = -1 } },
	{ MODKEY|ShiftMask,           	XK_g,	   cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,				XK_l,	   spawn,		   {.v = cmdlock } },
	{ 0,							XF86MonBrightnessDown, 	   spawn, {.v = cmdbrightnessdown } },
	{ 0,							XF86MonBrightnessUp,	   spawn, {.v = cmdbrightnessup } },
	{ 0,							XF86AudioLowerVolume,	   spawn, {.v = cmdvolumedown } },
	{ 0,							XF86AudioRaiseVolume,	   spawn, {.v = cmdvolumeup } },
	{ 0,							XF86AudioMute,			   spawn, {.v = cmdvolumetoggle } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_p,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_p,      quit,           {1} },
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

