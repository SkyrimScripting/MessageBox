#include <SkyrimScripting/Plugin.h>

#include "CustomMessageBox.h"

PluginLogDisable;

EventHandlers {
    On<RE::TESActivateEvent>([](const RE::TESActivateEvent* event) {
        if (event->actionRef->GetFormID() == 0x14) {
            auto activatedName = std::string{event->objectActivated->GetBaseObject()->GetName()};
            if (!activatedName.empty()) {
                auto message = std::format("You activated {}.\nHow do you feel about that?", activatedName);
                auto buttons = std::vector<std::string>{"Pretty good", "Not bad", "Ok"};
                CustomMessageBox::Show(message, buttons, [](uint32_t result) {
                    RE::DebugNotification(std::format("You selected {}", result).c_str());
                });
            }
        }
    });
}
