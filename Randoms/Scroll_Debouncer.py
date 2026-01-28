import time
import traceback
import threading
import sys
from ctypes import wintypes
import ctypes
try:
    # Keep pynput as a fallback for non-Windows platforms
    from pynput import mouse
except Exception:
    mouse = None
import pydirectinput # Used to simulate the clean scroll output
import ctypes

# --- Configuration ---
# The window of time (in seconds) over which to accumulate scroll events.
# A small value (e.g., 0.05s) works well for debouncing.
DEBOUNCE_WINDOW_TIME = 0.05 

# The number of scroll clicks (or units) to send as the corrected output.
# Standard mouse wheel registers about 1 click per notch.
SCROLL_CLICKS_TO_SEND = 1 

# Whether to suppress the original OS scroll events. Set to True to suppress
# (requires appropriate permissions); otherwise leave False so events are not
# blocked at the OS level.
# WARNING: Setting this to True attempts to suppress the original OS scroll
# events so only this program's cleaned scroll events are delivered to other
# applications. On Windows this may require running the script with
# administrator privileges. If you see no effect, try running the Python
# process as administrator and ensure no other global hooks interfere.
SUPPRESS_EVENTS = True

# --- Global State ---
scroll_counts = {'up': 0, 'down': 0}
last_scroll_time = 0
debounce_timer = None
lock = threading.Lock() # To safely update shared variables

def on_scroll(x, y, dx, dy):
    """
    Called every time a scroll event is detected by pynput.
    This function collects the noisy scroll events into our counter.
    """
    global last_scroll_time, debounce_timer

    with lock:
        # 1. Update the counts based on the scroll direction
        if dy > 0:
            scroll_counts['up'] += abs(dy)
        elif dy < 0:
            scroll_counts['down'] += abs(dy)
        
        # 2. Reset or start the debouncing timer
        current_time = time.time()
        
        # If the last event was too long ago, or no timer is running, start a new timer.
        if current_time - last_scroll_time > DEBOUNCE_WINDOW_TIME or debounce_timer is None or not debounce_timer.is_alive():
            
            # Cancel any potentially running timer (shouldn't happen often)
            if debounce_timer is not None and debounce_timer.is_alive():
                 debounce_timer.cancel()
            
            # Start the new debouncer thread
            debounce_timer = threading.Timer(DEBOUNCE_WINDOW_TIME, process_scroll_counts)
            debounce_timer.start()

        last_scroll_time = current_time

    # NOTE: Do NOT return False here — returning False will stop the listener.
    # If you want to suppress the OS event, set `SUPPRESS_EVENTS=True` and
    # pass `suppress=SUPPRESS_EVENTS` to the Listener in `start_listener()`.
    return None

def process_scroll_counts():
    """
    This function runs after the DEBOUNCE_WINDOW_TIME has passed.
    It determines the intended direction and sends a clean signal.
    """
    global scroll_counts

    with lock:
        up_count = scroll_counts['up']
        down_count = scroll_counts['down']

        # Reset counters for the next window
        scroll_counts['up'] = 0
        scroll_counts['down'] = 0

    # Compute net clicks: positive => up, negative => down. Send exactly the
    # intended net amount so the OS receives only our cleaned events and
    # scrolling stops as soon as we stop sending events.
    try:
        net = int(up_count) - int(down_count)
        if net > 0:
            print(f"CLEAN Scroll UP: Up={up_count}, Down={down_count}, Net={net}")
            try:
                send_scroll(net * SCROLL_CLICKS_TO_SEND)
            except Exception as e:
                print(f"Failed to send scroll up: {e}")

        elif net < 0:
            print(f"CLEAN Scroll DOWN: Up={up_count}, Down={down_count}, Net={net}")
            try:
                send_scroll(net * SCROLL_CLICKS_TO_SEND)
            except Exception as e:
                print(f"Failed to send scroll down: {e}")

        else:
            # Net zero => noise only. Do nothing; since we suppress original
            # events, no scroll will be delivered to the OS.
            pass
    except Exception as e:
        print(f"Unexpected error in process_scroll_counts: {e}")


