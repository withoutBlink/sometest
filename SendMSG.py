# This Python file uses the following encoding: utf-8

import websocket
import json
import time
import threading
import logging

def proto_encode():


def req_res(index):
    ws = websocket.WebSocket()
    ws.connect("ws://127.0.0.1:7064/tmix/items")
    ws.send("some method and content")
    respond = ws.recv()
    logging.info(respond)
    ws.close()
    print("client sent over",index)

if __name__ == "__main__":
    websocket.enableTrace(True)
    request = list()
    for clients in range(1):
        con = threading.Thread(target=req_res,args=(clients,))
        request.append(con)
        con.start()
