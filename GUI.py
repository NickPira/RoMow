import tkinter as tk
from tkinter import messagebox


def getDims():
    # insert a number into the entry box
    def insert_number(number):
        global current_entry
        if current_entry == 1:
            entry1.insert(tk.END, number)
        elif current_entry == 2:
            entry2.insert(tk.END, number)

    # set the current entry box as the active one
    def set_active_entry(entry_num):
        global current_entry
        current_entry = entry_num

    # save the input from both entry boxes
    def save_text():
        # Get the text from the entry boxes
        input_1 = float(entry1.get())
        input_2 = float(entry2.get())
    
        # Display a message box showing the saved inputs
        #messagebox.showinfo("Saved Texts", f"Length: {input_1}\nWidth: {input_2}")
    
        # Store them as global variables or use them as needed
        ##this##
        global saved_input_1, saved_input_2
        saved_input_1 = input_1
        saved_input_2 = input_2

    #clear text
    def clear_entry():
        entry1.delete(0, tk.END)
        entry2.delete(0, tk.END)

    

    # Create the main window
    root = tk.Tk()
    root.title("Area of the Lawn(m^2)")

    # Create entry boxes
    tk.Label(root, text="Length of the Lawn(m):").pack(pady=5)
    entry1 = tk.Entry(root, width=40)
    entry1.pack(pady=5)
    entry1.bind("<FocusIn>", lambda e: set_active_entry(1))

    tk.Label(root, text="Width of the Lawn(m):").pack(pady=5)
    entry2 = tk.Entry(root, width=40)
    entry2.pack(pady=5)
    entry2.bind("<FocusIn>", lambda e: set_active_entry(2))

    # Create a number pad
    number_frame = tk.Frame(root)
    number_frame.pack(pady=10)

    # Create buttons for numbers 0-9 and place them in a grid
    for i in range(1, 10):
        button = tk.Button(number_frame, text=str(i), width=5, height=2, command=lambda i=i: insert_number(str(i)))
        button.grid(row=(i-1)//3, column=(i-1)%3)

    # Button for 0
    button = tk.Button(number_frame, text="0", width=5, height=2, command=lambda: insert_number("0"))
    button.grid(row=3, column=1)

    # Button for .
    button = tk.Button(number_frame, text=".", width=5, height=2, command=lambda: insert_number("."))
    button.grid(row=3, column=2)

    # Create a button to save the text
    button = tk.Button(number_frame, text="Save",  width=5, height=2,command=save_text)
    button.grid(row=4, column=0)

    # Create a button to close the window
    button = tk.Button(number_frame, text = "close", width=5, height=2,command = root.destroy)
    button.grid(row=4, column=1)

    # Create a button to backspace
    button = tk.Button(number_frame, text="del",  width=5, height=2,command=clear_entry)
    button.grid(row=3, column=0)

    # Start the main event loop
    root.mainloop()

    # After the GUI is closed, you can use the saved inputs in your code
    return saved_input_1, saved_input_2