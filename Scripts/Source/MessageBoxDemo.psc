scriptName MessageBoxDemo extends Actor

event OnInit()
    string result = SkyMessage.Show("Hello from the messagebox!")
    Debug.Notification("RESULT: " + result)
endEvent
