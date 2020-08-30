obj-m += gtdev.o
all:
	$(MAKE) -C /lib/modules/`uname -r`/build M=`pwd` modules
	gcc gtdev-test-tool.c -o gtdev-test-tool
clean:
	$(MAKE) -C /lib/modules/`uname -r`/build M=`pwd` clean