def send_scroll(clicks: int):
    """
    Send a vertical scroll input. This tries several fallbacks because
    `pydirectinput` doesn't always expose a `scroll` function on all
    installations. Order:
      1. Use `pydirectinput.scroll` if present.
      2. Use `pyautogui.scroll` if available.
      3. Fallback to Windows `mouse_event` via `ctypes`.

    `clicks` is positive for scroll up, negative for scroll down.
    """
    if clicks == 0:
        return

    # 1) pydirectinput
    if hasattr(pydirectinput, 'scroll') and callable(getattr(pydirectinput, 'scroll')):
        pydirectinput.scroll(clicks)
        return

    # 2) pyautogui
    try:
        import pyautogui
        if hasattr(pyautogui, 'scroll') and callable(getattr(pyautogui, 'scroll')):
            pyautogui.scroll(clicks)
            return
    except Exception:
        # pyautogui not installed or failed — fall through
        pass

    # 3) Windows fallback using mouse_event (120 units per notch)
    try:
        WHEEL_DELTA = 120
        ctypes.windll.user32.mouse_event(0x0800, 0, 0, int(WHEEL_DELTA * clicks), 0)
        return
    except Exception as e:
        raise RuntimeError(f"No scroll method available and Windows fallback failed: {e}")

def start_listener():
    print("Mouse scroll debouncer is active. Press Ctrl+C to stop.")
    # On Windows, if SUPPRESS_EVENTS is enabled, install a low-level mouse
    # hook that suppresses only wheel events. This preserves normal mouse
    # movement and click events while blocking raw wheel messages.
    if sys.platform == 'win32' and SUPPRESS_EVENTS:
        try:
            install_windows_wheel_hook()
        except Exception as e:
            tb = traceback.format_exc()
            print(f"Failed to install Windows wheel hook: {e}\n{tb}")
            # Fall back to non-suppressing listener if possible
            if mouse is not None:
                with mouse.Listener(on_scroll=on_scroll, suppress=False) as listener:
                    try:
                        listener.join()
                    except KeyboardInterrupt:
                        print("\nDebouncer stopped.")
                return
            else:
                print("No fallback listener available; exiting.")
                return

        try:
            run_message_loop()
        except KeyboardInterrupt:
            print("\nDebouncer stopped.")
        except Exception as e:
            tb = traceback.format_exc()
            print(f"Error in message loop: {e}\n{tb}")
        finally:
            try:
                uninstall_windows_wheel_hook()
            except Exception:
                pass
    else:
        # Non-Windows or suppression disabled: use pynput listener (no global suppression)
        if mouse is None:
            print("pynput not available; cannot listen for mouse events on this platform.")
            return
        with mouse.Listener(on_scroll=on_scroll, suppress=False) as listener:
            try:
                listener.join()
            except KeyboardInterrupt:
                print("\nDebouncer stopped.")


def _log_exception_to_file(exc: Exception, context: str = ""):
    try:
        with open('scroll_debouncer.log', 'a', encoding='utf-8') as f:
            f.write(f"[{time.strftime('%Y-%m-%d %H:%M:%S')}] {context}: {exc}\n")
            f.write(traceback.format_exc())
            f.write('\n')
    except Exception:
        pass


