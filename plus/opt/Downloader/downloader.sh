#!/bin/sh
#
# NAME:         yad_wget
# VERSION:      0.2
# AUTHOR:       (c) 2014 Glutanimate
# DESCRIPTION:  graphical frontend to wget in form of a yad script
# FEATURES:     - display progress of multiple simultaneous downloads
#               - set maximum number of simultaneous downloads
# DEPENDENCIES: yad
#
#               Install yad on Ubuntu with:
#
#                   sudo add-apt-repository ppa:webupd8team/y-ppa-manager
#                   sudo apt-get update
#                   sudo apt-get install yad
#
# LICENSE:      GNU GPLv3 (http://www.gnu.de/documents/gpl-3.0.en.html)
#
# NOTICE:       THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW. 
#               EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES 
#               PROVIDE THE PROGRAM “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR 
#               IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
#               AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND 
#               PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE,
#               YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
#
#               IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING WILL ANY 
#               COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS THE PROGRAM AS 
#               PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY GENERAL, SPECIAL, 
#               INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE 
#               THE PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR DATA BEING RENDERED 
#               INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES OR A FAILURE OF THE 
#               PROGRAM TO OPERATE WITH ANY OTHER PROGRAMS), EVEN IF SUCH HOLDER OR OTHER 
#               PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
#
# USAGE:        yad_wget <space-delimited URLs>
#               Closing the yad dialog will terminate all downloads in progress

# Variables and settings

MAXDLS="5" # set maximum number of simultaneous downloads

URILIST="${1}" # gets list of URIs from stdin
SAVE_PATCH="${2}"
USAGE="$0 <space-delimited URLs>"

# Set GUI variables up
TITLE="Batocera.PLUS downloader"            # dialog title
TEXT="<b>Downloads</b> in progress:"        # dialog text
ICON="emblem-downloads"                     # window icon (appears in launcher)
IMAGE="browser-download"                    # window image (appears in dialog)

#URILIST="http://proof.ovh.net/files/100Mb.dat http://speedtest.wdc01.softlayer.com/downloads/test10.zip http://cachefly.cachefly.net/100mb.test"

# Usage checks

if [[ -z "$URILIST" ]]
  then
      echo "Error: No arguments provided"
      echo "Usage: $USAGE"
      exit 1
fi

if [ "${SAVE_PATCH}" != '' ]; then
    SAVE_PATCH="${HOME}/../downloads"
fi


# download file and extract progress, speed and ETA from wget
# we use sed regex for this
# source: http://ubuntuforums.org/showthread.php?t=306515&page=2&p=7455412#post7455412
# modified to work with different locales and decimal point conventions
download(){
    wget -c -P "${SAVE_PATCH}" "$1" 2>&1 | sed -r \
    "s/.* \([0-9]\+%\)\ \+\([0-9,.]\+.\) \(.*\)/$2:\1\n$2:# Downloading at \2\/s, ETA \3/"
    RET_WGET="${PIPESTATUS[0]}"             # get return code of wget
    if [[ "$RET_WGET" = 0 ]]                # check return code for errors
      then
          echo "$2:100%"
          echo "$2:#Download completed."
      else
          echo "$2:#Download error."
    fi
}


# compose list of bars for yad
for URI in $URILIST; do                     # iterate through all URIs
    FILENAME="${URI##*/}"                   # extract last field of URI as filename
    YADBARS="$YADBARS --bar=$FILENAME:NORM" # add filename to the list of URIs
done

IFS=" "
COUNTER="1"
DYNAMIC_COUNTER="1"

# main
# iterate through all URIs, download them in the background and 
# pipe all output simultaneously to yad
# source: http://pastebin.com/yBL2wjaY

for URI in $URILIST; do
    if [[ "$DYNAMIC_COUNTER" = "$MAXDLS" ]] # only download n files at a time
      then
          download "$URI" "$COUNTER"        # if limit reached wait until wget complete
          DYNAMIC_COUNTER="1"               # before proceeding (by not sending download() to bg)
      else
          download "$URI" "$COUNTER" &      # pass URI and URI number to download()
          DYNAMIC_COUNTER="$[$DYNAMIC_COUNTER+1]"
    fi
    COUNTER="$[$COUNTER+1]"                 # increment counter
done | yad --multi-progress --no-buttons --auto-close $YADBARS --title "$TITLE" \
--text "$TEXT" --window-icon "$ICON" --image "$IMAGE"

# ↑ launch yad multi progress-bar window