#undef NDEBUG
#include <assert.h>

#include "win32_vector.h"
#include "win32.h"
#include "win32_print.h"
#include <stdint.h>

#define DBG(format, ...) win32_errorfA("[WIN32_VECTOR] " format "\n", ## __VA_ARGS__)

/* extern */
void   win32_array_clear(HANDLE heap, DWORD width, char **array)
{
	win32_array_resize(heap, width, array, 0);
}

/* extern */
DWORD  win32_array_size(HANDLE heap, DWORD width, char **array)
{
	assert(width > 0);
	if(!array) return 0;
	if(!*array) return 0;
	size_t v_byte_size = win32_heap_memlen(heap, *array);
	DWORD v_width_size = v_byte_size / width;
	return v_width_size;
}

/* extern */
void   win32_array_resize(HANDLE heap, DWORD width, char **array, DWORD size)
{
	assert(width > 0);
	if(!array) return;
	if(!size)
	{
		if(*array)
		{
			win32_heap_free(heap, *array);
			*array = NULL;
		}
		return;
	}
	if(!*array)
	{
		*array = (char *)win32_heap_malloc(heap, width*size);
	}
	else
	{
		*array = (char *)win32_heap_realloc(heap, *array, width*size);
	}
}

/* extern */
void   win32_array_reserve(HANDLE heap, DWORD width, char **array, DWORD size)
{
	assert(width > 0);
	if(!array) return;
	DWORD v_old_size = win32_array_size(heap, width, array);
	if(v_old_size >= size) return;
	win32_array_resize(heap, width, array, size);
}

/* extern */
void   win32_array_get(HANDLE heap, DWORD width, char **array, DWORD pos, char *val)
{
	assert(width > 0);
	if(!val) return;
	ZeroMemory(val, width);
	if(!array) return;
	if(!*array) return;
	DWORD v_old_size = win32_array_size(heap, width, array);
	if(pos >= v_old_size) return;
	char *v_src = &(*array)[width*pos];
	CopyMemory(val, v_src, width);
}

/* extern */
void   win32_array_set(HANDLE heap, DWORD width, char **array, DWORD pos, char *val)
{
	assert(width > 0);
	if(!array) return;
	win32_array_reserve(heap, width, array, pos+1);
	char *v_dest = &(*array)[width*pos];
	if(val)
	{
		CopyMemory(v_dest, val, width);
	}
	else
	{
		ZeroMemory(v_dest, width);
	}
}

/* extern */
void   win32_array_push_back(HANDLE heap, DWORD width, char **array, char *val)
{
	assert(width > 0);
	if(!array) return;
	DWORD v_old_size = win32_array_size(heap, width, array);
	win32_array_set(heap, width, array, v_old_size, val);
}

/* extern */
void   win32_array_erase(HANDLE heap, DWORD width, char **array, DWORD pos, char *val)
{
	assert(width > 0);
	if(val) ZeroMemory(val, width);
	if(!array) return;
	if(!*array) return;
	DWORD v_old_size = win32_array_size(heap, width, array);
	if(pos >= v_old_size) return;
	if(val)
	{
		char *v_src = &(*array)[width*pos];
		CopyMemory(val, v_src, width);
	}
	for(int64_t i=pos+1; i<v_old_size; i++)
	{
		CopyMemory(&(*array)[width*(i-1)], &(*array)[width*i], width);
	}
	win32_array_resize(heap, width, array, v_old_size-1);
}

/* extern */
void   win32_array_insert(HANDLE heap, DWORD width, char **array, DWORD pos, char *val)
{
	assert(width > 0);
	if(!array) return;
	win32_array_reserve(heap, width, array, pos+1);
	DWORD v_old_size = win32_array_size(heap, width, array);
	win32_array_resize(heap, width, array, v_old_size+1);
	for (int64_t i = v_old_size-1; i >= pos; i--)
	{
		CopyMemory(&(*array)[width*(i+1)], &(*array)[width*i], width);
	}
	char *v_dest = &(*array)[width*pos];
	if(val)
	{
		CopyMemory(v_dest, val, width);
	}
	else
	{
		ZeroMemory(v_dest, width);
	}
}

/* extern */
void   win32_thread_char_clear(char **array)
{
	win32_thread_array_resize(sizeof(**array), (char **)array, 0);
}

/* extern */
DWORD   win32_thread_char_size(char **array)
{
	return win32_thread_array_size(sizeof(**array), (char **)array);
}

/* extern */
void   win32_thread_char_resize(char **array, DWORD size)
{
	win32_thread_array_resize(sizeof(**array), (char **)array, size);
}

/* extern */
void   win32_thread_char_reserve(char **array, DWORD size)
{
	win32_thread_array_reserve(sizeof(**array), (char **)array, size);
}

/* extern */
char   win32_thread_char_get(char **array, DWORD pos)
{
	char val;
	win32_thread_array_get(sizeof(**array), (char **)array, pos, (char *)&val);
	return val;
}

/* extern */
void   win32_thread_char_set(char **array, DWORD pos, char val)
{
	win32_thread_array_set(sizeof(**array), (char **)array, pos, (char *)&val);
}

/* extern */
void   win32_thread_char_push_back(char **array, char val)
{
	win32_thread_array_push_back(sizeof(**array), (char **)array, (char *)&val);
}

/* extern */
char   win32_thread_char_erase(char **array, DWORD pos)
{
	char val;
	win32_thread_array_erase(sizeof(**array), (char **)array, pos, (char *)&val);
	return val;
}

/* extern */
void   win32_thread_char_insert(char **array, DWORD pos, char val)
{
	win32_thread_array_insert(sizeof(**array), (char **)array, pos, (char *)&val);
}

/* extern */
void    win32_thread_wchar_clear(wchar_t **array)
{
	win32_thread_array_clear(sizeof(**array), (char **)array);
}

/* extern */
DWORD   win32_thread_wchar_size(wchar_t **array)
{
	return win32_thread_array_size(sizeof(**array), (char **)array);
}

/* extern */
void    win32_thread_wchar_resize(wchar_t **array, DWORD size)
{
	win32_thread_array_resize(sizeof(**array), (char **)array, size);
}

/* extern */
void    win32_thread_wchar_reserve(wchar_t **array, DWORD size)
{
	win32_thread_array_reserve(sizeof(**array), (char **)array, size);
}

/* extern */
wchar_t win32_thread_wchar_get(wchar_t **array, DWORD pos)
{
	wchar_t val;
	win32_thread_array_get(sizeof(**array), (char **)array, pos, (char *)&val);
	return val;
}

/* extern */
void    win32_thread_wchar_set(wchar_t **array, DWORD pos, wchar_t val)
{
	win32_thread_array_set(sizeof(**array), (char **)array, pos, (char *)&val);
}

/* extern */
void    win32_thread_wchar_push_back(wchar_t **array, wchar_t val)
{
	win32_thread_array_push_back(sizeof(**array), (char **)array, (char *)&val);
}

/* extern */
wchar_t win32_thread_wchar_erase(wchar_t **array, DWORD pos)
{
	wchar_t val;
	win32_thread_array_erase(sizeof(**array), (char **)array, pos, (char *)&val);
	return val;
}

/* extern */
void    win32_thread_wchar_insert(wchar_t **array, DWORD pos, wchar_t val)
{
	win32_thread_array_insert(sizeof(**array), (char **)array, pos, (char *)&val);
}
