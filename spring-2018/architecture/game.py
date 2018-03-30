import requests
import json
import time


if __name__ == "__main__":
    x = 0
    while x < 1000:
        url = 'http://superstar.lawlorcode.com/superstar/2018/orak/v0/chars/steve?set='
        steve = '{"name":"steve","class":"Serf","alignment":"Lawful%20Neutral",' + \
            '"appearance":"blue","location":{"room":"Intro","x":' + \
                str(x)+',"y":'+str(x)+'}}'
        full = url + steve
        print(full)
        out = requests.get(full)
        x += 3
        print(out.text)
