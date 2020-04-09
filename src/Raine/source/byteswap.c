#include "raine.h"
#include "files.h"
#include "newmem.h"

int main(int argc, char **argv) {
    if (argc == 1) {
	printf("syntax : byteswap file\n");
	return 0;
    }
    int size = size_file(argv[1]);
    if (size) {
	UINT8 *buf = malloc(size);
	if (!buf) {
	    printf("alloc error for %d bytes\n",size);
	    return -1;
	}
	load_file(argv[1],buf,size);
	ByteSwap(buf,size);
	save_file(argv[1],buf,size);
	free(buf);
    }
    return 0;
}

