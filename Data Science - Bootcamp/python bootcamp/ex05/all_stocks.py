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

def process_input(input_string):

  expressions = [expr.strip() for expr in input_string.split(',')]
  results = []

  for expr in expressions:
    expr_upper = expr.upper()

    if expr_upper in STOCKS:
        company_name = [name for name, ticker in COMPANIES.items() if ticker == expr_upper][0]
        results.append(f"{expr_upper} is a ticker symbol for {company_name}")
    elif expr.title() in COMPANIES:
          ticker = COMPANIES[expr.title()]
          results.append(f"{expr.title()} stock price is {STOCKS[ticker]}")
    else:
          results.append(f"{expr} is an unknown company or an unknown ticker symbol")
    
    print('\n'.join(results))

if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit()
    
    input_string = sys.argv[1]
    process_input(input_string)

