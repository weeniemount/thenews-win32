#include "toast.h"
#include <initguid.h>
#include <roapi.h>
#include <Windows.ui.notifications.h>
#include <notificationactivationcallback.h>
#include <tchar.h>
#include <stdio.h>
#include <shlobj.h>
#pragma comment(lib, "runtimeobject.lib")

static DWORD g_dwMainThreadId = 0;
static BOOL g_bInitialized = FALSE;
static DWORD g_dwCookie = 0;
static const wchar_t* g_appId = NULL;
static wchar_t g_appIdBuffer[256];
static toast_activation_callback_t g_activationCallback = NULL;

#define GUID_Impl_INotificationActivationCallback_Textual "0F82E845-CB89-4039-BDBF-67CA33254C76"
DEFINE_GUID(GUID_Impl_INotificationActivationCallback,
    0xf82e845, 0xcb89, 0x4039, 0xbd, 0xbf, 0x67, 0xca, 0x33, 0x25, 0x4c, 0x76);

DEFINE_GUID(IID_IToastNotificationManagerStatics,
    0x50ac103f, 0xd235, 0x4598, 0xbb, 0xef, 0x98, 0xfe, 0x4d, 0x1a, 0x3a, 0xd4);
DEFINE_GUID(IID_IToastNotificationFactory,
    0x04124b20, 0x82c6, 0x4229, 0xb1, 0x09, 0xfd, 0x9e, 0xd4, 0x66, 0x2b, 0x53);
DEFINE_GUID(IID_IXmlDocument,
    0xf7f3a506, 0x1e87, 0x42d6, 0xbc, 0xfb, 0xb8, 0xc8, 0x09, 0xfa, 0x54, 0x94);
DEFINE_GUID(IID_IXmlDocumentIO,
    0x6cd0e74e, 0xee65, 0x4489, 0x9e, 0xbf, 0xca, 0x43, 0xe8, 0x7b, 0xa6, 0x37);

typedef struct Impl_IGeneric {
    IUnknownVtbl* lpVtbl;
    LONG64 dwRefCount;
} Impl_IGeneric;

static Impl_IGeneric* g_pClassFactory = NULL;

static ULONG STDMETHODCALLTYPE Impl_IGeneric_AddRef(Impl_IGeneric* _this) {
    return InterlockedIncrement64(&(_this->dwRefCount));
}

static ULONG STDMETHODCALLTYPE Impl_IGeneric_Release(Impl_IGeneric* _this) {
    LONG64 dwNewRefCount = InterlockedDecrement64(&(_this->dwRefCount));
    if (!dwNewRefCount) free(_this);
    return dwNewRefCount;
}

static HRESULT STDMETHODCALLTYPE Impl_INotificationActivationCallback_QueryInterface(
    Impl_IGeneric* _this, REFIID riid, void** ppvObject) {
    if (!IsEqualIID(riid, &IID_INotificationActivationCallback) && !IsEqualIID(riid, &IID_IUnknown)) {
        *ppvObject = NULL;
        return E_NOINTERFACE;
    }
    *ppvObject = _this;
    _this->lpVtbl->AddRef(_this);
    return S_OK;
}

static HRESULT STDMETHODCALLTYPE Impl_INotificationActivationCallback_Activate(
    INotificationActivationCallback* _this, LPCWSTR appUserModelId, LPCWSTR invokedArgs,
    const NOTIFICATION_USER_INPUT_DATA* data, ULONG count) {
    
    if (g_activationCallback) {
        g_activationCallback(appUserModelId, invokedArgs);
    } else {
        wprintf(L"Toast activated: AUMID=\"%s\", Args=\"%s\"\n", appUserModelId, invokedArgs);
        if (!_wcsicmp(invokedArgs, L"action=closeApp")) {
            PostThreadMessageW(g_dwMainThreadId, WM_QUIT, 0, 0);
        }
    }
    return S_OK;
}

static const INotificationActivationCallbackVtbl Impl_INotificationActivationCallback_Vtbl = {
    .QueryInterface = Impl_INotificationActivationCallback_QueryInterface,
    .AddRef = Impl_IGeneric_AddRef,
    .Release = Impl_IGeneric_Release,
    .Activate = Impl_INotificationActivationCallback_Activate
};

