#include <SkyrimScripting/MessageBox.h>
#include <SkyrimScripting/Plugin.h>

#include <algorithm>
#include <atomic>
#include <unordered_map>
#include <vector>

// TODO: add <Escape> key to cancel support :)

PluginLogDisable;

namespace SkyrimScripting::MessageBox::Plugin {

    std::atomic<unsigned int> _nextMessageBoxId = 1;
    std::unordered_map<unsigned int, unsigned int> _messageBoxResults;
    std::unordered_map<unsigned int, std::vector<std::string>> _messageBoxButtons;

    unsigned int GetNewMessageBoxId() { return _nextMessageBoxId++; }

    namespace PapyrusInterface::SkyMessage {

        unsigned int ShowArrayNonBlocking(RE::StaticFunctionTag*, std::string bodyText,
                                          std::vector<std::string> buttonTexts) {
            std::erase_if(buttonTexts, [](const std::string& text) { return text.empty(); });
            auto messageBoxId = GetNewMessageBoxId();
            _messageBoxButtons.emplace(messageBoxId, buttonTexts);
            SkyrimScripting::ShowMessageBox(bodyText, buttonTexts, [messageBoxId](uint32_t result) {
                if (messageBoxId) _messageBoxResults.insert_or_assign(messageBoxId, result);
            });
            return messageBoxId;
        }

        unsigned int ShowNonBlocking(RE::StaticFunctionTag*, std::string bodyText, std::string button1,
                                     std::string button2 = "", std::string button3 = "", std::string button4 = "",
                                     std::string button5 = "", std::string button6 = "", std::string button7 = "",
                                     std::string button8 = "", std::string button9 = "", std::string button10 = "") {
            std::vector<std::string> buttonTexts;
            if (!button1.empty()) buttonTexts.push_back(button1);
            if (!button2.empty()) buttonTexts.push_back(button2);
            if (!button3.empty()) buttonTexts.push_back(button3);
            if (!button4.empty()) buttonTexts.push_back(button4);
            if (!button5.empty()) buttonTexts.push_back(button5);
            if (!button6.empty()) buttonTexts.push_back(button6);
            if (!button7.empty()) buttonTexts.push_back(button7);
            if (!button8.empty()) buttonTexts.push_back(button8);
            if (!button9.empty()) buttonTexts.push_back(button9);
            if (!button10.empty()) buttonTexts.push_back(button10);
            return ShowArrayNonBlocking(nullptr, bodyText, buttonTexts);
        }

        void Delete(RE::StaticFunctionTag*, unsigned int messageBoxId) {
            if (_messageBoxResults.contains(messageBoxId)) _messageBoxResults.erase(messageBoxId);
            if (_messageBoxButtons.contains(messageBoxId)) _messageBoxButtons.erase(messageBoxId);
        }

        std::string GetResultText(RE::StaticFunctionTag*, unsigned int messageBoxId, bool deleteResultOnAccess = true) {
            std::string resultString;
            if (_messageBoxResults.contains(messageBoxId) && _messageBoxButtons.contains(messageBoxId)) {
                auto index = _messageBoxResults.at(messageBoxId);
                auto buttons = _messageBoxButtons.at(messageBoxId);
                if (buttons.size() > index) resultString = buttons.at(index);
                if (deleteResultOnAccess) Delete(nullptr, messageBoxId);
            }
            return resultString;
        }

        unsigned int GetResultIndex(RE::StaticFunctionTag*, unsigned int messageBoxId,
                                    bool deleteResultOnAccess = true) {
            unsigned int index = 0;
            if (_messageBoxResults.contains(messageBoxId)) {
                index = _messageBoxResults.at(messageBoxId);
                if (deleteResultOnAccess) Delete(nullptr, messageBoxId);
            }
            return index;
        }

        bool IsMessageResultAvailable(RE::StaticFunctionTag*, unsigned int messageBoxId) {
            return _messageBoxResults.contains(messageBoxId);
        }
    }

    bool RegisterPapyrusFunctions(RE::BSScript::IVirtualMachine* vm) {
        vm->RegisterFunction("Show_NonBlocking", "SkyMessage", PapyrusInterface::SkyMessage::ShowNonBlocking);
        vm->RegisterFunction("ShowArray_NonBlocking", "SkyMessage", PapyrusInterface::SkyMessage::ShowArrayNonBlocking);
        vm->RegisterFunction("GetResultText", "SkyMessage", PapyrusInterface::SkyMessage::GetResultText);
        vm->RegisterFunction("GetResultIndex", "SkyMessage", PapyrusInterface::SkyMessage::GetResultIndex);
        vm->RegisterFunction("Delete", "SkyMessage", PapyrusInterface::SkyMessage::Delete);
        vm->RegisterFunction("IsMessageResultAvailable", "SkyMessage",
                             PapyrusInterface::SkyMessage::IsMessageResultAvailable);
        return true;
    }

    OnInit { SKSE::GetPapyrusInterface()->Register(RegisterPapyrusFunctions); }
}
