/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2013 The Chromium OS Authors.
 * Coypright (c) 2013 Guntermann & Drunck GmbH
 */

#ifndef __TPM_UTILS_H
#define __TPM_UTILS_H

#define COMMAND_BUFFER_SIZE 256

/* Internal error of TPM command library */
#define TPM_LIB_ERROR ((u32)~0u)

/**
 * tpm_open() - Request access to locality 0 for the caller
 *
 * After all commands have been completed the caller is supposed to
 * call tpm_close().
 *
 * Returns 0 on success, -ve on failure.
 */
int tpm_open(struct udevice *dev);

/**
 * tpm_close() - Close the current session
 *
 * Releasing the locked locality. Returns 0 on success, -ve 1 on
 * failure (in case lock removal did not succeed).
 */
int tpm_close(struct udevice *dev);

/**
 * Pack data into a byte string.  The data types are specified in
 * the format string: 'b' means unsigned byte, 'w' unsigned word,
 * 'd' unsigned double word, and 's' byte string.  The data are a
 * series of offsets and values (for type byte string there are also
 * lengths).  The data values are packed into the byte string
 * sequentially, and so a latter value could over-write a former
 * value.
 *
 * @param str		output string
 * @param size		size of output string
 * @param format	format string
 * @param ...		data points
 * @return 0 on success, non-0 on error
 */
int pack_byte_string(u8 *str, size_t size, const char *format, ...);

/**
 * Unpack data from a byte string.  The data types are specified in
 * the format string: 'b' means unsigned byte, 'w' unsigned word,
 * 'd' unsigned double word, and 's' byte string.  The data are a
 * series of offsets and pointers (for type byte string there are also
 * lengths).
 *
 * @param str		output string
 * @param size		size of output string
 * @param format	format string
 * @param ...		data points
 * @return 0 on success, non-0 on error
 */
int unpack_byte_string(const u8 *str, size_t size, const char *format, ...);

/**
 * Get TPM command size.
 *
 * @param command	byte string of TPM command
 * @return command size of the TPM command
 */
u32 tpm_command_size(const void *command);

/**
 * Get TPM response return code, which is one of TPM_RESULT values.
 *
 * @param response	byte string of TPM response
 * @return return code of the TPM response
 */
u32 tpm_return_code(const void *response);

/**
 * Send a TPM command and return response's return code, and optionally
 * return response to caller.
 *
 * @param command	byte string of TPM command
 * @param response	output buffer for TPM response, or NULL if the
 *			caller does not care about it
 * @param size_ptr	output buffer size (input parameter) and TPM
 *			response length (output parameter); this parameter
 *			is a bidirectional
 * @return return code of the TPM response
 */
u32 tpm_sendrecv_command(const void *command, void *response, size_t *size_ptr);

#endif /* __TPM_UTILS_H */