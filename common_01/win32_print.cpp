#undef NDEBUG
#include <assert.h>

#include "win32_print.h"
#include <windows.h>
#include <stdio.h>
#include "vardecl.h"

#include <mutex>
#include <string>
#include <vector>

#ifdef __GNUC__
/* http://stackoverflow.com/questions/3385515/static-assert-in-c */
#   define STATIC_ASSERT(X,Y) ({ extern int __attribute__((error("assertion failure: '" #X "' not true"))) compile_time_check(); ((X)?0:compile_time_check()),0; })
#else
#   define STATIC_ASSERT static_assert
#endif

#if 0x0
/* for debug */
static void sync_putsA(const char* s)
{
	HANDLE hStdOutput;
	hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwWriteByte;
	WriteConsoleA(hStdOutput, s, lstrlenA(s), &dwWriteByte, NULL);
	WriteConsoleA(hStdOutput, "\n", 1, &dwWriteByte, NULL);
	return;
}
#endif

class win32_print_mutex
{
private:
	CRITICAL_SECTION f_crit_sec;
public:
	explicit win32_print_mutex()
	{
		InitializeCriticalSection(&f_crit_sec);
	}
	virtual ~win32_print_mutex()
	{
		LeaveCriticalSection(&f_crit_sec);
	}
	void lock()
	{
		EnterCriticalSection(&f_crit_sec);
	}
	void unlock()
	{
		LeaveCriticalSection(&f_crit_sec);
	}
};
static win32_print_mutex *l_mutex = NULL;
static ALIGNED_ARRAY_DECL(char, l_mutex_holder, sizeof(*l_mutex), 16);

static inline win32_print_mutex *get_mutex()
{
	if (!l_mutex)
	{
		l_mutex = new (l_mutex_holder)win32_print_mutex();
	}
	return l_mutex;
}

static int win32_write_consoleA(HANDLE hconsole, const char *format, va_list args)
{
	char v_buffer[1024 + 1];
	v_buffer[1024] = 0;
	int len = wvsprintfA((LPSTR)v_buffer, format, args); // Win32 API
	for (int i = 0; i < len; i++)
	{
		if (v_buffer[i] == 0)
		{
			v_buffer[i] = '@';
		}
	}
	DWORD dwWriteByte;
	WriteConsoleA(hconsole, v_buffer, len, &dwWriteByte, NULL);
	OutputDebugStringA((LPCSTR)v_buffer);
	return len;
}

/* extern */
int win32_printfA(const char *format, ...)
{
	win32_print_mutex *v_mutex = get_mutex();
	v_mutex->lock();
	va_list args;
	va_start(args, format);
	int len = win32_write_consoleA(GetStdHandle(STD_OUTPUT_HANDLE), format, args);
	va_end(args);
	v_mutex->unlock();
	return len;
}

/* extern */
int win32_vprintfA(const char *format, va_list args)
{
	win32_print_mutex *v_mutex = get_mutex();
	v_mutex->lock();
	int len = win32_write_consoleA(GetStdHandle(STD_OUTPUT_HANDLE), format, args);
	v_mutex->unlock();
	return len;
}

/* extern */
int win32_errorfA(const char *format, ...)
{
	win32_print_mutex *v_mutex = get_mutex();
	v_mutex->lock();
	va_list args;
	va_start(args, format);
	int len = win32_write_consoleA(GetStdHandle(STD_ERROR_HANDLE), format, args);
	va_end(args);
	v_mutex->unlock();
	return len;
}

/* extern */
int win32_verrorfA(const char *format, va_list args)
{
	win32_print_mutex *v_mutex = get_mutex();
	v_mutex->lock();
	int len = win32_write_consoleA(GetStdHandle(STD_ERROR_HANDLE), format, args);
	v_mutex->unlock();
	return len;
}

static int win32_write_consoleW(HANDLE hconsole, const wchar_t *format, va_list args)
{
	wchar_t v_buffer[1024 + 1];
	v_buffer[1024] = 0;
	int len = wvsprintfW((LPWSTR)v_buffer, format, args); // Win32 API
	for (int i = 0; i < len; i++)
	{
		if (v_buffer[i] == 0)
		{
			v_buffer[i] = L'@';
		}
	}
	DWORD dwWriteByte;
	WriteConsoleW(hconsole, v_buffer, len, &dwWriteByte, NULL);
	OutputDebugStringW((LPCWSTR)v_buffer);
	return len;
}

/* extern */
int win32_printfW(const wchar_t *format, ...)
{
	win32_print_mutex *v_mutex = get_mutex();
	v_mutex->lock();
	va_list args;
	va_start(args, format);
	int len = win32_write_consoleW(GetStdHandle(STD_OUTPUT_HANDLE), format, args);
	va_end(args);
	v_mutex->unlock();
	return len;
}

/* extern */
int win32_vprintfW(const wchar_t *format, va_list args)
{
	win32_print_mutex *v_mutex = get_mutex();
	v_mutex->lock();
	int len = win32_write_consoleW(GetStdHandle(STD_OUTPUT_HANDLE), format, args);
	v_mutex->unlock();
	return len;
}

/* extern */
int win32_errorfW(const wchar_t *format, ...)
{
	win32_print_mutex *v_mutex = get_mutex();
	v_mutex->lock();
	va_list args;
	va_start(args, format);
	int len = win32_write_consoleW(GetStdHandle(STD_ERROR_HANDLE), format, args);
	va_end(args);
	v_mutex->unlock();
	return len;
}

/* extern */
int win32_verrorfW(const wchar_t *format, va_list args)
{
	win32_print_mutex *v_mutex = get_mutex();
	v_mutex->lock();
	int len = win32_write_consoleW(GetStdHandle(STD_ERROR_HANDLE), format, args);
	v_mutex->unlock();
	return len;
}

/* extern */
std::wstring wstring_printf(const wchar_t *format, ...)
{
	va_list args;
	va_start(args, format);
	int v_len = _vsnwprintf(nullptr, 0, format, args); // CRT API
	assert(v_len >= 0);
	std::vector<wchar_t> v_buffer(v_len + 1);
	_vsnwprintf(&v_buffer[0], v_len + 1, format, args); // CRT API
	assert(v_buffer[v_len] == 0);
	va_end(args);
	std::wstring v_wstr = &v_buffer[0];
	return v_wstr;
}
