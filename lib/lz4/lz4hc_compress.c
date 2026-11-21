/*
 * LZ4 HC compressor for the Linux kernel.
 *
 * The implementation is LZ4 v1.11.1 (lib/lz4/lz4hc.c, BSD 2-Clause,
 * Copyright (C) 2011-2023, Yann Collet), built in freestanding mode.
 * This file only adds the kernel specific glue.
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/lz4.h>

#undef current	/* lz4hc.c has variables of that name */
#include "lz4hc.c"

/*-******************************
 *	For backwards compatibility
 ********************************/
int lz4hc_compress(const unsigned char *src, size_t src_len,
	unsigned char *dst, size_t *dst_len, void *wrkmem)
{
	*dst_len = LZ4_compress_HC((const char *)src, (char *)dst, src_len,
		lz4_compressbound(src_len), LZ4HC_DEFAULT_CLEVEL, wrkmem);

	/*
	 * Prior lz4hc_compress will return -1 in case of error
	 * and 0 on success
	 * while new LZ4_compress_HC
	 * returns 0 in case of error
	 * and the output length on success
	 */
	if (!*dst_len)
		return -1;
	else
		return 0;
}

EXPORT_SYMBOL(LZ4_compress_HC);
EXPORT_SYMBOL(LZ4_compress_HC_destSize);
EXPORT_SYMBOL(LZ4_initStreamHC);
EXPORT_SYMBOL(LZ4_resetStreamHC_fast);
EXPORT_SYMBOL(LZ4_setCompressionLevel);
EXPORT_SYMBOL(LZ4_loadDictHC);
EXPORT_SYMBOL(LZ4_compress_HC_continue);
EXPORT_SYMBOL(LZ4_compress_HC_continue_destSize);
EXPORT_SYMBOL(LZ4_saveDictHC);
EXPORT_SYMBOL(lz4hc_compress);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("LZ4 HC compressor");