static HRESULT STDMETHODCALLTYPE Impl_IClassFactory_QueryInterface(
    Impl_IGeneric* _this, REFIID riid, void** ppvObject) {
    if (!IsEqualIID(riid, &IID_IClassFactory) && !IsEqualIID(riid, &IID_IUnknown)) {
        *ppvObject = NULL;
        return E_NOINTERFACE;
    }
    *ppvObject = _this;
    _this->lpVtbl->AddRef(_this);
    return S_OK;
}

static HRESULT STDMETHODCALLTYPE Impl_IClassFactory_LockServer(IClassFactory* _this, BOOL flock) {
    return S_OK;
}

static HRESULT STDMETHODCALLTYPE Impl_IClassFactory_CreateInstance(
    IClassFactory* _this, IUnknown* punkOuter, REFIID vTableGuid, void** ppv) {
    HRESULT hr = E_NOINTERFACE;
    Impl_IGeneric* thisobj = NULL;
    *ppv = 0;

    if (punkOuter) {
        hr = CLASS_E_NOAGGREGATION;
    } else {
        thisobj = malloc(sizeof(Impl_IGeneric));
        if (!thisobj) {
            hr = E_OUTOFMEMORY;
        } else {
            thisobj->lpVtbl = &Impl_INotificationActivationCallback_Vtbl;
            thisobj->dwRefCount = 1;
            hr = thisobj->lpVtbl->QueryInterface(thisobj, vTableGuid, ppv);
            thisobj->lpVtbl->Release(thisobj);
        }
    }
    return hr;
}

static const IClassFactoryVtbl Impl_IClassFactory_Vtbl = {
    .QueryInterface = Impl_IClassFactory_QueryInterface,
    .AddRef = Impl_IGeneric_AddRef,
    .Release = Impl_IGeneric_Release,
    .LockServer = Impl_IClassFactory_LockServer,
    .CreateInstance = Impl_IClassFactory_CreateInstance
};

