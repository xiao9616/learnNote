#include <iostream>
#include "message.h"
#include "device.h"
#include "pcDevice.h"
#include "mobileDevice.h"
#include "meaagePerfect.h"
#include "messageLite.h"

using namespace std;
int main() {
    device *pc = new pcDevice();
    device *mobile = new mobileDevice();
    message *messagelite = new messageLite(pc);
    message *messageperfect = new meaagePerfect(mobile);
    messagelite->Login();
    messagelite->sendMessage();
    messagelite->sendPicture();
    cout << "===============" << endl;
    messageperfect->Login();
    messageperfect->sendMessage();
    messageperfect->sendPicture();
    return 0;
}