# the news, win 32 edition

a win 32 edition of the first page of notifications from my [UWP app](https://github.com/weeniemount/thenews)

# download
download it from the [releases](https://github.com/weeniemount/thenews-win32/releases) or download a dev build from the [actions](https://github.com/weeniemount/thenews-win32/actions).

you can use the standalone exe or the dll. to use the dll look at the section below.

# how 2 use as a dll in c/c++
download the dll from the respective page and then include the "thenews.h" file. then you could do something like this:
```c
#include "thenews.h"

int main() {
    // you can do anything from the thenews.h file, but for this example we will use the random toast function
    ShowRandomToast()
    return 0;
}
```

then just compile with whatever compiler you use and use the .a or the .lib provided in the download!

# building it yourself
if you want to build it yourself, you have to install visual studio 2022. when you install it, use the "x86/x64 Native Command Prompt for VS 2022". this command prompt has the compiling tools you need. then just run build.bat for an exe or buildDLL.bat if you want a dll.