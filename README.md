# Text editor in ncurses, inspired by vim

This is small editor writen in c++ and ncurses library. For this moment it compile only for linux, but in future I will make version for windows.
Editor isn't complete, so it can have some bugs.

# Mode

Editor have three mode:

 - Write - in this mode you can write text.

 - Edit - in this mode you can paste, search etc.
 
 - Visual - in this mode you can selected text, copy or delete them.

# Key
  
  ## Edit mode 
  ```
  escape: quit editor.
  insert: mode change to write_mode. To change from write_mode to edit, also use insert_key
  w: mode change to visual_mode
  slash: you can search word in text.
  s: save file.
  p: paste text.
  ```
  
  ## Visual mode
  ```
  insert: mode change to edit_mode
  backspace: delete selected text
  c: copy text to buffer
  w, s, a, d: in this mode you can selected text by wsad keys.
  ```
  
# Plans for future
  - Make undo and redo
  - Interact with system_terminal
  - Syntax_highlighter
  - Disabled some key in modes
  - Mouse interaction
  - More operation on files
  - Better organise code
  
  
  
  
  
  
  
 

