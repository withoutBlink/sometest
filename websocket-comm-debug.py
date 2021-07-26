# This Python file uses the following encoding: utf-8

import websocket
import json
import time
import threading

def on_open(ws):
    print("connection opened")
    ws.send("Hello")

def on_error(ws, error):
    print("connection error")

def on_close(ws, close_status_code, close_msg):
    print("connection closed")
    ws.close

def on_message(ws, message):
    print(message)

if __name__ == "__main__":
    websocket.enableTrace(True)
    ws = websocket.WebSocketApp("ws://127.0.0.1:7064/tmix/items",
                                on_open=on_open,
                                on_message=on_message,
                                on_error=on_error,
                               on_close=on_close)

    client_thread = threading.Thread(target=ws.run_forever,args=())
    client_thread.start()

