from auction_jiang import Auction, User
from bidder_jiang import Bidder

if __name__ == "__main__":
    
    # constants setup
    num_rounds = 10 # must be >= 1
    num_users = 7 # must be >= 1
    num_bidders = 5 # must be >= 2

    # Generates lists of bidders, users, then constructs the Auction with them
    bidders = [Bidder(num_users, num_rounds) for _ in range(num_bidders)]
    users = [User() for _ in range(num_users)]
    auction = Auction(users, bidders)

    # Runs each auction round
    for round_number in range(num_rounds):
        print(f'{round_number=}')
        auction.execute_round()
