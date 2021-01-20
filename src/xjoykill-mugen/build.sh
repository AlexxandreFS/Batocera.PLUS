#!/bin/sh
cc xjoykill.c -o xjoykill -lX11
strip xjoykill
chmod +x xjoykill
exit 0