#include "linker.h"

const wchar_t linker[] =
L"<toast launch=\"action=viewPhoto&amp;photoId=92187\">\r\n"
L"  <visual>\r\n"
L"    <binding template=\"ToastGeneric\">\r\n"
L"      <text><![CDATA[BREAKING NEWS!!!]]></text>\r\n"
L"      <text><![CDATA[Discord user @linker.sh, from the server 'Face's attic', goes all in on black, loses it all in 1 night - tragedy unfolds.]]></text>\r\n"
L"      <image placement=\"inline\" src=\"file:///%TEMP%/thenews/linker.png\" />\r\n"
L"    </binding>\r\n"
L"  </visual>\r\n"
L"  <actions>\r\n"
L"    <action content=\"Read More\" arguments=\"likePhoto&amp;photoId=92187\" activationType=\"background\" />\r\n"
L"    <action content=\"discard\" arguments=\"action=commentPhoto&amp;photoId=92187\" activationType=\"foreground\" />\r\n"
L"  </actions>\r\n"
L"</toast>\r\n";

