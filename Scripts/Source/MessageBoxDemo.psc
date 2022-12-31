scriptName MessageBoxDemo extends Actor

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

