scriptName SkyMessage hidden
{Display custom Messages with any number of buttons!}

string function Show(string bodyText, string button1, string button2 = "", string button3 = "", string button4 = "", string button5 = "", string button6 = "", string button7 = "", string button8 = "", string button9 = "", string button10 = "", bool getIndex = false, float waitInterval = 0.1, float timeoutSeconds = 0.0) global
    int messageBoxId = Show_NonBlocking(bodyText, button1, button2, button3, button4, button5, button6, button7, button8, button9, button10)

    if ! messageBoxId
        Debug.MessageBox("Dynamic Message Box Not Found\n\n(Please install SkyrimScripting MessageBox SKSE plugin)")
    endIf

    ; Block and wait for the player to close the message
    bool waiting = true
    float startWaitTime = Utility.GetCurrentRealTime()
    while waiting && ! IsMessageResultAvailable(messageBoxId)
        float now = Utility.GetCurrentRealTime()
        float duration = now - startWaitTime
        if timeoutSeconds && duration >= timeoutSeconds
            Debug.Trace("[SkyMessage] Timed out " + bodyText + " [" + button1 + ", " + button2 + ", " + button3 + ", " + button4 + ", " + button5 + ", " + button6 + ", " + button7 + ", " + button8 + ", " + button9 + ", " + button10 + "]")
            waiting = false
        else
            Utility.WaitMenuMode(waitInterval)
        endIf
    endWhile

    if IsMessageResultAvailable(messageBoxId)
        if getIndex
            return GetResultIndex(messageBoxId)
        else
            return GetResultText(messageBoxId)
        endIf
    else
        return "TIMED_OUT"
    endIf
endFunction

string function ShowArray(string bodyText, string[] buttons, bool getIndex = false, float waitInterval = 0.1, float timeoutSeconds = 0.0) global
    int messageBoxId = ShowArray_NonBlocking(bodyText, buttons)
    
    if ! messageBoxId
        Debug.MessageBox("Dynamic Message Box Not Found\n\n(Please install SkyrimScripting MessageBox SKSE plugin)")
    endIf

    ; Block and wait for the player to close the message
    bool waiting = true
    float startWaitTime = Utility.GetCurrentRealTime()
    while waiting && ! IsMessageResultAvailable(messageBoxId)
        float now = Utility.GetCurrentRealTime()
        float duration = now - startWaitTime
        if timeoutSeconds && duration >= timeoutSeconds
            Debug.Trace("[SkyMessage] Timed out " + bodyText + " [" + buttons + "]")
            waiting = false
        else
            Utility.WaitMenuMode(waitInterval)
        endIf
    endWhile

    if IsMessageResultAvailable(messageBoxId)
        if getIndex
            return GetResultIndex(messageBoxId)
        else
            return GetResultText(messageBoxId)
        endIf
    else
        return "TIMED_OUT"
    endIf
endFunction

int function Show_NonBlocking(string bodyText, string button1, string button2 = "", string button3 = "", string button4 = "", string button5 = "", string button6 = "", string button7 = "", string button8 = "", string button9 = "", string button10 = "") global native

int function ShowArray_NonBlocking(string bodyText, string[] buttons) global native

string function GetResultText(int messageBoxId, bool deleteResultOnAccess = true) global native

int function GetResultIndex(int messageBoxId, bool deleteResultOnAccess = true) global native

function Delete(int messageBoxId) global native

bool function IsMessageResultAvailable(int messageBoxId) global native
