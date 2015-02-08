#ifndef _WIN32_VECTOR_H_
#define _WIN32_VECTOR_H_

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif
	/* Vector */
	void   win32_array_clear(HANDLE heap, DWORD width, char **array);
	DWORD  win32_array_size(HANDLE heap, DWORD width, char **array);
	void   win32_array_resize(HANDLE heap, DWORD width, char **array, DWORD size);
	void   win32_array_reserve(HANDLE heap, DWORD width, char **array, DWORD size);
	void   win32_array_get(HANDLE heap, DWORD width, char **array, DWORD pos, char *val);
	void   win32_array_set(HANDLE heap, DWORD width, char **array, DWORD pos, char *val);
	void   win32_array_push_back(HANDLE heap, DWORD width, char **array, char *val);
	void   win32_array_erase(HANDLE heap, DWORD width, char **array, DWORD pos, char *val);
	void   win32_array_insert(HANDLE heap, DWORD width, char **array, DWORD pos, char *val);

	//void   win32_global_array_clear(DWORD width, char **array);
	#define win32_global_array_clear(...) win32_array_clear(win32_global_heap(), ## __VA_ARGS__)
	//DWORD  win32_global_array_size(DWORD width, char **array);
	#define win32_global_array_size(...) win32_array_size(win32_global_heap(), ## __VA_ARGS__)
	//void   win32_global_array_resize(DWORD width, char **array, DWORD size);
	#define win32_global_array_resize(...) win32_array_resize(win32_global_heap(), ## __VA_ARGS__)
	//void   win32_global_array_reserve(DWORD width, char **array, DWORD size);
	#define win32_global_array_reserve(...) win32_array_reserve(win32_global_heap(), ## __VA_ARGS__)
	//void   win32_global_array_get(DWORD width, char **array, DWORD pos, char *val);
	#define win32_global_array_get(...) win32_array_get(win32_global_heap(), ## __VA_ARGS__)
	//void   win32_global_array_set(DWORD width, char **array, DWORD pos, char *val);
	#define win32_global_array_set(...) win32_array_set(win32_global_heap(), ## __VA_ARGS__)
	//void   win32_global_array_push_back(DWORD width, char **array, char *val);
	#define win32_global_array_push_back(...) win32_array_push_back(win32_global_heap(), ## __VA_ARGS__)
	//void   win32_global_array_erase(DWORD width, char **array, DWORD pos, char *val);
	#define win32_global_array_erase(...) win32_array_erase(win32_global_heap(), ## __VA_ARGS__)
	//void   win32_global_array_insert(DWORD width, char **array, DWORD pos, char *val);
	#define win32_global_array_insert(...) win32_array_insert(win32_global_heap(), ## __VA_ARGS__)

	//void   win32_thread_array_clear(DWORD width, char **array);
	#define win32_thread_array_clear(...) win32_array_clear(win32_thread_heap(), ## __VA_ARGS__)
	//DWORD  win32_thread_array_size(DWORD width, char **array);
	#define win32_thread_array_size(...) win32_array_size(win32_thread_heap(), ## __VA_ARGS__)
	//void   win32_thread_array_resize(DWORD width, char **array, DWORD size);
	#define win32_thread_array_resize(...) win32_array_resize(win32_thread_heap(), ## __VA_ARGS__)
	//void   win32_thread_array_reserve(DWORD width, char **array, DWORD size);
	#define win32_thread_array_reserve(...) win32_array_reserve(win32_thread_heap(), ## __VA_ARGS__)
	//void   win32_thread_array_get(DWORD width, char **array, DWORD pos, char *val);
	#define win32_thread_array_get(...) win32_array_get(win32_thread_heap(), ## __VA_ARGS__)
	//void   win32_thread_array_set(DWORD width, char **array, DWORD pos, char *val);
	#define win32_thread_array_set(...) win32_array_set(win32_thread_heap(), ## __VA_ARGS__)
	//void   win32_thread_array_push_back(DWORD width, char **array, char *val);
	#define win32_thread_array_push_back(...) win32_array_push_back(win32_thread_heap(), ## __VA_ARGS__)
	//void   win32_thread_array_erase(DWORD width, char **array, DWORD pos, char *val);
	#define win32_thread_array_erase(...) win32_array_erase(win32_thread_heap(), ## __VA_ARGS__)
	//void   win32_thread_array_insert(DWORD width, char **array, DWORD pos, char *val);
	#define win32_thread_array_insert(...) win32_array_insert(win32_thread_heap(), ## __VA_ARGS__)

	/* char array */
	void   win32_thread_char_clear(char **array);
	DWORD  win32_thread_char_size(char **array);
	void   win32_thread_char_resize(char **array, DWORD size);
	void   win32_thread_char_reserve(char **array, DWORD size);
	char   win32_thread_char_get(char **array, DWORD pos);
	void   win32_thread_char_set(char **array, DWORD pos, char val);
	void   win32_thread_char_push_back(char **array, char val);
	char   win32_thread_char_erase(char **array, DWORD pos);
	void   win32_thread_char_insert(char **array, DWORD pos, char val);
	/* wchar_t array */
	void    win32_thread_wchar_clear(wchar_t **array);
	DWORD   win32_thread_wchar_size(wchar_t **array);
	void    win32_thread_wchar_resize(wchar_t **array, DWORD size);
	void    win32_thread_wchar_reserve(wchar_t **array, DWORD size);
	wchar_t win32_thread_wchar_get(wchar_t **array, DWORD pos);
	void    win32_thread_wchar_set(wchar_t **array, DWORD pos, wchar_t val);
	void    win32_thread_wchar_push_back(wchar_t **array, wchar_t val);
	wchar_t win32_thread_wchar_erase(wchar_t **array, DWORD pos);
	void    win32_thread_wchar_insert(wchar_t **array, DWORD pos, wchar_t val);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus // ***** C++ only *****
#endif /* __cplusplus */

#endif /* _WIN32_VECTOR_H_ */
