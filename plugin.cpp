#include <SkyrimScripting/Plugin.h>

OnInit { logger::info("Hello log from SKSE Starter Kit!"); }
OnDataLoaded { ConsoleLog("Hello console from SKSE Starter Kit!"); }

EventHandlers {
    On<RE::TESActivateEvent>([](const RE::TESActivateEvent* event) {
        auto activated = event->objectActivated->GetBaseObject()->GetName();
        auto activator = event->actionRef->GetBaseObject()->GetName();
        ConsoleLog("{} activated {}", activator, activated);
    });
}
