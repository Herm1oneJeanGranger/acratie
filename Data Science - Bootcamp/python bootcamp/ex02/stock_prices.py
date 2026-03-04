import sys

COMPANIES = {
  'Apple': 'AAPL',
  'Microsoft': 'MSFT',
  'Netflix': 'NFLX',
  'Tesla': 'TSLA',
  'Nokia': 'NOK'
}

STOCKS = {
  'AAPL': 287.73,
  'MSFT': 173.79,
  'NFLX': 416.90,
  'TSLA': 724.88,
  'NOK': 3.37
}

def main():
    if len(sys.argv) != 2:
        return

    input_name = sys.argv[1]

    if input_name in COMPANIES:
        stock_symbol = COMPANIES[input_name]
        stock_price = STOCKS[stock_symbol]
        print(stock_price)
    elif input_name in STOCKS:
        print(STOCKS[input_name])
    else:
        print("Unknown company")

if __name__ == "__main__":
    main()



        


