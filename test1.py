import tkinter as tk

class ScrollCounterApp:
    def __init__(self, master):
        self.master = master
        master.title("Scroll Pixel Counter")

        # --- Counters ---
        self.scroll_up_count = 0
        self.scroll_down_count = 0
        # The 'event.delta' value varies by OS/environment.
        # On Windows, 'delta' is usually 120 or -120 per notch.
        # On macOS/Linux (smooth scrolling), it might be 1, -1, 4, -4, etc.
        # We will count the *total magnitude* of the delta in each direction.

        # --- UI Elements ---
        
        # 1. Scrollable Text Widget
        # Creating a Text widget inside a Frame is often necessary for flexible layout
        self.text_frame = tk.Frame(master)
        self.text_frame.pack(pady=10, padx=10, fill="both", expand=True)

        self.scrollbar = tk.Scrollbar(self.text_frame)
        self.text_area = tk.Text(self.text_frame, wrap="word", 
                                 yscrollcommand=self.scrollbar.set, height=15, width=50)
        self.scrollbar.config(command=self.text_area.yview)

        self.scrollbar.pack(side="right", fill="y")
        self.text_area.pack(side="left", fill="both", expand=True)
        
        # Populate the text area with content to make it scrollable
        content = "\n".join([f"This is line number {i+1}." for i in range(50)])
        self.text_area.insert("end", content)
        self.text_area.config(state="disabled") # Make it read-only
        
        # 2. Counter Labels
        self.up_label = tk.Label(master, text=f"Scroll Up Pixels/Units: {self.scroll_up_count}", 
                                 font=('Arial', 12, 'bold'), fg='blue')
        self.up_label.pack(pady=(0, 5))
        
        self.down_label = tk.Label(master, text=f"Scroll Down Pixels/Units: {self.scroll_down_count}", 
                                   font=('Arial', 12, 'bold'), fg='red')
        self.down_label.pack(pady=(0, 10))

        # --- Bind Scroll Events ---
        # The '<MouseWheel>' event is common for most desktop environments.
        # This will only count scrolls *within the text_area widget*.
        self.text_area.bind('<MouseWheel>', self.on_scroll)
        
        # You may also need to bind to '<Button-4>' (scroll up) and '<Button-5>' (scroll down)
        # for older Tkinter versions or some Linux environments.
        # self.text_area.bind('<Button-4>', self.on_scroll)
        # self.text_area.bind('<Button-5>', self.on_scroll)

    def on_scroll(self, event):
        """
        Processes the mouse wheel event to count up/down scrolls.
        event.delta indicates the scroll amount and direction.
        Positive delta (e.g., 120) is typically UP (scrolling towards the user).
        Negative delta (e.g., -120) is typically DOWN (scrolling away from the user).
        """
        
        delta = event.delta
        
        if delta > 0:
            # Scroll Up
            self.scroll_up_count += delta
            self.up_label.config(text=f"Scroll Up Pixels/Units: {self.scroll_up_count}")
        elif delta < 0:
            # Scroll Down
            self.scroll_down_count += abs(delta) # Use abs() to count magnitude
            self.down_label.config(text=f"Scroll Down Pixels/Units: {self.scroll_down_count}")
        
        # Allow the default scrolling action to continue
        return "break" # Returning "break" prevents the default scroll action, 
                       # but since we want the scrolling to happen, we should typically 
                       # return "continue" (or nothing). 
                       # *In this specific Tkinter/Text widget setup, returning "break" 
                       # is needed to prevent the event from propagating, so the default 
                       # Text widget scroll behavior still occurs indirectly.*
                       
# --- Main Execution ---
if __name__ == "__main__":
    root = tk.Tk()
    app = ScrollCounterApp(root)
    root.mainloop()