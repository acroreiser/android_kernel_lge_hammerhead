/*
 * LZ4 decompressor for the Linux kernel.
 *
 * The implementation is LZ4 v1.11.1 (lib/lz4/lz4.c, BSD 2-Clause,
 * Copyright (C) 2011-2023, Yann Collet), built in freestanding mode.
 * This file only adds the kernel specific glue.
 *
 * It is also #included by lib/decompress_unlz4.c for the pre-boot
 * decompressor (STATIC), where only the decoder itself is wanted.
 */
#include <linux/lz4.h>
#ifndef STATIC
#include <linux/module.h>
#include <linux/kernel.h>
#endif

#define LZ4_KERNEL_DECOMPRESS_ONLY
#undef current	/* lz4.c has variables of that name */
#include "lz4.c"

/*-******************************
 *	For backwards compatibility
 ********************************/
int lz4_decompress_unknownoutputsize(const unsigned char *src,
	size_t src_len, unsigned char *dest, size_t *dest_len)
{
	*dest_len = LZ4_decompress_safe((const char *)src, (char *)dest,
		src_len, *dest_len);

	/*
	 * Prior lz4_decompress_unknownoutputsize will return
	 * 0 for success and a negative result for error
	 * new LZ4_decompress_safe returns
	 * - the length of data read on success
	 * - and also a negative result on error
	 * meaning when result > 0, we just return 0 here
	 */
	if ((int)*dest_len > 0)
		return 0;
	else
		return -1;
}

int lz4_decompress(const unsigned char *src, size_t *src_len,
	unsigned char *dest, size_t actual_dest_len)
{
	*src_len = LZ4_decompress_fast((const char *)src, (char *)dest,
		actual_dest_len);

	/*
	 * Prior lz4_decompress will return
	 * 0 for success and a negative result for error
	 * new LZ4_decompress_fast returns
	 * - the length of data read on success
	 * - and also a negative result on error
	 * meaning when result > 0, we just return 0 here
	 */
	if ((int)*src_len > 0)
		return 0;
	else
		return -1;
}

#ifndef STATIC
EXPORT_SYMBOL(LZ4_decompress_safe);
EXPORT_SYMBOL(LZ4_decompress_safe_partial);
EXPORT_SYMBOL(LZ4_decompress_fast);
EXPORT_SYMBOL(LZ4_setStreamDecode);
EXPORT_SYMBOL(LZ4_decompress_safe_continue);
EXPORT_SYMBOL(LZ4_decompress_fast_continue);
EXPORT_SYMBOL(LZ4_decompress_safe_usingDict);
EXPORT_SYMBOL(LZ4_decompress_fast_usingDict);
EXPORT_SYMBOL(lz4_decompress_unknownoutputsize);
EXPORT_SYMBOL(lz4_decompress);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("LZ4 decompressor");
#endif
