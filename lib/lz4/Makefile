ccflags-y += -O3
# lz4.c is shared by the compressor and the decompressor: each of the two
# objects leaves the helpers of the other one unused
ccflags-y += -Wno-unused-function

obj-$(CONFIG_LZ4_COMPRESS) += lz4_compress.o
obj-$(CONFIG_LZ4HC_COMPRESS) += lz4hc_compress.o
obj-$(CONFIG_LZ4_DECOMPRESS) += lz4_decompress.o
