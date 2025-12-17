import os
import tkinter as tk
from tkinter import filedialog, messagebox, scrolledtext

# Configuration: Add other file extensions here if needed
TARGET_EXTENSIONS = {'.txt', '.cpp', '.py', '.h', '.hpp', '.c', '.md'}

def get_file_content(filepath):
    """Reads a file and returns its content. Handles encoding errors."""
    try:
        with open(filepath, 'r', encoding='utf-8', errors='replace') as f:
            return f.read()
    except Exception as e:
        return f"Error reading file: {e}"

def generate_llm_prompt(base_folder):
    """Walks through folder and generates formatted string including the root folder name."""
    output_lines = []
    
    # Get the name of the folder selected (e.g., "MyProject")
    root_folder_name = os.path.basename(base_folder)
    
    # Walk through the directory
    for root, dirs, files in os.walk(base_folder):
        for file in files:
            # Check file extension
            _, ext = os.path.splitext(file)
            if ext.lower() in TARGET_EXTENSIONS:
                full_path = os.path.join(root, file)
                
                # Get path relative to the selected folder (e.g., "src/main.cpp")
                rel_path = os.path.relpath(full_path, base_folder)
                
                # Combine root folder name with relative path (e.g., "MyProject/src/main.cpp")
                # We also replace backslashes with forward slashes for cleaner LLM formatting
                display_path = os.path.join(root_folder_name, rel_path).replace("\\", "/")
                
                content = get_file_content(full_path)
                
                # Format: 
                # -> FolderName/Path/file.ext
                # ```
                # code
                # ```
                output_lines.append(f"-> {display_path}")
                output_lines.append("```")
                output_lines.append(content)
                output_lines.append("```")
                output_lines.append("") # Empty line for separation

    return "\n".join(output_lines)

def select_folder():
    folder_selected = filedialog.askdirectory()
    if folder_selected:
        try:
            # Update status
            status_label.config(text="Processing files...")
            root.update()
            
            # Generate content
            formatted_text = generate_llm_prompt(folder_selected)
            
            # Display in text area
            text_area.delete(1.0, tk.END)
            text_area.insert(tk.END, formatted_text)
            
            status_label.config(text=f"Loaded files from: {os.path.basename(folder_selected)}")
        except Exception as e:
            messagebox.showerror("Error", str(e))
            status_label.config(text="Error occurred.")

def copy_to_clipboard():
    content = text_area.get(1.0, tk.END)
    root.clipboard_clear()
    root.clipboard_append(content)
    root.update() # Keep the clipboard content after window closes
    messagebox.showinfo("Success", "Content copied to clipboard!")

# --- GUI Setup ---
root = tk.Tk()
root.title("Folder to LLM Context")
root.geometry("700x600")

# Top Frame for Buttons
frame_top = tk.Frame(root)
frame_top.pack(pady=10)

btn_select = tk.Button(frame_top, text="Select Folder", command=select_folder, width=15)
btn_select.pack(side=tk.LEFT, padx=5)

btn_copy = tk.Button(frame_top, text="Copy to Clipboard", command=copy_to_clipboard, width=15, bg="#dddddd")
btn_copy.pack(side=tk.LEFT, padx=5)

# Status Label
status_label = tk.Label(root, text="Select a folder to begin", fg="gray")
status_label.pack()

# Text Area
text_area = scrolledtext.ScrolledText(root, wrap=tk.WORD, font=("Consolas", 10))
text_area.pack(expand=True, fill='both', padx=10, pady=10)

# Run
root.mainloop()