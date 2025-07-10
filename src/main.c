#include "toast.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <shlobj.h>
#include <time.h>
#include <stdlib.h>
#include "notifications/someoneDied.h"
#include "notifications/plzDonate.h"
#include "notifications/plzDonate2.h"
#include "notifications/systemDelete.h"
#include "notifications/johnCall.h"
#include "notifications/weather.h"
#include "notifications/johnFQ.h"
#include "notifications/websiteRedesign.h"
#include "notifications/roadblocks.h"
#include "notifications/linker.h"
#include "resource/resource.h"

// Array of all toast notifications for random selection
static const wchar_t* toast_notifications[] = {
    someoneDied,
    plzDonate,
    plzDonate2,
    systemDelete,
    johnCall,
    weather,
    johnFQ,
    websiteRedesign,
    roadblocks,
    linker
};

static const int toast_count = sizeof(toast_notifications) / sizeof(toast_notifications[0]);

#ifdef BUILD_DLL
// DLL Export definitions
#ifdef __cplusplus
extern "C" {
#endif

__declspec(dllexport) int ShowRandomToast();
__declspec(dllexport) int ShowToastByIndex(int index);
__declspec(dllexport) int ShowAllToasts();
__declspec(dllexport) int ShowToastByName(const char* name);
__declspec(dllexport) int GetToastCount();
__declspec(dllexport) void EnsureToastResources();

// RunDLL32 compatible wrapper functions
__declspec(dllexport) void CALLBACK RunDLL32_ShowRandomToast(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow);
__declspec(dllexport) void CALLBACK RunDLL32_ShowAllToasts(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow);
__declspec(dllexport) void CALLBACK RunDLL32_ShowToastByName(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow);
__declspec(dllexport) void CALLBACK RunDLL32_ShowToastByIndex(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow);

#ifdef __cplusplus
}
#endif
#endif

BOOL extract_resource_to_file(WORD resourceId, LPCWSTR resourceType, const wchar_t* outputPath) {
    HRSRC hResource = FindResourceW(NULL, MAKEINTRESOURCEW(resourceId), resourceType);
    if (!hResource) {
        return FALSE;
    }
    
    HGLOBAL hMemory = LoadResource(NULL, hResource);
    if (!hMemory) {
        return FALSE;
    }
    
    void* data = LockResource(hMemory);
    if (!data) {
        return FALSE;
    }
    
    DWORD size = SizeofResource(NULL, hResource);
    if (size == 0) {
        return FALSE;
    }
    
    HANDLE hFile = CreateFileW(outputPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return FALSE;
    }
    
    DWORD written;
    if (!WriteFile(hFile, data, size, &written, NULL) || written != size) {
        CloseHandle(hFile);
        return FALSE;
    }
    
    CloseHandle(hFile);
    return TRUE;
}

void ensure_resources() {
    wchar_t tempPath[MAX_PATH];
    if (!SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, tempPath))) {
        return;
    }
   
    wchar_t tempDirPath[MAX_PATH];
    wsprintfW(tempDirPath, L"%s\\Temp", tempPath);
    CreateDirectoryW(tempDirPath, NULL);
   
    wchar_t appPath[MAX_PATH];
    wsprintfW(appPath, L"%s\\Temp\\thenews", tempPath);
    if (!CreateDirectoryW(appPath, NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
        return;
    }
	
    wchar_t filePath[MAX_PATH];
   
    wsprintfW(filePath, L"%s\\johnphone.jpg", appPath);
    if (GetFileAttributesW(filePath) == INVALID_FILE_ATTRIBUTES) {
        extract_resource_to_file(IDR_JOHNPHONE_IMAGE, RT_RCDATA, filePath);
    }
   
    wsprintfW(filePath, L"%s\\answer.png", appPath);
    if (GetFileAttributesW(filePath) == INVALID_FILE_ATTRIBUTES) {
        extract_resource_to_file(IDR_ANSWER_ICON, RT_RCDATA, filePath);
    }
   
    wsprintfW(filePath, L"%s\\sunny.png", appPath);
    if (GetFileAttributesW(filePath) == INVALID_FILE_ATTRIBUTES) {
        extract_resource_to_file(IDR_SUNNY_ICON, RT_RCDATA, filePath);
    }
   
    wsprintfW(filePath, L"%s\\redesign.png", appPath);
    if (GetFileAttributesW(filePath) == INVALID_FILE_ATTRIBUTES) {
        extract_resource_to_file(IDR_REDESIGN_IMAGE, RT_RCDATA, filePath);
    }

	wsprintfW(filePath, L"%s\\roadblocks.gif", appPath);
    if (GetFileAttributesW(filePath) == INVALID_FILE_ATTRIBUTES) {
        extract_resource_to_file(IDR_ROADBLOCKS_IMAGE, RT_RCDATA, filePath);
    }

	wsprintfW(filePath, L"%s\\icon.png", appPath);
    if (GetFileAttributesW(filePath) == INVALID_FILE_ATTRIBUTES) {
        extract_resource_to_file(IDR_THENEWS_IMAGE, RT_RCDATA, filePath);
    }

	wsprintfW(filePath, L"%s\\linker.png", appPath);
    if (GetFileAttributesW(filePath) == INVALID_FILE_ATTRIBUTES) {
        extract_resource_to_file(IDR_LINKER_IMAGE, RT_RCDATA, filePath);
    }
}

