#ifndef FLASHPLAYER_H
#define FLASHPLAYER_H

#include <wchar.h>
const wchar_t flashPlayer[] =
L"<toast launch=\"action=viewStory&amp;storyId=92187\">\r\n"
L"  <visual>\r\n"
L"    <binding template=\"ToastGeneric\">\r\n"
L"      <image placement=\"appLogoOverride\" src=\"file:///%TEMP%/thenews/flashplayer.png\"/>\r\n"
L"      <text><![CDATA[BREAKING NEWS!!!]]></text>\r\n"
L"      <text>To view this notification, install Adobe&#174; Flash Player&#8482;</text>\r\n"
L"    </binding>\r\n"
L"  </visual>\r\n"
L"</toast>\r\n";

#endif // FLASHPLAYER_H
