/*
 * LZ4 compressor for the Linux kernel.
 *
 * The implementation is LZ4 v1.11.1 (lib/lz4/lz4.c, BSD 2-Clause,
 * Copyright (C) 2011-2023, Yann Collet), built in freestanding mode.
 * This file only adds the kernel specific glue.
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/lz4.h>

#define LZ4_KERNEL_COMPRESS_ONLY
#undef current	/* lz4.c has variables of that name */
#include "lz4.c"

/*-******************************
 *	For backwards compatibility
 ********************************/
int lz4_compress(const unsigned char *src, size_t src_len, unsigned char *dst,
	size_t *dst_len, void *wrkmem)
{
	*dst_len = LZ4_compress_default((const char *)src, (char *)dst,
		src_len, lz4_compressbound(src_len), wrkmem);

	/*
	 * Prior lz4_compress will return -1 in case of error
	 * and 0 on success
	 * while new LZ4_compress_fast/default
	 * returns 0 in case of error
	 * and the output length on success
	 */
	if (!*dst_len)
		return -1;
	else
		return 0;
}

EXPORT_SYMBOL(LZ4_sizeofState);
EXPORT_SYMBOL(LZ4_compress_default);
EXPORT_SYMBOL(LZ4_compress_fast);
EXPORT_SYMBOL(LZ4_compress_fast_extState);
EXPORT_SYMBOL(LZ4_compress_destSize);
EXPORT_SYMBOL(LZ4_initStream);
EXPORT_SYMBOL(LZ4_resetStream_fast);
EXPORT_SYMBOL(LZ4_loadDict);
EXPORT_SYMBOL(LZ4_saveDict);
EXPORT_SYMBOL(LZ4_compress_fast_continue);
EXPORT_SYMBOL(lz4_compress);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("LZ4 compressor");