# ---------------- Windows low-level hook implementation ------------------
if sys.platform == 'win32':
    user32 = ctypes.windll.user32
    kernel32 = ctypes.windll.kernel32

    WH_MOUSE_LL = 14
    WM_MOUSEWHEEL = 0x020A
    WM_MOUSEHWHEEL = 0x020E

    class POINT(ctypes.Structure):
        _fields_ = [('x', wintypes.LONG), ('y', wintypes.LONG)]

    class MSLLHOOKSTRUCT(ctypes.Structure):
        _fields_ = [
            ('pt', POINT),
            ('mouseData', wintypes.DWORD),
            ('flags', wintypes.DWORD),
            ('time', wintypes.DWORD),
            ('dwExtraInfo', ctypes.c_void_p),
        ]

    # Some Python versions / platforms don't define `wintypes.LRESULT`.
    # Provide a sensible fallback based on pointer size (LONG on 32-bit,
    # LONG LONG on 64-bit) so the callback signature is correct.
    try:
        LRESULT = wintypes.LRESULT
    except AttributeError:
        if ctypes.sizeof(ctypes.c_void_p) == ctypes.sizeof(ctypes.c_long):
            LRESULT = ctypes.c_long
        else:
            LRESULT = ctypes.c_longlong

    LowLevelMouseProc = ctypes.WINFUNCTYPE(LRESULT, ctypes.c_int, wintypes.WPARAM, wintypes.LPARAM)

    _mouse_hook_ptr = None
    _mouse_hook_handle = None

    def _wheel_notch_from_data(mouseData: int) -> int:
        # High-order word contains wheel delta; each notch is 120
        delta = ctypes.c_short((mouseData >> 16) & 0xffff).value
        return int(delta / 120)

    def _low_level_mouse_proc(nCode, wParam, lParam):
        # nCode == 0 indicates we should process the message
        if nCode == 0 and (wParam == WM_MOUSEWHEEL or wParam == WM_MOUSEHWHEEL):
            try:
                ms = ctypes.cast(lParam, ctypes.POINTER(MSLLHOOKSTRUCT)).contents
                notches = _wheel_notch_from_data(ms.mouseData)
                if notches != 0:
                    # Update counters and (re)start debounce timer
                    global last_scroll_time, debounce_timer
                    with lock:
                        if notches > 0:
                            scroll_counts['up'] += abs(notches)
                        else:
                            scroll_counts['down'] += abs(notches)

                        current_time = time.time()
                        if current_time - last_scroll_time > DEBOUNCE_WINDOW_TIME or debounce_timer is None or not debounce_timer.is_alive():
                            if debounce_timer is not None and debounce_timer.is_alive():
                                debounce_timer.cancel()
                            debounce_timer = threading.Timer(DEBOUNCE_WINDOW_TIME, process_scroll_counts)
                            debounce_timer.start()
                        last_scroll_time = current_time
                    # Return a non-zero value to suppress this wheel event only
                    return 1
            except Exception as e:
                print(f"Error in low-level mouse proc: {e}")

        # For all other events, pass them to next hook
        return user32.CallNextHookEx(_mouse_hook_handle, nCode, wParam, lParam)

    # Convert Python function to C callback and keep a reference to avoid GC
    _low_level_mouse_proc_ptr = LowLevelMouseProc(_low_level_mouse_proc)

    def install_windows_wheel_hook():
        global _mouse_hook_handle, _low_level_mouse_proc_ptr
        if _mouse_hook_handle is not None:
            return
        _mouse_hook_handle = user32.SetWindowsHookExW(WH_MOUSE_LL, _low_level_mouse_proc_ptr, kernel32.GetModuleHandleW(None), 0)
        if not _mouse_hook_handle:
            raise RuntimeError("Failed to install low-level mouse hook. Try running as Administrator.")

    def uninstall_windows_wheel_hook():
        global _mouse_hook_handle
        if _mouse_hook_handle:
            user32.UnhookWindowsHookEx(_mouse_hook_handle)
            _mouse_hook_handle = None

    def run_message_loop():
        msg = wintypes.MSG()
        while True:
            b = user32.GetMessageW(ctypes.byref(msg), None, 0, 0)
            if b == 0:
                break
            elif b == -1:
                break
            else:
                user32.TranslateMessage(ctypes.byref(msg))
                user32.DispatchMessageW(ctypes.byref(msg))

if __name__ == '__main__':
    start_listener()