void my_activation_callback(const wchar_t* appUserModelId, const wchar_t* invokedArgs) {
	return;
}

// Random toast function - randomly selects one of the available toasts
int show_random_toast() {
    // Initialize random seed
    srand((unsigned int)time(NULL));
    
    // Select random toast
    int random_index = rand() % toast_count;
    
    ensure_resources();
    
    // Set up registry entries
    RegSetKeyValueW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Classes\\AppUserModelId\\theNewsWin32", L"IconUri", REG_EXPAND_SZ, L"%TEMP%\\thenews\\icon.png", (wcslen(L"%TEMP%\\thenews\\icon.png") + 1) * sizeof(wchar_t));
    RegSetKeyValueW(HKEY_CURRENT_USER, L"SOFTWARE\\Classes\\AppUserModelId\\theNewsWin32", L"IconUri", REG_EXPAND_SZ, L"%TEMP%\\thenews\\icon.png", (wcslen(L"%TEMP%\\thenews\\icon.png") + 1) * sizeof(wchar_t));
    
    // Initialize toast system
    toast_setup_icon(L"%TEMP%\\thenews\\icon.png");
    HRESULT hr = toast_init(L"theNewsWin32", L"the news", L"%TEMP%\\thenews\\icon.png");
    if (FAILED(hr)) return 1;
    
    toast_set_activation_callback(my_activation_callback);
    
    // Show the randomly selected toast
    hr = poptoast(toast_notifications[random_index]);
    
    Sleep(1);
    toast_cleanup();
    
    return FAILED(hr);
}

int show_toast_and_exit(const wchar_t* toast_xml) {
	HRESULT hr;
	toast_setup_icon(L"%TEMP%\\thenews\\icon.png");
	hr = toast_init(L"theNewsWin32", L"the news", L"%TEMP%\\thenews\\icon.png");
	if (FAILED(hr)) return 1;
	toast_set_activation_callback(my_activation_callback);
	hr = poptoast(toast_xml);
	Sleep(1);
	toast_cleanup();
	return FAILED(hr);
}

int show_all_toasts() {
	toast_setup_icon(L"%TEMP%\\thenews\\icon.png");
	HRESULT hr = toast_init(L"theNewsWin32", L"the news", L"%TEMP%\\thenews\\icon.png");
	if (FAILED(hr)) return 1;
	toast_set_activation_callback(my_activation_callback);
	
	for (int i = 0; i < toast_count; i++) {
		poptoast(toast_notifications[i]);
	}

	toast_cleanup();
	return 0;
}

