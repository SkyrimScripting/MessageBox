scriptName MessageBoxDemo extends Actor
{!BIND}

event OnInit()
    string result = SkyMessage.Show("MessageBox created by Papyrus!", "One", "Two", "Five", "Three sir!", "Three")
    Debug.MessageBox("Result button: " + result)

    string index = SkyMessage.Show("MessageBox created by Papyrus!", "One", "Two", "Five", "Three sir!", "Three", getIndex = true)
    Debug.MessageBox("Result button index: " + index)
endEvent

event OnItemAdded(Form baseForm, int count, ObjectReference obj, ObjectReference source)
    GoToState("AskingPlayerIfTheyWantMore")

    string result = SkyMessage.Show( \
        "Looks like you got " + baseForm.GetName() + ".\nWould you like some more?", \
        "No, thanks", "Yes, please!", "Two more", "5 more!", "TEN MORE!!" \
    )

    if result == "Yes, please!"
        AddItem(baseForm, 1)
    elseIf result == "Two more"
        AddItem(baseForm, 2)
    elseIf result == "5 more!"
        AddItem(baseForm, 5)
    elseIf result == "TEN MORE!!"
        AddItem(baseForm, 10)
    endIf

    GoToState("")
endEvent

state AskingPlayerIfTheyWantMore
    event OnItemAdded(Form baseForm, int count, ObjectReference obj, ObjectReference source)
    endEvent
endState

