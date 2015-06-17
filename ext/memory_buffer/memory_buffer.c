/*
 * Ruby module to block device operations on Linux platforms.
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>

#include "ruby.h"

static const char *module_name = "MemoryBuffer";


static VALUE
create_aligned_string(VALUE self, VALUE ralign, VALUE rlen) {
	size_t	align	= (size_t)NUM2INT(ralign);
	size_t	len		= (size_t)NUM2INT(rlen);
	char	*abuf;
	VALUE	asb;

	if ((abuf = memalign(align, len)) == NULL) {
		rb_raise(rb_eNoMemError, "Could not allocate %d bytes of aligned memory\n", len);
	}

	asb = rb_str_new(NULL, 0);
	RBASIC(asb)->flags |= RSTRING_NOEMBED;
	RSTRING(asb)->as.heap.ptr = abuf;
	RSTRING(asb)->as.heap.aux.capa = len;

	return(asb);
}

VALUE	mMemoryBuffer;

/*
 * Initialize the class.
 */
void Init_memory_buffer()	{
	/*
	 * Define the module.
	 */
	mMemoryBuffer = rb_define_module(module_name);

	rb_define_singleton_method(mMemoryBuffer, "create_aligned_string", create_aligned_string, 2);
}