import os, sys
import threading
import websocket
import time


class WSClient:
    def __init__(self):
        self.listening = threading.Thread(target=self.on_respond)
        self.wbs = websocket.WebSocket()
        self.server_addr = 'ws://127.0.0.1:7063/tmix/items'
        self.rulespath = '/home/ht706/casic-tmix/rules/'
        self.messages = {}

    def on_respond(self):
        while self.wbs.connected:
            print(self.wbs.recv())

    def start_connection(self):
        if not self.wbs.connected:
            self.wbs.connect(self.server_addr)
        self.listening.start() # add thread

    def stop_connection(self):
        self.wbs.close()
        time.sleep(1)

    def send_msg(self, rulename:str):
        self.loadtrac()
        self.wbs.send(self.messages[rulename])
        time.sleep(1)

    def get_msglist(self):
        msglist = ""
        for message in self.messages:
            msglist = msglist + message + ' '
        return msglist

    def loadtrac(self):
        os.system('ls '+ self.rulespath + '>' + self.rulespath +'rulefiles.txt')
        rulefilenames = open(self.rulespath+'rulefiles.txt','r').readlines()
        for rule in rulefilenames:
            filepath = self.rulespath + rule
            self.messages[rule.split('.')[1]] = open(filepath,'r').read()

class StupidC:
    def __init__(self):
        wbsc = WSClient()
        wbsc.start_connection()
        

if __name__ == '__main__':
    rulelist = sys.argv
    wbsc = WSClient()
    wbsc.start_connection()
    for rule in rulelist:
        wbsc.send_msg(rule)

