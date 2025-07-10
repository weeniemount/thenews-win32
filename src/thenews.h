#ifndef THENEWS_H
#define THENEWS_H

#ifdef __cplusplus
extern "C" {
#endif

// DLL function declarations for external use
// When using the DLL, include this header file

/**
 * Show a random toast notification
 * @return 0 on success, non-zero on failure
 */
int ShowRandomToast();

/**
 * Show a toast notification by index
 * @param index Index of the toast (0-9)
 * @return 0 on success, non-zero on failure
 */
int ShowToastByIndex(int index);

/**
 * Show all toast notifications
 * @return 0 on success, non-zero on failure
 */
int ShowAllToasts();

/**
 * Show a toast notification by name
 * @param name Name of the toast notification
 * Available names: "someoneDied", "plzDonate", "plzDonate2", "systemDelete", 
 *                  "johnCall", "weather", "johnFQ", "websiteRedesign", 
 *                  "roadblocks", "linker", "random", "all"
 * @return 0 on success, non-zero on failure
 */
int ShowToastByName(const char* name);

/**
 * Get the total number of available toast notifications
 * @return Number of toast notifications
 */
int GetToastCount();

/**
 * Ensure all required resources are extracted
 */
void EnsureToastResources();

#ifdef __cplusplus
}
#endif

#endif // THENEWS_H