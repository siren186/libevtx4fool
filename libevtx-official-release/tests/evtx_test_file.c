/*
 * Library file type test program
 *
 * Copyright (C) 2011-2022, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "evtx_test_functions.h"
#include "evtx_test_getopt.h"
#include "evtx_test_libbfio.h"
#include "evtx_test_libcerror.h"
#include "evtx_test_libevtx.h"
#include "evtx_test_macros.h"
#include "evtx_test_memory.h"
#include "evtx_test_unused.h"

#include "../libevtx/libevtx_file.h"

#if !defined( LIBEVTX_HAVE_BFIO )

LIBEVTX_EXTERN \
int libevtx_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBEVTX_EXTERN \
int libevtx_file_open_file_io_handle(
     libevtx_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libevtx_error_t **error );

#endif /* !defined( LIBEVTX_HAVE_BFIO ) */

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make evtx_test_file generate verbose output
#define EVTX_TEST_FILE_VERBOSE
 */

/* Creates and opens a source file
 * Returns 1 if successful or -1 on error
 */
int evtx_test_file_open_source(
     libevtx_file_t **file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "evtx_test_file_open_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( libevtx_file_initialize(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	result = libevtx_file_open_file_io_handle(
	          *file,
	          file_io_handle,
	          LIBEVTX_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file != NULL )
	{
		libevtx_file_free(
		 file,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source file
 * Returns 1 if successful or -1 on error
 */
int evtx_test_file_close_source(
     libevtx_file_t **file,
     libcerror_error_t **error )
{
	static char *function = "evtx_test_file_close_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( libevtx_file_close(
	     *file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file.",
		 function );

		result = -1;
	}
	if( libevtx_file_free(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libevtx_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int evtx_test_file_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libevtx_file_t *file            = NULL;
	int result                      = 0;

#if defined( HAVE_EVTX_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libevtx_file_initialize(
	          &file,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libevtx_file_free(
	          &file,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libevtx_file_initialize(
	          NULL,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	file = (libevtx_file_t *) 0x12345678UL;

	result = libevtx_file_initialize(
	          &file,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	file = NULL;

#if defined( HAVE_EVTX_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libevtx_file_initialize with malloc failing
		 */
		evtx_test_malloc_attempts_before_fail = test_number;

		result = libevtx_file_initialize(
		          &file,
		          &error );

		if( evtx_test_malloc_attempts_before_fail != -1 )
		{
			evtx_test_malloc_attempts_before_fail = -1;

			if( file != NULL )
			{
				libevtx_file_free(
				 &file,
				 NULL );
			}
		}
		else
		{
			EVTX_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			EVTX_TEST_ASSERT_IS_NULL(
			 "file",
			 file );

			EVTX_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libevtx_file_initialize with memset failing
		 */
		evtx_test_memset_attempts_before_fail = test_number;

		result = libevtx_file_initialize(
		          &file,
		          &error );

		if( evtx_test_memset_attempts_before_fail != -1 )
		{
			evtx_test_memset_attempts_before_fail = -1;

			if( file != NULL )
			{
				libevtx_file_free(
				 &file,
				 NULL );
			}
		}
		else
		{
			EVTX_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			EVTX_TEST_ASSERT_IS_NULL(
			 "file",
			 file );

			EVTX_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_EVTX_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libevtx_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libevtx_file_free function
 * Returns 1 if successful or 0 if not
 */
int evtx_test_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libevtx_file_free(
	          NULL,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libevtx_file_open function
 * Returns 1 if successful or 0 if not
 */
int evtx_test_file_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libevtx_file_t *file     = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = evtx_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libevtx_file_initialize(
	          &file,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libevtx_file_open(
	          file,
	          narrow_source,
	          LIBEVTX_OPEN_READ,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libevtx_file_open(
	          NULL,
	          narrow_source,
	          LIBEVTX_OPEN_READ,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libevtx_file_open(
	          file,
	          NULL,
	          LIBEVTX_OPEN_READ,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libevtx_file_open(
	          file,
	          narrow_source,
	          -1,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libevtx_file_open(
	          file,
	          narrow_source,
	          LIBEVTX_OPEN_READ,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libevtx_file_free(
	          &file,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libevtx_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libevtx_file_open_wide function
 * Returns 1 if successful or 0 if not
 */
int evtx_test_file_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libevtx_file_t *file     = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = evtx_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libevtx_file_initialize(
	          &file,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libevtx_file_open_wide(
	          file,
	          wide_source,
	          LIBEVTX_OPEN_READ,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libevtx_file_open_wide(
	          NULL,
	          wide_source,
	          LIBEVTX_OPEN_READ,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libevtx_file_open_wide(
	          file,
	          NULL,
	          LIBEVTX_OPEN_READ,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libevtx_file_open_wide(
	          file,
	          wide_source,
	          -1,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libevtx_file_open_wide(
	          file,
	          wide_source,
	          LIBEVTX_OPEN_READ,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libevtx_file_free(
	          &file,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libevtx_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libevtx_file_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int evtx_test_file_open_file_io_handle(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libevtx_file_t *file             = NULL;
	size_t string_length             = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libbfio_file_initialize(
	          &file_io_handle,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVTX_TEST_ASSERT_IS_NOT_NULL(
         "file_io_handle",
         file_io_handle );

        EVTX_TEST_ASSERT_IS_NULL(
         "error",
         error );

	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#endif
	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        EVTX_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libevtx_file_initialize(
	          &file,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libevtx_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBEVTX_OPEN_READ,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libevtx_file_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBEVTX_OPEN_READ,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libevtx_file_open_file_io_handle(
	          file,
	          NULL,
	          LIBEVTX_OPEN_READ,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libevtx_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          -1,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libevtx_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBEVTX_OPEN_READ,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libevtx_file_free(
	          &file,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
         "file_io_handle",
         file_io_handle );

        EVTX_TEST_ASSERT_IS_NULL(
         "error",
         error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libevtx_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libevtx_file_close function
 * Returns 1 if successful or 0 if not
 */
int evtx_test_file_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libevtx_file_close(
	          NULL,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libevtx_file_open and libevtx_file_close functions
 * Returns 1 if successful or 0 if not
 */
int evtx_test_file_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error = NULL;
	libevtx_file_t *file     = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libevtx_file_initialize(
	          &file,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libevtx_file_open_wide(
	          file,
	          source,
	          LIBEVTX_OPEN_READ,
	          &error );
#else
	result = libevtx_file_open(
	          file,
	          source,
	          LIBEVTX_OPEN_READ,
	          &error );
#endif

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libevtx_file_close(
	          file,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libevtx_file_open_wide(
	          file,
	          source,
	          LIBEVTX_OPEN_READ,
	          &error );
#else
	result = libevtx_file_open(
	          file,
	          source,
	          LIBEVTX_OPEN_READ,
	          &error );
#endif

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libevtx_file_close(
	          file,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libevtx_file_free(
	          &file,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libevtx_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libevtx_file_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int evtx_test_file_signal_abort(
     libevtx_file_t *file )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libevtx_file_signal_abort(
	          file,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libevtx_file_signal_abort(
	          NULL,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libevtx_file_get_ascii_codepage function
 * Returns 1 if successful or 0 if not
 */
int evtx_test_file_get_ascii_codepage(
     libevtx_file_t *file )
{
	libcerror_error_t *error = NULL;
	int ascii_codepage       = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libevtx_file_get_ascii_codepage(
	          file,
	          &ascii_codepage,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libevtx_file_get_ascii_codepage(
	          NULL,
	          &ascii_codepage,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libevtx_file_get_ascii_codepage(
	          file,
	          NULL,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libevtx_file_set_ascii_codepage function
 * Returns 1 if successful or 0 if not
 */
int evtx_test_file_set_ascii_codepage(
     libevtx_file_t *file )
{
	int supported_codepages[ 15 ] = {
		LIBEVTX_CODEPAGE_ASCII,
		LIBEVTX_CODEPAGE_WINDOWS_874,
		LIBEVTX_CODEPAGE_WINDOWS_932,
		LIBEVTX_CODEPAGE_WINDOWS_936,
		LIBEVTX_CODEPAGE_WINDOWS_949,
		LIBEVTX_CODEPAGE_WINDOWS_950,
		LIBEVTX_CODEPAGE_WINDOWS_1250,
		LIBEVTX_CODEPAGE_WINDOWS_1251,
		LIBEVTX_CODEPAGE_WINDOWS_1252,
		LIBEVTX_CODEPAGE_WINDOWS_1253,
		LIBEVTX_CODEPAGE_WINDOWS_1254,
		LIBEVTX_CODEPAGE_WINDOWS_1255,
		LIBEVTX_CODEPAGE_WINDOWS_1256,
		LIBEVTX_CODEPAGE_WINDOWS_1257,
		LIBEVTX_CODEPAGE_WINDOWS_1258 };

	int unsupported_codepages[ 17 ] = {
		LIBEVTX_CODEPAGE_ISO_8859_1,
		LIBEVTX_CODEPAGE_ISO_8859_2,
		LIBEVTX_CODEPAGE_ISO_8859_3,
		LIBEVTX_CODEPAGE_ISO_8859_4,
		LIBEVTX_CODEPAGE_ISO_8859_5,
		LIBEVTX_CODEPAGE_ISO_8859_6,
		LIBEVTX_CODEPAGE_ISO_8859_7,
		LIBEVTX_CODEPAGE_ISO_8859_8,
		LIBEVTX_CODEPAGE_ISO_8859_9,
		LIBEVTX_CODEPAGE_ISO_8859_10,
		LIBEVTX_CODEPAGE_ISO_8859_11,
		LIBEVTX_CODEPAGE_ISO_8859_13,
		LIBEVTX_CODEPAGE_ISO_8859_14,
		LIBEVTX_CODEPAGE_ISO_8859_15,
		LIBEVTX_CODEPAGE_ISO_8859_16,
		LIBEVTX_CODEPAGE_KOI8_R,
		LIBEVTX_CODEPAGE_KOI8_U };

	libcerror_error_t *error = NULL;
	int codepage             = 0;
	int index                = 0;
	int result               = 0;

	/* Test set ASCII codepage
	 */
	for( index = 0;
	     index < 15;
	     index++ )
	{
		codepage = supported_codepages[ index ];

		result = libevtx_file_set_ascii_codepage(
		          file,
		          codepage,
		          &error );

		EVTX_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		EVTX_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	result = libevtx_file_set_ascii_codepage(
	          NULL,
	          LIBEVTX_CODEPAGE_ASCII,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	for( index = 0;
	     index < 17;
	     index++ )
	{
		codepage = unsupported_codepages[ index ];

		result = libevtx_file_set_ascii_codepage(
		          file,
		          codepage,
		          &error );

		EVTX_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		EVTX_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Clean up
	 */
	result = libevtx_file_set_ascii_codepage(
	          file,
	          LIBEVTX_CODEPAGE_WINDOWS_1252,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libevtx_file_get_flags function
 * Returns 1 if successful or 0 if not
 */
int evtx_test_file_get_flags(
     libevtx_file_t *file )
{
	libcerror_error_t *error = NULL;
	uint32_t flags           = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libevtx_file_get_flags(
	          file,
	          &flags,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libevtx_file_get_flags(
	          NULL,
	          &flags,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libevtx_file_get_flags(
	          file,
	          NULL,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libevtx_file_get_number_of_records function
 * Returns 1 if successful or 0 if not
 */
int evtx_test_file_get_number_of_records(
     libevtx_file_t *file )
{
	libcerror_error_t *error = NULL;
	int number_of_records    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libevtx_file_get_number_of_records(
	          file,
	          &number_of_records,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libevtx_file_get_number_of_records(
	          NULL,
	          &number_of_records,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libevtx_file_get_number_of_records(
	          file,
	          NULL,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libevtx_file_get_record_by_index function
 * Returns 1 if successful or 0 if not
 */
int evtx_test_file_get_record_by_index(
     libevtx_file_t *file )
{
	libcerror_error_t *error = NULL;
	libevtx_record_t *record = 0;
	int number_of_records    = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libevtx_file_get_number_of_records(
	          file,
	          &number_of_records,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( number_of_records == 0 )
	{
		return( 1 );
	}
	/* Test regular cases
	 */
	result = libevtx_file_get_record_by_index(
	          file,
	          0,
	          &record,
	          &error );

	/* TODO: remove after troubleshooting failing tests */
	EVTX_TEST_FPRINT_ERROR( error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "record",
	 record );

	result = libevtx_record_free(
	          &record,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libevtx_file_get_record_by_index(
	          NULL,
	          0,
	          &record,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "record",
	 record );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libevtx_file_get_record_by_index(
	          file,
	          -1,
	          &record,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "record",
	 record );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libevtx_file_get_record_by_index(
	          file,
	          0,
	          NULL,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "record",
	 record );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libevtx_file_get_number_of_recovered_records function
 * Returns 1 if successful or 0 if not
 */
int evtx_test_file_get_number_of_recovered_records(
     libevtx_file_t *file )
{
	libcerror_error_t *error        = NULL;
	int number_of_recovered_records = 0;
	int result                      = 0;

	/* Test regular cases
	 */
	result = libevtx_file_get_number_of_recovered_records(
	          file,
	          &number_of_recovered_records,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libevtx_file_get_number_of_recovered_records(
	          NULL,
	          &number_of_recovered_records,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libevtx_file_get_number_of_recovered_records(
	          file,
	          NULL,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libevtx_file_get_recovered_record_by_index function
 * Returns 1 if successful or 0 if not
 */
int evtx_test_file_get_recovered_record_by_index(
     libevtx_file_t *file )
{
	libcerror_error_t *error           = NULL;
	libevtx_record_t *recovered_record = 0;
	int number_of_recovered_records    = 0;
	int result                         = 0;

	/* Initialize test
	 */
	result = libevtx_file_get_number_of_recovered_records(
	          file,
	          &number_of_recovered_records,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( number_of_recovered_records == 0 )
	{
		return( 1 );
	}
	/* Test regular cases
	 */
	result = libevtx_file_get_recovered_record_by_index(
	          file,
	          0,
	          &recovered_record,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "recovered_record",
	 recovered_record );

	result = libevtx_record_free(
	          &recovered_record,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libevtx_file_get_recovered_record_by_index(
	          NULL,
	          0,
	          &recovered_record,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "recovered_record",
	 recovered_record );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libevtx_file_get_recovered_record_by_index(
	          file,
	          -1,
	          &recovered_record,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "recovered_record",
	 recovered_record );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libevtx_file_get_recovered_record_by_index(
	          file,
	          0,
	          NULL,
	          &error );

	EVTX_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	EVTX_TEST_ASSERT_IS_NULL(
	 "recovered_record",
	 recovered_record );

	EVTX_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libevtx_file_t *file             = NULL;
	system_character_t *source       = NULL;
	system_integer_t option          = 0;
	size_t string_length             = 0;
	int result                       = 0;

	while( ( option = evtx_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( EVTX_TEST_FILE_VERBOSE )
	libevtx_notify_set_verbose(
	 1 );
	libevtx_notify_set_stream(
	 stderr,
	 NULL );
#endif

	EVTX_TEST_RUN(
	 "libevtx_file_initialize",
	 evtx_test_file_initialize );

	EVTX_TEST_RUN(
	 "libevtx_file_free",
	 evtx_test_file_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		result = libbfio_file_initialize(
		          &file_io_handle,
		          &error );

		EVTX_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        EVTX_TEST_ASSERT_IS_NOT_NULL(
	         "file_io_handle",
	         file_io_handle );

	        EVTX_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		string_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
		EVTX_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        EVTX_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libevtx_check_file_signature_file_io_handle(
		          file_io_handle,
		          &error );

		EVTX_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		EVTX_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( result != 0 )
	{
		EVTX_TEST_RUN_WITH_ARGS(
		 "libevtx_file_open",
		 evtx_test_file_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		EVTX_TEST_RUN_WITH_ARGS(
		 "libevtx_file_open_wide",
		 evtx_test_file_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		EVTX_TEST_RUN_WITH_ARGS(
		 "libevtx_file_open_file_io_handle",
		 evtx_test_file_open_file_io_handle,
		 source );

		EVTX_TEST_RUN(
		 "libevtx_file_close",
		 evtx_test_file_close );

		EVTX_TEST_RUN_WITH_ARGS(
		 "libevtx_file_open_close",
		 evtx_test_file_open_close,
		 source );

		/* Initialize file for tests
		 */
		result = evtx_test_file_open_source(
		          &file,
		          file_io_handle,
		          &error );

		EVTX_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		EVTX_TEST_ASSERT_IS_NOT_NULL(
		 "file",
		 file );

		EVTX_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		EVTX_TEST_RUN_WITH_ARGS(
		 "libevtx_file_signal_abort",
		 evtx_test_file_signal_abort,
		 file );

#if defined( __GNUC__ ) && !defined( LIBEVTX_DLL_IMPORT )

		/* TODO: add tests for libevtx_file_open_read */

#endif /* defined( __GNUC__ ) && !defined( LIBEVTX_DLL_IMPORT ) */

		/* TODO: add tests for libevtx_file_is_corrupted */

		EVTX_TEST_RUN_WITH_ARGS(
		 "libevtx_file_get_ascii_codepage",
		 evtx_test_file_get_ascii_codepage,
		 file );

		EVTX_TEST_RUN_WITH_ARGS(
		 "libevtx_file_set_ascii_codepage",
		 evtx_test_file_set_ascii_codepage,
		 file );

		/* TODO: add tests for libevtx_file_get_format_version */

		/* TODO: add tests for libevtx_file_get_version */

		EVTX_TEST_RUN_WITH_ARGS(
		 "libevtx_file_get_flags",
		 evtx_test_file_get_flags,
		 file );

		EVTX_TEST_RUN_WITH_ARGS(
		 "libevtx_file_get_number_of_records",
		 evtx_test_file_get_number_of_records,
		 file );

		EVTX_TEST_RUN_WITH_ARGS(
		 "libevtx_file_get_record_by_index",
		 evtx_test_file_get_record_by_index,
		 file );

		EVTX_TEST_RUN_WITH_ARGS(
		 "libevtx_file_get_number_of_recovered_records",
		 evtx_test_file_get_number_of_recovered_records,
		 file );

#if defined( TODO )

		EVTX_TEST_RUN_WITH_ARGS(
		 "libevtx_file_get_recovered_record_by_index",
		 evtx_test_file_get_recovered_record_by_index,
		 file );

#endif /* defined( TODO ) */

		/* Clean up
		 */
		result = evtx_test_file_close_source(
		          &file,
		          &error );

		EVTX_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		EVTX_TEST_ASSERT_IS_NULL(
		 "file",
		 file );

		EVTX_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libbfio_handle_free(
		          &file_io_handle,
		          &error );

		EVTX_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		EVTX_TEST_ASSERT_IS_NULL(
	         "file_io_handle",
	         file_io_handle );

	        EVTX_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libevtx_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

