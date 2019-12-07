Adobe
Flash Player for Linux
Version 32.0.0.293

Adobe recommends that all users upgrade to the latest version of Adobe Flash 
Player for the most recent features, bug fixes, and security fixes.  
For more information on the new features in Flash Player, please visit 
http://www.adobe.com/products/flashplayer/.  For more information on system 
requirements, fixed issues, and known issues, see the release notes at 
https://helpx.adobe.com/flash-player/flash-player-releasenotes.html

To confirm which version of Flash Player you have currently installed, see 
http://www.adobe.com/software/flash/about/. Users should only install 
Players that have been downloaded from trusted sources, such as 
https://get.adobe.com/flashplayer/

Your use of this player is governed by the Adobe End User License Agreement 
found at http://www.adobe.com/legal/licenses-terms.html


Privacy
-------

Adobe is committed to preserving the privacy of end users. For more 
information on configuring Client-side privacy visit the Settings Manager 
Documentation: http://www.adobe.com/go/flashplayerhelp.


Installation instructions
-------------------------

Installing using the plugin tar.gz:
	o Unpack the plugin tar.gz and copy the files to the appropriate location.  
	o Save the plugin tar.gz locally and note the location the file was saved to.
	o Launch terminal and change directories to the location the file was saved to.
	o Unpack the tar.gz file.  Once unpacked you will see the following:
		+ libflashplayer.so
		+ /usr
	o Identify the location of the browser plugins directory, based on your Linux distribution and Firefox version
	o Copy libflashplayer.so to the appropriate browser plugins directory.  At the prompt type:
		+ cp libflashlayer.so <BrowserPluginsLocation>
	o Copy the Flash Player Local Settings configurations files to the /usr directory.  At the prompt type:
		+ sudo cp -r usr/* /usr

Installing the plugin using RPM:
   o As root, enter in terminal:
          + # rpm -Uvh <rpm_package_file>
          + Click Enter key and follow prompts

Installing the standalone player:
   o Unpack the tar.gz file
   o To execute the standalone player,
          + Double-click, or 
          + Enter in terminal: ./flashplayer


Uninstallation instructions
---------------------------

Manual uninstallation (for users who installed the plugin via Install script):
   o Delete libflashplayer.so binary and flashplayer.xpt file in 
   directory /home/<user>/.mozilla/plugins/

RPM uninstallation:
   o As root, enter in terminal:
          + # rpm -e flash-plugin
          + Click Enter key and follow prompts


Technical Issues and Reporting Bugs
-----------------------------------
 
The Adobe Support Center at https://helpx.adobe.com/support.html is a 
free online resource for support and troubleshooting information. 
Bug reports may be submitted at http://www.adobe.com/go/wish. 
To allow us to investigate reported bugs, please include the following 
information:
 
1) Platform and version
2) Browser version
3) Reproducible steps including a URL to the web site where the problem 
   was encountered.
 
If we need further information about a bug, you will be contacted. An 
automated reply will be sent to assure you that we have received your 
bug report. Due to the volume of mail received, we are not able to 
individually respond to each report.


Legal
-----

Adobe(R) Flash(R) Player. Copyright (C) 1996 - 2019 Adobe 
All Rights Reserved. Adobe and Flash  are either trademarks
or registered trademarks in the United States and/or other countries.