void show_help() {
	printf("the news - be annoying to everyone\n");
	printf("Usage: thenews.exe [command]\n\n");
	printf("Available commands:\n");
	printf("  help             - Show this help message\n");
	printf("  random           - Show a random toast notification\n");
	printf("  someoneDied      - Show breaking news about someone dying\n");
	printf("  plzDonate        - Show a donation request\n");
	printf("  plzDonate2       - Show a second donation request\n");
	printf("  systemDelete     - Show system deletion warning\n");
	printf("  johnCall         - Show incoming call from John Phone\n");
	printf("  weather          - Show weather forecast\n");
	printf("  johnFQ       	   - Show free friend request\n");
	printf("  websiteRedesign  - Show website redesign notification\n");
	printf("  roadblocks       - Show roadblocks notification\n");
	printf("  linker           - Show news about linker going all in on black, loses it all in one night\n");
	printf("  all              - Show all notifications\n\n");
	printf("  random              - Randomize through all notifications\n\n");
	printf("If no command is specified, shows a random notification.\n");
}

#ifdef BUILD_DLL
// DLL exported functions
__declspec(dllexport) int ShowRandomToast() {
    return show_random_toast();
}

__declspec(dllexport) int ShowToastByIndex(int index) {
    if (index < 0 || index >= toast_count) {
        return 1; // Invalid index
    }
    
    ensure_resources();
    RegSetKeyValueW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Classes\\AppUserModelId\\theNewsWin32", L"IconUri", REG_EXPAND_SZ, L"%TEMP%\\thenews\\icon.png", (wcslen(L"%TEMP%\\thenews\\icon.png") + 1) * sizeof(wchar_t));
    RegSetKeyValueW(HKEY_CURRENT_USER, L"SOFTWARE\\Classes\\AppUserModelId\\theNewsWin32", L"IconUri", REG_EXPAND_SZ, L"%TEMP%\\thenews\\icon.png", (wcslen(L"%TEMP%\\thenews\\icon.png") + 1) * sizeof(wchar_t));
    
    return show_toast_and_exit(toast_notifications[index]);
}

__declspec(dllexport) int ShowAllToasts() {
    ensure_resources();
    RegSetKeyValueW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Classes\\AppUserModelId\\theNewsWin32", L"IconUri", REG_EXPAND_SZ, L"%TEMP%\\thenews\\icon.png", (wcslen(L"%TEMP%\\thenews\\icon.png") + 1) * sizeof(wchar_t));
    RegSetKeyValueW(HKEY_CURRENT_USER, L"SOFTWARE\\Classes\\AppUserModelId\\theNewsWin32", L"IconUri", REG_EXPAND_SZ, L"%TEMP%\\thenews\\icon.png", (wcslen(L"%TEMP%\\thenews\\icon.png") + 1) * sizeof(wchar_t));
    
    return show_all_toasts();
}

__declspec(dllexport) int ShowToastByName(const char* name) {
    if (!name) return 1;
    
    ensure_resources();
    RegSetKeyValueW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Classes\\AppUserModelId\\theNewsWin32", L"IconUri", REG_EXPAND_SZ, L"%TEMP%\\thenews\\icon.png", (wcslen(L"%TEMP%\\thenews\\icon.png") + 1) * sizeof(wchar_t));
    RegSetKeyValueW(HKEY_CURRENT_USER, L"SOFTWARE\\Classes\\AppUserModelId\\theNewsWin32", L"IconUri", REG_EXPAND_SZ, L"%TEMP%\\thenews\\icon.png", (wcslen(L"%TEMP%\\thenews\\icon.png") + 1) * sizeof(wchar_t));
    
    if (strcmp(name, "someoneDied") == 0) {
        return show_toast_and_exit(someoneDied);
    } else if (strcmp(name, "plzDonate") == 0) {
        return show_toast_and_exit(plzDonate);
    } else if (strcmp(name, "plzDonate2") == 0) {
        return show_toast_and_exit(plzDonate2);
    } else if (strcmp(name, "systemDelete") == 0) {
        return show_toast_and_exit(systemDelete);
    } else if (strcmp(name, "johnCall") == 0) {
        return show_toast_and_exit(johnCall);
    } else if (strcmp(name, "weather") == 0) {
        return show_toast_and_exit(weather);
    } else if (strcmp(name, "johnFQ") == 0) {
        return show_toast_and_exit(johnFQ);
    } else if (strcmp(name, "websiteRedesign") == 0) {
        return show_toast_and_exit(websiteRedesign);
    } else if (strcmp(name, "roadblocks") == 0) {
        return show_toast_and_exit(roadblocks);
    } else if (strcmp(name, "linker") == 0) {
        return show_toast_and_exit(linker);
    } else if (strcmp(name, "random") == 0) {
        return show_random_toast();
    } else if (strcmp(name, "all") == 0) {
        return show_all_toasts();
    }
    
    return 1; // Unknown toast name
}

