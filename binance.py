import struct
from pprint import pprint
import requests

# public_key = "hbgU48ePFLdULct3waOlx3b0LDy4VZXz3lfu3PEaNnuEaH8Nc1nG9EhOTJ1pWoi9" # CryptoRoss
# private_key = "GgcnDXaQ9WgQCI5MBL77LxW2gid2iXNfQZ4sLY3ZQSIhNDdCuVJH09N9vi3tDToc" # CryptoRoss

api_url = "https://api.binance.com"

candlestick_route = "/api/v3/klines"


def get_last_price():
    querrystring = "?symbol=BTCUSDT&interval=1d&limit=1000"
    request_url = api_url + candlestick_route + querrystring
    response = s.get(request_url)
    hash_table = response.json()
    close_price = []
    for item in hash_table:
        close_price.append(float(item[4]))
    buf = struct.pack("%sf" % len(close_price), *close_price)
    print(close_price)
    file = open("BTCUSDT_1d_close.chart", "wb")
    file.write(buf)
    file.close()
    # for item in hash_table["symbols"]:
    #     # Check if pair is available for trading
    #     if "TRADING" in item["status"]:
    #         print("BINANCE:" + item["symbol"])


if __name__ == "__main__":
    s = requests.Session()
    get_last_price()
