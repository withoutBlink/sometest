import threading
import json
import websocket
import time

class WSClient(object):
    def __init__(self):
        self.listening = threading.Thread(target=self.on_respond)
        self.wbs = websocket.WebSocket()
        self.server_addr = 'ws://127.0.0.1:7064/tmix/items'
        self.rulesfile = '/home/ht706/casic-tmix/rules/rule_'

    def on_respond(self):
        while self.wbs.connected:
            print(self.wbs.recv())

    def start_connection(self):
        if not self.wbs.connected:
            self.wbs.connect(self.server_addr)
        self.listening.start()

    def stop_connection(self):
        self.wbs.close()
        time.sleep(1)

    def send_defaultmsg(self, rulenum):
        self.wbs.send(open(self.rulesfile + str(rulenum), 'r').read())
        time.sleep(1)


if __name__ == '__main__':
    wbsc = WSClient()
    wbsc.start_connection()
    wbsc.send_defaultmsg(rulenum=5)
    wbsc.stop_connection()