__declspec(dllexport) int GetToastCount() {
    return toast_count;
}

__declspec(dllexport) void EnsureToastResources() {
    ensure_resources();
}

// RunDLL32 compatible wrapper functions
__declspec(dllexport) void CALLBACK RunDLL32_ShowRandomToast(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow) {
    ShowRandomToast();
}

__declspec(dllexport) void CALLBACK RunDLL32_ShowAllToasts(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow) {
    ShowAllToasts();
}

__declspec(dllexport) void CALLBACK RunDLL32_ShowToastByName(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow) {
    // lpszCmdLine contains the command line arguments
    if (lpszCmdLine && strlen(lpszCmdLine) > 0) {
        // Remove quotes if present
        char* name = lpszCmdLine;
        if (name[0] == '"') {
            name++;
            char* end = strrchr(name, '"');
            if (end) *end = '\0';
        }
        ShowToastByName(name);
    } else {
        ShowRandomToast(); // Default to random if no name provided
    }
}

__declspec(dllexport) void CALLBACK RunDLL32_ShowToastByIndex(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow) {
    if (lpszCmdLine && strlen(lpszCmdLine) > 0) {
        int index = atoi(lpszCmdLine);
        ShowToastByIndex(index);
    } else {
        ShowRandomToast(); // Default to random if no index provided
    }
}

// DLL Entry Point
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            // Initialize when DLL is loaded
            srand((unsigned int)time(NULL));
            break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

#else
// EXE main function
int main(int argc, char** argv) {
	if (argc > 1 && strcmp(argv[1], "-ToastActivated") == 0) {
		return 0;
	}
	
	ensure_resources();
	RegSetKeyValueW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Classes\\AppUserModelId\\theNewsWin32", L"IconUri", REG_EXPAND_SZ, L"%TEMP%\\thenews\\icon.png", (wcslen(L"%TEMP%\\thenews\\icon.png") + 1) * sizeof(wchar_t));
	RegSetKeyValueW(HKEY_CURRENT_USER, L"SOFTWARE\\Classes\\AppUserModelId\\theNewsWin32", L"IconUri", REG_EXPAND_SZ, L"%TEMP%\\thenews\\icon.png", (wcslen(L"%TEMP%\\thenews\\icon.png") + 1) * sizeof(wchar_t));

	if (argc > 1) {
		if (strcmp(argv[1], "help") == 0) {
			show_help();
			return 0;
		} else if (strcmp(argv[1], "random") == 0) {
			return show_random_toast();
		} else if (strcmp(argv[1], "someoneDied") == 0) {
			return show_toast_and_exit(someoneDied);
		} else if (strcmp(argv[1], "plzDonate") == 0) {
			return show_toast_and_exit(plzDonate);
		} else if (strcmp(argv[1], "plzDonate2") == 0) {
			return show_toast_and_exit(plzDonate2);
		} else if (strcmp(argv[1], "systemDelete") == 0) {
			return show_toast_and_exit(systemDelete);
		} else if (strcmp(argv[1], "johnCall") == 0) {
			return show_toast_and_exit(johnCall);
		} else if (strcmp(argv[1], "weather") == 0) {
			return show_toast_and_exit(weather);
		} else if (strcmp(argv[1], "johnFQ") == 0) {
			return show_toast_and_exit(johnFQ);
		} else if (strcmp(argv[1], "websiteRedesign") == 0) {
			return show_toast_and_exit(websiteRedesign);
		} else if (strcmp(argv[1], "roadblocks") == 0) {
			return show_toast_and_exit(roadblocks);
		} else if (strcmp(argv[1], "linker") == 0) {
			return show_toast_and_exit(linker);
		} else if (strcmp(argv[1], "random") == 0) {
			return show_random_toast();
		} else if (strcmp(argv[1], "all") == 0) {
			return show_all_toasts();
		} else {
			return 1;
		}
	}

	// Default behavior: show random toast instead of all toasts
	return show_random_toast();
}
#endif