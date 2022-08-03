/*
 * The internal definitions
 *
 * Copyright (C) 2008-2022, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( LIBCDIRECTORY_INTERNAL_DEFINITIONS_H )
#define LIBCDIRECTORY_INTERNAL_DEFINITIONS_H

#include <common.h>
#include <types.h>

/* Define HAVE_LOCAL_LIBCDIRECTORY for local use of libcdirectory
 */
#if !defined( HAVE_LOCAL_LIBCDIRECTORY )
#include <libcdirectory/definitions.h>

/* The definitions in <libcdirectory/definitions.h> are copied here
 * for local use of libcdirectory
 */
#else

#define LIBCDIRECTORY_VERSION				20220105

/* The libcdirectory version string
 */
#define LIBCDIRECTORY_VERSION_STRING			"20220105"

/* The directory entry type definitions
 */
enum LIBCDIRECTORY_ENTRY_TYPES
{
	LIBCDIRECTORY_ENTRY_TYPE_UNDEFINED,
	LIBCDIRECTORY_ENTRY_TYPE_DEVICE,
	LIBCDIRECTORY_ENTRY_TYPE_DIRECTORY,
	LIBCDIRECTORY_ENTRY_TYPE_FILE,
	LIBCDIRECTORY_ENTRY_TYPE_LINK,
	LIBCDIRECTORY_ENTRY_TYPE_PIPE,
	LIBCDIRECTORY_ENTRY_TYPE_SOCKET
};

/* The directory entry compare flags
 */
enum LIBCDIRECTORY_COMPARE_FLAGS
{
	LIBCDIRECTORY_COMPARE_FLAG_NO_CASE		= 0x01
};

#endif

#endif

