/*
 * Copyright (C) 2024 Sebastian Ertz <sebastian.ertz@gmx.de>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/**
 * # Digest Functions
 *
 * The `digest` module bundles various digest functions.
 *
 * @module digest
 */

#include <md5.h>
#include <sha1.h>
#include <sha2.h>

#ifdef HAVE_DIGEST_EXTENDED
#include <md2.h>
#include <md4.h>
#endif

#include "ucode/module.h"


static uc_value_t *
uc_digest_calc_data(uc_value_t *str, char *(*fn)(const uint8_t *,size_t,char *))
{
	char buf[SHA512_DIGEST_STRING_LENGTH];

	if( ucv_type(str) != UC_STRING )
		return NULL;

	if( fn((const uint8_t *)ucv_string_get(str), ucv_string_length(str), buf) )
		return ucv_string_new(buf);

	return NULL;
}

static uc_value_t *
uc_digest_calc_file(uc_value_t *path, char *(fn)(const char *,char *))
{
	char buf[SHA512_DIGEST_STRING_LENGTH];

	if( ucv_type(path) != UC_STRING )
		return NULL;

	if( fn(ucv_string_get(path), buf) )
		return ucv_string_new(buf);

	return NULL;
}

/**
 * Calculates the MD5 hash of string and returns that hash.
 *
 * Returns `null` if a non-string argument is given.
 *
 * @function module:digest#md5
 *
 * @param {string} str
 * The string to hash.
 *
 * @returns {?string}
 *
 * @example
 * md5("This is a test");  // Returns "ce114e4501d2f4e2dcea3e17b546f339"
 * md5(123);               // Returns null
 */
static uc_value_t *
uc_digest_md5(uc_vm_t *vm, size_t nargs)
{
	return uc_digest_calc_data(uc_fn_arg(0), MD5Data);
}

/**
 * Calculates the SHA1 hash of string and returns that hash.
 *
 * Returns `null` if a non-string argument is given.
 *
 * @function module:digest#sha1
 *
 * @param {string} str
 * The string to hash.
 *
 * @returns {?string}
 *
 * @example
 * sha1("This is a test");  // Returns "a54d88e06612d820bc3be72877c74f257b561b19"
 * sha1(123);               // Returns null
 */
static uc_value_t *
uc_digest_sha1(uc_vm_t *vm, size_t nargs)
{
	return uc_digest_calc_data(uc_fn_arg(0), SHA1Data);
}

/**
 * Calculates the SHA256 hash of string and returns that hash.
 *
 * Returns `null` if a non-string argument is given.
 *
 * @function module:digest#sha256
 *
 * @param {string} str
 * The string to hash.
 *
 * @returns {?string}
 *
 * @example
 * sha256("This is a test");  // Returns "c7be1ed902fb8dd4d48997c6452f5d7e509fbcdbe2808b16bcf4edce4c07d14e"
 * sha256(123);               // Returns null
 */
static uc_value_t *
uc_digest_sha256(uc_vm_t *vm, size_t nargs)
{
	return uc_digest_calc_data(uc_fn_arg(0), SHA256Data);
}

#ifdef HAVE_DIGEST_EXTENDED
/**
 * Calculates the MD2 hash of string and returns that hash.
 *
 * Returns `null` if a non-string argument is given.
 *
 * @function module:digest#md2
 *
 * @param {string} str
 * The string to hash.
 *
 * @returns {?string}
 *
 * @example
 * md2("This is a test");  // Returns "dc378580fd0722e56b82666a6994c718"
 * md2(123);               // Returns null
 */
static uc_value_t *
uc_digest_md2(uc_vm_t *vm, size_t nargs)
{
	return uc_digest_calc_data(uc_fn_arg(0), MD2Data);
}

/**
 * Calculates the MD4 hash of string and returns that hash.
 *
 * Returns `null` if a non-string argument is given.
 *
 * @function module:digest#md4
 *
 * @param {string} str
 * The string to hash.
 *
 * @returns {?string}
 *
 * @example
 * md4("This is a test");  // Returns "3b487cf6856af7e330bc4b1b7d977ef8"
 * md4(123);               // Returns null
 */
static uc_value_t *
uc_digest_md4(uc_vm_t *vm, size_t nargs)
{
	return uc_digest_calc_data(uc_fn_arg(0), MD4Data);
}

/**
 * Calculates the SHA384 hash of string and returns that hash.
 *
 * Returns `null` if a non-string argument is given.
 *
 * @function module:digest#sha384
 *
 * @param {string} str
 * The string to hash.
 *
 * @returns {?string}
 *
 * @example
 * sha384("This is a test");  // Returns "a27c7667e58200d4c0688ea136968404a0da366b1a9fc19bb38a0c7a609a1eef2bcc82837f4f4d92031a66051494b38c"
 * sha384(123);               // Returns null
 */
static uc_value_t *
uc_digest_sha384(uc_vm_t *vm, size_t nargs)
{
	return uc_digest_calc_data(uc_fn_arg(0), SHA384Data);
}

