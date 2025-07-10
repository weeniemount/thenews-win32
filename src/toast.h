#ifndef TOAST_H
#define TOAST_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the toast notification system.
 * Must be called before using poptoast().
 * 
 * @param appId Application User Model ID (AUMID) for your app
 * @param displayName Display name for your app in notifications
 * @return S_OK on success, error HRESULT on failure
 */
HRESULT toast_init(const wchar_t* appId, const wchar_t* displayName, 
                   const wchar_t* customIconPath);

HRESULT toast_setup_icon(const wchar_t* iconPath);

/**
 * Show a toast notification.
 * 
 * @param toastXml XML content for the toast notification
 * @return S_OK on success, error HRESULT on failure
 */
HRESULT poptoast(const wchar_t* toastXml);

/**
 * Run the message loop to handle toast interactions.
 * This is a blocking call that processes messages until WM_QUIT is received.
 * 
 * @return 0 on normal exit
 */
int toast_message_loop(void);

/**
 * Cleanup the toast notification system.
 * Should be called before program exit.
 */
void toast_cleanup(void);

/**
 * Set a custom activation callback.
 * By default, the library handles basic activation.
 * 
 * @param callback Function to call when toast is activated
 */
typedef void (*toast_activation_callback_t)(const wchar_t* appUserModelId, const wchar_t* invokedArgs);
void toast_set_activation_callback(toast_activation_callback_t callback);

#ifdef __cplusplus
}
#endif

#endif // TOAST_H