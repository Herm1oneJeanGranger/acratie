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

    input_name = sys.argv[1].upper()

    company_name = next((name for name, symbol in COMPANIES.items() if symbol == input_name), None)


    if company_name:
        stock_price = STOCKS[input_name]
        print(f"{company_name} {stock_price}")
    else:
        print("Unknown ticker")

if __name__ == "__main__":
    main()