/**
 * Calculates the SHA384 hash of string and returns that hash.
 *
 * Returns `null` if a non-string argument is given.
 *
 * @function module:digest#sha384
 *
 * @param {string} str
 * The string to hash.
 *
 * @returns {?string}
 *
 * @example
 * sha512("This is a test");  // Returns "a028d4f74b602ba45eb0a93c9a4677240dcf281a1a9322f183bd32f0bed82ec72de9c3957b2f4c9a1ccf7ed14f85d73498df38017e703d47ebb9f0b3bf116f69"
 * sha512(123);               // Returns null
 */
static uc_value_t *
uc_digest_sha512(uc_vm_t *vm, size_t nargs)
{
	return uc_digest_calc_data(uc_fn_arg(0), SHA512Data);
}
#endif

/**
 * Calculates the MD5 hash of a given file and returns that hash.
 *
 * Returns `null` if an error occurred.
 *
 * @function module:digest#md5_file
 *
 * @param {string} path
 * The path to the file.
 *
 * @returns {?string}
 */
static uc_value_t *
uc_digest_md5_file(uc_vm_t *vm, size_t nargs)
{
	return uc_digest_calc_file(uc_fn_arg(0), MD5File);
}

/**
 * Calculates the SHA1 hash of a given file and returns that hash.
 *
 * Returns `null` if an error occurred.
 *
 * @function module:digest#sha1_file
 *
 * @param {string} path
 * The path to the file.
 *
 * @returns {?string}
 */
static uc_value_t *
uc_digest_sha1_file(uc_vm_t *vm, size_t nargs)
{
	return uc_digest_calc_file(uc_fn_arg(0), SHA1File);
}

/**
 * Calculates the SHA256 hash of a given file and returns that hash.
 *
 * Returns `null` if an error occurred.
 *
 * @function module:digest#sha256_file
 *
 * @param {string} path
 * The path to the file.
 *
 * @returns {?string}
 */
static uc_value_t *
uc_digest_sha256_file(uc_vm_t *vm, size_t nargs)
{
	return uc_digest_calc_file(uc_fn_arg(0), SHA256File);
}

#ifdef HAVE_DIGEST_EXTENDED
/**
 * Calculates the MD2 hash of a given file and returns that hash.
 *
 * Returns `null` if an error occurred.
 *
 * @function module:digest#md2_file
 *
 * @param {string} path
 * The path to the file.
 *
 * @returns {?string}
 */
static uc_value_t *
uc_digest_md2_file(uc_vm_t *vm, size_t nargs)
{
	return uc_digest_calc_file(uc_fn_arg(0), MD2File);
}

/**
 * Calculates the MD4 hash of a given file and returns that hash.
 *
 * Returns `null` if an error occurred.
 *
 * @function module:digest#md4_file
 *
 * @param {string} path
 * The path to the file.
 *
 * @returns {?string}
 */
static uc_value_t *
uc_digest_md4_file(uc_vm_t *vm, size_t nargs)
{
	return uc_digest_calc_file(uc_fn_arg(0), MD4File);
}

/**
 * Calculates the SHA384 hash of a given file and returns that hash.
 *
 * Returns `null` if an error occurred.
 *
 * @function module:digest#sha384_file
 *
 * @param {string} path
 * The path to the file.
 *
 * @returns {?string}
 */
static uc_value_t *
uc_digest_sha384_file(uc_vm_t *vm, size_t nargs)
{
	return uc_digest_calc_file(uc_fn_arg(0), SHA384File);
}

/**
 * Calculates the SHA512 hash of a given file and returns that hash.
 *
 * Returns `null` if an error occurred.
 *
 * @function module:digest#sha512_file
 *
 * @param {string} path
 * The path to the file.
 *
 * @returns {?string}
 */
static uc_value_t *
uc_digest_sha512_file(uc_vm_t *vm, size_t nargs)
{
	return uc_digest_calc_file(uc_fn_arg(0), SHA512File);
}
#endif


static const uc_function_list_t global_fns[] = {
	{ "md5",         uc_digest_md5         },
	{ "sha1",        uc_digest_sha1        },
	{ "sha256",      uc_digest_sha256      },
	{ "md5_file",    uc_digest_md5_file    },
	{ "sha1_file",   uc_digest_sha1_file   },
	{ "sha256_file", uc_digest_sha256_file },
#ifdef HAVE_DIGEST_EXTENDED
	{ "md2",         uc_digest_md2         },
	{ "md4",         uc_digest_md4         },
	{ "sha384",      uc_digest_sha384      },
	{ "sha512",      uc_digest_sha512      },
	{ "md2_file",    uc_digest_md2_file    },
	{ "md4_file",    uc_digest_md4_file    },
	{ "sha384_file", uc_digest_sha384_file },
	{ "sha512_file", uc_digest_sha512_file },
#endif
};

void uc_module_init(uc_vm_t *vm, uc_value_t *scope)
{
	uc_function_list_register(scope, global_fns);
}