// Helper function to check if file exists
static BOOL FileExists(const wchar_t* path) {
    DWORD dwAttrib = GetFileAttributesW(path);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

// Helper function to create directory if it doesn't exist
static BOOL CreateDirectoryRecursive(const wchar_t* path) {
    wchar_t temp[MAX_PATH];
    wcscpy_s(temp, MAX_PATH, path);
    
    for (wchar_t* p = temp; *p; p++) {
        if (*p == L'\\' || *p == L'/') {
            *p = L'\0';
            CreateDirectoryW(temp, NULL);
            *p = L'\\';
        }
    }
    return CreateDirectoryW(temp, NULL) || GetLastError() == ERROR_ALREADY_EXISTS;
}

HRESULT toast_init(const wchar_t* appId, const wchar_t* displayName, const wchar_t* customIconPath) {
    if (g_bInitialized) return S_OK;
    
    HRESULT hr = S_OK;
    g_dwMainThreadId = GetCurrentThreadId();
    
    wcscpy_s(g_appIdBuffer, 256, appId);
    g_appId = g_appIdBuffer;
    
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (SUCCEEDED(hr)) {
        hr = RoInitialize(RO_INIT_MULTITHREADED);
    }
    
    if (SUCCEEDED(hr)) {
        g_pClassFactory = malloc(sizeof(Impl_IGeneric));
        if (!g_pClassFactory) {
            hr = E_OUTOFMEMORY;
        } else {
            g_pClassFactory->lpVtbl = &Impl_IClassFactory_Vtbl;
            g_pClassFactory->dwRefCount = 1;
        }
    }
    
    if (SUCCEEDED(hr)) {
        hr = CoRegisterClassObject(&GUID_Impl_INotificationActivationCallback, 
            g_pClassFactory, CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &g_dwCookie);
    }
    
    if (SUCCEEDED(hr)) {
        wchar_t wszExePath[MAX_PATH + 100];
        ZeroMemory(wszExePath, sizeof(wszExePath));
        
        if (GetModuleFileNameW(NULL, wszExePath + 1, MAX_PATH)) {
            wszExePath[0] = L'"';
            wcscat_s(wszExePath, MAX_PATH + 100, L"\" -ToastActivated");
            
            hr = HRESULT_FROM_WIN32(RegSetValueW(HKEY_CURRENT_USER, 
                L"SOFTWARE\\Classes\\CLSID\\{" _T(GUID_Impl_INotificationActivationCallback_Textual) L"}\\LocalServer32", 
                REG_SZ, wszExePath, (wcslen(wszExePath) + 1) * sizeof(wchar_t)));
        } else {
            hr = E_FAIL;
        }
    }
    
    if (SUCCEEDED(hr)) {
        wchar_t regPath[512];
        swprintf_s(regPath, 512, L"SOFTWARE\\Classes\\AppUserModelId\\%s", appId);
        
        hr = HRESULT_FROM_WIN32(RegSetKeyValueW(HKEY_CURRENT_USER, regPath, 
            L"DisplayName", REG_SZ, displayName, (wcslen(displayName) + 1) * sizeof(wchar_t)));
        
        if (SUCCEEDED(hr)) {
            hr = HRESULT_FROM_WIN32(RegSetKeyValueW(HKEY_CURRENT_USER, regPath, 
                L"CustomActivator", REG_SZ, L"{" _T(GUID_Impl_INotificationActivationCallback_Textual) L"}", 
                39 * sizeof(wchar_t)));
        }
        
        if (SUCCEEDED(hr) && customIconPath && FileExists(customIconPath)) {
            hr = HRESULT_FROM_WIN32(RegSetKeyValueW(HKEY_CURRENT_USER, regPath, 
                L"IconUri", REG_SZ, customIconPath, (wcslen(customIconPath) + 1) * sizeof(wchar_t)));
            
            if (SUCCEEDED(hr)) {
                wchar_t hkcrPath[512];
                swprintf_s(hkcrPath, 512, L"AppUserModelId\\%s", appId);
                RegSetKeyValueW(HKEY_CLASSES_ROOT, hkcrPath, 
                    L"IconUri", REG_SZ, customIconPath, (wcslen(customIconPath) + 1) * sizeof(wchar_t));
            }
        }
    }
    
    if (SUCCEEDED(hr)) {
        g_bInitialized = TRUE;
    }
    
    return hr;
}

HRESULT poptoast(const wchar_t* toastXml) {
    if (!g_bInitialized) return E_FAIL;
    
    HRESULT hr = S_OK;
    
    HSTRING_HEADER hshAppId;
    HSTRING hsAppId = NULL;
    hr = WindowsCreateStringReference(g_appId, (UINT32)wcslen(g_appId), &hshAppId, &hsAppId);
    
    HSTRING_HEADER hshToastNotificationManager;
    HSTRING hsToastNotificationManager = NULL;
    if (SUCCEEDED(hr)) {
        hr = WindowsCreateStringReference(RuntimeClass_Windows_UI_Notifications_ToastNotificationManager, 
            (UINT32)(sizeof(RuntimeClass_Windows_UI_Notifications_ToastNotificationManager) / sizeof(wchar_t) - 1), 
            &hshToastNotificationManager, &hsToastNotificationManager);
    }
    
    __x_ABI_CWindows_CUI_CNotifications_CIToastNotificationManagerStatics* pToastNotificationManager = NULL;
    if (SUCCEEDED(hr)) {
        hr = RoGetActivationFactory(hsToastNotificationManager, &IID_IToastNotificationManagerStatics, 
            (LPVOID*)&pToastNotificationManager);
    }
    
    __x_ABI_CWindows_CUI_CNotifications_CIToastNotifier* pToastNotifier = NULL;
    if (SUCCEEDED(hr)) {
        hr = pToastNotificationManager->lpVtbl->CreateToastNotifierWithId(pToastNotificationManager, 
            hsAppId, &pToastNotifier);
    }
    
    HSTRING_HEADER hshXmlDocument;
    HSTRING hsXmlDocument = NULL;
    if (SUCCEEDED(hr)) {
        hr = WindowsCreateStringReference(RuntimeClass_Windows_Data_Xml_Dom_XmlDocument, 
            (UINT32)(sizeof(RuntimeClass_Windows_Data_Xml_Dom_XmlDocument) / sizeof(wchar_t) - 1), 
            &hshXmlDocument, &hsXmlDocument);
    }
    
    IInspectable* pInspectable = NULL;
    if (SUCCEEDED(hr)) {
        hr = RoActivateInstance(hsXmlDocument, &pInspectable);
    }
    
    __x_ABI_CWindows_CData_CXml_CDom_CIXmlDocument* pXmlDocument = NULL;
    if (SUCCEEDED(hr)) {
        hr = pInspectable->lpVtbl->QueryInterface(pInspectable, &IID_IXmlDocument, &pXmlDocument);
    }
    
    __x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentIO* pXmlDocumentIO = NULL;
    if (SUCCEEDED(hr)) {
        hr = pXmlDocument->lpVtbl->QueryInterface(pXmlDocument, &IID_IXmlDocumentIO, &pXmlDocumentIO);
    }
    
    HSTRING_HEADER hshToastXml;
    HSTRING hsToastXml = NULL;
    if (SUCCEEDED(hr)) {
        hr = WindowsCreateStringReference(toastXml, (UINT32)wcslen(toastXml), &hshToastXml, &hsToastXml);
    }
    
    if (SUCCEEDED(hr)) {
        hr = pXmlDocumentIO->lpVtbl->LoadXml(pXmlDocumentIO, hsToastXml);
    }
    
    HSTRING_HEADER hshToastNotification;
    HSTRING hsToastNotification = NULL;
    if (SUCCEEDED(hr)) {
        hr = WindowsCreateStringReference(RuntimeClass_Windows_UI_Notifications_ToastNotification, 
            (UINT32)(sizeof(RuntimeClass_Windows_UI_Notifications_ToastNotification) / sizeof(wchar_t) - 1), 
            &hshToastNotification, &hsToastNotification);
    }
    
    __x_ABI_CWindows_CUI_CNotifications_CIToastNotificationFactory* pNotificationFactory = NULL;
    if (SUCCEEDED(hr)) {
        hr = RoGetActivationFactory(hsToastNotification, &IID_IToastNotificationFactory, 
            (LPVOID*)&pNotificationFactory);
    }
    
    __x_ABI_CWindows_CUI_CNotifications_CIToastNotification* pToastNotification = NULL;
    if (SUCCEEDED(hr)) {
        hr = pNotificationFactory->lpVtbl->CreateToastNotification(pNotificationFactory, 
            pXmlDocument, &pToastNotification);
    }
    
    if (SUCCEEDED(hr)) {
        hr = pToastNotifier->lpVtbl->Show(pToastNotifier, pToastNotification);
    }
    
    if (pToastNotification) pToastNotification->lpVtbl->Release(pToastNotification);
    if (pNotificationFactory) pNotificationFactory->lpVtbl->Release(pNotificationFactory);
    if (pXmlDocumentIO) pXmlDocumentIO->lpVtbl->Release(pXmlDocumentIO);
    if (pXmlDocument) pXmlDocument->lpVtbl->Release(pXmlDocument);
    if (pInspectable) pInspectable->lpVtbl->Release(pInspectable);
    if (pToastNotifier) pToastNotifier->lpVtbl->Release(pToastNotifier);
    if (pToastNotificationManager) pToastNotificationManager->lpVtbl->Release(pToastNotificationManager);
    
    return hr;
}

int toast_message_loop(void) {
    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    return 0;
}

void toast_set_activation_callback(toast_activation_callback_t callback) {
    g_activationCallback = callback;
}

void toast_cleanup(void) {
    if (!g_bInitialized) return;
    
    if (g_dwCookie) {
        CoRevokeClassObject(g_dwCookie);
        g_dwCookie = 0;
    }
    
    if (g_pClassFactory) {
        g_pClassFactory->lpVtbl->Release(g_pClassFactory);
        g_pClassFactory = NULL;
    }
    
    RoUninitialize();
    CoUninitialize();
    
    g_bInitialized = FALSE;
}

// Helper function to copy icon to application directory
HRESULT toast_setup_icon(const wchar_t* sourceIconPath) {
    RegSetKeyValueW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Classes\\AppUserModelId\\theNewsWin32", L"IconUri", REG_SZ, L"%TEMP%\\thenews\\icon.png", (wcslen(L"%TEMP%\\thenews\\icon.png") + 1) * sizeof(wchar_t));
    wchar_t appDir[MAX_PATH];
    wchar_t destPath[MAX_PATH];
    
    // Get application directory
    if (!GetModuleFileNameW(NULL, appDir, MAX_PATH)) {
        return E_FAIL;
    }
    
    wchar_t* lastSlash = wcsrchr(appDir, L'\\');
    if (!lastSlash) {
        return E_FAIL;
    }
    
    *(lastSlash + 1) = L'\0';
    swprintf_s(destPath, MAX_PATH, L"%sicon.png", appDir);
    
    // Copy icon file to application directory
    if (CopyFileW(sourceIconPath, destPath, FALSE)) {
        return S_OK;
    }
    
    return HRESULT_FROM_WIN32(GetLastError());
}