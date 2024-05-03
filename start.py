import tkinter as tk

def go():
    # Function to handle the button click and print the value to the console
    def button_click(value):
   
        global entry
        entry = value
    

    # Create the main application window
    window = tk.Tk()
    window.title("Button Input Example")

    # Create Button 1 which inputs 0
    button1 = tk.Button(window, text="Yes", command=lambda: button_click(1))
    button1.pack(pady=10)

    # Create Button 2 which inputs 1
    button2 = tk.Button(window, text="No", command=lambda: button_click(0))
    button2.pack(pady=10)

    # Create a button to close the window
    button = tk.Button(window, text = "close", command = window.destroy)
    button.pack(pady=10)


    # Start the main event loop
    window.mainloop()
    print(entry)
    return entry
