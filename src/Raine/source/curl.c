/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2018, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
/* <DESC>
 * Download a given URL into a local file named page.out.
 * </DESC>
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <curl/curl.h>
#include <string.h>
#include "gui.h" // load_progress

static int progress_callback(void *clientp,
                             curl_off_t dltotal,
                             curl_off_t dlnow,
                             curl_off_t ultotal,
                             curl_off_t ulnow) {
    if (dltotal == 0) return 0;
    curl_progress_f(dlnow*100/dltotal);
    return 0; // non 0 to abort transfer
}

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

extern CURL *curl_handle;

int get_url(char *file, char *url)
{
  FILE *pagefile;
  int ret;

  // All the init stuff is taken care in raine.c, so that the connection can be re-used
  // internet archive is sadly regularly slow, it has a heavy traffic clearly so we use
  // all we can to speed up the transfer... !

  /* set URL to get here */
  curl_easy_setopt(curl_handle, CURLOPT_URL, url);

  /* Switch on full protocol/debug output while testing */
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 0L);

  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

  curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curl_handle, CURLOPT_XFERINFODATA, NULL);
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 0L);
  curl_easy_setopt(curl_handle, CURLOPT_XFERINFOFUNCTION, progress_callback);
  curl_easy_setopt(curl_handle, CURLOPT_NOBODY, 1);

  /* open the file */
  ret = curl_easy_perform(curl_handle);
  char *ct = "";
  if (ret == CURLE_OK)
      curl_easy_getinfo(curl_handle,CURLINFO_CONTENT_TYPE,&ct);
  if (strcmp(ct,"application/zip")) {
      printf("curl: didn't get application/zip, aborting...\n");
      return 1;
  }
  curl_easy_setopt(curl_handle, CURLOPT_NOBODY, 0);

  pagefile = fopen(file, "wb");
  if(pagefile) {

    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);

    /* get it! */
    ret = curl_easy_perform(curl_handle);

    /* close the header file */
    fclose(pagefile);
  }

  return ret;
}

