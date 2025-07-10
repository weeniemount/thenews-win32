#include "johnFQ.h"

const wchar_t johnFQ[] =
L"<toast launch=\"action=viewFriendRequest&amp;userId=49183\">\r\n"
L"  <visual>\r\n"
L"    <binding template=\"ToastGeneric\">\r\n"
L"      <text>John Phone sent you a friend request</text>\r\n"
L"      <text>i want Sponsorships.</text>\r\n"
L"      <image placement=\"appLogoOverride\" hint-crop=\"circle\" src=\"file:///%TEMP%/thenews/johnphone.jpg\" />\r\n"
L"    </binding>\r\n"
L"  </visual>\r\n"
L"  <actions>\r\n"
L"    <action content=\"Accept\" arguments=\"action=acceptFriendRequest&amp;userId=49183\" activationType=\"background\" />\r\n"
L"    <action content=\"Decline\" arguments=\"action=declineFriendRequest&amp;userId=49183\" activationType=\"background\" />\r\n"
L"  </actions>\r\n"
L"</toast>\r\n";
