UNIVERSE BIOS 3.3 for the NeoGeo CD system
------------------------------------------


  homepage = http://www.universebios.com
  email    = info@universebios.com


WARNING
-------
I TAKE NO RESPONSIBILITY FOR ANY DAMAGE CAUSED TO YOUR NEO•GEO CD HARDWARE WHILE
INSTALLING OR USING THE UNIVERSE BIOS. WHILE THE BIOS HAS BEEN FULLY TESTED ON THIS
HARDWARE YOU USE IT AT YOUR OWN RISK.

INSTALLING THE UNIVERSE BIOS ON THE NEO•GEO CD SYSTEM IS NOT EASY. DO NOT ATTEMPT TO
INSTALL YOURSELF UNLESS YOU KNOW WHAT YOU ARE DOING. IF IN DOUBT I SUGGEST CONTACTING
AN INSTALLER WHO CAN TO IT FOR YOU.

THE UNIVERSE BIOS HAS BEEN DESIGNED FOR NON COMMERCIAL USERS OF THE NEO•GEO CD TOP
LOADER, FRONT LOADER AND CDZ.


TERMS OF USE
------------
You can use the UNIVERSE BIOS as long as you own original genuine NeoGeo hardware.
Failure of this may result in you the user violating international copyright laws.
New program code within the UNIVERSE BIOS is (c) Razoola, original BIOS program
code remains copyrighted to SNK.

  DO NOT REVERSE ENGINEER, ALTER OR CHANGE THE UNIVERSE BIOS DATA OR CODE IN ANY WAY.

  DO NOT PROVIDE A SERVICE OFFERING THE UNIVERSE BIOS ON EPROM OR OTHER PHYSICAL
  FORMAT (FREE OR FOR PROFIT).

  DO NOT DISTRIBUTE A DUMP OF THE UNIVERSE BIOS UNLESS YOU ARE LEGALLY ABLE TO DO SO.
  I WILL NOT BE HELD RESPONSIBLE FOR OTHERS ACTIONS.


DONATIONS
---------
Although the UNIVERSE BIOS is free, if you find it useful then please consider donating
to help the cause. More information can be found on the official UNIVERSE BIOS homepage.


---------------------------------------------------------------------------------


INTRODUCTION
------------

The UNIVERSE BIOS is for owners of CD hardware that want an easy way to change country
region or between Arcade or Console mode on boot. Also included are other features that
are not normally possible using the standard CD bios.


  MAIN FEATURES
  -------------

  - Brings the CDZ style radio screen to Top and Front Loaders.

  - The ability to quickly and easily change country region (great for games that
    disable blood under USA region).

  - Want unlimited lives or energy... Then cheat in games using the built in
    cheat engine which currently holds over 1570 cheats!!!

  - If you are not happy with the cheats already there then you can patch
    directly into memory any place you like adding your own.

  - Access to the DEBUG DIP's and DEVELOPER mode.

  - PC-2-NEO which gives the ability to upload and download data from the
    system using a cable which can be easily built. 


  Other features
  --------------

  - Once region and operation mode is set the BIOS will remember settings until you
    change them again.

  - Look at internal memory with the built in memory viewer. This is handy for
    tracking faults with slots that don't work (multislot hardware) or carts
    that simply won't start.

  - The ability to soft reboot the system without the need of powering off and on.

  - Slightly faster loading on Top/Front Loaders (hardly noticeable but it's there). 

  - An MVS/AES BIOS SWITCH option (see below).

  - Suppress CD sector checks (failing drives work in some cases).


---------------------------------------------------------------------------------


USING THE CD UNIVERSE BIOS
--------------------------
The first time a CD system is switched on after UNIVERSE BIOS installation the
system will default to EURO region and the system type will be set as TOP LOADER
unless the system is a FRONT LOADER.

  Important Notes
  ---------------
  An incorrect system setting will cause the CD drive not to work correctly.

  If the systems backup SRAM battery is dead any changed settings will be lost on
  power down and the default settings will be reloaded. I would suggest recharging
  or replacing the onboard battery in this situation.


Accessing Menus
---------------
The following codes should be used while on the CD radio screen. 

  SELECT  = Main UNIVERSE BIOS Menu
  B+C	  = Access PC-2-NEO
  C+D	  = Eject (Front Loader only)

The following code is available in game only;

  START+SELECT = In Game Menu


The Main Menu
-------------
To navigate use player one controls, button (A) to select, (C) to exit. The Universe Bios
serial number is also displayed here. 

  Region
  ------
  Select the systems region, settings made here are stored. Options are; JP (Japan),
  US (USA), EU (Europe), BR (Brazil).

  System
  ------
  Select the system type. Options are Top Loader or CDZ. This must be set correctly before
  the CD drive will function correctly. On Front Loaders this option cannot be changed.


The In Game Menu
----------------
To navigate the In Game menus use player one controls and button (A) to select. Not doing
anything for a short period will cause the screen to blank while idle. This feature
prevents monitor burn if using the In Game menu to pause games. Available options are.

  The Cheat Database
  ------------------
  Everything is quite straight forward here although using cheats can cause adverse game
  effects. For example, if you experience game lockups when using a cheat try turning it
  off which may allow the game to continue and then enable it again later. Cheats can also
  cause GFX issues, most notably at the end for energy bars. On MULTISLOT hardware any
  active cheats will be disabled when changing game, they will not be restored automatically.

  Debug DIP Settings
  ------------------
  These settings are more advanced. Debug DIPS do different things depending on the game,
  unless you know what your doing it’s best to leave them alone although experimenting won’t
  cause damage. If a cheat is enabled that uses a games debug dip address you will see it
  via a highlighted number under the DIP value.

  Patch Memory
  ------------
  Here you can manually choose addresses in the NeoGeo memory space and patch byte values
  there. For example by placing different values into 0x320000 you can change any currently
  playing music. You can also use this feature for cheats and other stuff.

  Last menu option (selectable)
  -----------------------------
  The final menu setting is changeable, do this by moving the joystick left or right once
  highlighted. Possible options are;

    Soft Reboot System
    Menu Color Changer 
    Main Memory Viewer	
    Video RAM Viewer
    PC-2-NEO


---------------------------------------------------------------------------------


MVS/AES Bios switch
------------------- 
The CD UNIVERSE BIOS contains a dev MVS/AES UNIVERSE BIOS, install a switch for access.
Use contacts on the CD BiosMasta or lift A17 (pin 1) from PCB and switch it between
VCC (pin 21) and the address line where pin 1 would be connected on PCB. 
  
Using this in connection with PC-2-NEO makes it possible to upload and run homebrew
projects in an MVS/AES environment. It should be possible to load data into memory from
a CD (with CD UNIVERSE BIOS) and then switching to the MVS/AES bios. 
  
All MVS/AES button codes work plus these two codes accessible during system boot.

  A+B	      =	Force PC-2-NEO start
  A+B+SELECT  =	Reset font & Force PC-2-NE0 start

Note that the systems memory spec is a limiting factor in the size of data that can be
loaded. That aside the CD system is a good development tool for small game projects. 


---------------------------------------------------------------------------------


BURNING THE CD UNIVERSE BIOS ONTO EPROM
---------------------------------------

The CD UNIVERSE BIOS requries a 27C400 type EPROM, simply burn the UNIVERSE BIOS image
onto it and then put it in place of the original BIOS on your NeoGeo hardware.


OBTAINING THE UNIVERSE BIOS ON EPROM
------------------------------------

If you would like the CD UNIVERSE BIOS provided on EPROM because you don't have the ability
to do it yourself then visit the official homepage for information on how to get one.


---------------------------------------------------------------------------------